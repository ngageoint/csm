//#############################################################################
//
//    FILENAME:          WeightedSumCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    The WeightedSumCorrelationFunction class is derived from the
//    SPDCorrelationFunction class.  It allows multiple correlation
//    functions to be combined as a weighted sum and treated as a single
//    function.
//
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

#ifndef WEIGHTED_SUM_CORRELATIONFUNCTION_HEADER
#define WEIGHED_SUM_CORRELATIONFUNCTION_HEADER

#include "SPDCorrelationFunction.h"

namespace csm
{

class CSM_EXPORT_API WeightedSumCorrelationFunction : public SPDCorrelationFunction
{
public:
   
   using WeightedFunction = std::pair<double,SPDCFPtr>;
   
   WeightedSumCorrelationFunction();
   
   WeightedSumCorrelationFunction(const std::vector<WeightedFunction>& funcs,
                                  double dtEpsilon = 0.0);
   
     
   virtual ~WeightedSumCorrelationFunction();  
   virtual double getCorrelationCoefficient(double deltaTime) const;
   //> This method returns the correlation coefficient for the argument
   //  delta time.
   //<
   virtual std::vector<SPDCorrelationFunction::Parameter> parameters() const;   
   
   void setFunctions(const std::vector<WeightedFunction>& funcs,
                     double                               dtEpsilon);
   
   bool addFunction(const WeightedFunction& argFunc,
                    double                  weightTolerance = 2.0e-3);
   //> This method will attempt to add a weighted function the currently owned
   //  vector of functions.  If the sum of the weights would significantly exceed
   //  1.0, the function will not be added, and "false" is returned.  Otherwise,
   //  the function will be added and if the sum of the weights is within the
   //  argument weight tolerance, the weights will be scaled as necessary.
   //<
   
   size_t numberOfFunctions() const {return theFunctions.size();}

   const WeightedFunction& function(size_t index) const;

protected:

   static double sumOfWeights(const std::vector<WeightedFunction>& funcs);
   //> This method computes the sum of the weights of the argument functions
   //<
   
   static void checkAndScaleWeights(std::vector<WeightedFunction>& funcs,
                                    double weightTolerance = 2.0e-3);
   //> This static method checks the sum of the weights for the provided functions.
   //  If the passed in "weightTolerance" is negative or 0.0, no scaling will be
   //  performed.  If the sum is within "weightTolerance" of 1.0, the weights for the
   //  provided functions will be scaled so that their sum is 1.0.  Otherwise,
   //  if the sum is significantly larger than 1.0, a csm::Error is returned.
   //  If the sum is significantly less than 1.0, no scaling will occur.
   //<
   static double correlationCoefficentFor(double deltaTime,
                                          const std::vector<WeightedFunction>& funcs,
                                          double dtEpsilon);
   //> This static method computes the correlation coefficent for the argument
   //  wirghted functions.
   //<
   
   std::vector<WeightedFunction> theFunctions;
};
} // namespace csm

#endif
