//####################################################################
//
//    FILENAME:          ProjectionParameters.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for object space single image projection parameters.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-March-2022    Eugene Rose CCB Change CSM 3.0.4
//
//    NOTES:
//
//#####################################################################

#ifndef __CSM_GEOMETRY3D_H
#define __CSM_GEOMETRY3D_H

#include "csm.h"
#include "ObjectSpace.h"
//>
// need ObjectSpace.h for ObjectSpaceCoordinate etc.
//<

namespace csm
{
    
enum class ProjectionGeometryType
{
    RANGE,
    PLANE,
    RANGECOVAR,
    PLANECOVAR,
    UNSPECIFIED
};
//>
// This enum class identifies the projection parameters type.
//<

// ************************************************************
// ProjectionParameters virtual base class
// ************************************************************
class CSM_EXPORT_API ProjectionParameters
{

public:
    virtual ~ProjectionParameters() {};
    //> virtual destructor provides something for base class destructors to call on.
    //<

    virtual ProjectionGeometryType getType() const = 0;
    //> returns the type enum parameter
    //<
protected:
    ProjectionParameters() {};
    //> the default constructor does nothing
    //<

};

// ************************************************************
// ProjectionParametersCovar virtual base class
// ************************************************************
class CSM_EXPORT_API ProjectionParametersCovar
{

public:
    virtual ~ProjectionParametersCovar() {};
    //> virtual destructor provides something for base class destructors to call on.
    //<

    virtual ProjectionGeometryType getType() const = 0;
    //> returns the type enum parameter
    //<
protected:
    ProjectionParametersCovar() {};
    //> the default constructor does nothing
    //<

};

class CSM_EXPORT_API RangeParameters : public ProjectionParameters
{
public:
    RangeParameters();
    //>
    // default constructor sets range to zero and also
    // sets m_type to RANGE
    //<

    RangeParameters(double range);
    //>
    // initializes with the given range in meters
    //<

    ProjectionGeometryType getType() const;
    //>
    // get the geometry type (enum)
    //<

    double getRange() const;
    //> return the range value in meters
    //<
private:
    double m_range;
};

class CSM_EXPORT_API RangeParametersCovar : public ProjectionParametersCovar
{
public:
    RangeParametersCovar();
    //>
    // default constructor sets range and range variance to zero and also
    // sets m_type to RANGE
    //<

    RangeParametersCovar(double range, double rangeVariance);
    //>
    // initializes with the give values in meters and meters-squared
    //<

    ProjectionGeometryType getType() const;
    //>
    // get the geometry type (enum)
    //<

    double getRange() const;
    //> return the range value in meters
    //<

    double getRangeVariance() const;
    //>
    // returns the range variance
    //<
private:
    double m_range;
    //>
    // range value in meters
    //<
    double m_rangeVariance;
    //>
    // range variance in meters squared
    //<
};

class  CSM_EXPORT_API PlaneParameters : public ProjectionParameters
{
public:
    PlaneParameters();
    //> the default constructor will intialize the point and the vector to
    //  zero.
    // Also sets m_type to PLANE
    //<

    PlaneParameters(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal);
            
    //> this constructor will initialize the point and the normal with the give values.
    //<

    ProjectionGeometryType getType() const;
    //>
    // get the geometry type (enum)
    //<

    ObjectSpaceCoordinate getPoint() const;
    //> read the point
    //<

    ObjectSpaceVector getNormal() const;
    //> read the normal
    //<
private:
    ObjectSpaceCoordinate m_point;
    //> a point on the plane. 
    //<
    ObjectSpaceVector m_normal;
    //>
    // normal to the plane
    //<
};

class  CSM_EXPORT_API PlaneParametersCovar : public ProjectionParametersCovar
{
public:
    PlaneParametersCovar();
    //> the default constructor will intialize the point and the vector to
    //  zero. Also the point and vector covariances to zero.
    //  Also sets m_type to PLANE
    //<

    PlaneParametersCovar(const ObjectSpaceCoordinateCovar& coord, const ObjectSpaceVectorCovar& normal);			
    //> this constructor will initialize the point and the normal with the give values.
    //<

    ProjectionGeometryType getType() const;
    //>
    // get the geometry type (enum)
    //<

    ObjectSpaceCoordinateCovar getPoint() const;
    //> read the point
    //<

    ObjectSpaceVectorCovar getNormal() const;
    //> read the normal
    //<
private:
    ObjectSpaceCoordinateCovar m_point;
    //> a point on the plane. 
    //<
    ObjectSpaceVectorCovar m_normal;
    //>
    // normal to the plane
    //<
};
}

#endif // __CSM_GEOMETRY3D_H
