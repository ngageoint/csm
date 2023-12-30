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
//     28-Sep-2022   JPK      Added support for "deltaTimeEpsilon"
//     12-Nov-2023   JPK      Added use of ConstantCorrelationFunction.
//     22-Nov-2023   JPK      Modified various strings being passed to be
//                            static (since they never change) to improve
//                            efficiency.
//#############################################################################

#define CSM_LIBRARY
#include "MultiFunctionCorrelationModel.h"
#include "ConstantCorrelationFunction.h"
#include "Error.h"
#include <cmath>

static const std::string MFCM_NAME = "Multi-FunctionCorrelation";

namespace csm {
     
MultiFunctionCorrelationModel::MultiFunctionCorrelationModel(size_t numSMParams,
                                                             size_t numCPGroups)
   :
      CorrelationModel(MFCM_NAME,
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
   static const std::string METHOD_NAME = "getCorrelationParameterGroup";
   
   // make sure the index falls within the acceptable range
   checkSensorModelParameterIndex(smParamIndex,METHOD_NAME);

   // return the correlation parameter group index by reference
   return theGroupMapping[smParamIndex];
}

void MultiFunctionCorrelationModel::setCorrelationParameterGroup(size_t smParamIndex,
                                                                 size_t cpGroupIndex)
{
   static const std::string METHOD_NAME = "setCorrelationParameterGroup";
   
   // make sure the indices fall within the acceptable ranges
   checkSensorModelParameterIndex(smParamIndex,METHOD_NAME);
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);

   // set the group index for the given model parameter
   theGroupMapping[smParamIndex] = cpGroupIndex;
}

void MultiFunctionCorrelationModel::setCorrelationGroupFunction(
   size_t cpGroupIndex, const SPDCFPtr& corrFunction, double deltaTimeEpsilon)
{
   static const std::string METHOD_NAME = "setCorrelationGroupFunction";
   
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);

   // store the correlation parameter values
   // If passed in object is empty, assign a ConstantCorrelationFunction with
   // a value of 0.0
   
   if (!corrFunction)
   {
      SPDCFPtr ccf =
         std::make_shared<ConstantCorrelationFunction>(0.0,deltaTimeEpsilon);
      
      theCorrFunctions[cpGroupIndex] = ccf;
   }
   else
   {
      theCorrFunctions[cpGroupIndex] = corrFunction;
   }
   
   if (theCorrFunctions[cpGroupIndex] && deltaTimeEpsilon >= 0)
   {
      theCorrFunctions[cpGroupIndex]->setDeltaTimeEpsilon(deltaTimeEpsilon);
   }
}

double MultiFunctionCorrelationModel::getCorrelationCoefficient(
   size_t cpGroupIndex, double deltaTime) const
{
   static const std::string METHOD_NAME = "getCorrelationCoefficient";
   
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);
   
   if (!theCorrFunctions[cpGroupIndex]) return 0.0;
   
   return theCorrFunctions[cpGroupIndex]->getCorrelationCoefficient(deltaTime);
}

const SPDCFPtr&
MultiFunctionCorrelationModel::getCorrelationGroupFunction(size_t cpGroupIndex) const
{
   static const std::string METHOD_NAME = "getCorrelationGroupFunction";
   
   // make sure the index falls within the acceptable range
   checkParameterGroupIndex(cpGroupIndex,METHOD_NAME);

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
