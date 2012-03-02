//#############################################################################
//
//    FILENAME:   CSMISDFilename.h
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
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     01-Jul-2003   LMT      Initial version.
//     06-Feb-2004   KRW      Incorporates changes approved by
//                            January and February 2004
//                            Configuration control board.
//     12-Mar-2012   SCM      Refactored interfaces.
//
//    NOTES:
//
//#############################################################################

#ifndef __csm_ISDFILENAME_H
#define __csm_ISDFILENAME_H

#include "CSMImageSupportData.h"
#include "CSMMisc.h"

#include <string>

namespace csm {

class CSM_EXPORT_API FilenameIsd : public Isd
{
public:
   explicit FilenameIsd(const std::string& fn = "")
      : isd("FILENAME"), theFilename(fn) {}
   virtual ~FilenameIsd() {}

   std::string theFilename;
};

} // namespace csm

#endif

