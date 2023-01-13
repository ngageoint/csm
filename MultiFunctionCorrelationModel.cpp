//#############################################################################
//
//    FILENAME:          MultiFunctionCorrelationModel.cpp
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
//     21-Now-2021   JPK      Initial Coding
//
//#############################################################################

#define CSM_LIBRARY
#include "MultiFunctionCorrelationModel.h"
#include "Error.h"
#include <cmath>

namespace csm {
     
MultiFunctionCorrelationModel::MultiFunctionCorrelationModel(size_t numSMParams,
                                                             size_t numCPGroups)
   :
      CorrelationModel("Multi-FunctionCorrelation",
                       numCPGroups),
      theGroupMapping  (numSMParams, -1),
      theCorrFunctions (numCPGroups)
{}

MultiFunctionCorrelationModel::~MultiFunctionCorrelationModel()
{}

size_t MultiFunctionCorrelationModel::getNumSensorModelParameters() const
{
   return theGroupMapping.size();
}

int MultiFunctionCorrelationModel::getCorrelationParameterGroup(size_t smParamIndex) const
{
   // make sure the index falls within the acceptable range
   checkSensorModelParameterIndex(smParamIndex, "getCorrelationParameterGroup");

   // return the correlation parameter group index by reference
   return theGroupMapping[smParamIndex];
}

void MultiFunctionCorrelationModel::setCorrelationParameterGroup(size_t smParamIndex,
                                                                 size_t cpGroupIndex)
{
   // make sure the indices fall within the acceptable ranges
   checkSensorModelParameterIndex(smParamIndex, "setCorrelationParameterGroup");
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationParameterGroup");

   // set the group index for the given model parameter
   theGroupMapping[smParamIndex] = (int)cpGroupIndex;
}

void MultiFunctionCorrelationModel::setCorrelationGroupFunction(
   size_t cpGroupIndex, const SPDCFPtr& corrFunction)
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "setCorrelationGroupFunction");

   // store the correlation parameter values
   theCorrFunctions[cpGroupIndex] = corrFunction;
}

double MultiFunctionCorrelationModel::getCorrelationCoefficient(
   size_t cpGroupIndex, double deltaTime) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationCoefficient");
   
   if (!theCorrFunctions[cpGroupIndex]) return 0.0;
   
   return theCorrFunctions[cpGroupIndex]->getCorrelationCoefficient(deltaTime);
}

const SPDCFPtr&
MultiFunctionCorrelationModel::getCorrelationGroupFunction(size_t cpGroupIndex) const
{
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex, "getCorrelationGroupFunction");

   return theCorrFunctions[cpGroupIndex];
}

void MultiFunctionCorrelationModel::checkSensorModelParameterIndex(
   size_t smParamIndex, const std::string& functionName) const
{
   if (smParamIndex >= theGroupMapping.size())
   {
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "Sensor model parameter index is out of range.",
                  "csm::MultiFunctionCorrelationModel::" + functionName);
   }
}

void MultiFunctionCorrelationModel::checkParameterGroupIndex(
   size_t groupIndex, const std::string& functionName) const
{
   if (groupIndex >= theCorrFunctions.size())
   {
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "Correlation parameter group index is out of range.",
                  "csm::MultiFunctionCorrelationModel::" + functionName);
   }
}

} // namespace csm
