//#############################################################################
//
//    FILENAME:          ObjectSpacePointCloudGM.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    ObjectSpacePointCloudGM class.
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     31-Dec-2021   EJR  Initial Coding
//     31-Sep-2023   EJR    CSM 4.0. Replace ECEF with ObjectSpace.
// 
//    NOTES:
//
//    Refer to ObjectSpacePointCloudGM.h for more information.
//
//#############################################################################
#define CSM_LIBRARY

#include "GeometricModel.h"
#include "ObjectSpacePointCloudGM.h"

namespace csm {
ObjectSpacePointCloudGM::ObjectSpacePointCloudGM() { };

std::string ObjectSpacePointCloudGM::getFamily()const {
    return (GeometricModel::getFamily() + CSM_OSPC_FAMILY);
}


//*****************************************************************************
// ObjectSpacePointCloudGM::computeAllSensorPartials()
//*****************************************************************************

std::vector<ObjectSpacePointCloudGM::SensorPartials> ObjectSpacePointCloudGM::computeAllSensorPartials(
    const ObjectSpaceCoord& groundPt,
    param::Set pSet,
    double desiredPrecision,
    double* achievedPrecision,
    WarningList* warnings) const
{
    const std::vector<int> indices = csm::GeometricModel::getParameterSetIndices(pSet);

    std::vector<ObjectSpacePointCloudGM::SensorPartials> val;

    const size_t NUM_PARAMS = indices.size();

    if (NUM_PARAMS)
    {
        val.resize(NUM_PARAMS);

        //***
        // The achieved precision should be the MAXIMUM of the achieved
        // precision values found for each desired index.
        //***
        if (achievedPrecision) *achievedPrecision = 0.0;

        /*
        virtual ModelCoord objectSpaceToModel(const ObjectSpaceCoord& groundPt,
        double desiredPrecision = 0.001,
        double* achievedPrecision = NULL,
        WarningList* warnings = NULL) const = 0;
        */
        double osToMPrecision = 0.0;
        ModelCoord mc = objectSpaceToModel(groundPt,desiredPrecision,&osToMPrecision);
        if (achievedPrecision && (osToMPrecision > desiredPrecision))
        {
            *achievedPrecision = osToMPrecision;
        }

        for (int i = 0; i < NUM_PARAMS; ++i)
        {
            double prec = 0.0;
            val[i] = computeSensorPartials(indices[i],
                mc,
                groundPt,
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
// ObjectSpacePointCloudGM::computeAllSensorPartials()
//*****************************************************************************
std::vector<ObjectSpacePointCloudGM::SensorPartials> ObjectSpacePointCloudGM::computeAllSensorPartials(
    const ModelCoord& modelPt,
    const ObjectSpaceCoord& groundPt,
    param::Set pSet,
    double desiredPrecision,
    double* achievedPrecision,
    WarningList* warnings) const
{
    const std::vector<int> indices = csm::GeometricModel::getParameterSetIndices(pSet);

    std::vector<ObjectSpacePointCloudGM::SensorPartials> val;

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
                modelPt,
                groundPt,
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