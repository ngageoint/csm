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
//  ObjectSpaceVectorCovar::ObjectSpaceVectorCovar
//*****************************************************************************
ObjectSpaceVectorCovar::ObjectSpaceVectorCovar()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    for (int i = 0; i < 9; i++)
    {
        covariance[i] = 0.0;
    }
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

}

