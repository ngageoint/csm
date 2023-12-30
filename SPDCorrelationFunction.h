//##################################################################
//
//    FILENAME:          SPDCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for a class representing a symmetric positive definite
//    correlation function (SPDCF).
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     22-Nov-2021   JPK      Initial Coding
//     28-Sep-2022   JPK      Added "deltaTimeEpsilon"
//     12-Nov-2023   JPK      Added base class access to parameters
//                            and parameter names to simplify queries
//                            when specific information about the
//                            derived classes is needed.
//     22-Nov-2023   JPK      Parameter values/names are now acessed
//                            via virtual methods on dervied classes to
//                            remove potential inefficiences populating
//                            information when not needed.
//    NOTES:
//
//#####################################################################

#ifndef CSM_SPDCORRELATIONFUNCTION_HEADER
#define CSM_SPDCORRELATIONFUNCTION_HEADER

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "csm.h"

namespace csm
{

class CSM_EXPORT_API SPDCorrelationFunction
{
public:

   using Parameter = std::pair<std::string,double>;

   SPDCorrelationFunction(const std::string& name,
                          double             deltaTimeEpsilon)
      :
      theName       (name)
   {
      setDeltaTimeEpsilon(deltaTimeEpsilon);
   }
   
   virtual ~SPDCorrelationFunction() {}
      //> A virtual destructor is needed so derived class destructors will
      //  be called when the base class object is destroyed.
      //<

   virtual double getCorrelationCoefficient(double deltaTime) const = 0;
      //> This method returns the correlation coefficient for the given deltaTime.
      //  The deltaTime argument represents the difference in time, in seconds,
      //  for which the correlation is calculated.
      //
      //  The deltaTime argument should be positive, but the method uses the
      //  absolute value of the argument, so a negative deltaTime is acceptable.
      //<
   virtual std::vector<Parameter> parameters() const = 0;
      //> This method return the parameters for the current function.
      //<
      
   const std::string& name() const { return theName; }
  
   double deltaTimeEpsilon() const {return theDeltaTimeEpsilon;}
      //>  This method returns the delta time epsilon, i.e. the smallest
      //   value of epsilon for which the correlation function is computed.
      //   For any non-negative value smaller than this, the correlation
      //   coefficient is always 1.0 .  Unless explicitly set, this value is
      //   0.0.  The purpose of this value is to accomodate lack of
      //   precision with respect to the "delta time".
      //<
         
   void setDeltaTimeEpsilon(double deltaTimeEpsilon)
   {
      theDeltaTimeEpsilon = (deltaTimeEpsilon < 0.0 ? 0.0 : deltaTimeEpsilon);
   }
   //> This method sets the delta time epsilon, i.e. the smallest significant
   //  delta time for this correlation function.  The argument value should
   //  be non-negative.  If a negative value is encountered, the default
   //  value of 0.0 is used.
   //<
      
   static double clampedCoeff(double argValue,bool allowNegative)
   {
      if (allowNegative)
      {
         return (argValue < -1.0 ? -1.0 : (argValue > 1.0 ? 1.0 : argValue));
      }
            
      return (argValue < 0.0 ? 0.0 : (argValue > 1.0 ? 1.0 : argValue)); 
   }
   //> This static method "clamps" argValue to be in the range
   //  [0,1] ( or [-1,1] if allowNegative is "true").
   //<
      
protected:
   
   void setName(const std::string& name) 
   {
      theName = name;
   }

   
private:
   
   SPDCorrelationFunction()
      :
      theName             (CSM_UNKNOWN),
      theDeltaTimeEpsilon (0.0)
   {}
   //> This is the default constructor.  It is declared private to prevent
   //  its use.
   //<
      
   std::string theName;
   //> This data member is a string identifying the "name" of the
   //  current derived CorrelationModel.
   //<
   double      theDeltaTimeEpsilon;
   //> This data member represents the smallest "significant" delta time and
   //  must be >= 0.0.  Any delta time smaller than this value will be treated
   //  as 0.0, i.e. the returned correlation coefficient will be 1.0 .
   //<   
};

using SPDCFPtr = std::shared_ptr<SPDCorrelationFunction>;

} // namespace csm

#endif
