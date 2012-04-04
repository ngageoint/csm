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
//    simple ISD base class (for example, csm::Isd *isd).
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     01-Jul-2003   LMT      Initial version.
//     06-Feb-2004   KRW      Incorporates changes approved by 
//                            January and February 2004 CCB.
//     02-Mar-2012   SCM      Refactored interfaces.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSMIMAGESUPORTDATA_H
#define __CSMIMAGESUPORTDATA_H

#include <string>

#include "CSMMisc.h"

namespace csm
{

class CSM_EXPORT_API Isd
{
public:
   Isd() : theFormat("UNKNOWN"), theFilename() {}
      //> This constructor makes an "unknown" image support data object.  No
      //  informatino about the image will be available in this mode.
      //<

   explicit Isd(const std::string& filename)
      : theFormat("FILENAME"), theFilename(filename) {}
      //> This constructor makes a "filename" image support data object.  The
      //  only data available in this mode is the name of the file.
      //<

   virtual ~Isd() {}

   const std::string& format() const { return theFormat; }
      //> This method returns the format of the image support data.  Each
      //  class derived from csm::Isd has a different format string.
      //<

   const std::string filename() const { return theFilename; }
      //> This method returns the filename associated with the image support
      //  data, if any.  If there is no filename, then this string will be
      //  empty.
      //<
   void setFilename(const std::string& fn) { theFilename = fn; }
      //> This method sets the filename associated with the image support
      //  data.  If there is no associated filename, then an empty string
      //  should be used.
      //<

protected:
   explicit Isd(const std::string& format, const std::string& filename)
      : theFormat(format), theFilename(filename) {}

   std::string theFormat;
   std::string theFilename;
};

} // namespace csm

#endif

