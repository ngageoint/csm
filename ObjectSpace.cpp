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
//     31-December-2023    Eugene Rose CCB Change CSM 4.0
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
	//  ObjectSpaceCoord::ObjectSpaceCoord (copy constructor)
	//*****************************************************************************
	ObjectSpaceCoord::ObjectSpaceCoord(const ObjectSpaceCoord& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	//*****************************************************************************
	// ObjectSpaceCoord::operator=
	//*****************************************************************************
	ObjectSpaceCoord& ObjectSpaceCoord::operator=(const ObjectSpaceCoord& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//*****************************************************************************
	// ObjectSpaceCoord::setCoordinate
	//*****************************************************************************
	void ObjectSpaceCoord::setCoordinate(double xArg, double yArg, double zArg)
	{
		x = xArg;
		y = yArg;
		z = zArg;
	}

	//*****************************************************************************
	//  ObjectSpaceCoordCovar::ObjectSpaceCoordCovar
	//*****************************************************************************
	ObjectSpaceCoordCovar::ObjectSpaceCoordCovar()
	{
		x = 0;
		y = 0;
		z = 0;
		std::memset(covariance, 0, sizeof(covariance));
	}


	//*****************************************************************************
	//  ObjectSpaceCoordCovar::ObjectSpaceCoordCovar
	//*****************************************************************************
	ObjectSpaceCoordCovar::ObjectSpaceCoordCovar(
		double aX, double aY, double aZ)
	{
		x = aX; y = aY; z = aZ;
		std::memset(covariance, 0, sizeof(covariance));
	}

	//*****************************************************************************
	//  ObjectSpaceCoordCovar::ObjectSpaceCoordCovar
	//*****************************************************************************
	ObjectSpaceCoordCovar::ObjectSpaceCoordCovar(
		double aX, double aY, double aZ, const double aCovar[9])
	{
		x = aX; y = aY; z = aZ;
		std::memcpy(covariance, aCovar, sizeof(covariance));
	}

	//*****************************************************************************
	//  ObjectSpaceCoordCovar::ObjectSpaceCoordCovar
	//*****************************************************************************
	ObjectSpaceCoordCovar::ObjectSpaceCoordCovar(double aX, double aY, double aZ,
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
	//  ObjectSpaceCoordCovar::ObjectSpaceCoordCovar (copy constructor)
	//*****************************************************************************
	ObjectSpaceCoordCovar::ObjectSpaceCoordCovar(const ObjectSpaceCoordCovar& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		std::memcpy(covariance, other.covariance, sizeof(covariance));
	}

	//*****************************************************************************
	// ObjectSpaceCoordCovar::operator=
	//*****************************************************************************
	ObjectSpaceCoordCovar& ObjectSpaceCoordCovar::operator=(const ObjectSpaceCoordCovar& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		std::memcpy(covariance, other.covariance, sizeof(covariance));
		return *this;
	}

	//*****************************************************************************
	// ObjectSpaceCoordCovar::setCoordinate
	//*****************************************************************************
	void ObjectSpaceCoordCovar::setCoordinate(double xArg, double yArg, double zArg)
	{
		x = xArg;
		y = yArg;
		z = zArg;
	}

	//*****************************************************************************
	// ObjectSpaceCoordCovar::setCovariance
	//*****************************************************************************
	void ObjectSpaceCoordCovar::setCovariance(const double aCovar[9])
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
	void ObjectSpaceLocus::setPoint(const ObjectSpaceCoord& argPoint)
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
	void ObjectSpaceLocusCovar::setPoint(const ObjectSpaceCoordCovar& argPoint)
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

