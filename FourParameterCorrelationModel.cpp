//#############################################################################
//
//    FILENAME:          FourParameterCorrelationModel.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This class is used to compute the correlation between model
//    parameters in a community sensor model (CSM).
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     29-Mar-2012   SCM      Refactored interface.
//     22-Jun-2012   SCM      Made Parameters public, added accessor.
//     30-Oct-2012   SCM      Renamed to FourParameterCorrelationModel.h
//     06-Nov-2012   JPK      Updated equation per CR 2012 10 17 001
//     17-Dec-2012   BAH      Documentation updates.
//     20-Dec-2012   JPK      Fixed bug in constructor.
//     18-Feb-2013   JPK      Removed getNumCorrelationParameterGroups,
//                            now provided on base class.
//     01-Dec-2021   JPK      Modified to use FourParameterCorrelationFunction
//    NOTES:
//     Refer to FourParameterCorrelationModel.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "FourParameterCorrelationModel.h"
#include "FourParameterCorrelationFunction.h"
#include "Error.h"

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
      CorrelationModel("Four-parameter model (A, alpha, beta, tau)",
                       numCPGroups),
      theGroupMapping (numSMParams, -1),
      theCorrParams   (numCPGroups)
{}

FourParameterCorrelationModel::~FourParameterCorrelationModel()
{}

size_t FourParameterCorrelationModel::getNumSensorModelParameters() const
{
   return theGroupMapping.size();
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

   // set the group index for the given model parameter
   theGroupMapping[smParamIndex] = (int)cpGroupIndex;
}

void FourParameterCorrelationModel::setCorrelationGroupParameters(
   size_t cpGroupIndex, double a, double alpha, double beta, double tau)
{
   setCorrelationGroupParameters(cpGroupIndex, Parameters(a, alpha, beta, tau));
}

void FourParameterCorrelationModel::setCorrelationGroupParameters(
   size_t cpGroupIndex, const Parameters& params)
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationGroupParameters");

   // make sure the values of each correlation model parameter fall within acceptable ranges
   FourParameterCorrelationFunction::checkParameters(params);
   
   // store the correlation parameter values
   theCorrParams[cpGroupIndex] = params;
}

double FourParameterCorrelationModel::getCorrelationCoefficient(
   size_t cpGroupIndex, double deltaTime) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationCoefficient");

   // compute the value of the correlation coefficient
   return FourParameterCorrelationFunction::
          correlationCoefficientFor(theCorrParams[cpGroupIndex],
                                    deltaTime);
}

const FourParameterCorrelationModel::Parameters&
FourParameterCorrelationModel::getCorrelationGroupParameters(size_t cpGroupIndex) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationGroupParameters");

   return theCorrParams[cpGroupIndex];
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
