/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Top Menu functions
 */

#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "utility/stl/include/cpp_operator.h"

#include "base/menu/include/menu.h"

// Categories
LOGGING_CONTEXT(menuOverall, menu.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::menu::Menu::Menu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const app::key_sequence::KeySequence & key) : QWidget(parent), app::printable_object::PrintableObject(), menuBar(menuBar), menuName(menuName), key(key) {

	LOG_INFO(app::logger::info_level_e::ZERO, menuOverall, "Create menu:  " << *this);
	this->createMenu();
	this->createShortcuts();
}

app::base::menu::Menu::~Menu() {
	LOG_INFO(app::logger::info_level_e::ZERO, menuOverall,  "menu destructor");
}

void app::base::menu::Menu::createMenu() {
	EXCEPTION_ACTION_COND((this->menuBar.expired() == true), throw,  "Unable to get menu bar for menu " << menuName << " as it has already expired");
	std::shared_ptr<QMenuBar> bar = this->menuBar.lock();
	if (bar != Q_NULLPTR) {
		this->winMenu.reset(bar->addMenu(QWidget::tr(menuName)));
	}
}

void app::base::menu::Menu::createShortcuts() {
	this->expandMenu.reset(new QShortcut(this));

	// Do not bind key if it is not set
	if (this->key != app::key_sequence::KeySequence(QKeySequence::UnknownKey)) {
		this->expandMenu->setKey(this->key.toQKeySequence());
		connect(this->expandMenu.get(), &QShortcut::activated, this, &base::menu::Menu::expand);
	}
}

void app::base::menu::Menu::expand() {
	EXCEPTION_ACTION_COND((this->menuBar.expired() == true), throw,  "Unable to get menu bar for menu " << this->menuName << " as it has already expired");
	std::shared_ptr<QMenuBar> bar = this->menuBar.lock();
	if (bar != Q_NULLPTR) {
		// menu is expanded only if menu bar is visible
		if (bar->isVisible()) {
			LOG_INFO(app::logger::info_level_e::ZERO, menuOverall, "Expand menu " << this->menuName << " because shortcut key " << this->key.toString() << " has been pressed");
			this->winMenu->exec();
			this->setFocus();
		}
	}
}

void app::base::menu::Menu::setEnabledProperty(const bool & enabled) {
	this->expandMenu->setEnabled(enabled);
}

const std::string app::base::menu::Menu::print() const {
	std::string menuInfo;

	menuInfo = menuInfo + " name: " + this->menuName;
	menuInfo = menuInfo + " shortcut key: " + this->key.toString().toStdString();

	return menuInfo;
}
