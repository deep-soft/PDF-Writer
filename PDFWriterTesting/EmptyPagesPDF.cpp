/*
   Source File : EmptyPagesPDF.cpp


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
#include "PDFWriter.h"
#include "PDFPage.h"
#include "PDFRectangle.h"

#include "testing/TestIO.h"

#include <iostream>

using namespace std;
using namespace PDFHummus;

int EmptyPagesPDF(int argc, char* argv[])
{
	PDFWriter pdfWriter;
	LogConfiguration logConfiguration(true,true,BuildRelativeOutputPath(argv, "EmptyPagesLog.txt"));
	EStatusCode status; 

	do
	{
		status = pdfWriter.StartPDF(BuildRelativeOutputPath(argv, "EmptyPages.pdf"),ePDFVersion13,logConfiguration);
		if(status != PDFHummus::eSuccess)
		{
			cout<<"failed to start PDF\n";
			break;
		}	


		PDFPage* page = new PDFPage();
		page->SetMediaBox(PDFRectangle(0,0,595,842));

		for(int i=0;i<4 && PDFHummus::eSuccess == status;++i)
		{
			status = pdfWriter.WritePage(page);
			if(status != PDFHummus::eSuccess)
				cout<<"failed to write page "<<i<<"\n";
		}
		delete page;		

		status = pdfWriter.EndPDF();
		if(status != PDFHummus::eSuccess)
		{
			cout<<"failed in end PDF\n";
			break;
		}
	}while(false);
	return status == eSuccess ? 0:1;
}
