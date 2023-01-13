//####################################################################
//
//    FILENAME:          MultipleCorrelationModelsContainer.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for a container class to hold and manage multiple correlation
//    model functions. For example, a different model for each parameter
//    group.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-December-2021   Eugene Rose CCB Change CSM 3.0.4. Part of
//                        RSM Enhancements
//
//    NOTES:
//
//#####################################################################

#ifndef __CSM_MULTICORRMODEL_H
#define __CSM_MULTICORRMODEL_H

#include "CorrelationModel.h"
#include <vector>
#include <map>
#include <memory>

namespace csm
{
	class CSM_EXPORT_API MultipleCorrelationModelsContainer : public CorrelationModel
	{
	public:
		~MultipleCorrelationModelsContainer() {};

		MultipleCorrelationModelsContainer(size_t numCorrelationFunctions);
		//<
		// construct a container of CorrelationModels with given size.
		//<
		
		std::shared_ptr<CorrelationModel> getModel(const size_t modelNum) const;
		//<
		// returns a shared pointer to a CorrelationModel. The shared pointer
		// is not released until all references are closed.
		//<
		
		bool addModel(size_t paramGroupIndex, std::shared_ptr<CorrelationModel> m);
		//<
		// Adds a model to the internally managed list.
		// true - the key was not already present and was inserted.
		// false - the key was alredy present and was not inserted.
		//<
		
		virtual size_t getNumSensorModelParameters() const;
		//> with no model number provided, cannot determine the number of sensor model
		//  parameters.
		//<

		virtual size_t getNumSensorModelParameters(size_t modelNum) const;
		//> Works like CorrelationModel.getNumSensorModelParameters and uses modelNum
		//  to determine which model to use.
		//<
		
		size_t getNumCorrelationParameterGroups() const { return 1; }
		//<
		// every model in the multi-model container is defined to have 1 parameter
		// group.
		//<


		int getCorrelationParameterGroup(size_t modelNum) const { return 0; };
		//<
		// the index of any parameter group is 0 because there is only one
		// parameter group per model in the multi-model container.
		//<
		
		double getCorrelationCoefficient(size_t modelNum, double deltaTime)const;
		//> Works like CorrelationModel.getCorrelationCoefficient but uses the "cpGroupIndex"
		//  parameter as the model number in the list and assumes that cpGroupIndex is 0.
		//<

		const std::string& getDecorrelationEventTime(size_t modelNum) const;
		//> Works like CorrelationModel(getDecorrelationEventTime) but uses "cpGroupIndex"
		//  as the model number in the list of models and assumes that index is 0.
		//<

	private:
		//std::vector<std::shared_ptr<CorrelationModel>> theModels;
		std::map<size_t, std::shared_ptr<CorrelationModel>> theModels;
		bool isMember(const size_t modelNumber) const;
	};
}


#endif // __CSM_MULTICORRMODEL_H
