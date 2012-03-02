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
//                       Date          Author        Comment
//    SOFTWARE HISTORY: 16 Sep 2010    Gene Rose     Initial version.
//
//    NOTES:
//
//#############################################################################
#ifndef __CSMPARAMETERSHARING_H
#define __CSMPARAMETERSHARING_H
namespace CSM_SHARING {
static const int NOT_INITIALIZED = 0;
static const int SHARE_BY_MODEL_NAME = 1;
static const int SHARE_BY_SENSOR_ID = 2;
static const int SHARE_BY_PLATFORM_ID = 3;
static const int SHARE_BY_COLLECTION_ID = 4;
static const int SHARE_BY_TRAJECTORY_ID = 5;
static const int SHARE_BY_DATE_TIME_MATCH = 6;
// sharing criteria class is not virtual
class CSM_EXPORT_API csm_ParameterSharingCriteria
{
public:
   // data access
   int Type() const {return m_type;};
   double Time() const {return m_time_limit;};
   // constructors
   csm_ParameterSharingCriteria(int t): m_type(t)
   {
      m_time_limit = 0.0;
   }
   csm_ParameterSharingCriteria(double tl)
   {
      m_type = CSM_SHARING::SHARE_BY_DATE_TIME_MATCH;
      m_time_limit = tl;
   }
   csm_ParameterSharingCriteria()
   {
      m_type = CSM_SHARING::NOT_INITIALIZED;
      m_time_limit = 0.0;
   }
protected:
   int m_type;
   double m_time_limit;
};
};      // namespace CSM_SHARING
#endif // __CSMPARAMETER_SHARING_H

