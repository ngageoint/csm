//#############################################################################
//
//    FILENAME:          ObjectSpaceRasterGM.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    ObjectSpaceRasterGM class.
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//      31-Dec-2021   EJR  Initial Coding
// 
//    NOTES:
//
//    Refer to ObjectSpaceRasterGM.h for more information.
//
//#############################################################################
#define CSM_LIBRARY

#include "GeometricModel.h"
#include "ObjectSpaceRasterGM.h"

namespace csm {
//*****************************************************************************
// ObjectSpaceRasterGM::ObjectSpaceRasterGM
//*****************************************************************************
ObjectSpaceRasterGM::ObjectSpaceRasterGM() { };

//*****************************************************************************
// ObjectSpaceRasterGM::getFamily
//*****************************************************************************
std::string ObjectSpaceRasterGM::getFamily()const {
    return (GeometricModel::getFamily() + CSM_OSRASTER_FAMILY);
}

//*****************************************************************************
// ObjectSpaceRasterGM::computeAllSensorPartials
//*****************************************************************************
std::vector<ObjectSpaceRasterGM::SensorPartials> ObjectSpaceRasterGM::computeAllSensorPartials(
    const ObjectSpaceCoordinate& objectSpacePt,
    param::Set pSet,
    double desiredPrecision,
    double* achievedPrecision,
    WarningList* warnings) const
{
    const std::vector<int> indices = csm::GeometricModel::getParameterSetIndices(pSet);

    std::vector<ObjectSpaceRasterGM::SensorPartials> val;

    const size_t NUM_PARAMS = indices.size();

    if (NUM_PARAMS)
    {
        val.resize(NUM_PARAMS);

        //***
        // The achieved precision should be the MAXIMUM of the achieved
        // precision values found for each desired index.
        //***
        if (achievedPrecision) *achievedPrecision = 0.0;

        ImageCoord ip = objectSpaceToImage(objectSpacePt);
        for (int i = 0; i < NUM_PARAMS; ++i)
        {
            double prec = 0.0;
            val[i] = computeSensorPartials(indices[i],
                ip,
                objectSpacePt,
                desiredPrecision,
                &prec,
                warnings);

            if (achievedPrecision && (prec > *achievedPrecision))
            {
                *achievedPrecision = prec;
            }
        }
    }
    return val;
};

//*****************************************************************************
// ObjectSpaceRasterGM::computeAllSensorPartials
//*****************************************************************************
std::vector<ObjectSpaceRasterGM::SensorPartials> ObjectSpaceRasterGM::computeAllSensorPartials(
    const ImageCoord& imagePt,
    const ObjectSpaceCoordinate& objectSpacePt,
    param::Set pSet,
    double desiredPrecision,
    double* achievedPrecision,
    WarningList* warnings) const
{
    const std::vector<int> indices = csm::GeometricModel::getParameterSetIndices(pSet);

    std::vector<ObjectSpaceRasterGM::SensorPartials> val;

    const size_t NUM_PARAMS = indices.size();

    if (NUM_PARAMS)
    {
        val.resize(NUM_PARAMS);

        //***
        // The achieved precision should be the MAXIMUM of the achieved
        // precision values found for each desired index.
        //***
        if (achievedPrecision) *achievedPrecision = 0.0;

        for (int i = 0; i < NUM_PARAMS; ++i)
        {
            double prec = 0.0;
            val[i] = computeSensorPartials(indices[i],
                imagePt,
                objectSpacePt,
                desiredPrecision,
                &prec,
                warnings);

            if (achievedPrecision && (prec > *achievedPrecision))
            {
                *achievedPrecision = prec;
            }
        }
    }
    return val;
}

}