/**
 * @copyright
 * @file command_line_argument.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window JSON Data functions
 */

// Qt libraries
#include <QtCore/QtGlobal>

// Required by qInfo
#include <QtCore/QtDebug>

#include "global_constants.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"
#include "command_line_argument.h"

// Categories
Q_LOGGING_CATEGORY(commandLineArgumentOverall, "commandLineArgument.overall", MSG_TYPE_LEVEL)

std::shared_ptr<command_line_argument::CommandLineArgument> command_line_argument::CommandLineArgument::makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const std::string & shortCmdKeyValue, const std::string & longCmdKeyValue, const std::string & defaultValueKeyValue, const int & numberOfArgumentsKeyValue, const std::string & helpKeyValue) {
	std::shared_ptr<command_line_argument::CommandLineArgument> newData = std::make_shared<command_line_argument::CommandLineArgument>(jsonKey, nameKeyValue, shortCmdKeyValue, longCmdKeyValue, defaultValueKeyValue, numberOfArgumentsKeyValue, helpKeyValue);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "Creating JSON data: " << *newData);
	return newData;
}

command_line_argument::CommandLineArgument::CommandLineArgument(const std::string & jsonKey, const std::string & nameKeyValue, const std::string & shortCmdKeyValue, const std::string & longCmdKeyValue, const std::string & defaultValueKeyValue, const int & numberOfArgumentsKeyValue, const std::string & helpKeyValue) : json_data::JsonData(command_line_argument::CommandLineArgument::parameter_t(command_line_argument::keyNames.cbegin(), command_line_argument::keyNames.cend())), key(jsonKey), name(nameKeyValue), shortCmd(shortCmdKeyValue), longCmd(longCmdKeyValue), defaultValue(defaultValueKeyValue), numberOfArguments(numberOfArgumentsKeyValue), help(helpKeyValue) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "Main window JSON Data constructor. Data " << *this);

}

command_line_argument::CommandLineArgument::CommandLineArgument(const command_line_argument::CommandLineArgument & rhs) : json_data::JsonData(rhs), key(rhs.key), name(rhs.name), shortCmd(rhs.shortCmd), longCmd(rhs.longCmd), defaultValue(rhs.defaultValue), numberOfArguments(rhs.numberOfArguments), help(rhs.help) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "Copy constructor main window JSON data");

}

command_line_argument::CommandLineArgument & command_line_argument::CommandLineArgument::operator=(const command_line_argument::CommandLineArgument & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "Copy assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	json_data::JsonData::operator=(rhs);

	if (this->key.compare(rhs.key) != 0) {
		this->key = rhs.key;
	}
	if (this->name.compare(rhs.name) != 0) {
		this->name = rhs.name;
	}
	if (this->shortCmd.compare(rhs.shortCmd) != 0) {
		this->shortCmd = rhs.shortCmd;
	}
	if (this->longCmd.compare(rhs.longCmd) != 0) {
		this->longCmd = rhs.longCmd;
	}
	if (this->defaultValue.compare(rhs.defaultValue) != 0) {
		this->defaultValue = rhs.defaultValue;
	}
	if (this->numberOfArguments == rhs.numberOfArguments) {
		this->numberOfArguments = rhs.numberOfArguments;
	}
	if (this->help.compare(rhs.help) != 0) {
		this->help = rhs.help;
	}

	return *this;

}

command_line_argument::CommandLineArgument::CommandLineArgument(command_line_argument::CommandLineArgument && rhs) : json_data::JsonData(rhs), key(std::exchange(rhs.key, std::string())), name(std::exchange(rhs.name, std::string())), shortCmd(std::exchange(rhs.shortCmd, std::string())), longCmd(std::exchange(rhs.longCmd, std::string())), defaultValue(std::exchange(rhs.defaultValue, std::string())), numberOfArguments(std::exchange(rhs.numberOfArguments, -1)), help(std::exchange(rhs.help, std::string())) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "Move constructor main window JSON data");
}

command_line_argument::CommandLineArgument & command_line_argument::CommandLineArgument::operator=(command_line_argument::CommandLineArgument && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "Move assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		json_data::JsonData::operator=(rhs);
		this->key = std::exchange(rhs.key, std::string());
		this->name = std::exchange(rhs.name, std::string());
		this->shortCmd = std::exchange(rhs.shortCmd, std::string());
		this->longCmd = std::exchange(rhs.longCmd, std::string());
		this->defaultValue = std::exchange(rhs.defaultValue, std::string());
		this->numberOfArguments = std::exchange(rhs.numberOfArguments, -1);
		this->help = std::exchange(rhs.help, std::string());
	}

	return *this;
}

