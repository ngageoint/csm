//#############################################################################
//
//    FILENAME:   CSMMisc.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the constants and other definitions used by the CSM.
//
//    LIMITATIONS:       None
//
//                       Date          Author   Comment
//    SOFTWARE HISTORY: 01-Jul-2003    LMT      Initial version.
//
//    NOTES:
//
//#############################################################################
#ifndef __CSMMISC_H
#define __CSMMISC_H
#ifdef _WIN32
# ifdef CSM_LIBRARY
# define CSM_EXPORT_API __declspec(dllexport)
# else
# define CSM_EXPORT_API __declspec(dllimport)
# endif
#else
# define CSM_EXPORT_API
#endif
   // The getVersion() and getCSMVersion() methods should use CURRENT_CSM_VERSION to
   // return the CSM API version that the sensor model/plugin was written to.
   // The CSM 3.00 API is specified by version equal to 3000.
   static const int CURRENT_CSM_VERSION = 3000;
   static const int TEMP_STRING_LENGTH = 2048;
   static const int MAX_NAME_LENGTH = 40;
   static const int MAX_FUNCTION_NAME_LENGTH = 80;
   static const int MAX_MESSAGE_LENGTH = 512;
class CSM_EXPORT_API CSMMisc
{
   public:
//--------------------------------------------------------------------------
// Enumeratons
//--------------------------------------------------------------------------
   enum Param_CharType
{       NONE,
       FICTITIOUS,
       REAL,
       EXACT    };
//>
// This enumeration lists the possible parameter or characteristic
//  types as follows.
//
//  NONE       - Parameter value has not yet been initialized.
//  FICTITIOUS - Parameter value has been calculated by resection
//               or other means.
//  REAL       - Parameter value has been measured or read from
//               support data.
//  EXACT      - Parameter value has been specified and is assumed to
//               have no uncertainty.
//<
};
#endif

