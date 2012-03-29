/**
 * This header defines the CSMFourParameterCorrelationModel class.  This class
 * is used to compute the correlation between adjustable parameters in a
 * community sensor model (CSM).
 *
 * The class is a wrapper around the equation
 *
 * rho = alpha + a * (1 - alpha) * (1 + beta) / (beta + exp(deltaT / tau)),
 *
 * where a, alpha, beta, and tau are the correlation parameters, deltaT is the
 * difference in time, and rho is the correlation coefficient.
 *
 * The class assumes that sensor model parameter are divided into disjoint
 * groups, such that the correlation coefficient between any two parameters in
 * the same group is given by the equation above, and the correlation between
 * two parameters in different groups is 0.0.  This implementation provides a
 * way to assign sensor model parameters to groups, to set the values of the
 * correlation parameters for a given group, and to compute the equation above.
 **/

#ifndef _FOURPARAMETERCORRELATIONMODEL_H_
#define _FOURPARAMETERCORRELATIONMODEL_H_

#include <vector>
#include "TSMCovarianceModel.h"
#include "TSMWarning.h"

class TSM_EXPORT_API CSMFourParameterCorrelationModel : public tsm_CovarianceModel {

public:
	/**
	 * Constructor.  The number of sensor model parameters and correlation
	 * parameter groups must be provided.
	 *
	 * Preconditions:
	 * * numSMParams must be non-negative
	 * * numCPGroups must be non-negative
	 **/
	CSMFourParameterCorrelationModel(int numSMParams, int numCPGroups);

	/**
	 * Returns the number of sensor model parameters by reference in the
	 * numSMParams variable.  The returned value will be the same as the value
	 * of numSMParams passed to the constructor when the object was created.
	 **/
	TSMWarning* getNumSensorModelParameters(int& numSMParams) const;

	/**
	 * Returns the number of correlation parameter groups by reference in the
	 * numCPGroups variable.  The returned value will be the same as the value
	 * of numCPGroups passed to the constructor when the object was created.
	 **/
	TSMWarning* getNumCorrelationParameterGroups(int& numCPGroups) const;

	/**
	 * Returns the index of the correlation parameter group to which the given
	 * sensor model parameter belongs.  The smParamIndex variable is the index
	 * of a sensor model parameter.  The index of that parameter's group is
	 * returned in the cpGroupIndex variable.  If the sensor model parameter
	 * does not belong to a group, cpGroupIndex will be set to -1.
	 *
	 * Precondition:
	 * * 0 <= smParamIndex < numSMParams
	 *
	 * Postcondition:
	 * * -1 <= cpGroupIndex < numCPGroups
	 **/
	TSMWarning* getCorrelationParameterGroup(int smParamIndex, int& cpGroupIndex) const;

	/**
	 * Sets the index of the correlation parameter group to which the given
	 * sensor model parameter belongs.  The smParamIndex variable is the index
	 * of a sensor model parameter, and the cpGroupIndex variable is the index
	 * of the correlation parameter group to which it should be added.
	 *
	 * Preconditions:
	 * * 0 <= smParamIndex < numSMParams
	 * * 0 <= cpGroupIndex < numCPGroups
	 *
	 * Notes:
	 * Although the getCorrelationParameterGroup function can return -1 as a group
	 * index (indicating the group has not been set), it is an error to try to set
	 * the group index to -1.
	 **/
	TSMWarning* setCorrelationParameterGroup(int smParamIndex, int cpGroupIndex);

	/**
	 * Sets the values of the correlation parameters for a given group.  The
	 * cpGroupIndex variable holds the index of a correlation parameter group,
	 * and the remaining arguments are the values of the correlation parameters
	 * in that group.
	 *
	 * Precondition:
	 * * 0 <= cpGroupIndex < numCPGroups
	 * * -1.0 <= a <= 1.0
	 * * 0.0 <= alpha <= 1.0
	 * * 0.0 <= beta
	 * * 0.0 < tau
	 **/
	TSMWarning* setCorrelationGroupParameters(int cpGroupIndex, double a, double alpha, double beta, double tau);

	/**
	 * Computes the correlation coefficient for the given correlation parameter
	 * group and delta-time.  The cpGroupIndex variable holds the index of a
	 * correlation parameter group.  The deltaTime variable represents the
	 * difference in time for the correlation calculation.  The correlation
	 * coefficient is returned by reference in the corrCoeff variable.
	 *
	 * Preconditions:
	 * * 0 <= cpGroupIndex < numCPGroups
	 *
	 * Postconditions:
	 * * -1.0 <= corrCoeff <= 1.0
	 *
	 * Notes:
	 * The deltaTime parameter should be positive, but the function uses the
	 * absolute value of the variable, so a negative deltaTime is acceptable
	 * input.
	 * If the computed correlation coefficient is outside the range [-1, 1],
	 * the function will "clamp" the returned value to the nearest number
	 * within that range.  For example, if the correlation coefficient equation
	 * evaluates to 1.1 for a given deltaTime, the value 1.0 will be returned
	 * in corrCoeff.
	 **/
	TSMWarning* getCorrelationCoefficient(int cpGroupIndex, double deltaTime, double& corrCoeff) const;

protected:

	// represents a set of four correlation parameters, grouped to simplify the implementation
	struct TSM_EXPORT_API CorrelationParameters {
	
		CorrelationParameters();
		CorrelationParameters(const double& a, const double& alpha, const double& beta, const double& tau);
		
		double _a, _alpha, _beta, _tau;
	};

	// stores the mapping between sensor model parameter indices and correlation parameter group indices
	std::vector<int> _groupMapping;

	// stores the values of the correlation parameters for each parameter group
	std::vector<CorrelationParameters> _corrParams;

	/**
	 * If the given sensor model parameter index is not within the range
	 * [0, numSMParams), throws a TSMError.
	 **/
	void checkSensorModelParameterIndex(int smParamIndex, const std::string& functionName) const;

	/**
	 * If the given correlation parameter group index is not within the range
	 * [0, numCPGroups), throws a TSMError.
	 **/
	void checkParameterGroupIndex(int groupIndex, const std::string& functionName) const;

};

#endif
