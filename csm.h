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
//     31-Oct-2012   SCM      Moved common sensor type and mode defines here.
//     29-Nov-2012   JPK      Added Parameter and SharingCriteria structs and
//                            ParamSet struct.
//     06-Dec-2012   JPK      Renamed ParamSet and ParamType to Set and Type
//                            and put them in new namespace "param".
//                            Implemented additional constructors for
//                            ImageCoordCovar and EcefCoordCovar and added
//                            new struct EcefLocus.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_CSM_H
#define __CSM_CSM_H

#include <vector>
#include <string>

#ifdef _WIN32
# ifdef CSM_LIBRARY
#  define CSM_EXPORT_API __declspec(dllexport)
# else
#  define CSM_EXPORT_API __declspec(dllimport)
# endif
#elif LINUX_BUILD
# define CSM_EXPORT_API __attribute__ ((visibility("default")))
#else
#  define CSM_EXPORT_API
#endif

// The getVersion() and getCsmVersion() methods should use CURRENT_CSM_VERSION to
// return the CSM API version that the sensor model/plugin was written to.
#define CURRENT_CSM_VERSION csm::Version(3, 0, 1);

// common definition for an unknown name,type,node,etc.
#define CSM_UNKNOWN "UNKNOWN"

// common sensor types returned from csm::Model::getSensorType()
#define CSM_SENSOR_TYPE_UNKNOWN       CSM_UNKNOWN
#define CSM_SENSOR_TYPE_EO            "EO"
#define CSM_SENSOR_TYPE_IR            "IR"
#define CSM_SENSOR_TYPE_MWIR          "MWIR"
#define CSM_SENSOR_TYPE_LWIR          "LWIR"
#define CSM_SENSOR_TYPE_SAR           "SAR"
#define CSM_SENSOR_TYPE_EOIRSC        "EO_IR_SPECIAL_CASE"

// common sensor modes returned from csm::Model::getSensorMode()
#define CSM_SENSOR_MODE_UNKNOWN       CSM_UNKNOWN
#define CSM_SENSOR_MODE_FRAME         "FRAME"
#define CSM_SENSOR_MODE_PULSE         "PULSE"
#define CSM_SENSOR_MODE_PB            "PUSHBROOM"
#define CSM_SENSOR_MODE_WB            "WHISKBROOM"
#define CSM_SENSOR_MODE_SPOT          "SPOT"
#define CSM_SENSOR_MODE_STRIP         "STRIP"
#define CSM_SENSOR_MODE_SCAN          "SCAN"
#define CSM_SENSOR_MODE_VIDEO         "VIDEO"
#define CSM_SENSOR_MODE_BODY_POINTING "BODY_POINTING"

namespace csm
{
   namespace param
   {
      enum Type
      //>
      // This enumeration lists the possible parameter or characteristic
      //  types as follows.
      //
      //  NONE       - Parameter value has not yet been initialized.
      //  FICTITIOUS - Parameter value has been calculated by resection
      //               or other means.
      //  REAL       - Parameter value has been measured or read from
      //               support data.
      //  EXACT      - Parameter value has been specified and is not
      //               to be adjusted, but may contribute to error
      //               propagation.
      {
         NONE = 0 ,
         FICTITIOUS,
         REAL,
         EXACT
      };
      //<

      enum Set
      //>
      // This enumeration lists the set of parameters a user may be interested
      // in exploiting, and membership in one of these sets is determined by
      //  parameter type.
      //  VALID      - Parameters of type NONE are excluded.
      //               All others are included,
      //  ADJUSTABLE - Only REAL or FICTICIOUS parameters are included
      //  FIXED      - Only EXACT parameters are included.
      {
         VALID = 0,
         ADJUSTABLE,
         FIXED
      };
      //<
   }

   //***
   // STRUCT: SharingCriteria
   //> This structure stores information regarding whether or not parameters
   // can be "shared", based on common characteristics.
   //<
   //***
   struct SharingCriteria
   {
   public:
      bool      matchesName;
      bool      matchesSensorID;
      bool      matchesPlatformID;
      bool      matchesCollectionID;
      bool      matchesTrajectoryID;
      bool      matchesDateTime;
      double    maxTimeDelta;

      SharingCriteria()
         :
            matchesName         (false),
            matchesSensorID     (false),
            matchesPlatformID   (false),
            matchesCollectionID (false),
            matchesTrajectoryID (false),
            matchesDateTime     (false),
            maxTimeDelta        (0.0)
      {}

      SharingCriteria(bool   byName,
                      bool   bySensorID,
                      bool   byPlatformID,
                      bool   byCollectionID,
                      bool   byTrajectoryID,
                      bool   byDateTime,
                      double maxDelta)
         :
           matchesName         (byName),
           matchesSensorID     (bySensorID),
           matchesPlatformID   (byPlatformID),
           matchesCollectionID (byCollectionID),
           matchesTrajectoryID (byTrajectoryID),
           matchesDateTime     (byDateTime),
           maxTimeDelta        (maxDelta)
      {}
   };

