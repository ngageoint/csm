//#############################################################################
//
//    FILENAME:          WeightedSumCorrelationFunction.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    The WeightedSumCorrelationFunction class derives from the
//    SPDCorrelationFunction class.  It allows multiple correlation
//    functions to be combined as a weighted sum and treated as a single
//    function.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     22-Nov-2023   JPK      Initial Coding
//
//    NOTES:
//
//#############################################################################

#define CSM_LIBRARY
#include "WeightedSumCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <sstream>

namespace csm
{
static const std::string WSCF_NAME   = "WeightedSum";
static const std::string PARAM_NAME = "Weight_";

static const double WEIGHT_SUM_TOLERANCE = 2.0e-3;
//> This value indicates the allowable tolerance for the sum of the weights.
// If weights sum to a value of 1.0 +/- WEIGHT_SUM_TOLERANCE, all weights
// shall be scaled so that their sum is 1.0
//<

WeightedSumCorrelationFunction::WeightedSumCorrelationFunction()
   :
      SPDCorrelationFunction (WSCF_NAME,0.0),
      theFunctions           ()
{}

WeightedSumCorrelationFunction::
WeightedSumCorrelationFunction(const std::vector<WeightedFunction>& funcs,
                               double                               dtEpsilon)
   :
      SPDCorrelationFunction (WSCF_NAME,dtEpsilon),
      theFunctions           (funcs)
{ 
   checkAndScaleWeights(theFunctions);
}

WeightedSumCorrelationFunction::~WeightedSumCorrelationFunction()
{}

double WeightedSumCorrelationFunction::
       getCorrelationCoefficient(double deltaTime) const
{
   const double dtEpsilon = deltaTimeEpsilon();

   return correlationCoefficentFor(deltaTime,
                                   theFunctions,
                                   dtEpsilon);
}

std::vector<SPDCorrelationFunction::Parameter>
WeightedSumCorrelationFunction::parameters() const
{
   std::vector<SPDCorrelationFunction::Parameter> paramVec;

   const size_t NUM_FUNCS = theFunctions.size();

   for (size_t f = 0; f < NUM_FUNCS; ++f)
   {
      std::stringstream weightStrm;
      weightStrm <<  PARAM_NAME << f;

      paramVec.push_back(std::make_pair(weightStrm.str(),
                                        theFunctions[f].first));
      std::vector<SPDCorrelationFunction::Parameter> fVec =
         theFunctions[f].second->parameters();

      paramVec.insert(paramVec.end(),fVec.begin(),fVec.end());
   }

   return paramVec;
}

void WeightedSumCorrelationFunction::
setFunctions(const std::vector<WeightedFunction>& funcs,
             double                               dtEpsilon)
{
   theFunctions = funcs;

   checkAndScaleWeights(theFunctions);
   
   setDeltaTimeEpsilon(dtEpsilon);
}

bool WeightedSumCorrelationFunction::
addFunction(const WeightedFunction& argFunc,
            double                  weightTolerance)
{
   const double totalSum = sumOfWeights(theFunctions) + argFunc.first;
   
   //***
   // Make sure passed in tolerance in non-negative
   //***
   if (weightTolerance < 0.0) weightTolerance = 0.0;

   //***
   // If sum of weights including argument function is significantly larger
   // then 1.0, do no add the function.
   //***
   if (totalSum > (1.0 + weightTolerance))
   {
      return false;
   }

   theFunctions.push_back(argFunc);
   
   //***
   // If the sum of weights is within tolerance of 1.0, scale the weights
   //***
   if (totalSum > (1.0 - weightTolerance))
   {
      checkAndScaleWeights(theFunctions);
   }

   return true;
}

const WeightedSumCorrelationFunction::WeightedFunction&
WeightedSumCorrelationFunction::function(size_t index) const
{
   static const std::string METHOD_NAME =
      "WeightedSumCorrelationFunction::function";
   
   if (theFunctions.empty())
   {
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "No correlation functions found.",
                  METHOD_NAME);
   }
   
   if (index < theFunctions.size())
   {
      return theFunctions[index];
   }

   std::stringstream errStrm;

   errStrm << "Requested function at index : " << index
           << " but valid range is [0," << theFunctions.size() -1;

    throw Error(Error::INDEX_OUT_OF_RANGE,
                errStrm.str(),
                METHOD_NAME);
}

double WeightedSumCorrelationFunction::
       sumOfWeights(const std::vector<WeightedFunction>& funcs)
{
  const size_t NUM_FUNCS = funcs.size();

   double sum = 0.0;

   for (size_t f = 0; f < NUM_FUNCS; ++f)
   {
      const WeightedFunction& wf = funcs[f];

      sum += wf.first;
   }
   
   return sum;
}

void WeightedSumCorrelationFunction::
     checkAndScaleWeights(std::vector<WeightedFunction>& funcs,
                     double                         weightTolerance)
{
   static const std::string METHOD_NAME =
      " WeightedSumCorrelationFunction::checkAndScaleWeights";
   
   //***
   // Make sure passed in tolerance in non-negative
   //***
   if (weightTolerance < 0.0) weightTolerance = 0.0;
   
   const double sum = sumOfWeights(funcs);
   
   //***
   // Do not allow sums significantly larger than 1.0
   //***
   if (sum > (1.0 + weightTolerance))
   {
      std::stringstream errStrm;
      errStrm << "Sum of weights : "
              << sum
              << " is significantly greater than 1.0 .";

      throw Error(Error::BOUNDS,
                  errStrm.str(),
                  METHOD_NAME);
   }
   
   //***
   // For sums close to 1.0, scale the weights
   //***
   if (sum > (1.0 - weightTolerance))
   {
      const double scale = 1.0/sum;

      if (scale != 1.0)
      {
         const size_t NUM_FUNCS = funcs.size();
         
         for (size_t f = 0; f < NUM_FUNCS; ++f)
         {
            WeightedFunction& wf = funcs[f];
            
            wf.first *= scale;
         }
      }
   }

   //***
   // If the sum is significantly less than 1.0, do not scale
   //***
}

double WeightedSumCorrelationFunction::
correlationCoefficentFor(double deltaTime,
                         const std::vector<WeightedFunction>& funcs,
                         double dtEpsilon)
{
   if (deltaTime != 0.0)
   {
      if (std::fabs(deltaTime) >= dtEpsilon)
      {
         double corrSum = 0.0;

         const size_t NUM_FUNC = funcs.size();
         
         for (size_t f = 0; f < NUM_FUNC; ++f)
         {
            const WeightedFunction& wf = funcs[f];
            
            //***
            // skip over any unititialized functions.
            //***
            if (!wf.second) continue;
            
            corrSum += wf.first*(wf.second->
                                 getCorrelationCoefficient(deltaTime));
         }

         return corrSum;
      }
   }
   //***
   // if delta time is bounded by epsilon, correlation coefficient is 1.0
   //***
   return 1.0;
}
} // namespace csm
   
