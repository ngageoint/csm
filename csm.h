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
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     01-Jul-2003   LMT      Initial version.
//     02-Mar-2012   SCM      Added csm namespace.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSMMISC_H
#define __CSMMISC_H

#ifdef _WIN32
# ifdef CSM_LIBRARY
#  define CSM_EXPORT_API __declspec(dllexport)
# else
#  define CSM_EXPORT_API __declspec(dllimport)
# endif
#elif LINUX_BUILD
# define CSM_EXPORT_API __atribute__ ((visibility("default")))
#else
#  define CSM_EXPORT_API
#endif

namespace csm
{
   // The getVersion() and getCSMVersion() methods should use CURRENT_CSM_VERSION to
   // return the CSM API version that the sensor model/plugin was written to.
   // The CSM 3.00 API is specified by version equal to 3000.
   enum
   {
      CURRENT_CSM_VERSION = 3000,
      TEMP_STRING_LENGTH = 2048,
      MAX_NAME_LENGTH = 40,
      MAX_FUNCTION_NAME_LENGTH = 80,
      MAX_MESSAGE_LENGTH = 512
   }

   enum ParamType
   {
      NONE,
      FICTITIOUS,
      REAL,
      EXACT
   };
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

   //***
   // STRUCT: ImageCoord
   //> The ImageCoord class represents a 2 dimensional point in image space.
   //  Usually, it represents an abolute point location, but some uses on the
   //  SensorModel interface use it as a size (location vector).
   //<
   //***
   struct ImageCoord
   {
   public:
      double line;
      double samp;

      ImageCoord() : line(0.0), samp(0.0) {}
      ImageCoord(double aLine, double aSamp) : line(aLine), samp(aSamp) {}
   };

   //***
   // STRUCT: ImageVector
   //> The ImageCoord class represents a 2 dimensional vector in image space.
   //  This can sometimes be used to represent the size of an image.
   //<
   //***
   struct ImageVector
   {
   public:
      double line;
      double samp;

      ImageVector() : line(0.0), samp(0.0) {}
      ImageVector(double aLine, double aSamp) : line(aLine), samp(aSamp) {}
   };

   //***
   // STRUCT: EcefCoord
   //> The EcefCoord class represents a 3 dimensional location in Earth
   //  Centered Earth Fixed space.  Usually, it will represent an abolute
   //  point, but some uses of this class in the SensorModel class call for it
   //  to represent an ECEF location vector or an ECEF velocity vector.
   //
   //  The units of the doubles are meters when the object is used as a
   //  location, and meters/second when used as a velocity.
   //<
   //***
   struct EcefCoord
   {
   public:
      double x;
      double y;
      double z;

      EcefCoord() : x(0.0), y(0.0), z(0.0) {}
      EcefCoord(double aX, double aY, double aZ) : x(aX), y(aY), z(aZ) {}
   };

   //***
   // STRUCT: EcefVector
   //> The EcefVector class represents a 3 dimensional vector in Earth
   //  Centered Earth Fixed space.  It can represent an ECEF location vector or
   //  an ECEF velocity vector.
   //<
   //***
   struct EcefVector
   {
   public:
      double x;
      double y;
      double z;

      EcefVector() : x(0.0), y(0.0), z(0.0) {}
      EcefVector(double aX, double aY, double aZ) : x(aX), y(aY), z(aZ) {}
   };

} // namespace csm

#endif

