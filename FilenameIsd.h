//#############################################################################
//
//    FILENAME:   csm_ISDFilename.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the Filename ISD class derived from the csm_ISD base class.
//    ISD is encapsulated in a C++ class for transfer through the CSM
//    interface. This class is designed allow a std::string indicating the name
//    of a file that contains ISD. The field _filename should be set to the
//    full path name of the file.
//
//    LIMITATIONS:       None
//
//                       Date          Author   Comment
//    SOFTWARE HISTORY: 01-Jul-2003    LMT      Initial version.
//                       06-Feb-2004   KRW      Incorporates changes approved by
//                                                January and February 2004
//                                                Configuration control board.
//    NOTES:
//
//#############################################################################
#ifndef __csm_ISDFILENAME_H
#define __csm_ISDFILENAME_H
#include "CSMImageSupportData.h"
#include <string>
#include "CSMMisc.h"
#ifdef _WIN32
#pragma warning( disable : 4291 )
#pragma warning( disable : 4251 )
#endif
class CSM_EXPORT_API filenameISD : public csm_ISD
{
public:
   filenameISD() { _format = "FILENAME"; }
   ~filenameISD() { }
   std::string _filename;
};
#endif

