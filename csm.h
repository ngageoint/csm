//#############################################################################
//
//    FILENAME:          csm.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for constants and other definitions used in the CSM API.
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
//     17-Dec-2012   BAH      Documentation updates.
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

// The getCsmVersion method should use CURRENT_CSM_VERSION to
// return the CSM API version that the sensor model/plugin was written to.
#define CURRENT_CSM_VERSION csm::Version(3, 0, 1);

// Common definition for an unknown name, type, node,etc.
#define CSM_UNKNOWN "UNKNOWN"

// Common sensor types returned from the csm::Model::getSensorType method.
#define CSM_SENSOR_TYPE_UNKNOWN       CSM_UNKNOWN
#define CSM_SENSOR_TYPE_EO            "EO"
#define CSM_SENSOR_TYPE_IR            "IR"
#define CSM_SENSOR_TYPE_MWIR          "MWIR"
#define CSM_SENSOR_TYPE_LWIR          "LWIR"
#define CSM_SENSOR_TYPE_SAR           "SAR"
#define CSM_SENSOR_TYPE_EOIRSC        "EO_IR_SPECIAL_CASE"

// Common sensor modes returned from the csm::Model::getSensorMode method.
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
      // This enumeration lists the possible model parameter or characteristic
      // types as follows.
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
      // This enumeration lists the set of model parameters that a user may be
      // interested in exploiting.  Membership in one of these sets is
      // determined by model parameter type.
      //
      //  VALID      - Parameters of type NONE are excluded. 
      //               All others are included,
      //  ADJUSTABLE - Only REAL or FICTICIOUS parameters are included.
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
   //> This structure stores information regarding whether or not a model
   //  parameter might be "shared" between models of the same type, based on
   //  common characteristics.
   //<
   //***
   struct SharingCriteria
   {
   public:
      bool      matchesName;
        //> Requires that the models have the same model name as given by
        //  the Model::getModelName method.  Will almost always be set to true.
        //<

      bool      matchesSensorID;
        //> Requires that the models have the same sensor ID as given by
        //  the Model::getSensorIdentifier method.
        //<

      bool      matchesPlatformID;
        //> Requires that the models have the same platform ID as given by
        //  the Model::getPlatformIdentifier method.
        //<

      bool      matchesCollectionID;
        //> Requires that the models have the same collection ID as given by
        //  the Model::getCollectionIdentifier method.
        //<

      bool      matchesTrajectoryID;
        //> Requires that the models have the same trajectory ID as given by
        //  the Model::getTrajectoryIdentifier method.
        //<

      bool      matchesDateTime;
        //> Requires that the models' imaging times must be within a certain
        //  time delta.  It is typically sufficient to compare the times at
        //  the start of the image.
        //<

      double    maxTimeDelta;
        //> Maximum time separation, in seconds, for a model parameter to be
        //  shared when matchesDateTime is true.
        //<

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
   //> This structure represents a two-dimensional image coordinate
   //  (line, sample in pixels).
   //  It typically represents an absolute coordinate.
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
   //> This structure represents an image coordinate with a corresponding
   //  2x2 covariance matrix.
   //
   //  The covariance is stored as an array of four elements that can be
   //  accessed directly or through the two-dimensional covar2d methods.
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
   //> This structure represents a two-dimensional vector in image space.
   //  Units are pixels.  It can be used to represent the size of an image.
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
   //> This structure represents a three-dimensional location (x,y,z in meters)
   //  in the WGS-84 Earth Centered Earth Fixed (ECEF) coordinate system.
   //  It typically represents an absolute coordinate; the EcefVector structure
   //  is used for velocity and direction vectors.
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
   //> This structure represents an ECEF coordinate with a corresponding
   //  3x3 covariance matrix.
   //
   //  The covariance is stored as an array of nine elements that can be
   //  accessed directly or through the two-dimensional covar2d methods.
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
   //> This structure represents a three-dimensional vector in the WGS-84 Earth
   //  Centered Earth Fixed coordinate system.
   //  It can represent an ECEF direction vector (unitless) or
   //  an ECEF velocity vector (in meters per second).
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
   // > This structure contains an ECEF coordinate (in meters) and
   //   an ECEF direction vector (unitless).
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
