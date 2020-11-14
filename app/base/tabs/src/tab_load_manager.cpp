/**
 * @copyright
 * @file tab_load_manager.cpp
 * @author Andrea Gianarda
 * @date 09th April 2020
 * @brief Tab Load Manager functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "base/tabs/include/tab_load_manager.h"

// Categories
LOGGING_CONTEXT(tabLoadManagerOverall, tabLoadManager.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabLoadManagerStatus, tabLoadManager.status, TYPE_LEVEL, INFO_VERBOSITY)

tab_load_manager::TabLoadManager::TabLoadManager(QWidget * parent): QWidget(parent), status(tab_shared_types::load_status_e::IDLE), progress(0) {
	LOG_INFO(logger::info_level_e::ZERO, tabLoadManagerOverall,  "TabLoadManager constructor");

}

tab_load_manager::TabLoadManager::~TabLoadManager() {
	LOG_INFO(logger::info_level_e::ZERO, tabLoadManagerOverall,  "TabLoadManager destructor");

}

void tab_load_manager::TabLoadManager::startLoading() {
	this->setProgress(0);
}

void tab_load_manager::TabLoadManager::setProgress(const int & value) {
	if (this->progress != value) {
		this->progress = value;
		emit progressChanged(this->progress);
		this->setStatus(tab_shared_types::load_status_e::LOADING);
	}
}

void tab_load_manager::TabLoadManager::endLoading(const bool & success) {
	if (success == true) {
		this->setStatus(tab_shared_types::load_status_e::FINISHED);
	} else {
		this->setStatus(tab_shared_types::load_status_e::ERROR);
	}
}

void tab_load_manager::TabLoadManager::setStatus(const tab_shared_types::load_status_e & value) {
	if (this->status != value) {
		LOG_INFO(logger::info_level_e::ZERO, tabLoadManagerStatus,  "tab load status changed from " << this->status << " to " << value);
		this->status = value;
		emit statusChanged(this->status);
	}
}

CONST_GETTER(tab_load_manager::TabLoadManager::getProgress, int &, this->progress)

CONST_GETTER(tab_load_manager::TabLoadManager::getStatus, tab_shared_types::load_status_e &, this->status)
