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
//     03-Sep-2021   SCM      Removed IRIX support.
//     01-Dec-2021   JPK      Modified to use LinearDecayCorrelationFunction
//     12-Nov-2023   JPK      Updated to allow relaxation of strictly
//                            monotonically decreasing correlation parameters
//                            for backwards compatibility.
//     21-Nov-2023  JPK       Modified to use LinearDecayCorrelationFunction::
//                            correlationCoefficientFor() static method.
//     22-Nov-2023  JPK       Modified to use LinearDecayCorrelationFunction::
//                            checkParameters()
//    NOTES:
//     Refer to LinearDecayCorrelationModel.h for more information.
//#############################################################################
#define CSM_LIBRARY
#include "LinearDecayCorrelationModel.h"
#include "LinearDecayCorrelationFunction.h"
#include "Error.h"

#include <cmath>
using std::exp;
using std::fabs;

static const std::string LDCM_NAME = "LinearDecayCorrelation";

namespace csm {

LinearDecayCorrelationModel::LinearDecayCorrelationModel(size_t numSMParams,
                                                         size_t numCPGroups)
   :
      CorrelationModel (LDCM_NAME,
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
   static const std::string METHOD_NAME = "setCorrelationParameterGroup";
   
   // make sure the indices fall within the acceptable ranges
   checkSensorModelParameterIndex(smParamIndex,METHOD_NAME);
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);

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
   static const std::string METHOD_NAME = "setCorrelationGroupParameters";
   
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);
   
   // Check parameters using LinearDecayCorrelationFunction but do not enforce
   // strict monotonicity for backward compatibility.
   // If parameters are not within expected range, this will cause a csm::Error
   // to be thrown.
   
   LinearDecayCorrelationFunction::
      checkParameters(params.theInitialCorrsPerSegment,
                      params.theTimesPerSegment,
                      false);
   
   // store the correlation parameter values
   theCorrParams[cpGroupIndex] = params;
}

double LinearDecayCorrelationModel::getCorrelationCoefficient(
   size_t cpGroupIndex,
   double deltaTime) const
{
   static const std::string METHOD_NAME = "getCorrelationCoefficient";
   
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);
   
   const Parameters& params = theCorrParams[cpGroupIndex];

   return (LinearDecayCorrelationFunction::
           correlationCoefficientFor(deltaTime,
                                     params.theInitialCorrsPerSegment,
                                     params.theTimesPerSegment,
                                     0.0));
}

const LinearDecayCorrelationModel::Parameters&
LinearDecayCorrelationModel::getCorrelationGroupParameters(
   size_t cpGroupIndex) const
{
   static const std::string METHOD_NAME  = "getCorrelationGroupParameters";
   
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);

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