   //***
   // STRUCT: ImageCoord
   //> The ImageCoord structure represents a 2 dimensional point in image space.
   //  Usually, it represents an abolute point location.
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
         //> Default Constructor
         //<
      ImageCoordCovar(double aLine, double aSamp)
         : ImageCoord(aLine, aSamp) { memset(covariance, 0, sizeof(covariance)); }
         //> Constructor taking point only (all covariance entries are 0)
         //<
      ImageCoordCovar(double aLine, double aSamp, double aCovar[4])
         : ImageCoord(aLine, aSamp) { memcpy(covariance, aCovar, sizeof(covariance)); }
         //> Constructor taking point and a 4 element array of doubles for
         //  covariance.  Note that no check is made to insure symmetry of
         //  covariance matrix.
         //<
      ImageCoordCovar(double aLine,   double aSamp,
                      double aCovar00,double aCovar01,
                                      double aCovar11)
         :
            ImageCoord(aLine, aSamp)
      {
         covariance[0] = aCovar00;
         covariance[1] = covariance[2] = aCovar01;
         covariance[3] = aCovar11;
      }
         //> Constructor taking point and upper triangular portion of
         //  covariance matrix.  Elements are assigned to covariance matrix
         //  assuming symmetry.
         //<

      //***
      //> The 2 x 2 covariance matrix for the image coordinate is stored in a one dimensional
      // array.  Elements can either be accessed directly from that array, or via a
      // two dimensional lookup using the covar2d() methods below.  Note that using the
      // "non-const" method allows assignment as well as retrieval.
      // Ex.   To look up the variance in the sample direction of a coordinate "coord" and
      // assign it to a variable A, the syntax would be:
      //
      // Using one dimensional access : double A = coord.covariance[3];
      // Using two dimensional access : double A = coord.covar2d(1,1);
      //
      // Similarly, to assign a value of 0.5 as the variance in the sample direction
      // for "coord", the syntax would be:
      //
      // Using one dimensional access : coord.covariance[3] = 0.5;
      // Using two dimensional access : coord.covar2d(1,1) = 0.5;
      //<
      //***
      double covariance[4];
      double  covar2d(unsigned int l, unsigned int s) const { return covariance[2*l + s]; }
      double& covar2d(unsigned int l, unsigned int s)       { return covariance[2*l + s]; }
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
         //> Default Constructor
         //<
      EcefCoordCovar(double aX, double aY, double aZ)
         : EcefCoord(aX, aY, aZ) { memset(covariance, 0, sizeof(covariance)); }
         //> Constructor taking point only (all covariance entries are 0)
         //<
      EcefCoordCovar(double aX, double aY, double aZ, double aCovar[9])
         : EcefCoord(aX, aY, aZ) { memcpy(covariance, aCovar, sizeof(covariance)); }
         //> Constructor taking point and a 9 element array of doubles for
         //  covariance.  Note that no check is made to insure symmetry of
         //  covariance matrix.
         //<
      EcefCoordCovar(double aX,       double aY,       double aZ,
                     double aCovar00, double aCovar01, double aCovar02,
                                      double aCovar11, double aCovar12,
                                                       double aCovar22)
         :
            EcefCoord(aX, aY, aZ)
      {
         covariance[0] = aCovar00;
         covariance[1] = covariance[3] = aCovar01;
         covariance[2] = covariance[6] = aCovar02;
         covariance[4] = aCovar11;
         covariance[5] = covariance[7] = aCovar12;
         covariance[8] = aCovar22;
      }
         //> Constructor taking point and upper triangular portion of
         //  covariance matrix.  Elements are assigned to covariance matrix
         //  assuming symmetry.
         //<

      //***
      //> The 3 x 3 covariance matrix for the ECEF coordinate is stored in a one dimensional
      // array.  Elements can either be accessed directly from that array, or via a
      // two dimensional lookup using the covar2d() methods below.  Note that using the
      // "non-const" method allows assignment as well as retrieval.
      // Ex.   To look up the variance in the Z direction of a coordinate "coord" and
      // assign it to a variable A, the syntax would be:
      //
      // Using one dimensional access : double A = coord.covariance[8];
      // Using two dimensional access : double A = coord.covar2d(2,2);
      //
      // Similarly, to assign a value of 9.0 as the variance in the Z direction
      // for "coord", the syntax would be:
      //
      // Using one dimensional access : coord.covariance[8] = 9.0;
      // Using two dimensional access : coord.covar2d(2,2) = 9.0;
      //<
      //***
      double covariance[9];
      double  covar2d(unsigned int l, unsigned int s) const { return covariance[3*l + s]; }
      double& covar2d(unsigned int l, unsigned int s)       { return covariance[3*l + s]; }
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

   //***
   // STRUCT: EcefLocus
   //> The EcefLocus structure contains a point and a direction in Earth
   //  Centered Earth Fixed space.
   //<
   //***
   struct EcefLocus
   {
   public:
      EcefCoord  point;
      EcefVector direction;

      EcefLocus() : point() , direction() {}

      EcefLocus(const EcefCoord& argPoint,
                const EcefVector& argDirection)
         :
            point     (argPoint),
            direction (argDirection)
      {}

      EcefLocus(double ptX , double ptY , double ptZ,
                double dirX, double dirY, double dirZ)
         :
            point    (ptX, ptY, ptZ),
            direction(dirX,dirY,dirZ)
      {}
   };

} // namespace csm

#endif
