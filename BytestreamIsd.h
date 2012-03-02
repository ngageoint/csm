//#############################################################################
//
//    FILENAME:   CSMISDByteStream.h
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
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     01-Jul-2003   LMT      Initial version.
//     06-Feb-2004   KRW      Incorporates changes approved by
//                            January and February 2004
//                            Configuration control board.
//     02-Mar-2012   SCM      Refactored interfaces.
//
//    NOTES:
//
//#############################################################################

#ifndef __csm_ISDBYTESTREAM_H
#define __csm_ISDBYTESTREAM_H

#include "CSMImageSupportData.h"
#include "CSMMisc.h"
#include <string>

namespace csm {

class CSM_EXPORT_API BytestreamIsd : public Isd
{
public:
   explicit BytestreamIsd(const string& data)
      : isd("BYTESTREAM"), theData(data) {}
   virtual ~BytestreamIsd() {}

   std::string theData;
};

} // namespace csm

#endif

