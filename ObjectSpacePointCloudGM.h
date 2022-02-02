
//#############################################################################
//
//    FILENAME:          ObjectSpacePointCloudGM.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract class that is to provide a common interface from
//    which CSM point cloud geometric models that operate in non ECEF
//    coordinate systems will inherit.  It is derived from the
//    GeometricModel class.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     31-Dec-2021   EJR    Initial version.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_OBJECT_POINTCLOUD_GM_H
#define __CSM_OBJECT_POINTCLOUD_GM_H

#include "csm.h"
#include "Error.h"
#include "GeometricModel.h"
#include "ObjectSpace.h"
#include "csmPointCloud.h"
#define CSM_OSPC_FAMILY "ObjectSpacePointCloud"

namespace csm {

class CorrelationModel;

class CSM_EXPORT_API ObjectSpacePointCloudGM : public GeometricModel {
public:
    ObjectSpacePointCloudGM();
    virtual ~ObjectSpacePointCloudGM() { }

    virtual std::string getFamily() const;
    //> This method returns the Family ID for the current model.
    //<

    virtual Version getVersion() const = 0;
    //> get the protected data member that defines the specifics
    // of the LSR object space being used by the model.
    //< 
        
    //---
    // Model-space description
    //---
    virtual ModelCoordProperties getModelCoordinateProperties() const = 0;
    //> This method returns a structure containing human-readable
    //  descriptions of the model-space coordinate system used by this
    //  sensor model.  See the definition of ModelCoordProperties for an
    //  example of how it might be initialized.
    //<

    // replace Geometric versions which are ecef-based
    virtual ObjectSpaceCoordinate getObjectSpaceReferencePoint() const = 0;
    //> This method returns the ground point indicating the general
    //  location of the image.
    //<

    virtual void setObjectSpaceReferencePoint(const ObjectSpaceCoordinate& groundPt) = 0;
    //> This method sets the ground point indicating the general location
    //  of the image.
    //<

