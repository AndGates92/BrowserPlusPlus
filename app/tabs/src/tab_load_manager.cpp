/**
 * @copyright
 * @file tab_load_manager.cpp
 * @author Andrea Gianarda
 * @date 09rd April 2020
 * @brief Tab Load Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "tab_load_manager.h"

// Categories
Q_LOGGING_CATEGORY(tabLoadManagerOverall, "tabLoadManager.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(tabLoadManagerStatus, "tabLoadManager.status", MSG_TYPE_LEVEL)

tab_load_manager::TabLoadManager::TabLoadManager(QWidget * parent): QWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabLoadManagerOverall,  "TabLoadManager constructor");

	this->progress = 0;
	this->status = tab_shared_types::load_status_e::IDLE;

}

tab_load_manager::TabLoadManager::~TabLoadManager() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabLoadManagerOverall,  "TabLoadManager destructor");

}

void tab_load_manager::TabLoadManager::startLoading() {
	this->setProgress(0);
}

void tab_load_manager::TabLoadManager::setProgress(int value) {
	if (this->progress != value) {
		this->progress = value;
		emit progressChanged(this->progress);
		this->setStatus(tab_shared_types::load_status_e::LOADING);
	}
}

void tab_load_manager::TabLoadManager::endLoading(bool success) {
	if (success == true) {
		this->setStatus(tab_shared_types::load_status_e::FINISHED);
	} else {
		this->setStatus(tab_shared_types::load_status_e::ERROR);
	}
}

void tab_load_manager::TabLoadManager::setStatus(tab_shared_types::load_status_e value) {
	if (this->status != value) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabLoadManagerStatus,  "tab load status changed from " << this->status << " to " << value);
		this->status = value;
		emit statusChanged(this->status);
	}
}

BASE_GETTER(tab_load_manager::TabLoadManager::getProgress, int, this->progress)

BASE_GETTER(tab_load_manager::TabLoadManager::getStatus, tab_shared_types::load_status_e, this->status)