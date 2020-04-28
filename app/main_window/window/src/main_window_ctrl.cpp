/**
 * @copyright
 * @file main_window_ctrl.cpp
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "key_sequence.h"
#include "main_window_ctrl.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlOverall, "mainWindowCtrl.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlUserInput, "mainWindowCtrl.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlSearch, "mainWindowCtrl.search", MSG_TYPE_LEVEL)

main_window_ctrl::MainWindowCtrl::MainWindowCtrl(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent) : main_window_ctrl_base::MainWindowCtrlBase(core, parent, main_window_ctrl::commandFileFullPath) {

	// Shortcuts
	this->createExtraShortcuts();

	// Connect signals and slots
	this->connectExtraSignals();

	// Update info label - as no tabs in the window, then updateInfo must be explicitely called
	const int tabIndex = this->windowCore->getCurrentTabIndex();
	this->updateInfo(tabIndex);
}

main_window_ctrl::MainWindowCtrl::~MainWindowCtrl() {

}

void main_window_ctrl::MainWindowCtrl::createExtraShortcuts() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Create shortcuts");

}

void main_window_ctrl::MainWindowCtrl::connectExtraSignals() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Connect signals");

	connect(this->windowCore->topMenuBar->getFileMenu()->exitAction, &QAction::triggered, this, &main_window_ctrl::MainWindowCtrl::closeWindow);

}

void main_window_ctrl::MainWindowCtrl::keyReleaseEvent(QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();
	QString userTypedText = this->windowCore->getUserText();

	if (event->type() == QEvent::KeyRelease) {

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Backspace:
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << userTypedText);
				// Last position of the string
				if (userTypedText.isEmpty() == false) {
					// Compute position of the last character in the string
					const int endString = userTypedText.count() - 1;
					// Delete last character of the string
					userTypedText = userTypedText.remove(endString, 1);
					this->printUserInput(main_window_shared_types::text_action_e::SET, userTypedText);
				} else if (windowState != main_window_shared_types::state_e::COMMAND) {
					this->moveToCommandStateFromNonIdleState(windowState, static_cast<Qt::Key>(releasedKey));
				}
				break;
			default:
				break;
		}
	}
}

void main_window_ctrl::MainWindowCtrl::executeAction(const main_window_shared_types::state_e & windowState) {
	const QString userTypedText = this->windowCore->getUserText();
	switch (windowState) {
		case main_window_shared_types::state_e::QUIT:
			this->closeWindow();
			break;
		case main_window_shared_types::state_e::TOGGLE_MENUBAR:
			this->toggleShowMenubar();
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::COMMAND:
			// Cannot use userTypesText because it has been updated by the printUserInput function
			this->executeCommand(userTypedText, main_window_shared_types::state_postprocessing_e::ACTION);
			break;
		default:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "User typed text " << userTypedText);
			break;
	}
}

void main_window_ctrl::MainWindowCtrl::prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) {

	const int pressedKey = event->key();

	switch (windowState) {
		case main_window_shared_types::state_e::COMMAND:
			if (pressedKey == Qt::Key_Space) {
				this->executeCommand(this->windowCore->getUserText(), main_window_shared_types::state_postprocessing_e::NONE);
			} else if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
				this->printUserInput(main_window_shared_types::text_action_e::APPEND, event->text());
			}
			break;
		case main_window_shared_types::state_e::IDLE:
			if (pressedKey == Qt::Key_Colon) {
				const main_window_shared_types::state_e requestedWindowState = main_window_shared_types::state_e::COMMAND;
				this->changeWindowState(requestedWindowState, main_window_shared_types::state_postprocessing_e::POSTPROCESS, static_cast<Qt::Key>(pressedKey));
				this->setAllShortcutEnabledProperty(false);
			}
			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
			break;
		default:
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlUserInput,  "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}
}

void main_window_ctrl::MainWindowCtrl::toggleShowMenubar() {
	const bool menubarVisible = this->windowCore->topMenuBar->isVisible();
	this->windowCore->topMenuBar->setVisible(!menubarVisible);
}

void main_window_ctrl::MainWindowCtrl::closeWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close slot: exiting from the browser");
	emit this->closeWindowSignal();
}

void main_window_ctrl::MainWindowCtrl::postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) {
	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Previous windowState " << previousState << " and current windowState " << windowState );

	switch (windowState) {
		case main_window_shared_types::state_e::IDLE:
			this->setAllShortcutEnabledProperty(true);
			this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
			break;
		case main_window_shared_types::state_e::QUIT:
			this->closeWindow();
			break;
		case main_window_shared_types::state_e::TOGGLE_MENUBAR:
			this->toggleShowMenubar();
			this->changeWindowState(main_window_shared_types::state_e::IDLE, main_window_shared_types::state_postprocessing_e::POSTPROCESS);
			break;
		case main_window_shared_types::state_e::COMMAND:
			this->setAllShortcutEnabledProperty(false);
			break;
		default: 
			QEXCEPTION_ACTION(throw, "Unable to postprocess transaction to " << windowState << " is valid as state " << windowState << " doesn't have a defined postprocess action");
			break;
	}
}

bool main_window_ctrl::MainWindowCtrl::isValidWindowState(const main_window_shared_types::state_e & requestedWindowState) {
	bool isValid = false;
	const main_window_shared_types::state_e windowState = this->windowCore->getMainWindowState();

	switch (requestedWindowState) {
		case main_window_shared_types::state_e::IDLE:
			// It is always possible to go to the idle state
			isValid = true;
			break;
		case main_window_shared_types::state_e::QUIT:
		case main_window_shared_types::state_e::COMMAND:
		case main_window_shared_types::state_e::TOGGLE_MENUBAR:
			// It is only possible to start a new command if in the idle state
			isValid = (windowState == main_window_shared_types::state_e::IDLE);
			break;
		default: 
			QEXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}
