#ifndef INHERITED_ENABLE_SHARED_FROM_THIS_H
#define INHERITED_ENABLE_SHARED_FROM_THIS_H
/**
 * @copyright
 * @file inherited_enable_shared_from_this.h
 * @author Andrea Gianarda
 * @date 15th of July 2020
 * @brief Inherited Enable Shared From This header file
*/

#include <memory>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "logging_macros.h"

/** @defgroup InheritedEnableSharedFromThisGroup Inherited Enable Shared From This Doxygen Group
 *  Inherited Enable Shared From This functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(inheritedEnableSharedFromThisOverall)

namespace inherited_enable_shared_from_this {

	/**
	 * @brief InheritedEnableSharedFromThis class
	 *
	 */
	template<typename derivedType, typename baseType>
	class InheritedEnableSharedFromThis {

		public:
			/**
			 * @brief Function: explicit InheritedEnableSharedFromThis()
			 *
			 * InheritedEnableSharedFromThis constructor
			 */
			explicit InheritedEnableSharedFromThis();

			/**
			 * @brief Function: virtual ~InheritedEnableSharedFromThis()
			 *
			 * InheritedEnableSharedFromThis destructor
			 */
			virtual ~InheritedEnableSharedFromThis();

			/**
			 * @brief Function: std::shared_ptr<derivedType> shared_from_this()
			 *
			 * \return shared pointer of this
			 *
			 * This function returns a shared pointer to this
			 */
			std::shared_ptr<derivedType> shared_from_this();

			/**
			 * @brief Function: std::weak_ptr<derivedType> weak_from_this()
			 *
			 * \return weak pointer of this
			 *
			 * This function returns a weak pointer to this
			 */
			std::weak_ptr<derivedType> weak_from_this();

	};
}
/** @} */ // End of InheritedEnableSharedFromThisGroup group

template<typename derivedType, typename baseType>
inherited_enable_shared_from_this::InheritedEnableSharedFromThis<derivedType, baseType>::InheritedEnableSharedFromThis() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, inheritedEnableSharedFromThisOverall,  "InheritedEnableSharedFromThis constructor");

}

template<typename derivedType, typename baseType>
inherited_enable_shared_from_this::InheritedEnableSharedFromThis<derivedType, baseType>::~InheritedEnableSharedFromThis() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, inheritedEnableSharedFromThisOverall,  "InheritedEnableSharedFromThis destructor");

}

template<typename derivedType, typename baseType>
std::shared_ptr<derivedType> inherited_enable_shared_from_this::InheritedEnableSharedFromThis<derivedType, baseType>::shared_from_this() {
	return std::static_pointer_cast<derivedType>(baseType::shared_from_this());
}

template<typename derivedType, typename baseType>
std::weak_ptr<derivedType> inherited_enable_shared_from_this::InheritedEnableSharedFromThis<derivedType, baseType>::weak_from_this() {
	return this->shared_from_this();
}

#endif // INHERITED_ENABLE_SHARED_FROM_THIS_H