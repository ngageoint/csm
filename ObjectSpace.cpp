//####################################################################
//
//    FILENAME:          ObjectSpace.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Implementation for object space definition class and non-ECEF Object Space coordinate
//    classes.
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
#define CSM_LIBRARY
#include "csm.h"
#include "ObjectSpace.h"

namespace csm
{
//*****************************************************************************
//  ObjectSpaceCoordinate::ObjectSpaceCoordinate (copy constructor)
//*****************************************************************************
ObjectSpaceCoordinate::ObjectSpaceCoordinate(const ObjectSpaceCoordinate& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

//*****************************************************************************
// ObjectSpaceCoordinate::operator=
//*****************************************************************************
ObjectSpaceCoordinate& ObjectSpaceCoordinate::operator=(const ObjectSpaceCoordinate& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

//*****************************************************************************
// ObjectSpaceCoordinate::setCoordinate
//*****************************************************************************
void ObjectSpaceCoordinate::setCoordinate(double xArg, double yArg, double zArg)
{
    x = xArg;
    y = yArg;
    z = zArg;
}

//*****************************************************************************
//  ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar
//*****************************************************************************
ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar()
{
    x = 0;
    y = 0;
    z = 0;
    std::memset(covariance, 0, sizeof(covariance));
}


//*****************************************************************************
//  ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar
//*****************************************************************************
ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar(
    double aX, double aY, double aZ)
{
    x = aX; y = aY; z = aZ;
    std::memset(covariance, 0, sizeof(covariance));
}

//*****************************************************************************
//  ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar
//*****************************************************************************
ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar(
    double aX, double aY, double aZ, const double aCovar[9])
{
    x = aX; y = aY; z = aZ;
    std::memcpy(covariance, aCovar, sizeof(covariance));
}

//*****************************************************************************
//  ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar
//*****************************************************************************
ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar(double aX, double aY, double aZ,
    double aCovar00, double aCovar01, double aCovar02,
    double aCovar11, double aCovar12,
    double aCovar22)
{
    x = aX; y = aY; z = aZ;
    covariance[0] = aCovar00;
    covariance[1] = covariance[3] = aCovar01;
    covariance[2] = covariance[6] = aCovar02;
    covariance[4] = aCovar11;
    covariance[5] = covariance[7] = aCovar12;
    covariance[8] = aCovar22;
}

//*****************************************************************************
//  ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar (copy constructor)
//*****************************************************************************
ObjectSpaceCoordinateCovar::ObjectSpaceCoordinateCovar(const ObjectSpaceCoordinateCovar& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    std::memcpy(covariance, other.covariance, sizeof(covariance));
}

//*****************************************************************************
// ObjectSpaceCoordinateCovar::operator=
//*****************************************************************************
ObjectSpaceCoordinateCovar& ObjectSpaceCoordinateCovar::operator=(const ObjectSpaceCoordinateCovar& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    std::memcpy(covariance, other.covariance, sizeof(covariance));   
    return *this;
}

//*****************************************************************************
// ObjectSpaceCoordinateCovar::setCoordinate
//*****************************************************************************
void ObjectSpaceCoordinateCovar::setCoordinate(double xArg, double yArg, double zArg)
{
    x = xArg;
    y = yArg;
    z = zArg;
}

//*****************************************************************************
// ObjectSpaceCoordinateCovar::setCovariance
//*****************************************************************************
void ObjectSpaceCoordinateCovar::setCovariance(const double aCovar[9])
{
    std::memcpy(covariance, aCovar, sizeof(covariance));
}

//*****************************************************************************
//  ObjectSpaceVector::ObjectSpaceVector (copy constructor)
//*****************************************************************************
ObjectSpaceVector::ObjectSpaceVector(const ObjectSpaceVector& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

//*****************************************************************************
// ObjectSpaceVector::operator=
//*****************************************************************************
ObjectSpaceVector& ObjectSpaceVector::operator=(const ObjectSpaceVector& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

//*****************************************************************************
// ObjectSpaceVector::setCoordinate
//*****************************************************************************
void ObjectSpaceVector::setCoordinate(double xArg, double yArg, double zArg)
{
    x = xArg;
    y = yArg;
    z = zArg;
}

//*****************************************************************************
//  ObjectSpaceVectorCovar::ObjectSpaceVectorCovar
//*****************************************************************************
ObjectSpaceVectorCovar::ObjectSpaceVectorCovar()
{
    x = 0.0;
    y = 0.0;
    z = 0.0; 
    std::memset(covariance, 0, sizeof(covariance));
}

//*****************************************************************************
//  ObjectSpaceVectorCovar::ObjectSpaceVectorCovar
//*****************************************************************************
ObjectSpaceVectorCovar::ObjectSpaceVectorCovar(double aX, double aY, double aZ,
    double aCovar[9])
{
    x = aX;
    y = aY;
    z = aZ;
    std::memcpy(covariance, aCovar, sizeof(covariance));
}

//*****************************************************************************
//  ObjectSpaceVectorCovar::ObjectSpaceVectorCovar
//*****************************************************************************
ObjectSpaceVectorCovar::ObjectSpaceVectorCovar(double aX, double aY, double aZ,
    double aCovar00, double aCovar01, double aCovar02,
    double aCovar11, double aCovar12,
    double aCovar22)
{
    x = aX;
    y = aY;
    z = aZ;
    covariance[0] = aCovar00;
    covariance[1] = covariance[3] = aCovar01;
    covariance[2] = covariance[6] = aCovar02;
    covariance[4] = aCovar11;
    covariance[5] = covariance[7] = aCovar12;
    covariance[8] = aCovar22;

}


//*****************************************************************************
//  ObjectSpaceVectorCovar::ObjectSpaceVectorCovar (copy constructor)
//*****************************************************************************
ObjectSpaceVectorCovar::ObjectSpaceVectorCovar(const ObjectSpaceVectorCovar& other)
{
    x = other.x;
    y = other.y;
    z = other.z; 
    std::memcpy(covariance, other.covariance, sizeof(covariance));
}

//*****************************************************************************
// ObjectSpaceVectorCovar::operator=
//*****************************************************************************
ObjectSpaceVectorCovar& ObjectSpaceVectorCovar::operator=(const ObjectSpaceVectorCovar& other)
{
    x = other.x;
    y = other.y;
    z = other.z; 
    std::memcpy(covariance, other.covariance, sizeof(covariance));
    
    return *this;
}

//*****************************************************************************
// ObjectSpaceVectorCovar::setCoordinate
//*****************************************************************************
void ObjectSpaceVectorCovar::setCoordinate(double xArg, double yArg, double zArg)
{
    x = xArg;
    y = yArg;
    z = zArg;
}

//*****************************************************************************
// ObjectSpaceVectorCovar::setCovariance
//*****************************************************************************
void ObjectSpaceVectorCovar::setCovariance(const double aCovar[9])
{
    std::memcpy(covariance, aCovar, sizeof(covariance));
}

//*****************************************************************************
//  ObjectSpaceLocus::ObjectSpaceLocus (copy constructor)
//*****************************************************************************
ObjectSpaceLocus::ObjectSpaceLocus(const ObjectSpaceLocus& other)
{
    point = (other.point);  // use assignment operator of ObjectSpacePoint
    direction = (other.direction); // use assignment operator of ObjectSpaceVector
}

//*****************************************************************************
// ObjectSpaceLocus::operator=
//*****************************************************************************
ObjectSpaceLocus& ObjectSpaceLocus::operator=(const ObjectSpaceLocus& other)
{
    point = (other.point);  // use assignment operator of ObjectSpacePoint
    direction = (other.direction); // use assignment operator of ObjectSpaceVector
    return *this;
}

//*****************************************************************************
// ObjectSpaceLocus::setPoint
//*****************************************************************************
void ObjectSpaceLocus::setPoint(const ObjectSpaceCoordinate& argPoint)
{
    point = argPoint;
}

//*****************************************************************************
// ObjectSpaceLocus::setVector
//*****************************************************************************
void ObjectSpaceLocus::setVector(const ObjectSpaceVector& argDirection)
{
    direction = argDirection;
}

//*****************************************************************************
//  ObjectSpaceLocusCovar::ObjectSpaceLocusCovar (copy constructor)
//*****************************************************************************
ObjectSpaceLocusCovar::ObjectSpaceLocusCovar(const ObjectSpaceLocusCovar& other)
{
    point = (other.point);  // use assignment operator of ObjectSpacePoint
    direction = (other.direction); // use assignment operator of ObjectSpaceVector
}

//*****************************************************************************
// ObjectSpaceLocusCovar::operator=
//*****************************************************************************
ObjectSpaceLocusCovar& ObjectSpaceLocusCovar::operator=(const ObjectSpaceLocusCovar& other)
{
    point = (other.point);  // use assignment operator of ObjectSpacePoint
    direction = (other.direction); // use assignment operator of ObjectSpaceVector
    return *this;
}

//*****************************************************************************
// ObjectSpaceLocusCovar::setPoint
//*****************************************************************************
void ObjectSpaceLocusCovar::setPoint(const ObjectSpaceCoordinateCovar& argPoint)
{
    point = argPoint;
}

//*****************************************************************************
// ObjectSpaceLocusCovar::setVector
//*****************************************************************************
void ObjectSpaceLocusCovar::setVector(const ObjectSpaceVectorCovar& argDirection)
{
    direction = argDirection;
}

}

