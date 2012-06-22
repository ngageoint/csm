//#############################################################################
//
//    FILENAME:          CSMFourParameterCorrelationModel.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This header defines the CSMFourParameterCorrelationModel class.  This
//    class is used to compute the correlation between adjustable parameters in
//    a community sensor model (CSM).
//
//    The class is a wrapper around the equation
//
//    rho = alpha + a * (1 - alpha) * (1 + beta) / (beta + exp(deltaT / tau)),
//
//    where a, alpha, beta, and tau are the correlation parameters, deltaT is
//    the difference in time, and rho is the correlation coefficient.
//
//    The class assumes that sensor model parameter are divided into disjoint
//    groups, such that the correlation coefficient between any two parameters
//    in the same group is given by the equation above, and the correlation
//    between two parameters in different groups is 0.0.  This implementation
//    provides a way to assign sensor model parameters to groups, to set the
//    values of the correlation parameters for a given group, and to compute
//    the equation above.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     29-Mar-2012   SCM      Refactored interface.
//     22-Jun-2012   SCM      Made CorrelationParameters public, added accessor.
//
//    NOTES:
//
//#############################################################################

#ifndef _CSM3_FOURPARAMETERCORRELATIONMODEL_H_
#define _CSM3_FOURPARAMETERCORRELATIONMODEL_H_

#include "CSMCovarianceModel.h"
#include "CSMWarning.h"

#include <vector>

namespace csm
{

class CSM_EXPORT_API FourParameterCorrelationModel : public CovarianceModel
{
public:
   // represents a set of four correlation parameters, grouped to simplify the implementation
   struct CSM_EXPORT_API CorrelationParameters
   {
      CorrelationParameters() : a(0.), alpha(0.), beta(0.), tau(0.) {}
      CorrelationParameters(double aA, double aAlpha, double aBeta, double aTau)
         : a(aA), alpha(aAlpha), beta(aBeta), tau(aTau) {}

      double a;
      double alpha;
      double beta;
      double tau;
   };

   FourParameterCorrelationModel(size_t numSMParams, size_t numCPGroups);
      //> Constructor.  The number of sensor model parameters and correlation
      //  parameter groups must be provided.
      //
      // Preconditions:
      // * numSMParams must be non-negative
      // * numCPGroups must be non-negative
      //<

   virtual ~FourParameterCorrelationModel();

   virtual size_t getNumSensorModelParameters() const;
      //> Returns the number of sensor model parameters. The returned value
      //  will be the same as the value of numSMParams passed to the
      //  constructor when the object was created.
      //<
   virtual size_t getNumCorrelationParameterGroups() const;
      //> Returns the number of correlation parameter groups. The returned
      //  value will be the same as the value of numCPGroups passed to the
      //  constructor when the object was created.
      //<

   virtual int getCorrelationParameterGroup(size_t smParamIndex) const;
      //> Returns the index of the correlation parameter group to which the given
      //  sensor model parameter belongs.  The smParamIndex variable is the index
      //  of a sensor model parameter.  If the sensor model parameter
      //  does not belong to a group, the return value will be -1.
      //
      //  Precondition:
      //  * 0 <= smParamIndex < numSMParams
      //<

   virtual double getCorrelationCoefficient(size_t cpGroupIndex, double deltaTime) const;
      //>  Computes the correlation coefficient for the given correlation parameter
      //  group and delta-time.  The cpGroupIndex variable holds the index of a
      //  correlation parameter group.  The deltaTime variable represents the
      //  difference in time for the correlation calculation.
      //
      //  Preconditions:
      //  * 0 <= cpGroupIndex < numCPGroups
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

   void setCorrelationParameterGroup(size_t smParamIndex, size_t cpGroupIndex);
      //> Sets the index of the correlation parameter group to which the given
      //  sensor model parameter belongs.  The smParamIndex variable is the index
      //  of a sensor model parameter, and the cpGroupIndex variable is the index
      //  of the correlation parameter group to which it should be added.
      //
      //  Preconditions:
      //  * 0 <= smParamIndex < numSMParams
      //  * 0 <= cpGroupIndex < numCPGroups
      //
      //  Notes:
      //
      //  Although the getCorrelationParameterGroup function can return -1 as a group
      //  index (indicating the group has not been set), it is an error to try to set
      //  the group index to -1.
      //<

   void setCorrelationGroupParameters(size_t cpGroupIndex, double a, double alpha, double beta, double tau);
      //> Sets the values of the correlation parameters for a given group.  The
      //  cpGroupIndex variable holds the index of a correlation parameter group,
      //  and the remaining arguments are the values of the correlation parameters
      //  in that group.
      //
      //  Precondition:
      //  * 0 <= cpGroupIndex < numCPGroups
      //  * -1.0 <= a <= 1.0
      //  * 0.0 <= alpha <= 1.0
      //  * 0.0 <= beta
      //  * 0.0 < tau
      //<

   void setCorrelationGroupParameters(size_t cpGroupIndex, const CorrelationParameters& params);
      //> Sets the values of the correlation parameters for a given group.
      //
      //  Throws an exception if cpGroupIndex or any of the correlation
      //  parameters is out of range.
      //<

   const CorrelationParameters& getCorrelationGroupParameters(size_t cpGroupIndex) const;
      //> Returns the values of the correlation parameters for a given group.
      //
      //  Throws an exception if cpGroupIndex is out of range.
      //<

protected:
   std::vector<int> theGroupMapping;
      //> This data member stores the mapping between sensor model parameter
      //  indices and correlation parameter group indices.
      //<

   std::vector<CorrelationParameters> theCorrParams;
      //> This data member stores the values of the correlation parameters for
      //  each parameter group.
      //<

   void checkSensorModelParameterIndex(size_t smParamIndex, const std::string& functionName) const;
      //> If the given sensor model parameter index is not within the range
      //  [0, numSMParams), throws a CSMError.
      //<

   void checkParameterGroupIndex(size_t groupIndex, const std::string& functionName) const;
      //> If the given correlation parameter group index is not within the range
      //  [0, numCPGroups), throws a CSMError.
      //<

};

} // namespace csm

#endif
