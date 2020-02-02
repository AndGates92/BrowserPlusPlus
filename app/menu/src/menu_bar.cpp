/**
 * @copyright
 * @file menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Menu bar functions
 */

#include <iostream>
// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "menu_bar.h"
#include "global_types.h"
#include "global_macros.h"

Q_LOGGING_CATEGORY(menuBarOverall, "menuBar.overall", MSG_TYPE_LEVEL)

menu_bar::MenuBar::MenuBar(QWidget * window) : QMenuBar(window), window(window) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, menuBarOverall,  "Main window menu bar constructor");

}

menu_bar::MenuBar::~MenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, menuBarOverall,  "Main window menu bar desstructor");

}
