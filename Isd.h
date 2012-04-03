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
   Isd() : theFormat("UNKNOWN") {}
   virtual ~Isd() {}

   const std::string& format() const { return theFormat; }

protected:
   explicit Isd(const std::string& format) : theFormat(format) {}

   std::string theFormat;
};

} // namespace csm

#endif

