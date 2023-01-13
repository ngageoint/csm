
//#############################################################################
//
//    FILENAME:          ObjectSpaceRasterGM.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract class that is to provide a common interface from
//    which CSM raster geometric models that operate in non ECEF
//    coordinate systems will inherit.  It is derived from the
//    GeometricModel class.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     31-SEP 23   EJR    Initial version.
//     31-Sep-2023   EJR    CSM 4.0. Replace ECEF with ObjectSpace.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_OBJECTRASTERGM_H
#define __CSM_OBJECTRASTERGM_H

#include "csm.h"
#include "ProjectionParameters.h"
#include "Error.h"
#include "GeometricModel.h"
#include "CoordinateReferenceSystem.h"
#include "ObjectSpace.h"
#define CSM_RASTER_FAMILY "Raster"

namespace csm
{
class CorrelationModel;

class CSM_EXPORT_API ObjectSpaceRasterGM : public GeometricModel
{
public:
    ObjectSpaceRasterGM();
    //> 
    // default ctor does nothing
    //<

    virtual ~ObjectSpaceRasterGM() {};
    //>
    //  need a desctructor realization so that subclass destructors have
    //< something to call when they are destroyed.

    virtual CoordinateReferenceSystem getCoordinateReferenceSystem() const = 0;
    //> get the protected data member that defines which
    //  object space being used by the model.
    //<

    std::string getFamily()const;
    //> This method returns the Family ID for the current model.
    //<

    virtual Version getVersion() const = 0;
    //> This method returns the version of the model code.  The Version
    //  object can be compared to other Version objects with its comparison
    //  operators.  Not to be confused with the CSM API version.
    //<
    
    // these two methods supplement the methods in GeometricModel which work
    // in ECEF space.
    virtual ObjectSpaceCoord getReferencePoint() const = 0;
    //> This method returns the object space point indicating the general
    //  location of the image.
    //<

