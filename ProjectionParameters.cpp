//#############################################################################
//
//    FILENAME:          ProjectionParameters.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for helper methods associated with
//    object space single image projection parameters.
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     31-Dec-2021   Rose  Initial Coding CSM 3.0.4
//
//#############################################################################
#define CSM_LIBRARY

#include "ProjectionParameters.h"
#include <cmath>


namespace csm
{

//*****************************************************************************
// range3d::range3d()
//*****************************************************************************
geometryType3d range3d::getType() const
{
    return geometryType3d::RANGE;
}

//*****************************************************************************
// range3d::range3d()
//*****************************************************************************
range3d::range3d()
{
    m_range = 0.0;
}

//*****************************************************************************
// range3d::range3d(double range)
//*****************************************************************************
range3d::range3d(double range)
{
    m_range = range;
}

//*****************************************************************************
// range3d::getrange
//*****************************************************************************
double range3d::getRange() const
{
    return m_range;
}

//*****************************************************************************
// range3dCovar::getType(()
//*****************************************************************************
geometryType3d range3dCovar::getType() const
{
    return geometryType3d::RANGECOVAR;
}

//*****************************************************************************
// range3dCovar::range3dCovar()
//*****************************************************************************
range3dCovar::range3dCovar()
{
    m_range = 0.0;
    m_rangeVariance = 0.0;
}

//*****************************************************************************
// range3dCovar::range3dCovar(double range, double rangeVar)
//*****************************************************************************
range3dCovar::range3dCovar(double range, double rangeVar)
{
    m_range = range;
    m_rangeVariance = rangeVar;
}

//*****************************************************************************
// range3dCovar::getrange
//*****************************************************************************
double range3dCovar::getRange() const
{
    return m_range;
}

//*****************************************************************************
// range3dCovar::getrangeVariance
//*****************************************************************************
double range3dCovar::getRangeVariance() const
{
    return m_rangeVariance;
}

//*****************************************************************************
// plane3d::getType(()
//*****************************************************************************
geometryType3d plane3d::getType() const
{
    return geometryType3d::PLANE;
}
//*****************************************************************************
// plane3d::plane3d()
//*****************************************************************************
plane3d::plane3d()
{
    m_point = ObjectSpaceCoordinate();
    m_normal = ObjectSpaceVector();
}

//*****************************************************************************
// plane3d::plane3d(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal)
//******************************************************************************
plane3d::plane3d(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal)
{
    m_point = coord;
    m_normal = normal;
}
//*******************************************************************************
// plane3d::getPoint()
//********************************************************************************
ObjectSpaceCoordinate plane3d::getPoint() const
{
    return m_point;
}

//*******************************************************************************
// plane3d::getNormal()
//********************************************************************************
ObjectSpaceVector plane3d::getNormal() const
{
    return m_normal;
}


//*****************************************************************************
// plane3dCovar::getType(()
//*****************************************************************************
geometryType3d plane3dCovar::getType() const
{
    return geometryType3d::PLANECOVAR;
}

//*******************************************************************************
// plane3dCovar::plane3dCovar()
//********************************************************************************
plane3dCovar::plane3dCovar()
{
    m_point = ObjectSpaceCoordinateCovar();
    m_normal = ObjectSpaceVectorCovar();
}

//*****************************************************************************
// plane3d::plane3d(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal)
//******************************************************************************
plane3dCovar::plane3dCovar(const ObjectSpaceCoordinateCovar& coord, const ObjectSpaceVectorCovar& normal)
{
    m_point = coord;
    m_normal = normal;
}

//*******************************************************************************
// plane3dCovar::getPoint()
//********************************************************************************
ObjectSpaceCoordinateCovar plane3dCovar::getPoint() const
{
    return m_point;
}

//*******************************************************************************
// plane3dCovar::getNormal()
//********************************************************************************
ObjectSpaceVectorCovar plane3dCovar::getNormal() const
{
    return m_normal;
}

} // namespace csm
