//#############################################################################
//
//    FILENAME:   CSMImageSupportData.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the ISD base class. ISD is encapsulated in a C++ class for
//    transfer through the CSM interface. ISD is passed as a pointer to a
//    simple ISD base class (for example, csm_ISD *isd). i
//
//    LIMITATIONS:       None
//
//                       Date          Author   Comment
//    SOFTWARE HISTORY: 01-Jul-2003    LMT      Initial version.
//                       06-Feb-2004   KRW      Incorporates changes approved by
//                                               January and February 2004
//                                               Configuration control board.
//
//    NOTES:
//
//#############################################################################
#ifndef __CSMIMAGESUPORTDATA_H
#define __CSMIMAGESUPORTDATA_H
#include <string>
#include "CSMMisc.h"
#ifdef _WIN32
#pragma warning( disable : 4291 )
#pragma warning( disable : 4251 )
#endif
class CSM_EXPORT_API csm_ISD
{
public:
   csm_ISD() { _format = "UNKNOWN"; }
   virtual   ~csm_ISD(){ _format.erase(); }
   void getFormat( std::string &format ) const { format = _format; }
protected:
   std::string _format;
};
#endif

