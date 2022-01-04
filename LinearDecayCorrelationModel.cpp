//#############################################################################
//
//    FILENAME:          LinearDecayCorrelationModel.cpp
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
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     20-Nov-2012   ISK      Initial Release.
//     30-Oct-2012   SCM      Renamed to LinearDecayCorrelationModel.h
//     17-Dec-2012   BAH      Documentation updates.
//     20-Dec-2012   JPK      Fixed bug in constructor.
//     18-Feb-2013   JPK      Removed getNumCorrelationParameterGroups,
//                            now provided on base class.
//     01Dec-2021    JPK      Modified to use LinearDecayCorrelationFunction
//    NOTES:
//     Refer to LinearDecayCorrelationModel.h for more information.
//#############################################################################
#define CSM_LIBRARY
#include "LinearDecayCorrelationModel.h"
#include "LinearDecayCorrelationFunction.h"
#include "Error.h"

#ifdef IRIXN32
#include "math.h"
#else
#include <cmath>
using std::exp;
using std::fabs;
#endif

namespace csm {

LinearDecayCorrelationModel::LinearDecayCorrelationModel(size_t numSMParams,
                                                         size_t numCPGroups)
   :
      CorrelationModel ("LinearDecayCorrelation",
                        numCPGroups),
      theGroupMapping  (numSMParams, -1),
      theCorrParams    (numCPGroups)
{}

LinearDecayCorrelationModel::~LinearDecayCorrelationModel()
{
}

size_t LinearDecayCorrelationModel::getNumSensorModelParameters() const
{
   return theGroupMapping.size();
}

int LinearDecayCorrelationModel::getCorrelationParameterGroup(size_t smParamIndex) const
{
   // make sure the index falls within the acceptable range
   checkSensorModelParameterIndex(smParamIndex, "getCorrelationParameterGroup");

   // return the correlation parameter group index by reference
   return theGroupMapping[smParamIndex];
}

void LinearDecayCorrelationModel::setCorrelationParameterGroup(
   size_t smParamIndex,
   size_t cpGroupIndex)
{
   // make sure the indices fall within the acceptable ranges
   checkSensorModelParameterIndex(smParamIndex, "setCorrelationParameterGroup");
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationParameterGroup");

   // set the group index for the given model parameter
   theGroupMapping[smParamIndex] = cpGroupIndex;
}

void LinearDecayCorrelationModel::setCorrelationGroupParameters(
   size_t cpGroupIndex,
   const std::vector<double>& initialCorrsPerSegment,
   const std::vector<double>& timesPerSegment)
{
   setCorrelationGroupParameters(
      cpGroupIndex, Parameters(initialCorrsPerSegment, timesPerSegment) );
}

void LinearDecayCorrelationModel::setCorrelationGroupParameters(
   size_t            cpGroupIndex,
   const Parameters& params)
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationGroupParameters");

   LinearDecayCorrelationFunction::checkParameters(params);
   
   // store the correlation parameter values
   theCorrParams[cpGroupIndex] = params;
}

double LinearDecayCorrelationModel::getCorrelationCoefficient(
   size_t cpGroupIndex,
   double deltaTime) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationCoefficient");

   // compute the value of the correlation coefficient
   return LinearDecayCorrelationFunction::
      correlationCoefficientFor(theCorrParams[cpGroupIndex],
                                deltaTime);
}

const LinearDecayCorrelationModel::Parameters&
LinearDecayCorrelationModel::getCorrelationGroupParameters(
   size_t cpGroupIndex) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationGroupParameters");

   return theCorrParams[cpGroupIndex];
}

void LinearDecayCorrelationModel::checkSensorModelParameterIndex(
   size_t             smParamIndex, 
   const std::string& functionName) const
{
   if (smParamIndex >= theGroupMapping.size())
   {
      throw Error(
         Error::INDEX_OUT_OF_RANGE,
         "Sensor model parameter index is out of range.",
         "csm::LinearDecayCorrelationModel::" + functionName);
   }
}

void LinearDecayCorrelationModel::checkParameterGroupIndex(
   size_t             groupIndex,
   const std::string& functionName) const
{
   if (groupIndex >= theCorrParams.size())
   {
      throw Error(
         Error::INDEX_OUT_OF_RANGE,
         "Correlation parameter group index is out of range.",
         "csm::LinearDecayCorrelationModel::" + functionName);
   }
}

} // namespace csm
