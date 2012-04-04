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
//    format. The field "data" is set with the ISD.  The field "filename" may
//    be set with the source filename.
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

namespace csm
{

class CSM_EXPORT_API BytestreamIsd : public Isd
{
public:
   explicit BytestreamIsd(const std::string& data,
                          const std::string& filename = "")
      : Isd("BYTESTREAM", filename), theData(data) {}
   virtual ~BytestreamIsd() {}

   const std::string data() const { return theData; }
      //> This method returns the raw bytestream data associated with the image
      //  support data.  This should not be empty.
      //<
   void setData(const std::string& data) { theData = data; }
      //> This method returns the raw bytestream data associated with the image
      //  support data.  This should not be empty.
      //<

private:
   std::string theData;
      //> This data member is the ISD data to be used in construting the CSM
      //  model.  It must be supplied.
      //<
};

} // namespace csm

#endif

