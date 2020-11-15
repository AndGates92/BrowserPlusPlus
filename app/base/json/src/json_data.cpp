/**
 * @copyright
 * @file json_data.cpp
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief JSON Data functions
 */

#include "common/include/global_constants.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/exception_macros.h"
#include "common/include/constructor_macros.h"
#include "base/json/include/json_data.h"

// Categories
LOGGING_CONTEXT(jsonDataOverall, jsonData.overall, TYPE_LEVEL, INFO_VERBOSITY)

json::JsonData::JsonData(const json::JsonData::parameter_t & jsonParameters) : printable_object::PrintableObject(), parameters(jsonParameters) {

	LOG_INFO(logger::info_level_e::ZERO, jsonDataOverall,  "JSON Data constructor. Data " << *this);

}

json::JsonData::JsonData(const json::JsonData & rhs): parameters(rhs.parameters) {

	LOG_INFO(logger::info_level_e::ZERO, jsonDataOverall,  "Copy constructor JSON data");

}

json::JsonData & json::JsonData::operator=(const json::JsonData & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, jsonDataOverall,  "Copy assignment operator for JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->parameters != rhs.parameters) {
		this->parameters = rhs.parameters;
	}

	return *this;

}

json::JsonData::JsonData(json::JsonData && rhs): parameters(std::exchange(rhs.parameters, json::JsonData::parameter_t())) {
	LOG_INFO(logger::info_level_e::ZERO, jsonDataOverall,  "Move constructor JSON data");
}

json::JsonData & json::JsonData::operator=(json::JsonData && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, jsonDataOverall,  "Move assignment operator for JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->parameters = std::exchange(rhs.parameters, json::JsonData::parameter_t());
	}

	return *this;
}

json::JsonData::~JsonData() {

	LOG_INFO(logger::info_level_e::ZERO, jsonDataOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string json::JsonData::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + "JSON Parameters:\n";
	for (const auto & p : this->parameters) {
		structInfo = structInfo + "- " + p + "\n";
	}

	return structInfo;
}

CONST_GETTER(json::JsonData::getParameters, json::JsonData::parameter_t &, this->parameters)

void json::JsonData::addParameter(const std::string & name) {
	this->parameters.insert(name);
}

bool json::JsonData::operator==(const json::JsonData & rhs) {
	bool isSame = true;
	isSame &= (this->parameters == rhs.parameters);

	return isSame;
}

bool json::JsonData::operator!=(const json::JsonData & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}
