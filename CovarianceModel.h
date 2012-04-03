//##################################################################
//
//    FILENAME:   CSMCovarianceModel.h
//
//    CLASSIFICATION:    UNCLASSIFIED
//
//    DESCRIPTION:
//
//    Header for the covariance model used by the CSM.
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     29-Mar-2012   SCM      Refactored interface.
//
//    NOTES:
//
//#####################################################################

#ifndef __CSMCOVARIANCE_MODEL_H
#define __CSMCOVARIANCE_MODEL_H

#include <string>
#include "CSMMisc.h"

namespace csm
{

class CSM_EXPORT_API CovarianceModel
{
public:
   CovarianceModel() : theFormat("UNKNOWN") {}
   virtual ~CovarianceModel() {}

   const std::string& format() const { return theFormat; }

protected:
   std::string theFormat;
};

} // namespace csm

#endif
