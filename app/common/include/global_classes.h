#ifndef GLOBAL_CLASSES_H
#define GLOBAL_CLASSES_H
/**
 * @copyright
 * @file global_classes.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Classes header file
*/

#include <string>

/** @defgroup CommonGroup Common Macros and Functions Doxygen Group
 *  Common Macros and Functions
 *  @{
 */

namespace app {

	namespace shared {

		/**
		 * @brief StringCompare struct
		 *
		 */
		struct StringCompare {
			// Struct sets the default access to public
			/**
			 * @brief Function: bool operator() (const std::string & rhs, const std::string & lhs) const
			 *
			 * \param rhs: string to compare
			 * \param lhs: string to compare
			 *
			 * \return: true if the two strings are identical, false otherwise
			 *
			 * This function compares two std::string objects
			 */
			bool operator() (const std::string & rhs, const std::string & lhs) const;
		};

	}

}
/** @} */ // End of CommonGroup group

#endif // GLOBAL_CLASSES_H
