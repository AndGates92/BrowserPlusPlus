/**
 * @copyright
 * @file parser.cpp
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Parser
 */

// Qt libraries
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/shared/exception.h"
#include "app/utility/json/parser.h"

LOGGING_CONTEXT(jsonParserOverall, jsonParser.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(jsonParserFileContent, jsonParser.file_content, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(jsonParserValue, jsonParser.value, TYPE_LEVEL, INFO_VERBOSITY)

app::utility::json::Parser::Parser(QString fileName, QIODevice::OpenModeFlag openFlags) : app::utility::json::Wrapper::Wrapper(fileName,openFlags) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonParserOverall, "Creating JSON Parser of file " << fileName);

	this->readJson();

}

app::utility::json::Parser::Parser(const app::utility::json::Parser & rhs) : app::utility::json::Wrapper(rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonParserOverall, "Copy constructor json parser");

}

app::utility::json::Parser & app::utility::json::Parser::operator=(const app::utility::json::Parser & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonParserOverall, "Copy assignment operator for json parser");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	this->app::utility::json::Wrapper::operator=(rhs);
	return *this;
}

app::utility::json::Parser::Parser(app::utility::json::Parser && rhs) : app::utility::json::Wrapper(std::move(rhs)) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonParserOverall, "Move constructor json parser");
}

app::utility::json::Parser & app::utility::json::Parser::operator=(app::utility::json::Parser && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonParserOverall, "Move assignment operator for json parser");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	this->app::utility::json::Wrapper::operator=(std::move(rhs));

	return *this;
}

app::utility::json::Parser::~Parser() {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonParserOverall, "Destructor of Parser class");

}

const QStringList app::utility::json::Parser::getJsonKeys() const {
	if (this->jsonContent.type() == QJsonValue::Object) {
		const QJsonObject jsonObject(this->jsonContent.toObject());
		const QStringList jsonKeys(jsonObject.keys());
		return jsonKeys;
	} else {
		EXCEPTION_ACTION(throw, "JSON file content is of type " << this->jsonContent.type() << ". Unable to retrive key for a file content of type different from object");
	}

	return QStringList();
}

const std::pair<bool, QString> app::utility::json::Parser::findKeyValue(const QString & treeRoot, const QString & key) const {

	std::pair<bool, QString> found = std::make_pair(false, QString());

	// If it is a QJsonObject, get all keys otherwise throw an exception
	if (this->jsonContent.type() == QJsonValue::Object) {
		const QJsonObject jsonObject(this->jsonContent.toObject());
		const QJsonValue value(jsonObject.value(treeRoot));
		found = this->searchJson(value, key);
	} else {
		EXCEPTION_ACTION(throw, "JSON file content is of type " << this->jsonContent.type() << ". Unable to retrive key for a file content of type different from object");
	}

	// Log only if search has been successful
	if (found.first == true) {
		LOG_INFO(app::logger::info_level_e::ZERO, jsonParserFileContent, "JSON tree root: " << treeRoot << " key: " << key << " value " << found.second);
	}

	return found;

}

QMap<QString, QString> app::utility::json::Parser::findKeyAllValues(const QString & key) const {

	QMap<QString, QString> foundMap;

	// If it is a QJsonObject, get all keys otherwise throw an exception
	if (this->jsonContent.type() == QJsonValue::Object) {
		const QJsonObject jsonObject(this->jsonContent.toObject());
		const QStringList jsonKeys (jsonObject.keys());
		// Iterate over all key of the object
		for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
			LOG_INFO(app::logger::info_level_e::ZERO, jsonParserFileContent, "Searching key: " << key << " under tree " << *keyIter);
			const auto found = this->findKeyValue(*keyIter, key);

			// Add value only if it is not empty
			if (found.first == true) {
				// Match key and value and add to QMap
				foundMap.insert(*keyIter, found.second);
			}
		}
	} else {
		EXCEPTION_ACTION(throw, "JSON file content is of type " << this->jsonContent.type() << ". Unable to retrive key for a file content of type different from object");
	}

	return foundMap;

}

std::pair<bool, QString> app::utility::json::Parser::searchJson(const QJsonValue & content, const QString & key) const {

	std::pair<bool, QString> found = std::make_pair(false, QString());
	switch (content.type()) {
		case QJsonValue::Object:
		{
			LOG_INFO(app::logger::info_level_e::ZERO, jsonParserFileContent, "Searching in JSON Object");
			const QJsonObject jsonObject (content.toObject());

			// search key in current JSON object or keep looking for it
			found = this->searchJsonObject(jsonObject, key);

			break;
		}
		case QJsonValue::Array:
		{
			LOG_INFO(app::logger::info_level_e::ZERO, jsonParserFileContent, "Searching in JSON Array");
			const QJsonArray & jsonArray (content.toArray());
			// Iterate over all elements of array
			for (QJsonArray::const_iterator arrayIter = jsonArray.begin(); arrayIter != jsonArray.end(); arrayIter++) {
				this->searchJson(*arrayIter, key);
			}
			break;
		}
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, jsonParserFileContent, "Cannot find key in type " << content.type() << ". Expected values are array (" << QJsonValue::Array << ") or object (" << QJsonValue::Object << ")");
			break;
	}

	return found;
}

std::pair<bool, QString> app::utility::json::Parser::searchJsonObject(const QJsonObject & object, const QString & key) const {
	std::pair<bool, QString> found = std::make_pair(false, QString());
	if (object.contains(key) == true) {
		QJsonObject::const_iterator iter = object.constFind(key);
		QJsonValue value(iter.value());
		QString valueStr = QString();
		bool match = false;
		if (value.isString() == true) {
			match = true;
			valueStr = value.toString();
		} else if (value.isDouble() == true) {
			match = true;
			valueStr.setNum(value.toDouble(), 'f', 6);
		} else if (value.isBool() == true) {
			match = true;
			if (value.toBool() == true) {
				valueStr = "true";
			} else {
				valueStr = "false";
			}
		} else {
			EXCEPTION_ACTION(throw, "Unable to convert value of type "  << value.type() << " of key " << key << " to string");
		}
		if (match == true) {
			LOG_INFO(app::logger::info_level_e::ZERO, jsonParserValue, "Found key " << key << " with value " << valueStr);
			found = std::make_pair(match, valueStr);
		}
	} else {
		const QStringList jsonKeys (object.keys());
		// Iterate over all key of the object
		for (QStringList::const_iterator keyIter = jsonKeys.cbegin(); keyIter != jsonKeys.cend(); keyIter++) {
			LOG_INFO(app::logger::info_level_e::ZERO, jsonParserFileContent, "JSON key: " << *keyIter);
			const QJsonValue value(object.value(*keyIter));
			found = this->searchJson(value, key);
			if (found.first == true) {
				break;
			}
		}
	}

	return found;
}
