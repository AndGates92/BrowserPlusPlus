/**
 * @copyright
 * @file main_window_tab_load_manager.cpp
 * @author Andrea Gianarda
 * @date 09rd April 2020
 * @brief Main Window Tab Load Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_tab_load_manager.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabLoadManagerOverall, "mainWindowTabLoadManager.overall", MSG_TYPE_LEVEL)

main_window_tab_load_manager::MainWindowTabLoadManager::MainWindowTabLoadManager(QWidget * parent): tab_load_manager::TabLoadManager(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabLoadManagerOverall,  "MainWindowTabLoadManager constructor");

}

main_window_tab_load_manager::MainWindowTabLoadManager::~MainWindowTabLoadManager() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabLoadManagerOverall,  "MainWindowTabLoadManager destructor");

}