command_line_argument::CommandLineArgument::~CommandLineArgument() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandLineArgumentOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string command_line_argument::CommandLineArgument::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + json_data::JsonData::print();
	structInfo = structInfo + "- key in the JSON file: " + this->key + "\n";
	structInfo = structInfo + "- name of the action: " + this->name + "\n";
	structInfo = structInfo + "- short command of the action: " + this->shortCmd + "\n";
	structInfo = structInfo + "- long command of the action: " + this->longCmd + "\n";
	structInfo = structInfo + "- default argument of the action: " + this->defaultValue + "\n";
	structInfo = structInfo + "- number of arguments of the action: " + std::to_string(this->numberOfArguments) + "\n";
	structInfo = structInfo + "- help for the action: " + this->help + "\n";

	return structInfo;
}

CONST_GETTER(command_line_argument::CommandLineArgument::getKey, std::string &, this->key)
CONST_GETTER(command_line_argument::CommandLineArgument::getName, std::string &, this->name)
CONST_GETTER(command_line_argument::CommandLineArgument::getShortCmd, std::string &, this->shortCmd)
CONST_GETTER(command_line_argument::CommandLineArgument::getLongCmd, std::string &, this->longCmd)
CONST_GETTER(command_line_argument::CommandLineArgument::getDefaultValue, std::string &, this->defaultValue)
CONST_GETTER(command_line_argument::CommandLineArgument::getNumberOfArguments, int &, this->numberOfArguments)
CONST_GETTER(command_line_argument::CommandLineArgument::getHelp, std::string &, this->help)

void command_line_argument::CommandLineArgument::setValueFromMemberName(const std::string & name, const void * value) {
	QEXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().end()), throw, "Parameter " << QString::fromStdString(name) << " has not been found among the action parameters. In order to add it, please call void command_line_argument::CommandLineArgument::addParameter(const std::string & name)");

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->key = *strPtr;
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->name = *strPtr;
	} else if (name.compare("ShortCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->shortCmd = *strPtr;
	} else if (name.compare("LongCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->longCmd = *strPtr;
	} else if (name.compare("DefaultValue") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->defaultValue = *strPtr;
	} else if (name.compare("NumberArguments") == 0) {
		const int * const intPtr(static_cast<const int *>(value));
		this->numberOfArguments = *intPtr;
	} else if (name.compare("Help") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->help = *strPtr;
	} else {
		QEXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << QString::fromStdString(name) << ".");
	}
}

const void * command_line_argument::CommandLineArgument::getValueFromMemberName(const std::string & name) const {
	QEXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << QString::fromStdString(name) << " has not been found among the action parameters. In order to add it, please call void command_line_argument::CommandLineArgument::addParameter(const std::string & name)");

	const void * value = nullptr;

	if (name.compare("Key") == 0) {
		value = &(this->key);
	} else if (name.compare("Name") == 0) {
		value = &(this->name);
	} else if (name.compare("ShortCmd") == 0) {
		value = &(this->shortCmd);
	} else if (name.compare("LongCmd") == 0) {
		value = &(this->longCmd);
	} else if (name.compare("DefaultValue") == 0) {
		value = &(this->defaultValue);
	} else if (name.compare("NumberArguments") == 0) {
		value = &(this->numberOfArguments);
	} else if (name.compare("Help") == 0) {
		value = &(this->help);
	} else {
		QEXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << QString::fromStdString(name) << ".");
	}

	return value;
}

bool command_line_argument::CommandLineArgument::isSameFieldValue(const std::string & name, const void * value) const {
	QEXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << QString::fromStdString(name) << " has not been found among the action parameters. In order to add it, please call void command_line_argument::CommandLineArgument::addParameter(const std::string & name)");

	bool isSame = false;

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->key.compare(*strPtr) == 0);
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->name.compare(*strPtr) == 0);
	} else if (name.compare("ShortCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->shortCmd.compare(*strPtr) == 0);
	} else if (name.compare("LongCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->longCmd.compare(*strPtr) == 0);
	} else if (name.compare("DefaultValue") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->defaultValue.compare(*strPtr) == 0);
	} else if (name.compare("NumberArguments") == 0) {
		const int * const intPtr(static_cast<const int *>(value));
		isSame = (this->numberOfArguments == *intPtr);
	} else if (name.compare("Help") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->help.compare(*strPtr) == 0);
	} else {
		QEXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << QString::fromStdString(name) << ".");
	}

	return isSame;
}

bool command_line_argument::CommandLineArgument::operator==(const command_line_argument::CommandLineArgument & rhs) {
	bool isSame = true;
	isSame &= this->json_data::JsonData::operator==(rhs);
	isSame &= (this->key.compare(rhs.key) == 0);
	isSame &= (this->name.compare(rhs.name) == 0);
	isSame &= (this->shortCmd.compare(rhs.shortCmd) == 0);
	isSame &= (this->longCmd.compare(rhs.longCmd) == 0);
	isSame &= (this->defaultValue.compare(rhs.defaultValue) == 0);
	isSame &= (this->numberOfArguments == rhs.numberOfArguments);
	isSame &= (this->help.compare(rhs.help) == 0);

	return isSame;
}

bool command_line_argument::CommandLineArgument::operator!=(const command_line_argument::CommandLineArgument & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}