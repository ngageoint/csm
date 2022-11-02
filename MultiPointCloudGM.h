//#############################################################################
//
//    FILENAME:          MultiPointCloudGM.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    
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

#ifndef __CSM_MULTI_POINTCLOUDGM_H
#define __CSM_MULTI_POINTCLOUDGM_H

#include "PointCloudGM.h"
#include "csmPointCloud.h"
#include "csmMultiPoint.h"

#define CSM_POINTCLOUD_FAMILY "PointCloud"

namespace csm {

class CorrelationModel;

class CSM_EXPORT_API MultiPointCloudGM : public PointCloudGM {

public:
	virtual ~MultiPointCloudGM() { }
	
    virtual std::string getFamily() const { return ("MULTIPOINT_POINT_CLOUD"); };

    // destructor implementation is needed so there will be something to call when derived
        // classes are destroyed.
    virtual ~MultiPointCloudGM() {};
	   //> This method returns the Family ID for the current model.
	   //<


	virtual MultiModelCoord multiGroundToModel(MultiEcefCoord& groundPts, 
												  double desiredPrecision = 0.001, 
												  MultiDbl *achievedPrecisions = NULL, 
												  std::vector<WarningList> *warnings = NULL) const = 0;
	   //> This method converts the given vector of groundPt (x,y,z in ECEF meters) to a
	   //  returned vector of model coordinates (m0,m1,m2 in the model's coordinate
	   //  space).
	   //
	   //  Iterative algorithms will use desiredPrecision, in meters, as the
	   //  convergence criterion, otherwise it will be ignored.
	   //
	   //  If a non-NULL vector of achievedPrecision arguments are received, it will be
	   //  populated with the actual precisions, in meters, achieved by iterative
	   //  algorithms and 0.0 for deterministic algorithms.
	   //
	   //  If a non-NULL warnings argument is received, it will be populated
	   //  as applicable.
	   //<

   
      virtual std::vector<ModelCoordCovar> multiGroundToModel(MultiEcefCoordCovar& groundPts,
														 double desiredPrecision = 0.001, 
														 MultiDbl *achievedPrecisions = NULL, 
														 std::vector<WarningList> *warnings = NULL) const = 0;
      //> This method converts the given vector of groundPts (x,y,z in ECEF meters and
      //  corresponding 3x3 covariance in ECEF meters squared) to a returned
      //  vector of model coordinates with covariance (m0,m1,m2 in the model's
      //  coordinate space and corresponding 3x3 covariance).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL vector of achievedPrecision arguments is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<
 
   virtual MultiEcefCoord multiModelToGround(MultiModelCoord& modelPts, 
												double desiredPrecision = 0.001, 
												MultiDbl* achievedPrecision = NULL, 
												std::vector<WarningList*> *warnings = NULL) const = 0;
      //> This method converts the given vector of modelPts (m0,m1,m2 in model
      //  coordinates) to a returned vector of ground coordinates (x,y,z in ECEF meters).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL vector of achievedPrecision arguments is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual MultiEcefCoordCovar multiModelToGround(MultiModelCoordCovar & modelPts, 
													 double desiredPrecision = 0.001, 
													 MultiDbl *achievedPrecisions = NULL, 
													 std::vector<WarningList*> *warnings = NULL) const = 0;
      //> This method converts the given vector of modelPts (m0,m1,m2 in model
      //  coordinates) and corresponding 3x3 covariance to a returned vector of ground
      //  coordinates with covariance (x,y,z in ECEF meters and corresponding
      //  3x3 covariance in ECEF meters squared).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL vector of achievedPrecision arguments is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   //---
   // Uncertainty Propagation
   //---
   
      //> This type is used to hold the partial derivatives of model
      //  coordinates m0, m1, and m2, respectively, with respect to a model
      //  parameter.
      //<


   virtual std::vector<csm::PointCloudGM::SensorPartials> multiComputeSensorPartials(int index,
												MultiEcefCoord & groundPts, 
												double desiredPrecision = 0.001, 
												MultiDbl* achievedPrecision = NULL, 
												WarningList* warnings = NULL) const = 0;
      //> 
      // This is the multi-point version of ComputeSensorPartials that takes EcefCoord input.
      //<
   
   virtual std::vector<csm::PointCloudGM::SensorPartials> multiComputeSensorPartials(int index,
												const MultiModelCoord& modelPts, 
												MultiEcefCoord & groundPts, 
												double desiredPrecision = 0.001, 
												MultiDbl * achievedPrecision = NULL, 
												std::vector<WarningList> * warnings = NULL) const = 0;
   //> 
  // This is the multi-point version of ComputeSensorPartials that takes all forms of input
  // ground points for efficiency.
  //<

   std::vector<ModelPartialsVctr> multiComputeAllSensorPartials(const MultiEcefCoord& groundPts,
																param::Set pSet = param::VALID, 
																double desiredPrecision = 0.001, 
																MultiDbl * achievedPrecision = NULL, 
																std::vector<WarningList> * warnings = NULL) const;
   //> 
   // This is the multi-point version of ComputeAllSensorPartials that takes EcefCoord input.
   //<

   virtual std::vector<ModelPartialsVctr> multiComputeAllSensorPartials(const MultiModelCoord& modelPts,
																const std::vector<EcefCoord> & groundPts, 
																param::Set pSet = param::VALID, 
																double desiredPrecision = 0.001, 
																MultiDbl * achievedPrecision = NULL, 
																std::vector<WarningList> * warnings = NULL) const;
   //> 
// This is the multi-point version of ComputeAllSensorPartials that takes all forms of input
// ground points for efficiency.
//<

   virtual MultiDblVctr multiComputeGroundPartials(const MultiEcefCoord& groundPts) const = 0;
      //> This method returns a vector of vectors of partial derivatives of model
      //  coordinates m0, m1, m2 with respect to the given groundPts (x,y,z in ECEF meters).
      //
      //  The inner vector contains the set of 9 partial dervitatives for a given point.
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

   virtual MultiDblVctr multiGetUnmodeledError(const MultiModelCoord& modelPts) const = 0;
      //> This method returns a vector of 3x3 covariance matrices (in model coordinates)
      //  at the given vector of modelPt for any model error not accounted for by the
      //  model parameters.
      //
      //  The inner vector contains the 9 values of the 3x3 covariance matrix for a single point.
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

   virtual MultiDblVctr multiGetUnmodeledCrossCovariance(const ModelCoordPair &modelCoords) const = 0;
      //> This method returns a vector of 3x3 cross-covariance matrix (in model
      //  coordinates) between eaach pair of model points pts1 and pts2 for any model error not
      //  accounted for by the model parameters.
      //
      //  The inner vector contains the 9 elements of the cross covariance between a pair of points.
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
};

} // namespace csm

#endif // __CSM_MULTI_POINTCLOUDGM_H
