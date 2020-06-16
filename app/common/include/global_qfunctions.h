#ifndef GLOBAL_QFUNCTIONS_H
#define GLOBAL_QFUNCTIONS_H
/**
 * @copyright
 * @file global_qfunctions.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Qt Functions header file
*/

#include <string>

#include <qt5/QtCore/QtDebug>
#include <qt5/QtCore/QMetaEnum>

#include "exception_macros.h"

/** @defgroup GlobalQFunctionsGroup Global Qt Functions Doxygen Group
 *  Global Qt Functions
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(readFileOverall)

namespace global_qfunctions {

	/**
	 * @brief Function: QString qEnumToQString(const qenum value, const bool printEnumKeyOnly = false)
	 *
	 * \param value: enumerator to be converted to a string
	 * \param printEnumKeyOnly: boolean to choose whether the namespace and enumerator type name are printed. True means print only enumator key and false means print key as well as scope and type name
	 *
	 * \return enumerator converted to a QString
	 *
	 * This function converts an enumerator registered with the Qt Meta-Object system to a QString
	 */
	template<typename qenum>
	QString qEnumToQString(const qenum value, const bool printEnumKeyOnly = false);

	/**
	 * @brief Function: qenum qStringToQEnum(const QString & str)
	 *
	 * \param str: string to search in the enum range
	 *
	 * \return the enum found or -1 if not found
	 *
	 * This function finds the enumerator corresponding to the string
	 */
	template<typename qenum>
	qenum qStringToQEnum(const QString & str);

}
/** @} */ // End of GlobalQFunctionsGroup group

template<typename qenum>
QString global_qfunctions::qEnumToQString(const qenum value, const bool printEnumKeyOnly) {

	QMetaEnum metaEnum(QMetaEnum::fromType<qenum>());
	// Convert enumeration value to std::string
	// Cast value to int to comply with function definition
	//std::string valueStr(metaEnum.valueToKey(int(value)));
	const char * valueCStr = metaEnum.valueToKey(int(value));

	QString fullValueStr(QString::null);
	if (valueCStr == NULL)
		fullValueStr.append("UNKNOWN_ENUM");
	else {
		std::string valueStr(valueCStr);

		QEXCEPTION_ACTION_COND((valueStr.empty() == true), throw,  "Convertion of enumerator " << metaEnum.scope() << "::" << metaEnum.name() << " to string return a null std::string");

		if (printEnumKeyOnly == false) {
			fullValueStr.append(metaEnum.scope());
			fullValueStr.append("::");
			fullValueStr.append(metaEnum.name());
			fullValueStr.append("::");
		}

		fullValueStr.append(valueStr.c_str());
	}

	return fullValueStr;
}

template<typename qenum>
qenum global_qfunctions::qStringToQEnum(const QString & str) {

	QMetaEnum metaEnum(QMetaEnum::fromType<qenum>());
	int val = -1;
	if (metaEnum.isFlag() == true) {
		// Conversion QString -> std::string -> const char *
		val = metaEnum.keysToValue(str.toStdString().c_str());
	} else {
		// Conversion QString -> std::string -> const char *
		val = metaEnum.keyToValue(str.toStdString().c_str());
	}
	qenum valEnum = static_cast<qenum>(val);

	return valEnum;
}


#endif // GLOBAL_QFUNCTIONS_H