#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H
/**
 * @copyright
 * @file global_functions.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Functions header file
*/

#include <string>
#include <list>

#include <qt5/QtCore/QMetaEnum>
#include <qt5/QtCore/QVariant>
#include <qt5/QtCore/QLoggingCategory>

#include "global_macros.h"
#include "exception_macros.h"

/** @defgroup GlobalFunctionsGroup Global Functions Doxygen Group
 *  Global Functions
 *  @{
 */
namespace global_functions {

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
	 * @brief Function: void moveListElements(std::list<type> & l, int from, int to)
	 *
	 * \param l: list whose elements are to be moved
	 * \param from: position where the element to move is
	 * \param to: position where the element has to be moved
	 *
	 * This function moves an element of the list l from position from to position to
	 */
	template<typename type>
	void moveListElements(std::list<type> & l, int from, int to);

	/**
	 * @brief Function: void printList(const global_types::qinfo_level_e & verbosity, const QLoggingCategory & category, const std::string & name, const std::list<type> & l)
	 *
	 * \param verbosity: verbosity level
	 * \param category: print category
	 * \param name: name of the list
	 * \param l: list to print
	 *
	 * This function allows to print all elements of a list
	 */
	template<typename type>
	void printList(const global_types::qinfo_level_e & verbosity, const QLoggingCategory & category (), const std::string & name, const std::list<type> & l);
}
/** @} */ // End of GlobalFunctionsGroup group

template<typename qenum>
QString global_functions::qEnumToQString(const qenum value, const bool printEnumKeyOnly) {

	QMetaEnum metaEnum(QMetaEnum::fromType<qenum>());
	// Convert enumeration value to std::string
	// Cast value to int to comply with function definition
	std::string valueStr = metaEnum.valueToKey(int(value));

	QEXCEPTION_ACTION_COND((valueStr.empty() == true), throw,  "Convertion of enuerator " << metaEnum.scope() << "::" << metaEnum.name() << " to string return a null std::string");

	QString fullValueStr(QString::null);

	if (printEnumKeyOnly == false) {
		fullValueStr.append(metaEnum.scope());
		fullValueStr.append("::");
		fullValueStr.append(metaEnum.name());
		fullValueStr.append("::");
	}

	fullValueStr.append(valueStr.c_str());

	return fullValueStr;
}

template<typename type>
void global_functions::moveListElements(std::list<type> & l, int from, int to) {

	const int lSize = l.size();

	auto fromIter = l.begin();
	QEXCEPTION_ACTION_COND((lSize < from), throw,  "Trying to access element at position " << from << " of a list that has " << lSize << " elements");
	std::advance(fromIter, from);

	auto toIter = l.begin();
	QEXCEPTION_ACTION_COND((lSize < to), throw,  "Trying to move element at position " << from << " to position " << to << " of a list that has " << lSize << " elements");
	std::advance(toIter, to);

	// insert element at index from at index to using iterator range (iter, firstEl, lastEl)
	// firstEl is always included whereas the element pointer by lastEl is not
	l.insert(toIter, fromIter, fromIter);

	// Delete element at position from as it has already copied at position to
	l.erase(fromIter);

}

template<typename type>
void global_functions::printList(const global_types::qinfo_level_e & verbosity, const QLoggingCategory & category (), const std::string & name, const std::list<type> & l) {

	std::for_each(
		l.cbegin(),
		l.cend(),
		[&verbosity, &category, &name](const type & el) {
			QINFO_PRINT(verbosity, category,  "[ List " << name.c_str() << " ] Element " << el.qprint());
		}
	);

}

#endif // GLOBAL_FUNCTIONS_H
