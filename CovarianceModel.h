//##################################################################
//
//    FILENAME:   TSMCovarianceModel.h
//
//    CLASSIFICATION:    UNCLASSIFIED
//
//    DESCRIPTION:
//
//    Header for the covariance model used by the TSM.
//
//    LIMITATIONS:       None
// 
//                       Date          Author   Comment    
//    SOFTWARE HISTORY:  
//
//    NOTES:
//
//#####################################################################

#ifndef __TSMCOVARIANCE_MODEL_H
#define __TSMCOVARIANCE_MODEL_H

#include <string>
#include "TSMMisc.h"

class TSM_EXPORT_API tsm_CovarianceModel
{
public:
   tsm_CovarianceModel ()         { _format = "UNKNOWN"; }
   virtual ~tsm_CovarianceModel (){ _format.erase(); }

   void getFormat( std::string &format ) const { format = _format; }

protected:

   std::string _format;

};

#endif
