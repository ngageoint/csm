//#####################################################################
//
//    FILENAME:   CSMError.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the error structure used by the CSM.
//
//    LIMITATIONS:       None
//
//                            Date          Author       Comment
//    SOFTWARE HISTORY:   1 June 2004 Kevin Lam        CCB Change
//                       24 June 2005 Len Tomko        CCB Change Added
//                                                     DATA_NOT_AVAILABLE
//                       09 Mar 2010   Don Leonard     CCB Change Deleted
DATA_NOT_AVAILABLE
//                                                                //
***********************
//    NOTES:
//
//#####################################################################
#ifndef __CSMERROR_H
#define __CSMERROR_H
#include <string>
#include "CSMMisc.h"
#ifdef WIN32
#pragma warning( disable : 4291 )
#pragma warning( disable : 4251 )
#endif
class CSM_EXPORT_API CSMError
{
   public:
      //-----------------------------------------------------------
      // Errors
      //-------------------------------------------------------------
      enum ErrorType
      {
         ALGORITHM = 1,
         BOUNDS,
         FILE_READ,
         FILE_WRITE,
         ILLEGAL_MATH_OPERATION,
         INDEX_OUT_OF_RANGE,
         INVALID_SENSOR_MODEL_STATE,
         INVALID_USE,
         ISD_NOT_SUPPORTED,
         MEMORY,
         SENSOR_MODEL_NOT_CONSTRUCTIBLE,
         SENSOR_MODEL_NOT_SUPPORTED,
         STRING_TOO_LONG,
         UNKNOWN_ERROR,
         UNSUPPORTED_FUNCTION,
         UNKNOWN_SUPPORT_DATA
      };
      CSMError()
      {
      }
      CSMError(
         const ErrorType&   aErrorType,
         const std::string& aMessage,
         const std::string& aFunction)
      {
         setCSMError( aErrorType, aMessage, aFunction );
      }
      ErrorType          getError()    { return theError; }
      const std::string& getMessage() { return theMessage; }
      const std::string& getFunction() { return theFunction; }
      void setCSMError(
         const ErrorType&    aErrorType,
         const std::string& aMessage,
         const std::string& aFunction)
      {
         theError    = aErrorType;
         theMessage = aMessage;
         theFunction = aFunction;
      }
   private:
      ErrorType   theError;
      //> enumeration of the error (for application control),
      //<
      std::string theMessage;
      //> string describing the error.
      //<
      std::string theFunction;
      //> string identifying the function in which the error occurred.
      //<
};

#endif // __CSMERROR_H

