/**
 * This file contains the implementation of the
 * CSMFourParameterCorrelationModel class.  See the comments in the header file
 * for more information about the class interface.
 **/
#define CSM_LIBRARY
#include "CSMFourParameterCorrelationModel.h"
#include "CSMError.h"

#ifdef IRIXN32
#include "math.h"
#else
#include <cmath>
using std::exp;
using std::fabs;
#endif

namespace csm {

FourParameterCorrelationModel::FourParameterCorrelationModel(size_t numSMParams,
                                                             size_t numCPGroups)
   :
      theGroupMapping(numSMParams, -1),
      theCorrParams(numSMParams)
{
   // set the format string in the base class
   theFormat = "Four-parameter model (A, alpha, beta, tau)";
}

FourParameterCorrelationModel::~FourParameterCorrelationModel()
{
}

size_t FourParameterCorrelationModel::getNumSensorModelParameters() const
{
   return theGroupMapping.size();
}

size_t FourParameterCorrelationModel::getNumCorrelationParameterGroups() const
{
   return theCorrParams.size();
}

int FourParameterCorrelationModel::getCorrelationParameterGroup(size_t smParamIndex) const
{
   // make sure the index falls within the acceptable range
   checkSensorModelParameterIndex(smParamIndex, "getCorrelationParameterGroup");

   // return the correlation parameter group index by reference
   return theGroupMapping[smParamIndex];
}

void FourParameterCorrelationModel::setCorrelationParameterGroup(size_t smParamIndex,
                                                                 size_t cpGroupIndex)
{
   // make sure the indices fall within the acceptable ranges
   checkSensorModelParameterIndex(smParamIndex, "setCorrelationParameterGroup");
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationParameterGroup");

   // set the group index for the given sensor model parameter
   theGroupMapping[smParamIndex] = cpGroupIndex;
}

void FourParameterCorrelationModel::setCorrelationGroupParameters(
   size_t cpGroupIndex, double a, double alpha, double beta, double tau)
{
   static const char* const MODULE =
      "csm::FourParameterCorrelationModel::setCorrelationGroupParameters";

   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationGroupParameters");

   // make sure the values of each correlation model parameter fall within acceptable ranges
   if ((a < -1.0) || (a > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter A must be in the range [-1, 1].",
                  MODULE);
   }

   if ((alpha < 0.0) || (alpha > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter alpha must be in the range [0, 1].",
                  MODULE);
   }

   if (beta < 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter beta must be non-negative.",
                  MODULE);
   }

   if (tau <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter tau must be positive.",
                  MODULE);
   }

   // store the correlation parameter values
   theCorrParams[cpGroupIndex] = CorrelationParameters(a, alpha, beta, tau);
}

double FourParameterCorrelationModel::getCorrelationCoefficient(
   size_t cpGroupIndex, double deltaTime) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationCoefficient");

   // compute the value of the correlation coefficient
   const CorrelationParameters& cp = theCorrParams[cpGroupIndex];
   double corrCoeff = cp.theAlpha +
                      (cp.theA * (1.0 - cp.theAlpha) * (1.0 + cp.theBeta) /
                       (cp.theBeta + exp(fabs(deltaTime) / cp.theTau)));

   // if necessary, clamp the coefficient value to the acceptable range
   if (corrCoeff < -1.0) return -1.0;
   if (corrCoeff > 1.0)  return 1.0;

   return corrCoeff;
}

void FourParameterCorrelationModel::checkSensorModelParameterIndex(
   size_t smParamIndex, const std::string& functionName) const
{
   if (smParamIndex >= theGroupMapping.size())
   {
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "Sensor model parameter index is out of range.",
                  "csm::FourParameterCorrelationModel::" + functionName);
   }
}

void FourParameterCorrelationModel::checkParameterGroupIndex(
   size_t groupIndex, const std::string& functionName) const
{
   if (groupIndex >= theCorrParams.size())
   {
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "Correlation parameter group index is out of range.",
                  "csm::FourParameterCorrelationModel::" + functionName);
   }
}

} // namespace csm
