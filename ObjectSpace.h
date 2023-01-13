//####################################################################
//
//    FILENAME:          ObjectSpace.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for non-ECEF ObjectSpace coordinate classes.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-Sep-2023   EJR    CSM 4.0. Replace ECEF with ObjectSpace. 4.0
//
//    NOTES:
//
//#####################################################################

#ifndef __CSM_OBJECTSPACE_H
#define __CSM_OBJECTSPACE_H

namespace csm
{

//***
// STRUCT: ObjectSpaceCoord
//> This structure represents a three-dimensional point in the object space coordinate system.
//
//  Coordinate values are in units of meters.
//<
//***
struct CSM_EXPORT_API ObjectSpaceCoord
{
public:
    double x;
    double y;
    double z;
    //> three coordinate values
    //<

    ObjectSpaceCoord() :
        x(0.0), y(0.0), z(0.0) {}
    //> the default constructor initializes the coordinates all to 0.0
    //<

    ObjectSpaceCoord(double aX, double aY, double aZ) :  x(aX), y(aY), z(aZ) {}
    //> constructor that initializes with the values given
    //<

    ObjectSpaceCoord(const ObjectSpaceCoord& other);
    //>
    // copy constructor
    //<

    ObjectSpaceCoord& operator=(const ObjectSpaceCoord& other);
    //>
    // assignment operator
    //<

    void setCoordinate(double x, double y, double z);
    //>
    // set all three coordinate values
    //<

}; // ObjectSpaceCoord

//***
// STRUCT: ObjectCoordinateCovar
//> This structure represents a three-dimensional point in the object space coordinate system
//  and its 3 by 3 covariance matrix.
//
//  Coordinate values are in units of meters and covariances are in units of meters-squared.
//<
//***
struct CSM_EXPORT_API ObjectSpaceCoordCovar
{
public:
    double x;
    double y;
    double z;
    //> three coordinate values
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

    ObjectSpaceCoordCovar();
    //> Default Constructor
    //<

    ObjectSpaceCoordCovar(double aX, double aY, double aZ);
    //> This constructor takes x, y, and z values in meters.
    //  The covariance is set to zeroes.
    //<

    ObjectSpaceCoordCovar(double aX, double aY, double aZ, const double aCovar[9]);
    //> This constructor takes x, y, and z values in meters and
    //  covariance as an array of nine doubles in meters squared.
    //  Note that no check is made to ensure symmetry of the covariance
    //  matrix.
    //<

    ObjectSpaceCoordCovar(double aX, double aY, double aZ,
        double aCovar00, double aCovar01, double aCovar02,
        double aCovar11, double aCovar12,
        double aCovar22);
    //> This constructor takes x, y, and z values in meters and the
    //  upper-triangular portion of a covariance matrix in meters squared.
    //  It is assumed that the covariance matrix is symmetric.
    //<	   

    ObjectSpaceCoordCovar(const ObjectSpaceCoordCovar& other);
    //>
    // copy constructor
    //<

    ObjectSpaceCoordCovar& operator=(const ObjectSpaceCoordCovar& other);
    //>
    // assignment operator
    //<

    void setCoordinate(double x, double y, double z);
    //>
    // set all three coordinate values
    //<

    void setCovariance(const double aCovar[9]);
    //>
    // set the covariance in an existing object
    //<

}; // ObjectSpaceCoordCovar

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

    ObjectSpaceVector(const ObjectSpaceVector& other);
    //>
    // copy constructor
    //<

    ObjectSpaceVector& operator=(const ObjectSpaceVector& other);
    //>
    // assignment operator
    //<

    void setCoordinate(double x, double y, double z);
    //>
    // set all three coordinate values
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

    ObjectSpaceVectorCovar(const ObjectSpaceVectorCovar& other);
    //>
    // copy constructor
    //<

    ObjectSpaceVectorCovar& operator=(const ObjectSpaceVectorCovar& other);
    //>
    // assignment operator
    //<

    void setCoordinate(double x, double y, double z);
    //>
    // set all three coordinate values
    //<

    void setCovariance(const double aCovar[9]);
    //>
    // set the covariance in an existing object
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
    ObjectSpaceCoord  point;
    //> the origin point of the locus vector.
    //<

    ObjectSpaceVector direction;
    //> the three components of the direction vector.
    //<

    ObjectSpaceLocus() : point(), direction() {}
    //< the default constructors set all of the initial values to 0.0.
    //>


    ObjectSpaceLocus(const ObjectSpaceCoord& argPoint,
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

    ObjectSpaceLocus(const ObjectSpaceLocus& other);
    //>
    // copy constructor
    //<

    ObjectSpaceLocus& operator=(const ObjectSpaceLocus& other);
    //>
    // assignment operator
    //<

    void setPoint(const ObjectSpaceCoord& argPoint);
    //>
    // set the point in an existing object
    //<

    void setVector(const ObjectSpaceVector& argDirection);
    //>
    // set the direction in an existing object
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
    ObjectSpaceCoordCovar  point;
    //> the origin point of the locus vector.
    //<

    ObjectSpaceVectorCovar direction;
    //> the three components of the direction vector.
    //<

    ObjectSpaceLocusCovar() : point(), direction() {}
    //< the default constructors set all of the initial values to 0.0.
    //>

    ObjectSpaceLocusCovar(const ObjectSpaceCoordCovar& argPoint,
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

    ObjectSpaceLocusCovar(const ObjectSpaceLocusCovar& other);
    //>
    // copy constructor
    //<

    ObjectSpaceLocusCovar& operator=(const ObjectSpaceLocusCovar& other);
    //>
    // assignment operator
    //<


    void setPoint(const ObjectSpaceCoordCovar& argPoint);
    //>
    // set the point in an existing object
    //<

    void setVector(const ObjectSpaceVectorCovar& argDirection);
    //>
    // set the direction in an existing object
    //<

};

} // namespace csm
#endif // __CSM_OBJECTSPACE_H
