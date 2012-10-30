//#############################################################################
//
//    FILENAME:   Nitf21Isd.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the NITF 2.1 ISD class derived from the csm_ISD base class.
//    ISD is encapsulated in a C++ class for transfer through the CSM
//    interface. ISD is passed as a pointer to a simple ISD base class
//    (for example, csm_ISD *isd).
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     01-Jul-2003   LMT      Initial version.
//     06-Feb-2004   KRW      Incorporates changes approved by
//                             January and February 2004
//                             Configuration control board.
//     01-Nov-2004   KRW      October 2004 CCB
//     08-Jan-2005   KRW      Multi Image/Frame ? Administrative changes
//     02-Mar-2012   SCM      Refactored interfaces.
//     30-Oct-2012   SCM      Renamed to Nitf21Isd.h.  And deleted.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_NITF21ISD_H
#define __CSM_NITF21ISD_H

#include "NitfIsd.h"

namespace csm
{

class CSM_EXPORT_API Nitf21Isd : public NitfIsd
{
public:
   Nitf21Isd() : NitfIsd("NITF2.1") {}
   virtual ~Nitf21Isd() {}
};

} // namespace csm

#endif

