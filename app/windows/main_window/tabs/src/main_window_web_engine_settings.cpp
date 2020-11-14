/**
 * @copyright
 * @file main_window_web_engine_settings.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine settings functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/main_window_web_engine_settings.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEngineSettingsOverall, mainWindowWebEngineSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_web_engine_settings::MainWindowWebEngineSettings::MainWindowWebEngineSettings(QWebEngineSettings * newSettings): web_engine_settings::WebEngineSettings(newSettings) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings constructor");

}

main_window_web_engine_settings::MainWindowWebEngineSettings::MainWindowWebEngineSettings(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs) : web_engine_settings::WebEngineSettings(rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy constructor web engine settings");

}

main_window_web_engine_settings::MainWindowWebEngineSettings & main_window_web_engine_settings::MainWindowWebEngineSettings::operator=(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy assignment operator for web engine settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	this->web_engine_settings::WebEngineSettings::operator=(rhs);

	return *this;
}

main_window_web_engine_settings::MainWindowWebEngineSettings::MainWindowWebEngineSettings(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs) :  web_engine_settings::WebEngineSettings(std::move(rhs)) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move constructor web engine settings");
}

main_window_web_engine_settings::MainWindowWebEngineSettings & main_window_web_engine_settings::MainWindowWebEngineSettings::operator=(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move assignment operator for web engine settings");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->web_engine_settings::WebEngineSettings::operator=(std::move(rhs));
	}

	return *this;
}

main_window_web_engine_settings::MainWindowWebEngineSettings::~MainWindowWebEngineSettings() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings destructor");

}
