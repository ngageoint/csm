//#############################################################################
//
//    FILENAME:   csm.h
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
//     30-Oct-2012   SCM      Changed covariances from std::vectors to arrays.
//                            Made the covariances public.
//     30-Oct-2012   SCM      Renamed to csm.h
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_CSM_H
#define __CSM_CSM_H

#include <vector>

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

// The getVersion() and getCSMVersion() methods should use CURRENT_CSM_VERSION to
// return the CSM API version that the sensor model/plugin was written to.
#define CURRENT_CSM_VERSION csm::Version(3, 0);
   
namespace csm
{
   enum ParamType
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
   {
      NONE,
      FICTITIOUS,
      REAL,
      EXACT
   };
   //<

   //***
   // STRUCT: ImageCoord
   //> The ImageCoord structure represents a 2 dimensional point in image space.
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
   // STRUCT: ImageCoordCovar
   //> The ImageCoordCovar structure is an image coordinate with covariance
   //  information.
   //
   //  The covariance vector is always 4 elements.  It can be accessed either
   //  through the one dimensional covar() method, or the two dimensional
   //  covar() method.
   //<
   //***
   struct ImageCoordCovar : public ImageCoord
   {
   public:
      ImageCoordCovar() : ImageCoord() { memset(covariance, 0, sizeof(covariance)); }
      ImageCoordCovar(double aLine, double aSamp)
         : ImageCoord(aLine, aSamp) { memset(covariance, 0, sizeof(covariance)); }
      ImageCoordCovar(double aLine, double aSamp, double aCovar[4])
         : ImageCoord(aLine, aSamp) { memcpy(covariance, aCovar, sizeof(covariance)); }

      double  covar2d(unsigned int l, unsigned int s) const { return covariance[2*l + s]; }
      double& covar2d(unsigned int l, unsigned int s)       { return covariance[2*l + s]; }

      double covariance[4];
   };

   //***
   // STRUCT: ImageVector
   //> The ImageCoord structure represents a 2 dimensional vector in image
   //  space. This can sometimes be used to represent the size of an image.
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
   //> The EcefCoord structure represents a 3 dimensional location in Earth
   //  Centered Earth Fixed space.  Usually, it will represent an abolute
   //  point, but some uses of this structure in the SensorModel class call for
   //  it to represent an ECEF location vector or an ECEF velocity vector.
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
   // STRUCT: EcefCoordCovar
   //> The EcefCoordCovar structure is an ECEF coordinate with covariance
   //  information.
   //
   //  The covariance vector is always 9 elements.  It can be accessed either
   //  through the one dimensional covar() method, or the two dimensional
   //  covar() method.
   //<
   //***
   struct EcefCoordCovar : public EcefCoord
   {
   public:
      EcefCoordCovar() : EcefCoord() { memset(covariance, 0, sizeof(covariance)); }
      EcefCoordCovar(double aX, double aY, double aZ)
         : EcefCoord(aX, aY, aZ) { memset(covariance, 0, sizeof(covariance)); }
      EcefCoordCovar(double aX, double aY, double aZ, double aCovar[9])
         : EcefCoord(aX, aY, aZ) { memcpy(covariance, aCovar, sizeof(covariance)); }

      double  covar2d(unsigned int l, unsigned int s) const { return covariance[3*l + s]; }
      double& covar2d(unsigned int l, unsigned int s)       { return covariance[3*l + s]; }

      double covariance[9];
   };

   //***
   // STRUCT: EcefVector
   //> The EcefVector structure represents a 3 dimensional vector in Earth
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

