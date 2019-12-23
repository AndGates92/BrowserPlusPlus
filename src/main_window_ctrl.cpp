/**
 * @copyright
 * @file main_window_ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_ctrl.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlOverall, "mainWindowCtrl.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlCenterWindow, "mainWindowCtrl.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlUserInput, "mainWindowCtrl.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlSearch, "mainWindowCtrl.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabs, "mainWindowCtrl.tabs", MSG_TYPE_LEVEL)

main_window_ctrl::MainWindowCtrl::MainWindowCtrl(QWidget * parent, int tabIndex, int tabCount) : parent(parent) {

	this->mainWindowState = main_window_shared_types::state_e::IDLE;
	this->userText = Q_NULLPTR;

	this->tabctrl = new main_window_ctrl_tab::MainWindowCtrlTab(parent, tabIndex, tabCount);

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

void main_window_ctrl::MainWindowCtrl::setAllMenuShortcutEnabledProperty(bool enabled) {
	emit this->enabledPropertyMenuSignal(enabled);
}

void main_window_ctrl::MainWindowCtrl::setAllWindowShortcutEnabledProperty(bool enabled) {
	this->tabctrl->setAllTabShortcutEnabledProperty(enabled);
	this->toggleShowMenuBarKey->setEnabled(enabled);
}

void main_window_ctrl::MainWindowCtrl::setAllShortcutEnabledProperty(bool enabled) {
	this->setAllMenuShortcutEnabledProperty(enabled);
	this->setAllWindowShortcutEnabledProperty(enabled);
}

void main_window_ctrl::MainWindowCtrl::createShortcuts() {
	// m will hide/show the menu bar
	this->toggleShowMenuBarKey = new QShortcut(parent);
	this->toggleShowMenuBarKey->setKey(Qt::Key_M);

	// q will close the browser
	this->closeKey = new QShortcut(parent);
	this->closeKey->setKey(Qt::Key_Q);
}

void main_window_ctrl::MainWindowCtrl::connectSignals() {

	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubar);
	connect(this->closeKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::closeWindow);

	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setShortcutEnabledPropertySignal, this, &main_window_ctrl::MainWindowCtrl::setAllShortcutEnabledProperty);
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setUserInputStrSignal, this, &main_window_ctrl::MainWindowCtrl::formUserInputStr);

	// Share window state with tab control
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::setStateSignal, this, &main_window_ctrl::MainWindowCtrl::setState);
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::requestStateSignal, this, &main_window_ctrl::MainWindowCtrl::getState);
	connect(this, &main_window_ctrl::MainWindowCtrl::sendStateSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::receiveState);

	// share current tab index
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::requestCurrentTabIndexSignal, this, &main_window_ctrl::MainWindowCtrl::getCurrentTabIndex);
	connect(this, &main_window_ctrl::MainWindowCtrl::sendCurrentTabIndexSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::receiveCurrentTabIndex);

	// share tab count
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::requestTabCountSignal, this, &main_window_ctrl::MainWindowCtrl::getTabCount);
	connect(this, &main_window_ctrl::MainWindowCtrl::sendTabCountSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::receiveTabCount);

	// open tab action
	connect(this, &main_window_ctrl::MainWindowCtrl::openNewTabSignal, this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::openNewTab);

	// Update info in the info bar following action
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::updateInfoActionSignal, this, &main_window_ctrl::MainWindowCtrl::updateInfo);

	// Update website in info bar
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::updateWebsiteSignal, this, &main_window_ctrl::MainWindowCtrl::updateWebsite);

	// Add tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::addNewTabSignal, this, &main_window_ctrl::MainWindowCtrl::addNewTab);

	// Close tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::closeTabSignal, this, &main_window_ctrl::MainWindowCtrl::closeTab);

	// Move tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::moveSignal, this, &main_window_ctrl::MainWindowCtrl::move);

	// Search in current tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::searchCurrentTabSignal, this, &main_window_ctrl::MainWindowCtrl::searchCurrentTab);

	// Refresh URL tab
	connect(this->tabctrl, &main_window_ctrl_tab::MainWindowCtrlTab::refreshUrlSignal, this, &main_window_ctrl::MainWindowCtrl::refreshUrl);

}

void main_window_ctrl::MainWindowCtrl::toggleShowMenubar() {
	emit toggleShowMenubarSignal();
}

void main_window_ctrl::MainWindowCtrl::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit closeWindowSignal();
}

void main_window_ctrl::MainWindowCtrl::executeCommand(QString command) {

	if (command.compare("open") == 0) {

	}
/*
	// m will hide/show the menu bar
	connect(this->toggleShowMenuBarKey, &QShortcut::activated, this, &main_window_ctrl::MainWindowCtrl::toggleShowMenubar);

	// q will close the browser
	connect(this->fileMenu->exitAction, &QAction::triggered, this, &main_window_ctrl::MainWindowCtrl::close);
*/
}

