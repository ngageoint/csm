//#############################################################################
//
//    FILENAME:   csm_ISDByteStream.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the ByteStream ISD class derived from the csm_ISD base class.
//    ISD is encapsulated in a C++ class for transfer through the CSM
//    interface. This class is designed to hold ISD in a std::string of unspecified
//    format. The field _isd is set with the ISD.
//
//    LIMITATIONS:       None
//
//                       Date          Author   Comment
//    SOFTWARE HISTORY: 01-Jul-2003    LMT      Initial version.
//                       06-Feb-2004   KRW      Incorporates changes approved by
//                                                January and February 2004
//                                               Configuration control board.
//    NOTES:
//
//#############################################################################
#ifndef __csm_ISDBYTESTREAM_H
#define __csm_ISDBYTESTREAM_H
#include "CSMImageSupportData.h"
#include <string>
#include "CSMMisc.h"
#ifdef _WIN32
#pragma warning( disable : 4291 )
#pragma warning( disable : 4251 )
#endif
class CSM_EXPORT_API bytestreamISD : public csm_ISD
{
public:
   bytestreamISD() { _format = "BYTESTREAM"; }
   bytestreamISD(std::string filename);
   ~bytestreamISD() {_format.erase(); _isd.erase();}
   std::string _isd;
};
#endif

