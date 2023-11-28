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

   size_t numberOfFunctions() const {return theFunctions.size();}

   const WeightedFunction& function(size_t index) const;
   
   static void checkFunctions(const std::vector<WeightedFunction>& funcs);
   //> This static method verifies the sum of the weighted functions is
   //  not greater than 1.0
   //<
   static double correlationCoefficentFor(double deltaTime,
                                          const std::vector<WeightedFunction>& funcs,
                                          double dtEpsilon);
   //> This static method computes the correlation coefficent for the argument
   //  wirghted functions.
   //<
   
private:

   std::vector<WeightedFunction> theFunctions;
   
};
} // namespace csm

#endif
