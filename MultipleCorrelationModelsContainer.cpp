//####################################################################
//
//    FILENAME:          MultipleCorrelationModelsContainer.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Implementation for a container class to hold and manage multiple correlation
//    model functions. For example, a different model for each parameter
//    group.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-December-2021   Eugene Rose CCB Change CSM 3.0.4
//
//    NOTES:
//
//#####################################################################
#define CSM_LIBRARY
#pragma warning( disable : 4715) // TODO REMOVE
#include "MultipleCorrelationModelsContainer.h"
#include <vector>
#include <map>
#include <memory>
namespace  csm 
{
    bool MultipleCorrelationModelsContainer::isMember(const size_t modelNumber) const
    {
        if (theModels.find(modelNumber) != theModels.end())
            return true;
        return false;
    }
	MultipleCorrelationModelsContainer::MultipleCorrelationModelsContainer(size_t numCorrelationFunctions)
	: 
        CorrelationModel("MultipleFunctionContainer",0)
    {
		
	}
    std::shared_ptr<CorrelationModel> MultipleCorrelationModelsContainer::getModel(const size_t paramGroupIndex) const
	{
        if (! isMember(paramGroupIndex))
        {
            return std::shared_ptr<CorrelationModel>(0);
        }
		return theModels.at(paramGroupIndex);
	}
	bool MultipleCorrelationModelsContainer::addModel(size_t paramGroupIndex, std::shared_ptr<CorrelationModel> m)
	{
        //std::pair <std::shared_ptr<CorrelationModel>,bool> init;
        std::pair < std::map<size_t, std::shared_ptr<CorrelationModel>>::iterator, bool> init;
        std::pair < size_t, std::shared_ptr<CorrelationModel>> aPair(paramGroupIndex, m);
        init = theModels.insert(aPair);
        if (init.second)
            return false; // the key was not present and was inserted
        else
            return true;  // the key was already present and was not inserted
	}

    size_t MultipleCorrelationModelsContainer::getNumSensorModelParameters(size_t modelNum) const
    {
        if (isMember(modelNum))
            return getModel(modelNum)->getNumSensorModelParameters();
        else
            return 0;
    }

    double MultipleCorrelationModelsContainer::getCorrelationCoefficient(size_t modelNum,
        double deltaTime) const
    {
        if (isMember(modelNum))
            return getModel(modelNum)->getCorrelationCoefficient(0, deltaTime);
        else
            return 0.0;
    }

	const std::string& MultipleCorrelationModelsContainer::getDecorrelationEventTime(size_t modelNum) const
	{
        if (isMember(modelNum))
        {
            try
            {
                return getModel(modelNum)->getDecorrelationEventTime(0);
            }
            catch (csm::Error e)
            {
                throw e;
            }
            catch (...)
            {
                throw csm::Error(csm::Error::UNKNOWN_ERROR, "unhandled exception",
                    "MultipleCorrelationModelsContainer.getDecorrelationEventTime");
            }
        }
        else
            // nothing to do?
            throw csm::Error(csm::Error::BOUNDS, "model is not a member", "MultipleCorrelationModelsContainer.getDecorrelationEventTime");


	}

    size_t MultipleCorrelationModelsContainer::getNumSensorModelParameters() const
    {
        return 0;
    }
}