/**
 * @copyright
 * @file combo_box_find.cpp
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Find functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtCore/QVariant>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "windows/secondary_windows/find_window/include/combo_box_find.h"

// Categories
LOGGING_CONTEXT(comboBoxFindOverall, comboBoxFind.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::find_window::ComboBoxFind::ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const app::shared::offset_type_e itemDirection, std::unique_ptr<app::action::Action> itemAction) : app::combo_box_item::ComboBoxItem(itemIcon, itemUserData, itemAction), direction(itemDirection) {
	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxFindOverall,  "combo box find constructor with direction " << this->direction);

}

app::find_window::ComboBoxFind::ComboBoxFind(app::find_window::ComboBoxFind && rhs) : app::combo_box_item::ComboBoxItem(std::move(rhs)), direction(std::exchange(rhs.direction, app::shared::offset_type_e::IDLE)) {
	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxFindOverall,  "combo box find move constructor with direction " << this->direction);
}

app::find_window::ComboBoxFind & app::find_window::ComboBoxFind::operator=(app::find_window::ComboBoxFind && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, comboBoxFindOverall,  "Move assignment operator for combo box find with direction " << rhs.direction);

	if (&rhs != this) {
		app::combo_box_item::ComboBoxItem::operator=(std::move(rhs));
		this->direction = std::exchange(rhs.direction, app::shared::offset_type_e::IDLE);
	}

	return *this;
}

CONST_GETTER(app::find_window::ComboBoxFind::getDirection, app::shared::offset_type_e &, this->direction)
