//####################################################################
//
//    FILENAME:          ObjectSpace.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for object space definition class and non-ECEF ObjectSpace coordinate classes.
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

#ifndef __CSM_OBJECTSPACE_H
#define __CSM_OBJECTSPACE_H

#include <cstring>

namespace csm
{
enum class CSM_EXPORT_API ObjectSpaceType : unsigned char
{
    LSR,
    ECI,
    UNDEFINED
};
//>
// This enum class identifies the object space type.
//<
    
//***
// STRUCT: ObjectSpaceCoordinate
//> This structure represents a three-dimensional point in the object space coordinate system.
//
//  Coordinate values are in units of meters.
//<
//***
struct CSM_EXPORT_API ObjectSpaceCoordinate
{
public:
    double x;
    double y;
    double z;
    //> three coordinate values
    //<

    ObjectSpaceCoordinate() :
        x(0.0), y(0.0), z(0.0) {}
    //> the default constructor initializes the coordinates all to 0.0
    //<

    ObjectSpaceCoordinate(double aX, double aY, double aZ) :  x(aX), y(aY), z(aZ) {}
    //> constructor that initializes with the values given
    //<
}; // ObjectSpaceCoordinate

//***
// STRUCT: ObjectCoordinateCovar
//> This structure represents a three-dimensional point in the object space coordinate system
//  and its 3 by 3 covariance matrix.
//
//  Coordinate values are in units of meters and covariances are in units of meters-squared.
//<
//***
struct CSM_EXPORT_API ObjectSpaceCoordinateCovar : public ObjectSpaceCoordinate
{
public:
    double covariance[9];
//> 3x3 coordinate covariance matrix, in meters squared,
//  stored as an array of nine doubles as follows:
//
//-  [0] = x  variance
//-  [1] = xy covariance
//-  [2] = xz covariance
//-  [3] = yx covariance
//-  [4] = y  variance
//-  [5] = yz covariance
//-  [6] = zx covariance
//-  [7] = zy covariance
//-  [8] = z  variance
//<


    ObjectSpaceCoordinateCovar();
    //> Default Constructor
    //<

    ObjectSpaceCoordinateCovar(double aX, double aY, double aZ);
    //> This constructor takes x, y, and z values in meters.
    //  The covariance is set to zeroes.
    //<

    ObjectSpaceCoordinateCovar(double aX, double aY, double aZ, const double aCovar[9]);
    //> This constructor takes x, y, and z values in meters and
    //  covariance as an array of nine doubles in meters squared.
    //  Note that no check is made to ensure symmetry of the covariance
    //  matrix.
    //<

    ObjectSpaceCoordinateCovar(double aX, double aY, double aZ,
        double aCovar00, double aCovar01, double aCovar02,
        double aCovar11, double aCovar12,
        double aCovar22);
    //> This constructor takes x, y, and z values in meters and the
    //  upper-triangular portion of a covariance matrix in meters squared.
    //  It is assumed that the covariance matrix is symmetric.
    //<	   

}; // ObjectSpaceCoordinateCovar

//***
// STRUCT: ObjectSpaceVector
//> This structure represents a three-dimensional vector in the object space coordinate system.
//
//  Vector coordinates are in units of meters.
//<
//***
struct CSM_EXPORT_API ObjectSpaceVector
{
public:
    double x;
    double y;
    double z;
    //> these are the vector components in units of meters.
    //<

    ObjectSpaceVector() : x(0.0), y(0.0), z(0.0) {}
    //> This constructor takes x, y, and z values in meters.
    //  The covariance is set to zeroes.
    //<
    ObjectSpaceVector(double aX, double aY, double aZ) :  x(aX), y(aY), z(aZ) {}
    //> constructor that initializes with the values given
    //<
};

//***
// STRUCT: ObjectSpaceVectorCovar
//> This structure represents a three-dimensional vector and its 3 by 3 covariance matrix
//  in the object space coordinate system.
//
//  Vector coordinates are in units of meters and covariances are in units of meters-squared.
//<
//***
struct CSM_EXPORT_API ObjectSpaceVectorCovar
{
public:
    double x;
    double y;
    double z;
    //> these are the vector components in units of meters.
    //<

    double covariance[9];
    //> 3x3 coordinate covariance matrix, in meters squared,
    //  stored as an array of nine doubles as follows:
    //
    //-  [0] = x  variance
    //-  [1] = xy covariance
    //-  [2] = xz covariance
    //-  [3] = yx covariance
    //-  [4] = y  variance
    //-  [5] = yz covariance
    //-  [6] = zx covariance
    //-  [7] = zy covariance
    //-  [8] = z  variance
    //<

    ObjectSpaceVectorCovar();
    //> default constructor initializes coordinates and covariances to 0.0
    //<

    ObjectSpaceVectorCovar(double aX, double aY, double aZ, double covar[9]);
    //> constructor that initializes with the values given
    //<

    ObjectSpaceVectorCovar(double aX, double aY, double aZ,
        double aCovar00, double aCovar01, double aCovar02,
        double aCovar11, double aCovar12,
        double aCovar22);
    //> This constructor takes x, y, and z values in meters and the
    //  upper-triangular portion of a covariance matrix in meters squared.
    //  It is assumed that the covariance matrix is symmetric.
    //<	   
};

//***
// STRUCT: ObjectSpaceLocus
//> This structure contains an object space coordinate (in meters) and
//  an object space direction vector.
//<
//***
struct CSM_EXPORT_API ObjectSpaceLocus
{
public:
    ObjectSpaceCoordinate  point;
    //> the origin point of the locus vector.
    //<

    ObjectSpaceVector direction;
    //> the three components of the direction vector.
    //<

    ObjectSpaceLocus() : point(), direction() {}
    //< the default constructors set all of the initial values to 0.0.
    //>


    ObjectSpaceLocus(const ObjectSpaceCoordinate& argPoint,
        const ObjectSpaceVector& argDirection)
        :
        point(argPoint),
        direction(argDirection)
    {}
    //> construct with the values given
    //<

    ObjectSpaceLocus( double ptX, double ptY, double ptZ,
        double dirX, double dirY, double dirZ)
        :
        point(ptX, ptY, ptZ),
        direction(dirX, dirY, dirZ)
    {}
    //> construct with the coordinate values and vector components given.
    //<
};


//***
// STRUCT: ObjectSpaceLocusCovar
//> This structure contains an object space coordinate (in meters) and
//  an object space direction vector.
//<
//***
struct CSM_EXPORT_API ObjectSpaceLocusCovar
{
public:
    ObjectSpaceCoordinateCovar  point;
    //> the origin point of the locus vector.
    //<

    ObjectSpaceVectorCovar direction;
    //> the three components of the direction vector.
    //<

    ObjectSpaceLocusCovar() : point(), direction() {}
    //< the default constructors set all of the initial values to 0.0.
    //>


    ObjectSpaceLocusCovar(const ObjectSpaceCoordinateCovar& argPoint,
        const ObjectSpaceVectorCovar& argDirection)
        :
        point(argPoint),
        direction(argDirection)
    {}
    //> construct with the values given
    //<

    ObjectSpaceLocusCovar(double ptX, double ptY, double ptZ, double pt_covar[9],
        double dirX, double dirY, double dirZ, double dir_covar[9])
        :
        point(ptX, ptY, ptZ,pt_covar),
        direction(dirX, dirY, dirZ, dir_covar)
    {}
    //> construct with the coordinate values and vector components given.
    //<
};

} // namespace csm
#endif // __CSM_OBJECTSPACE_H
