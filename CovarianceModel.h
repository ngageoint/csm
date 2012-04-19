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
//     29-Mar-2012   SCM      Refactored interface
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

   virtual size_t getNumSensorModelParameters() const = 0;
      //> Returns the number of sensor model parameters. The returned value
      //  will be the same as the value of numSMParams passed to the
      //  constructor when the object was created.
      //<
   virtual size_t getNumCorrelationParameterGroups() const = 0;
      //> Returns the number of correlation parameter groups. The returned
      //  value will be the same as the value of numCPGroups passed to the
      //  constructor when the object was created.
      //<

   virtual int getCorrelationParameterGroup(size_t smParamIndex) const = 0;
      //> Returns the index of the correlation parameter group to which the given
      //  sensor model parameter belongs.  The smParamIndex variable is the index
      //  of a sensor model parameter.  If the sensor model parameter
      //  does not belong to a group, the return value will be -1.
      //
      //  The smParamIndex must be less than getNumSensorModelParameters().
      //<

   virtual double getCorrelationCoefficient(size_t cpGroupIndex,
                                            double deltaTime) const = 0;
      //>  Computes the correlation coefficient for the given correlation parameter
      //  group and delta-time.  The cpGroupIndex variable holds the index of a
      //  correlation parameter group.  The deltaTime variable represents the
      //  difference in time for the correlation calculation.
      //
      //  The cpGroupIndex must be less than getNumCorrelationParameterGroups().
      //
      //  Notes:
      //
      //  The deltaTime parameter should be positive, but the function uses the
      //  absolute value of the variable, so a negative deltaTime is acceptable
      //  input.
      //
      //  If the computed correlation coefficient is outside the range [-1, 1],
      //  the function will "clamp" the returned value to the nearest number
      //  within that range.  For example, if the correlation coefficient equation
      //  evaluates to 1.1 for a given deltaTime, the value 1.0 will be returned.
      //<


protected:
   std::string theFormat;
};

} // namespace csm

#endif
