#ifndef TYPE_PRINT_MACROS_H
#define TYPE_PRINT_MACROS_H
/**
 * @copyright
 * @file global_macros.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Type Print Macros file
*/

#include "global_functions.h"

/** @defgroup TypePrintMacrosGroup Type Print Macros Doxygen Group
 *  Type Print Macros
 *  @{
 */

/**
 * @brief QDEBUG_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 * It needs the type to be coverted to a QString
 */
#define QDEBUG_OVERLOAD_PRINT_OP(TYPE) \
	QDebug & operator<< (QDebug & os, const TYPE & value) { \
		QString str(QString::null); \
		str << value; \
		os << str; \
		return os; \
	}

/**
 * @brief QSTRING_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 * It needs the type to be coverted to a QString
 */
#define QSTRING_OVERLOAD_PRINT_OP(TYPE) \
	QString & operator<< (QString & str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		str.append(valStr); \
		return str; \
	}

/**
 * @brief QSTRING_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define QSTRING_OVERLOAD_PLUS_OP(TYPE) \
	const QString operator+ (const QString & str, const TYPE & value) { \
		QString mergedStr(QString::null); \
		QTextStream(&mergedStr) << str << value; \
		return str; \
	}

/**
 * @brief STRING_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define STRING_OVERLOAD_PLUS_OP(TYPE) \
	const std::string operator+ (const std::string & str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		std::string mergedStr; \
		mergedStr = str + valStr.toStdString(); \
		return mergedStr; \
	}

/**
 * @brief CHAR_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define CHAR_OVERLOAD_PLUS_OP(TYPE) \
	const std::string operator+ (const char * str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		std::string mergedStr; \
		mergedStr = str + valStr.toStdString(); \
		return mergedStr; \
	}

/**
 * @brief QTEXTSTREAM_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 */
#define QTEXTSTREAM_OVERLOAD_PRINT_OP(TYPE) \
	QTextStream & operator<< (QTextStream & str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		str << valStr; \
		return str; \
	}

/**
 * @brief OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE)
 *
 * \param TYPE : type to have operator overloaded for
 *
 * Define function body to overload operator + and operator << for a type Type.
 */
#define OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE) \
	STRING_OVERLOAD_PLUS_OP(TYPE) \
	CHAR_OVERLOAD_PLUS_OP(TYPE) \
	QDEBUG_OVERLOAD_PRINT_OP(TYPE) \
	QSTRING_OVERLOAD_PRINT_OP(TYPE) \
	QTEXTSTREAM_OVERLOAD_PRINT_OP(TYPE) \
	QSTRING_OVERLOAD_PLUS_OP(TYPE)

/**
 * @brief OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE)
 *
 * \param TYPE : type to have operator overloaded for
 *
 * Declares function prototypes to overload operator + and operator << for a type Type.
 */
#define OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(CLASS, TYPE) \
	Q_ENUM_NS(CLASS) \
	QDebug & operator<< (QDebug & os, const TYPE & type); \
	QTextStream & operator<< (QTextStream & str, const TYPE & type); \
	QString & operator<< (QString & str, const TYPE & type); \
	const QString operator+ (const QString & str, const TYPE & type); \
	const std::string operator+ (const std::string & str, const TYPE & value); \
	const std::string operator+ (const char * cStr, const TYPE & value);

/** @} */ // End of TypePrintMacrosGroup group

#endif // TYPE_PRINT_MACROS_H
