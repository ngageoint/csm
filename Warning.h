//####################################################################
//
//    FILENAME:   CSMWarning.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the warning structure used by the CSM.
//
//    LIMITATIONS:       None
//
//                       Date          Author   Comment
//    SOFTWARE HISTORY: 1 June 2004    Kevin Lam CCB Change
//
//    NOTES:
//
//###################################################################
#ifndef __CSMWARNING_H
#define __CSMWARNING_H
#include <string>
#include "CSMMisc.h"
#ifdef WIN32
#pragma warning( disable : 4291 )
#pragma warning( disable : 4251 )
#endif
class CSM_EXPORT_API CSMWarning
{
   public:
      //-------------------------------------------------------------
      // Warnings
      //---------------------------------------------------------------
      enum WarningType
      {
         UNKNOWN_WARNING = 1,
         DATA_NOT_AVAILABLE,
         PRECISION_NOT_MET,
         NEGATIVE_PRECISION,
         IMAGE_COORD_OUT_OF_BOUNDS,
         IMAGE_ID_TOO_LONG,
         NO_INTERSECTION,
         DEPRECATED_FUNCTION
      };
      CSMWarning()
      {
      }
      CSMWarning(
          const WarningType& aWarningType,
          const std::string& aMessage,
          const std::string& aFunction)
      {
          setCSMWarning( aWarningType, aMessage, aFunction );
      }
      WarningType         getWarning()   { return theWarning; }
      const std::string& getMessage() { return theMessage; }
      const std::string& getFunction() { return theFunction; }
      void setCSMWarning(
          const WarningType& aWarningType,
          const std::string& aMessage,
          const std::string& aFunction)
        {
            theWarning = aWarningType;
            theMessage = aMessage;
            theFunction = aFunction;
        }
   private:
      WarningType theWarning;
      //> enumeration of the warning (for application control),
      //<
      std::string theMessage;
      //> string describing the warning.
      //<
      std::string theFunction;
      //> string identifying the function in which the warning occurred.
      //<
};
#endif // __CSMWARNING_H

