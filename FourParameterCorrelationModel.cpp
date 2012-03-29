/**
 * This file contains the implementation of the
 * CSMFourParameterCorrelationModel class.  See the comments in the header file
 * for more information about the class interface.
 **/
#define TSM_LIBRARY
#include "CSMFourParameterCorrelationModel.h"
#include "TSMError.h"

#ifdef IRIXN32
#include "math.h"
#else
#include <cmath>
using std::exp;
using std::fabs;
#endif

CSMFourParameterCorrelationModel::CSMFourParameterCorrelationModel(int numSMParams, int numCPGroups) {
	// make sure that the parameters are non-negative
	if (numSMParams < 0)
		throw TSMError(TSMError::BOUNDS, std::string("Number of sensor model parameters must be non-negative."), std::string("CSMFourParameterCorrelationModel::CSMFourParameterCorrelationModel"));
	if (numCPGroups < 0)
		throw TSMError(TSMError::BOUNDS, std::string("Number of correlation parameter groups must be non-negative."), std::string("CSMFourParameterCorrelationModel::CSMFourParameterCorrelationModel"));

	// set the format string in the base class
	_format = std::string("Four-parameter model (A, alpha, beta, tau)");

	// initialize the vectors that will store the group mapping and correlation parameters
	_groupMapping.resize(numSMParams, -1);
	_corrParams.resize(numCPGroups);
}

TSMWarning* CSMFourParameterCorrelationModel::getNumSensorModelParameters(int& numSMParams) const {
	// return the number of sensor model parameters by reference
	numSMParams = static_cast<int>(_groupMapping.size());
	return NULL;
}

TSMWarning* CSMFourParameterCorrelationModel::getNumCorrelationParameterGroups(int& numCPGroups) const {
	// return the number of correlation parameter groups by reference
	numCPGroups = static_cast<int>(_corrParams.size());
	return NULL;
}

TSMWarning* CSMFourParameterCorrelationModel::getCorrelationParameterGroup(int smParamIndex, int& cpGroupIndex) const {
	// make sure the index falls within the acceptable range
	checkSensorModelParameterIndex(smParamIndex, std::string("CSMFourParameterCorrelationModel::getCorrelationParameterGroup"));

	// return the correlation parameter group index by reference
	cpGroupIndex = _groupMapping[smParamIndex];
	return NULL;
}

TSMWarning* CSMFourParameterCorrelationModel::setCorrelationParameterGroup(int smParamIndex, int cpGroupIndex) {
	// make sure the indices fall within the acceptable ranges
	checkSensorModelParameterIndex(smParamIndex, std::string("CSMFourParameterCorrelationModel::setCorrelationParameterGroup"));
	checkParameterGroupIndex(cpGroupIndex, std::string("CSMFourParameterCorrelationModel::setCorrelationParameterGroup"));

	// set the group index for the given sensor model parameter
	_groupMapping[smParamIndex] = cpGroupIndex;
	return NULL;
}

TSMWarning* CSMFourParameterCorrelationModel::setCorrelationGroupParameters(int cpGroupIndex, double a, double alpha, double beta, double tau) {
	// make sure the index falls within the acceptable range
	checkParameterGroupIndex(cpGroupIndex, std::string("CSMFourParameterCorrelationModel::setCorrelationGroupParameters"));

	// make sure the values of each correlation model parameter fall within acceptable ranges
	if ((a < -1.0) || (a > 1.0))
		throw TSMError(TSMError::BOUNDS, std::string("Correlation parameter A must be in the range [-1, 1]."), std::string("CSMFourParameterCorrelationModel::setCorrelationGroupParameters"));
	if ((alpha < 0.0) || (alpha > 1.0))
		throw TSMError(TSMError::BOUNDS, std::string("Correlation parameter alpha must be in the range [0, 1]."), std::string("CSMFourParameterCorrelationModel::setCorrelationGroupParameters"));
	if (beta < 0.0)
		throw TSMError(TSMError::BOUNDS, std::string("Correlation parameter beta must be non-negative."), std::string("CSMFourParameterCorrelationModel::setCorrelationGroupParameters"));
	if (tau <= 0.0)
		throw TSMError(TSMError::BOUNDS, std::string("Correlation parameter tau must be positive."), std::string("CSMFourParameterCorrelationModel::setCorrelationGroupParameters"));

	// store the correlation parameter values
	_corrParams[cpGroupIndex] = CorrelationParameters(a, alpha, beta, tau);
	return NULL;
}

TSMWarning* CSMFourParameterCorrelationModel::getCorrelationCoefficient(int cpGroupIndex, double deltaTime, double& corrCoeff) const {
	// make sure the index falls within the acceptable range
	checkParameterGroupIndex(cpGroupIndex, std::string("CSMFourParameterCorrelationModel::getCorrelationCoefficient"));

	// compute the value of the correlation coefficient
	const CorrelationParameters& cp = _corrParams[cpGroupIndex];
	corrCoeff = cp._alpha + cp._a * (1.0 - cp._alpha) * (1.0 + cp._beta) / (cp._beta + exp(fabs(deltaTime) / cp._tau));

	// if necessary, clamp the coefficient value to the acceptable range
	if (corrCoeff < -1.0)
		corrCoeff = -1.0;
	if (corrCoeff > 1.0)
		corrCoeff = 1.0;

	return NULL;
}

void CSMFourParameterCorrelationModel::checkSensorModelParameterIndex(int smParamIndex, const std::string& functionName) const {
	size_t i = static_cast<size_t>(smParamIndex);
	if (i >= _groupMapping.size())
		throw TSMError(TSMError::INDEX_OUT_OF_RANGE, std::string("Sensor model parameter index is out of range."), functionName);
}

void CSMFourParameterCorrelationModel::checkParameterGroupIndex(int groupIndex, const std::string& functionName) const {
	size_t i = static_cast<size_t>(groupIndex);
	if (i >= _corrParams.size())
		throw TSMError(TSMError::INDEX_OUT_OF_RANGE, std::string("Correlation parameter group index is out of range."), functionName);
}

CSMFourParameterCorrelationModel::CorrelationParameters::CorrelationParameters() : _a(0.0), _alpha(0.0), _beta(0.0), _tau(1.0) {
}

CSMFourParameterCorrelationModel::CorrelationParameters::CorrelationParameters(const double& a, const double& alpha, const double& beta, const double& tau) : _a(a), _alpha(alpha), _beta(beta), _tau(tau) {
}