    //---
    // Core Transformations
    //---
    virtual ModelCoord objectSpaceToModel(const ObjectSpaceCoordinate& groundPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given groundPt (x,y,z in meters) to a
    //  returned model coordinate (m0,m1,m2 in the model's coordinate
    //  space).
    //
    //  Iterative algorithms will use desiredPrecision, in meters, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ModelCoordCovar objectSpaceToModel(const ObjectSpaceCoordinateCovar& groundPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given groundPt (x,y,z in meters and
    //  corresponding 3x3 covariance in meters squared) to a returned
    //  model coordinate with covariance (m0,m1,m2 in the model's
    //  coordinate space and corresponding 3x3 covariance).
    //
    //  Iterative algorithms will use desiredPrecision, in meters, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ObjectSpaceCoordinate modelToObjectSpace(const ModelCoord& modelPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given modelPt (m0,m1,m2 in model
    //  coordinates) to a returned ground coordinate (x,y,z in meters).
    //
    //  Iterative algorithms will use desiredPrecision, in meters, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual ObjectSpaceCoordinateCovar modelToObjectSpace(const ModelCoordCovar& modelPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This method converts the given modelPt (m0,m1,m2 in model
    //  coordinates) and corresponding 3x3 covariance to a returned ground
    //  coordinate with covariance (x,y,z in meters and corresponding
    //  3x3 covariance in meters squared).
    //
    //  Iterative algorithms will use desiredPrecision, in meters, as the
    //  convergence criterion, otherwise it will be ignored.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the actual precision, in meters, achieved by iterative
    //  algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    //---
    // Model bounds
    //---
    virtual ModelBounds getValidModelBounds() const = 0;
    //> This method returns an object representing the model-space region
    //  over which the current model is valid.  The ModelBounds object has a
    //  contains() function that may be used to check whether a given model
    //  coordinate lies within this region.
    //
    //  NOTE: Attempting to use the model for transformations involving model
    //  coordinates outside the returned bounds may result in incorrect or
    //  misleading error estimates!
    //<

    //---
    // Uncertainty Propagation
    //---
    struct SensorPartials
    {
        double dM0;
        double dM1;
        double dM2;
    };
    //> This type is used to hold the partial derivatives of model
    //  coordinates m0, m1, and m2, respectively, with respect to a model
    //  parameter.
    //<


    virtual SensorPartials computeSensorPartials(int index,
        const ObjectSpaceCoordinate& groundPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This is one of two overloaded methods.  This method takes only
    //  the necessary inputs.  Some efficiency may be obtained by using the
    //  other method.  Even more efficiency may be obtained by using the
    //  computeAllSensorPartials method.
    //
    //  This method returns the partial derivatives of m0, m1, and m2 (in
    //  model coordinates) with respect to the model parameter given by
    //  index, at the given groundPt (x,y,z in meters).
    //
    //  Derived model implementations may wish to implement this method by
    //  calling the groundToImage method and passing the resulting image
    //  coordinate to the other computeSensorPartials method.
    //
    //  If a non-NULL achievedPrecision argument is received, it will be
    //  populated with the highest actual precision, in meters, achieved by
    //  iterative algorithms and 0.0 for deterministic algorithms.
    //
    //  If a non-NULL warnings argument is received, it will be populated
    //  as applicable.
    //<

    virtual SensorPartials computeSensorPartials(int index,
        const ModelCoord& modelPt,
        const ObjectSpaceCoordinate& groundPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
    //> This is one of two overloaded methods.  This method takes
    //  an input model coordinate for efficiency.  Even more efficiency may
    //  be obtained by using the computeAllSensorPartials method.
    //
    //  This method returns the partial derivatives of m0, m1, and m2 (in
    //  model coordinates) with respect to the model parameter given by
    //  index, at the given groundPt (x,y,z in meters).
    //
    //  The modelPt, corresponding to the groundPt, is given so that it does
    //  not need to be computed by the method.  Results are undefined if
    //  the modelPt provided does not correspond to the result of calling the
    //  groundToModel method with the given groundPt.
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

    virtual std::vector<SensorPartials> computeAllSensorPartials(const ObjectSpaceCoordinate& groundPt,
        param::Set pSet = param::VALID,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const;
    //> This is one of two overloaded methods.  This method takes only
    //  the necessary inputs.  Some efficiency may be obtained by using the
    //  other method.
    //
    //  This method returns the partial derivatives of m0, m1, and m2 (in
    //  model coordinates) with respect to each of the model parameters at
    //  the given groundPt (x,y,z in meters).  Desired model parameters
    //  are indicated by the given pSet.
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
    //  The value returned is a vector of structures with m0, m1, and m2
    //  partials for one model parameter in each structure.  The indices of
    //  the corresponding model parameters can be found by calling the
    //  getParameterSetIndices method for the given pSet.
    //
    //  Derived models may wish to implement this directly for efficiency,
    //  but an implementation is provided here that calls the
    //  computeSensorPartials method for each desired parameter index.
    //<

    virtual std::vector<SensorPartials> computeAllSensorPartials(const ModelCoord& modelPt,
        const ObjectSpaceCoordinate& groundPt,
        param::Set pSet = param::VALID,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const;
    //> This is one of two overloaded methods.  This method takes
    //  an input image coordinate for efficiency.
    //
    //  This method returns the partial derivatives of m0, m1, and m2 (in
    //  model coordinates) with respect to each of the model parameters at
    //  the given groundPt (x,y,z in meters).  Desired model parameters
    //  are indicated by the given pSet.
    //
    //  The modelPt, corresponding to the groundPt, is given so that it does
    //  not need to be computed by the method.  Results are undefined if
    //  the modelPt provided does not correspond to the result of calling the
    //  groundToModel method with the given groundPt.
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
    //  The value returned is a vector of structures with m0, m1, and m2
    //  partials for one model parameter in each structure.  The indices of
    //  the corresponding model parameters can be found by calling the
    //  getParameterSetIndices method for the given pSet.
    //
    //  Derived models may wish to implement this directly for efficiency,
    //  but an implementation is provided here that calls the
    //  computeSensorPartials method for each desired parameter index.
    //<

    virtual std::vector<double> computeObjectSpacePartials(const ObjectSpaceCoordinate& groundPt) const = 0;
    //> This method returns the partial derivatives of model coordinates m0,
    //  m1, m2 with respect to the given groundPt (x,y,z in meters).
    //
    //  The value returned is a vector with nine elements as follows:
    //
    //-  [0] = partial derivative of m0 with respect to x
    //-  [1] = partial derivative of m0 with respect to y
    //-  [2] = partial derivative of m0 with respect to z
    //-  [3] = partial derivative of m1 with respect to x
    //-  [4] = partial derivative of m1 with respect to y
    //-  [5] = partial derivative of m1 with respect to z
    //-  [6] = partial derivative of m2 with respect to x
    //-  [7] = partial derivative of m2 with respect to y
    //-  [8] = partial derivative of m2 with respect to z
    //<

    virtual const CorrelationModel& getCorrelationModel() const = 0;
    //> This method returns a reference to a correlation model.
    //  The correlation model is used to determine the correlation between
    //  the model parameters of different models of the same type.
    //  It is primarily used for replacement sensor model generation;
    //  most applications will use the getCrossCovarianceMatrix function.
    //<

    inline std::vector<double> getUnmodeledError(const ModelCoord& modelPt) const;
    //> This method returns the 3x3 covariance matrix (in model coordinates)
    //  at the given modelPt for any model error not accounted for by the
    //  model parameters.
    //
    //  The value returned is a vector of nine elements as follows:
    //
    //-  [0] = m0 variance
    //-  [1] = m0/m1 covariance
    //-  [2] = m0/m2 covariance
    //-  [3] = m1/m0 covariance
    //-  [4] = m1 variance
    //-  [5] = m1/m2 covariance
    //-  [6] = m2/m0 covariance
    //-  [7] = m2/m1 covariance
    //-  [8] = m2 variance
    //<

    virtual std::vector<double> getUnmodeledCrossCovariance(const ModelCoord& pt1,
        const ModelCoord& pt2) const = 0;
    //> This method returns the 3x3 cross-covariance matrix (in model
    //  coordinates) between model points pt1 and pt2 for any model error not
    //  accounted for by the model parameters.
    //
    //  The value returned is a vector of nine elements as follows:
    //
    //-  [0] = pt1.m0/pt2.m0 covariance
    //-  [1] = pt1.m0/pt2.m1 covariance
    //-  [2] = pt1.m0/pt2.m2 covariance
    //-  [3] = pt1.m1/pt2.m0 covariance
    //-  [4] = pt1.m1/pt2.m1 covariance
    //-  [5] = pt1.m1/pt2.m2 covariance
    //-  [6] = pt1.m2/pt2.m0 covariance
    //-  [7] = pt1.m2/pt2.m1 covariance
    //-  [8] = pt1.m2/pt2.m2 covariance
    //<
    ObjectSpaceType getObjectSpaceDefinition() const;
    //> get the protected data member that defines the specifics
    // of the LSR object space being used by the model.
    //<
    //
protected:
    ObjectSpaceType m_objectSpaceDefinition;
    void setObjectSpaceDefinition(const ObjectSpaceType& osd);
};

//*****************************************************************************
// PointCloudGM::getUnmodeledError
//*****************************************************************************
inline  std::vector<double> ObjectSpacePointCloudGM::getUnmodeledError(const ModelCoord& modelPt) const
{
    return getUnmodeledCrossCovariance(modelPt, modelPt);
}
    

} // namespace csm

#endif // __CSM_OBJECT_POINTCLOUD_GM_H
