/*
   Source File : OpenTypeTest.cpp


   Copyright 2011 Gal Kahana PDFWriter

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   
*/
#include "OpenTypeFileInput.h"
#include "InputFile.h"

#include "BoxingBase.h"
#include "OutputFile.h"
#include "CharStringType2Tracer.h"
#include "IByteWriterWithPosition.h"

#include <iostream>

#include "testing/TestIO.h"

using namespace PDFHummus;

static EStatusCode SaveCharstringCode(char* argv[],unsigned short inFontIndex,unsigned short inGlyphIndex,CFFFileInput* inCFFFileInput)
{
	OutputFile glyphFile;

	EStatusCode status = glyphFile.OpenFile(
        BuildRelativeOutputPath(argv,
            string("glyphCFF")  + Long(inFontIndex).ToString() + "_" + inCFFFileInput->GetGlyphName(0,inGlyphIndex) + ".txt"));

	do
	{
		if(status != PDFHummus::eSuccess)
			break;
		
		CharStringType2Tracer tracer;

		status = tracer.TraceGlyphProgram(inFontIndex,inGlyphIndex,inCFFFileInput,glyphFile.GetOutputStream());

	}while(false);

	glyphFile.CloseFile();

	return status;
}

static EStatusCode TestFont(char* argv[])
{
	EStatusCode status;
	InputFile otfFile;

	do
	{
		status = otfFile.OpenFile(BuildRelativeInputPath(argv,"fonts/BrushScriptStd.otf"));

		if(status != PDFHummus::eSuccess)
		{
			cout<<"cannot read bursh script font file\n";
			break;
		}


		OpenTypeFileInput openTypeReader;

		status = openTypeReader.ReadOpenTypeFile(otfFile.GetInputStream(),0);
		if(status != PDFHummus::eSuccess)
		{
			cout<<"could not read open type file\n";
			break;
		}

		// show just abcd and notdef

		status = SaveCharstringCode(argv,0,0,&openTypeReader.mCFF);
		for(unsigned short i=66; i < 70 && PDFHummus::eSuccess == status; ++i)
			status = SaveCharstringCode(argv,0,i,&openTypeReader.mCFF);
	}while(false);
	return status;
}


int OpenTypeTest(int argc, char* argv[])
{
	return TestFont(argv) == eSuccess ? 0:1;
}