void main_window_ctrl::MainWindowCtrl::keyPressEvent(QKeyEvent * event) {

	int pressedKey = event->key();

	this->tabctrl->keyPressEvent(event);

	if (event->type() == QEvent::KeyPress) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " key " << event->text() << " i.e. number 0x" << hex << pressedKey);

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->userText);

				if (this->mainWindowState == main_window_shared_types::state_e::OPEN_TAB) {
					emit this->addNewTabSignal(this->userText);
				} else if (this->mainWindowState == main_window_shared_types::state_e::SEARCH) {
					emit this->searchCurrentTabSignal(this->userText);
				} else if ((this->mainWindowState == main_window_shared_types::state_e::CLOSE_TAB) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_LEFT) || (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE)) {
					this->tabctrl->processTabIndex(this->userText);
				}
				this->mainWindowState = main_window_shared_types::state_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
				break;
			case Qt::Key_Escape:
				this->mainWindowState = main_window_shared_types::state_e::IDLE;
				this->setAllShortcutEnabledProperty(true);
				formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
				break;
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << this->userText);
				// Last position of the string
				if (this->userText.isEmpty() == 0) {
					int endString = this->userText.count() - 1;
					this->userText.remove(endString, 1);
					formUserInputStr(main_window_shared_types::text_action_e::SET, this->userText);
				}
				break;
			default:
				if ((this->mainWindowState == main_window_shared_types::state_e::OPEN_TAB) || (this->mainWindowState == main_window_shared_types::state_e::SEARCH)) {
					if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
						formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					}
				} else if ((this->mainWindowState == main_window_shared_types::state_e::CLOSE_TAB) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_RIGHT) || (this->mainWindowState == main_window_shared_types::state_e::MOVE_LEFT)) {
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					} else {
						qWarning(mainWindowCtrlTabs) << "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
					// If no sign is provided, the tab is considered as absolute value
					// If + or - sign is provided, then the value is considered to be relative to the current tab
					// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
					// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					} else if ((this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::IDLE) && ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_L) || (pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_Minus))) {
						formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
					} else {
						qWarning(mainWindowCtrlTabs) << "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar\n";
					}
				} else if (this->mainWindowState == main_window_shared_types::state_e::COMMAND) {
					formUserInputStr(main_window_shared_types::text_action_e::APPEND, event->text());
					if (pressedKey >= Qt::Key_Space) {
						this->executeCommand(this->userText);
					}
				} else {
					if (pressedKey == Qt::Key_Colon) {
						this->mainWindowState = main_window_shared_types::state_e::COMMAND;
						this->setAllShortcutEnabledProperty(false);
					}
					formUserInputStr(main_window_shared_types::text_action_e::CLEAR);
				}
				break;
		}

	}

}

void main_window_ctrl::MainWindowCtrl::setShortcutEnabledProperty (bool enabled) {
	this->setAllShortcutEnabledProperty(enabled);
}

