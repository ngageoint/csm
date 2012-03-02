//#############################################################################
//
//    FILENAME:   CSMParameterSharing.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the constants and other definitions used by the CSM Parameter
//    Sharing function.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     16 Sep 2010   Gene Rose  Initial version.
//     02-Mar-2012   SCM      Refactored interfaces.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSMPARAMETERSHARING_H
#define __CSMPARAMETERSHARING_H

#include "TSMMisc.h"

namespace csm {

enum SharingType
//>
{
   NOT_INITIALIZED = 0,
   SHARE_BY_MODEL_NAME = 1,
   SHARE_BY_SENSOR_ID = 2,
   SHARE_BY_PLATFORM_ID = 3,
   SHARE_BY_COLLECTION_ID = 4,
   SHARE_BY_TRAJECTORY_ID = 5,
   SHARE_BY_DATE_TIME_MATCH = 6
};
//<

// sharing criteria class is not virtual
class CSM_EXPORT_API ParameterSharingCriteria
{
public:
   // constructors
   ParameterSharingCriteria() : theType(NOT_INITIALIZED), theTimeLimit(0.0) {}
   explicit ParameterSharingCriteria(SharingType t)
      : theType(t), theTimeLimit(0.0) {}
   explicit ParameterSharingCriteria(double tl)
      : theType(SHARE_BY_DATE_TIME_MATCH), theTimeLimit(tl) {}

   // data access
   SharingType type() const { return theType; };
   double timeLimit() const {return theTimeLimit;};

private:
   SharingType theType;
   double theTimeLimit;
};

} // namespace csm

#endif // __CSMPARAMETER_SHARING_H

