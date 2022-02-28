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
const double &RangeParameters::getRange() const
{
    return m_range;
}

//*****************************************************************************
// RangeParameters::setrange
//*****************************************************************************
void RangeParameters::setRange(double range)
{
    m_range = range;
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
// RangeParametersCovar::setrange
//*****************************************************************************
void RangeParametersCovar::setRange(double range)
{
    m_range = range;
}

//*****************************************************************************
// RangeParametersCovar::setrangeVariance
//*****************************************************************************
void RangeParametersCovar::setRangeVariance(double rangeVar)
{
    m_rangeVariance = rangeVar;
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
const ObjectSpaceCoordinate& PlaneParameters::getPoint() const
{
    return m_point;
}

//*******************************************************************************
// PlaneParameters::getNormal()
//********************************************************************************
const ObjectSpaceVector& PlaneParameters::getNormal() const
{
    return m_normal;
}

//*******************************************************************************
// PlaneParameters::setPoint()
//********************************************************************************
void PlaneParameters::setPoint(const ObjectSpaceCoordinate& pointArg)
{
    m_point = pointArg; // assignment operator usage
}

//*******************************************************************************
// PlaneParameters::setNormal()
//********************************************************************************
void PlaneParameters::setNormal(const ObjectSpaceVector& normalArg)
{
    m_normal = normalArg; // assignment operator usage
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
const ObjectSpaceCoordinateCovar& PlaneParametersCovar::getPoint() const
{
    return m_point;
}

//*******************************************************************************
// PlaneParametersCovar::getNormal()
//********************************************************************************
const ObjectSpaceVectorCovar& PlaneParametersCovar::getNormal() const
{
    return m_normal;
}

//*******************************************************************************
// PlaneParametersCovar::setPoint()
//********************************************************************************
void PlaneParametersCovar::setPoint(const ObjectSpaceCoordinateCovar& pointArg)
{
    m_point = pointArg; // assignment operator usage
}

//*******************************************************************************
// PlaneParametersCovar::setNormal()
//********************************************************************************
void PlaneParametersCovar::setNormal(const ObjectSpaceVectorCovar& normalArg)
{
    m_normal = normalArg; // assignment operator usage
}

} // namespace csm
