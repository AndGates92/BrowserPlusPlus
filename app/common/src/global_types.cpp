/**
 * @copyright
 * @file global_enums.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Global Types functions
 */

#include <iostream>

#include <QtCore/QTextStream>

#include "common/include/type_print_macros.h"
#include "common/include/global_enums.h"

namespace app {

	namespace shared {

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::shared::qinfo_level_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::shared::sign_e)

		// Overload << operator for offset_type_e
		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::shared::offset_type_e)

		// Overload << operator for element_position_e
		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::shared::element_position_e)

	}

}
