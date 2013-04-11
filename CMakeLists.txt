project(PDFHUMMUS)
cmake_minimum_required (VERSION 2.6)

if(NOT PDFHUMMUS_NO_DCT)
	ADD_SUBDIRECTORY(LibJpeg)
endif(NOT PDFHUMMUS_NO_DCT)
	ADD_SUBDIRECTORY(ZLib)
if(NOT PDFHUMMUS_NO_TIFF)
	ADD_SUBDIRECTORY(LibTiff)
endif(NOT PDFHUMMUS_NO_TIFF)
ADD_SUBDIRECTORY(FreeType)
ADD_SUBDIRECTORY(PDFWriter)
ADD_SUBDIRECTORY(PDFWriterTestPlayground)