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


namespace csm
{

//*****************************************************************************
// RangeParameters::RangeParameters()
//*****************************************************************************
ProjectionGeometryType RangeParameters::getType() const
{
    return ProjectionGeometryType::RANGE;
}

//*****************************************************************************
// RangeParameters::RangeParameters()
//*****************************************************************************
RangeParameters::RangeParameters()
{
    m_range = 0.0;
}

//*****************************************************************************
// RangeParameters::RangeParameters(double range)
//*****************************************************************************
RangeParameters::RangeParameters(double range)
{
    m_range = range;
}

//*****************************************************************************
// RangeParameters::getrange
//*****************************************************************************
double RangeParameters::getRange() const
{
    return m_range;
}

//*****************************************************************************
// RangeParametersCovar::getType(()
//*****************************************************************************
ProjectionGeometryType RangeParametersCovar::getType() const
{
    return ProjectionGeometryType::RANGECOVAR;
}

//*****************************************************************************
// RangeParametersCovar::RangeParametersCovar()
//*****************************************************************************
RangeParametersCovar::RangeParametersCovar()
{
    m_range = 0.0;
    m_rangeVariance = 0.0;
}

//*****************************************************************************
// RangeParametersCovar::RangeParametersCovar(double range, double rangeVar)
//*****************************************************************************
RangeParametersCovar::RangeParametersCovar(double range, double rangeVar)
{
    m_range = range;
    m_rangeVariance = rangeVar;
}

//*****************************************************************************
// RangeParametersCovar::getrange
//*****************************************************************************
double RangeParametersCovar::getRange() const
{
    return m_range;
}

//*****************************************************************************
// RangeParametersCovar::getrangeVariance
//*****************************************************************************
double RangeParametersCovar::getRangeVariance() const
{
    return m_rangeVariance;
}

//*****************************************************************************
// PlaneParameters::getType(()
//*****************************************************************************
ProjectionGeometryType PlaneParameters::getType() const
{
    return ProjectionGeometryType::PLANE;
}
//*****************************************************************************
// PlaneParameters::PlaneParameters()
//*****************************************************************************
PlaneParameters::PlaneParameters()
{
    m_point = ObjectSpaceCoordinate();
    m_normal = ObjectSpaceVector();
}

//*****************************************************************************
// PlaneParameters::PlaneParameters(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal)
//******************************************************************************
PlaneParameters::PlaneParameters(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal)
{
    m_point = coord;
    m_normal = normal;
}
//*******************************************************************************
// PlaneParameters::getPoint()
//********************************************************************************
ObjectSpaceCoordinate PlaneParameters::getPoint() const
{
    return m_point;
}

//*******************************************************************************
// PlaneParameters::getNormal()
//********************************************************************************
ObjectSpaceVector PlaneParameters::getNormal() const
{
    return m_normal;
}


//*****************************************************************************
// PlaneParametersCovar::getType(()
//*****************************************************************************
ProjectionGeometryType PlaneParametersCovar::getType() const
{
    return ProjectionGeometryType::PLANECOVAR;
}

//*******************************************************************************
// PlaneParametersCovar::PlaneParametersCovar()
//********************************************************************************
PlaneParametersCovar::PlaneParametersCovar()
{
    m_point = ObjectSpaceCoordinateCovar();
    m_normal = ObjectSpaceVectorCovar();
}

//*****************************************************************************
// PlaneParameters::PlaneParameters(const ObjectSpaceCoordinate& coord, const ObjectSpaceVector& normal)
//******************************************************************************
PlaneParametersCovar::PlaneParametersCovar(const ObjectSpaceCoordinateCovar& coord, const ObjectSpaceVectorCovar& normal)
{
    m_point = coord;
    m_normal = normal;
}

//*******************************************************************************
// PlaneParametersCovar::getPoint()
//********************************************************************************
ObjectSpaceCoordinateCovar PlaneParametersCovar::getPoint() const
{
    return m_point;
}

//*******************************************************************************
// PlaneParametersCovar::getNormal()
//********************************************************************************
ObjectSpaceVectorCovar PlaneParametersCovar::getNormal() const
{
    return m_normal;
}

} // namespace csm
