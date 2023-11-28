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
   checkFunctions(theFunctions);
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
   checkFunctions(funcs);

   theFunctions = funcs;

   setDeltaTimeEpsilon(dtEpsilon);
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

void WeightedSumCorrelationFunction::
     checkFunctions(const std::vector<WeightedFunction>& funcs)
{
   static const std::string METHOD_NAME =
      " WeightedSumCorrelationFunction::checkFunctions";
   
   const size_t NUM_FUNCS = funcs.size();

   double sum = 0.0;

   for (size_t f = 0; f < NUM_FUNCS; ++f)
   {
      const WeightedFunction& wf = funcs[f];
      
      //***
      // If there is no correlation function, do not add any weight.
      //***
      if (!wf.second)
      {
         continue;
      }
      
      sum += wf.first;
   }

   if (sum > 1.0)
   {
      std::stringstream errStrm;
      errStrm << "Sum of weights : " << sum << " is greater than 1.0 .";

      throw Error(Error::BOUNDS,
                  errStrm.str(),
                  METHOD_NAME);
   }
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
   