QString main_window_ctrl::MainWindowCtrl::getActionName() {
	QString actionName = Q_NULLPTR;
	switch (this->mainWindowState) {
		case main_window_shared_types::state_e::IDLE:
			actionName = "";
			break;
		case main_window_shared_types::state_e::OPEN_TAB:
			actionName = "open";
			break;
		case main_window_shared_types::state_e::COMMAND:
			actionName = "command";
			break;
		case main_window_shared_types::state_e::CLOSE_TAB:
			actionName = "close";
			break;
		case main_window_shared_types::state_e::REFRESH_TAB:
			actionName = "refresh";
			break;
		case main_window_shared_types::state_e::MOVE_LEFT:
			actionName = "move left";
			break;
		case main_window_shared_types::state_e::MOVE_RIGHT:
			actionName = "move right";
			break;
		case main_window_shared_types::state_e::TAB_MOVE:
			actionName = "move tab";
			if (this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::RIGHT) {
				actionName.append(" right");
			} else if (this->tabctrl->getMoveValueType() == main_window_shared_types::move_value_e::LEFT) {
				actionName.append(" left");
			}
			break;
		case main_window_shared_types::state_e::SEARCH:
			actionName = "search";
			break;
		default:
			actionName = "Unknown state";
			break;
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << this->mainWindowState << " action text " << actionName);

	return actionName;
}

void main_window_ctrl::MainWindowCtrl::formUserInputStr(const main_window_shared_types::text_action_e action, QString text) {

	QString textPrint = Q_NULLPTR;
	if (text == Q_NULLPTR) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "Action is " << action << " for user input " << textPrint);
	switch (action) {
		case main_window_shared_types::text_action_e::SET:
			this->userText.clear();
			this->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::APPEND:
			this->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::CLEAR:
			this->userText.clear();
			break;
		default:
			qWarning(mainWindowCtrlUserInput) << "Unknown action " << action << "\n";
			break;
	}

	QString textLabel = Q_NULLPTR;
	if (this->mainWindowState != main_window_shared_types::state_e::IDLE) {
		QString userAction = Q_NULLPTR;
		if (this->mainWindowState != main_window_shared_types::state_e::COMMAND) {
			userAction = this->getActionName();
		}
		textLabel.append(":" + userAction + " " + this->userText);

	}
	emit updateUserInputBarSignal(textLabel);
}

void main_window_ctrl::MainWindowCtrl::getState() {
	emit this->sendStateSignal(this->mainWindowState);
}

void main_window_ctrl::MainWindowCtrl::setState(main_window_shared_types::state_e state) {
	this->mainWindowState = state;
}

void main_window_ctrl::MainWindowCtrl::getCurrentTabIndex() {
	emit this->requestCurrentTabIndexSignal();
}

void main_window_ctrl::MainWindowCtrl::receiveCurrentTabIndex(int tabIndex) {
	emit this->sendCurrentTabIndexSignal(tabIndex);
}

void main_window_ctrl::MainWindowCtrl::getTabCount() {
	emit this->requestTabCountSignal();
}

void main_window_ctrl::MainWindowCtrl::receiveTabCount(int tabCount) {
	emit this->sendTabCountSignal(tabCount);
}

void main_window_ctrl::MainWindowCtrl::refreshUrl(int offset, int sign) {
	emit this->refreshUrlSignal(offset, sign);
}

void main_window_ctrl::MainWindowCtrl::closeTab(int index) {
	emit this->closeTabSignal(index);
}

void main_window_ctrl::MainWindowCtrl::move(int offset, int sign, const main_window_shared_types::object_type_e & object) {
	emit this->moveSignal(offset, sign, object);
}

void main_window_ctrl::MainWindowCtrl::addNewTab(QString search) {
	emit this->addNewTabSignal(search);
}

void main_window_ctrl::MainWindowCtrl::updateInfo(int index) {
	emit this->updateInfoActionSignal(index);
}

void main_window_ctrl::MainWindowCtrl::updateWebsite(int index) {
	emit this->updateWebsiteSignal(index);
}

void main_window_ctrl::MainWindowCtrl::searchCurrentTab(QString search) {
	emit this->searchCurrentTabSignal(search);
}

void main_window_ctrl::MainWindowCtrl::openNewTab() {
	emit this->openNewTabSignal();
}

