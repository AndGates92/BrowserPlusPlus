/**
 * @copyright
 * @file menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Menu bar functions
 */

#include <iostream>

#include "base/menu/include/menu_bar.h"
#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"

LOGGING_CONTEXT(menuBarOverall, menuBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

menu_bar::MenuBar::MenuBar(QWidget * parent) : QMenuBar(parent) {
	LOG_INFO(logger::info_level_e::ZERO, menuBarOverall,  "Menu bar constructor");

}

menu_bar::MenuBar::~MenuBar() {
	LOG_INFO(logger::info_level_e::ZERO, menuBarOverall,  "Menu bar desstructor");

}