    virtual void setReferencePoint(const ObjectSpaceCoord& objectSpacePt) = 0;
    //> This method sets the object space point indicating the general location
    //  of the image.
    //<
    //---
    // Core Photogrammetry
    //---
    virtual ImageCoord objectSpaceToImage(const ObjectSpaceCoord& objectSpacePt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given objectSpacePt (x,y,z in Object Space meters) to a
    //  returned image coordinate (line, sample in full image space pixels).
    //
    //  Iterative algorithms will use desiredPrecision, in pixels, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in pixels, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ImageCoordCovar objectSpaceToImage(
        const ObjectSpaceCoordCovar & objectSpacePt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given objectSpacePt (x,y,z in meters and
    //  corresponding 3x3 covariance in meters squared) to a returned
    //  image coordinate with covariance (line, sample in full image space
    //  pixels and corresponding 2x2 covariance in pixels squared).
    //
    //  Iterative algorithms will use desiredPrecision, in pixels, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in pixels, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ObjectSpaceCoord imageToObjectSpace(
        const ImageCoord& imagePt,
        const ProjectionParameters &geometry,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given imagePt (line,sample in full image
    //  space pixels) and given projection parameters to a returned
    //  object space coordinate (x,y,z in Object Space meters).
    //
    //  Iterative algorithms will use desiredPrecision, in pixels, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If ProjectionParameters pointer *geometry is NULL, then the sensor model will
    //  use the last non-null passed value. If it is NULL and this is the first call to
    //  imageToObjectSpace, then a csm::Error::ErrorType::INVALID_USE exception is thrown.
    // 
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in pixels, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ObjectSpaceCoordCovar imageToObjectSpace(
        const ImageCoordCovar& imagePt,
        const ProjectionParametersCovar &geometry,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given imagePt (line, sample in full image
    //  space pixels and corresponding 2x2 covariance in pixels squared)
    //  and given projetion parameters with covariances to a returned object space
    //  coordinate with covariance (x,y,z in Object Space meters and corresponding
    //  3x3 covariance in Object Space meters squared).
    //
    //  Iterative algorithms will use desiredPrecision, in pixels, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If ProjectionParameters pointer *geometry is NULL, then the sensor model will
    //  use the last non-null passed value. If it is NULL and this is the first call to
    //  imageToObjectSpace, then a csm::Error::ErrorType::INVALID_USE exception is thrown.
    // 
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in pixels, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ObjectSpaceLocus imageToProximateImagingLocus(
        const ImageCoord& imagePt,
        const ObjectSpaceCoord& objectSpacePt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method, for the given imagePt (line, sample in full image space
    //  pixels), returns the position and direction of the imaging locus
    //  nearest the given objectSpacePt (x,y,z in Object Space meters).
    //
    //  Note that there are two opposite directions possible.  Both are
    //  valid, so either can be returned; the calling application can convert
    //  to the other as necessary.
    //
    //  Iterative algorithms will use desiredPrecision, in meters, as the
    //  convergence criterion for the locus position, otherwise it will be
    //  ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ObjectSpaceLocus imageToRemoteImagingLocus(
        const ImageCoord& imagePt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method, for the given imagePt (line, sample in full image space
    //  pixels), returns the position and direction of the imaging locus
    //  at the sensor.
    //
    //  Note that there are two opposite directions possible.  Both are
    //  valid, so either can be returned; the calling application can convert
    //  to the other as necessary.
    //
    //  Iterative algorithms will use desiredPrecision, in meters, as the
    //  convergence criterion for the locus position, otherwise it will be
    //  ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //
    //  Notes:
    //
    //  The remote imaging locus is only well-defined for optical sensors.
    //  It is undefined for SAR sensors and might not be available for
    //  polynomial and other non-physical models.  The
    //  imageToProximateImagingLocus method should be used instead where
    //  possible.
    //<

    //---
    // Monoscopic Mensuration
    //---
    virtual ImageCoord getImageStart() const = 0;
    //> This method returns the starting coordinate (line, sample in full
    //  image space pixels) for the imaging operation.  Typically (0,0).
    //<

    virtual ImageVector getImageSize() const = 0;
    //> This method returns the number of lines and samples in full image
    //  space pixels for the imaging operation.
    //
    //  Note that the model might not be valid over the entire imaging
    //  operation.  Use getValidImageRange() to get the valid range of image
    //  coordinates.
    //<
    using ImageCoordPair = std::pair<ImageCoord, ImageCoord>;
    virtual ImageCoordPair getValidImageRange() const = 0;
    //> This method returns the minimum and maximum image coordinates
    //  (line, sample in full image space pixels), respectively, over which
    //  the current model is valid.  The image coordinates define opposite
    //  corners of a rectangle whose sides are parallel to the line and
    //  sample axes.
    //
    //  The valid image range does not always match the full image
    //  coverage as returned by the getImageStart and getImageSize methods.
    //
    //  Used in conjunction with the getValidHeightRange method, it is
    //  possible to determine the full range of ground coordinates over which
    //  the model is valid.
    //<

    virtual std::pair<double, double> getValidRangeRange() const = 0;
    //> This method returns the minimum and maximum range (in meters
    //  relative to the sensor position), respectively, over which the model is
    //  valid.  
    //
    //  If there are no limits defined for the model, (-99999.0,99999.0)
    //  will be returned.
    //<

    virtual ObjectSpaceVector getIlluminationDirection(const ObjectSpaceCoord& objectSpacePt) const = 0;
    //> This method returns a vector defining the direction of
    //  illumination at the given objectSpacePt (x,y,z in Object Space meters).
    //  Note that there are two opposite directions possible.  Both are
    //  valid, so either can be returned; the calling application can convert
    //  to the other as necessary.
    //<

    //---
    // Time and Trajectory
    //---
    virtual double getImageTime(const ImageCoord& imagePt) const = 0;
    //> This method returns the time in seconds at which the pixel at the
    //  given imagePt (line, sample in full image space pixels) was captured
    //
    //  The time provided is relative to the reference date and time given
    //  by the Model::getReferenceDateAndTime method.
    //<

    virtual ObjectSpaceCoord getSensorPosition(const ImageCoord& imagePt) const = 0;
    //> This method returns the position of the physical sensor
    // (x,y,z in Object Space meters) when the pixel at the given imagePt
    // (line, sample in full image space pixels) was captured.
    //
    //<

    virtual ObjectSpaceCoord getSensorPosition(double time) const = 0;
    //> This method returns the position of the physical sensor
    //  (x,y,z Object Space meters) at the given time relative to the reference date
    //  and time given by the Model::getReferenceDateAndTime method.
    //<

    virtual ObjectSpaceVector getSensorVelocity(const ImageCoord& imagePt) const = 0;
    //> This method returns the velocity of the physical sensor
    // (x,y,z in Object Space meters per second) when the pixel at the given imagePt
    // (line, sample in full image space pixels) was captured.
    //<

    virtual ObjectSpaceVector getSensorVelocity(double time) const = 0;
    //> This method returns the velocity of the physical sensor
    //  (x,y,z in Object Space meters per second ) at the given time relative to the
    //  reference date and time given by the Model::getReferenceDateAndTime
    //  method.
    //<

/// 
/// *******************************************************************************
    //---
    // Uncertainty Propagation
    //---
    typedef std::pair<double,double> SensorPartials;
    //> This type is used to hold the partial derivatives of line and
    //  sample, respectively, with respect to a model parameter.
    //  The units are pixels per the model parameter units.
    //<

    virtual SensorPartials computeSensorPartials(
        int index,
        const ObjectSpaceCoord& objectSpacePt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This is one of two overloaded methods.  This method takes only
    //  the necessary inputs.  Some effieciency can be obtained by using the
    //  other method.  Even more efficiency can be obtained by using the
    //  computeAllSensorPartials method.
    //
    //  This method returns the partial derivatives of line and sample
    //  (in pixels per the applicable model parameter units), respectively,
    //  with respect to the model parameter given by index at the given
    //  objectSpacePt (x,y,z in Object Space meters).
    //
    //  Derived model implementations may wish to implement this method by
    //  calling the groundToImage method and passing the resulting image
    //  coordinate to the other computeSensorPartials method.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the highest actual precision, in meters, achieved by
    //  iterative algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual SensorPartials computeSensorPartials(
        int index,
        const ImageCoord& imagePt,
        const ObjectSpaceCoord& objectSpacePt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This is one of two overloaded methods.  This method takes
    //  an input image coordinate for efficiency.  Even more efficiency can
    //  be obtained by using the computeAllSensorPartials method.
    //
    //  This method returns the partial derivatives of line and sample
    //  (in pixels per the applicable model parameter units), respectively,
    //  with respect to the model parameter given by index at the given
    //  objectSpacePt (x,y,z in Object Space meters).
    //
    //  The imagePt, corresponding to the objectSpacePt, is given so that it does
    //  not need to be computed by the method.  Results are unpredictable if
    //  the imagePt provided does not correspond to the result of calling the
    //  groundToImage method with the given objectSpacePt.
    //
    //  Implementations with iterative algorithms (typically ground-to-image
    //  calls) will use desiredPrecision, in meters, as the convergence
    //  criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the highest actual precision, in meters, achieved by
    //  iterative algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual std::vector<ObjectSpaceRasterGM::SensorPartials> computeAllSensorPartials(
        const ObjectSpaceCoord& objectSpacePt,
        param::Set pSet = param::VALID,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This is one of two overloaded methods.  This method takes only
    //  the necessary inputs.  Some effieciency can be obtained by using the
    //  other method.
    //
    //  This method returns the partial derivatives of line and sample
    //  (in pixels per the applicable model parameter units), respectively,
    //  with respect to to each of the desired model parameters at the given
    //  objectSpacePt (x,y,z in Object Space meters).  Desired model parameters are
    //  indicated by the given pSet.
    //
    //  Implementations with iterative algorithms (typically ground-to-image
    //  calls) will use desiredPrecision, in meters, as the convergence
    //  criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the highest actual precision, in meters, achieved by
    //  iterative algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //
    //  The value returned is a vector of pairs with line and sample partials
    //  for one model parameter in each pair.  The indices of the
    //  corresponding model parameters can be found by calling the
    //  getParameterSetIndices method for the given pSet.
    //
    //  Derived models may wish to implement this directly for efficiency,
    //  but an implementation is provided here that calls the
    //  computeSensorPartials method for each desired parameter index.
    //<

    virtual std::vector<ObjectSpaceRasterGM::SensorPartials> computeAllSensorPartials(
        const ImageCoord& imagePt,
        const ObjectSpaceCoord& objectSpacePt,
        param::Set pSet = param::VALID,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This is one of two overloaded methods.  This method takes
    //  an input image coordinate for efficiency.
    //
    //  This method returns the partial derivatives of line and sample
    //  (in pixels per the applicable model parameter units), respectively,
    //  with respect to to each of the desired model parameters at the given
    //  objectSpacePt (x,y,z in Object Space meters).  Desired model parameters are
    //  indicated by the given pSet.
    //
    //  The imagePt, corresponding to the objectSpacePt, is given so that it does
    //  not need to be computed by the method.  Results are unpredictable if
    //  the imagePt provided does not correspond to the result of calling the
    //  groundToImage method with the given objectSpacePt.
    //
    //  Implementations with iterative algorithms (typically ground-to-image
    //  calls) will use desiredPrecision, in meters, as the convergence
    //  criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the highest actual precision, in meters, achieved by
    //  iterative algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //
    //  The value returned is a vector of pairs with line and sample partials
    //  for one model parameter in each pair.  The indices of the
    //  corresponding model parameters can be found by calling the
    //  getParameterSetIndices method for the given pSet.
    //
    //  Derived models may wish to implement this directly for efficiency,
    //  but an implementation is provided here that calls the
    //  computeSensorPartials method for each desired parameter index.
    //<

    virtual std::vector<double> computeObjectSpacePartials(
        const ObjectSpaceCoord& objectSpacePt) const = 0;
    //> This method returns the partial derivatives of line and sample
    //  (in pixels per meter) with respect to the given objectSpacePt
    //  (x,y,z in Object Space meters).
    //
    //  The value returned is a vector with six elements as follows:
    //
    //-  [0] = line wrt x
    //-  [1] = line wrt y
    //-  [2] = line wrt z
    //-  [3] = sample wrt x
    //-  [4] = sample wrt y
    //-  [5] = sample wrt z
    //<

    virtual const CorrelationModel& getCorrelationModel() const = 0;
    //> This method returns a reference to a CorrelationModel.
    //  The CorrelationModel is used to determine the correlation between
    //  the model parameters of different models of the same type.
    //  These correlations are used to establish the "a priori" cross-covariance
    //  between images. While some applications (such as generation of a 
    //  replacement sensor model) may wish to call this method directly,
    //  it is reccommended that the inherited method 
    //  GeometricModel::getCrossCovarianceMatrix() be called instead.
    //<

    inline std::vector<double> getUnmodeledError(const ImageCoord& imagePt) const
    {
        return getUnmodeledCrossCovariance(imagePt, imagePt);
    }
    //> This method returns the 2x2 line and sample covariance (in pixels
    //  squared) at the given imagePt for any model error not accounted for
    //  by the model parameters.
    //
    //  The value returned is a vector of four elements as follows:
    //
    //-  [0] = line variance
    //-  [1] = line/sample covariance
    //-  [2] = sample/line covariance
    //-  [3] = sample variance
    //<

    virtual std::vector<double> getUnmodeledCrossCovariance(
        const ImageCoord& pt1,
        const ImageCoord& pt2) const = 0;
    //> This method returns the 2x2 line and sample cross covariance
    //  (in pixels squared) between the given imagePt1 and imagePt2 for any
    //  model error not accounted for by the model parameters.  The error is
    //  reported as the four terms of a 2x2 matrix, returned as a 4 element
    //  vector.
    //< };

};

} // namespace csm

#endif // __CSM_OBJECTRASTERGM_H
