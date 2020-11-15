/**
 * @copyright
 * @file open_file.cpp
 * @author Andrea Gianarda
 * @date 12th October 2020
 * @brief Open file functions
 */

#include <QtTest/QTest>
#include <QtGui/QKeySequence>

#include <sstream>
#include <string>

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "utility/qt/include/qt_operator.h"
#include "utility/stl/include/stl_helper.h"
#include "tests/include/open_file.h"
#include "base/tester/include/base_suite.h"

LOGGING_CONTEXT(openFileOverall, openFile.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openFileTest, openFile.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace open_file {

	namespace {

		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string jsonFilePath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		static const std::string jsonFileName("tab_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		static const std::string jsonFileFullPath(jsonFilePath + jsonFileName);

	}

}

open_file::OpenFile::OpenFile(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts) : command_test::CommandTest(testSuite, "Open file", open_file::jsonFileFullPath, useShortcuts) {
	LOG_INFO(logger::info_level_e::ZERO, openFileOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

open_file::OpenFile::~OpenFile() {
	LOG_INFO(logger::info_level_e::ZERO, openFileOverall,  "Test " << this->getName() << " destructor");
}

void open_file::OpenFile::testBody() {

	LOG_INFO(logger::info_level_e::ZERO, openFileTest,  "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::unique_ptr<main_window::CtrlWrapper> & windowCtrl =  this->windowWrapper->getWindowCtrl();
	const std::shared_ptr<main_window::Core> & windowCore = this->windowWrapper->getWindowCore();

	const std::string openCommandName("open file");
	this->executeCommand(openCommandName, std::string());

	const std::shared_ptr<main_window::PopupContainer> & popupContainer = this->windowWrapper->getPopupContainer();
	ASSERT((popupContainer != nullptr), test_enums::error_type_e::POPUP, "Popup container pointer is null");
	std::shared_ptr<open_popup::OpenPopup> openFilePopup = popupContainer->getOpenFilePopup();
	ASSERT((openFilePopup != nullptr), test_enums::error_type_e::POPUP, "Open file popup pointer is null");
	std::stringstream openFilePopupAddress;
	openFilePopupAddress << openFilePopup.get();
	std::shared_ptr<popup_base::PopupBase> currentPopupWidget = popupContainer->getCurrentWidget();
	ASSERT((currentPopupWidget != nullptr), test_enums::error_type_e::POPUP, "Current popup widget pointer is null");
	std::stringstream currentPopupWidgetAddress;
	currentPopupWidgetAddress << currentPopupWidget.get();
	ASSERT((openFilePopup == currentPopupWidget), test_enums::error_type_e::POPUP, "Open file popup pointer address " + openFilePopupAddress.str() + " doesn't match current popup widget " + currentPopupWidgetAddress.str());

	if (openFilePopup != nullptr) {
		ASSERT((openFilePopup->isVisible() == true), test_enums::error_type_e::POPUP, "Open file popup is not visible even though command " + openCommandName + " was executed.");

		ASSERT((windowCore->getTabCount() == 0), test_enums::error_type_e::TABS, "No tab opened but actual number of tabs is " + std::to_string(windowCore->getTabCount()));

		// Try to type text while not in insert mode
		const std::string dummyText("aaaaaa");
		QTest::keyClicks(openFilePopup.get(), QString::fromStdString(dummyText));
		QApplication::processEvents(QEventLoop::AllEvents);
		const std::string initialFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((initialFilePath.empty() == true), test_enums::error_type_e::POPUP, "Typed filepath is expected to be empty because the open file popup is not in insert mode instead it has the following text " + initialFilePath);

		// Enable insert mode
		QTest::keyEvent(QTest::KeyAction::Click, openFilePopup.get(), 'i');
		QApplication::processEvents(QEventLoop::AllEvents);

		// Open file
		const std::string filename("Makefile");
		QTest::keyClicks(openFilePopup.get(), QString::fromStdString(filename));
		QApplication::processEvents(QEventLoop::AllEvents);
		const std::string typedFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((typedFilePath.compare(filename) == 0), test_enums::error_type_e::POPUP, "Typed filepath " + typedFilePath + " doesn't match expected filepath " + filename);

		if (this->commandSentThroughShortcuts() == true) {
			QTest::keyClick(windowCtrl.get(), Qt::Key_Escape);
			QTest::keyEvent(QTest::KeyAction::Click, openFilePopup.get(), 'o');
		} else {
			QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);
		}
		QApplication::processEvents(QEventLoop::AllEvents);

		ASSERT((windowCore->getTabCount() == 1), test_enums::error_type_e::TABS, "Opened file " + filename + " in tab - actual number of tabs " + std::to_string(windowCore->getTabCount()));
		ASSERT((openFilePopup->isVisible() == false), test_enums::error_type_e::POPUP, "Open file popup is visible even though file " + filename + " was opened.");

		const std::string textInStatusBar = windowCore->bottomStatusBar->getUserInputText().toStdString();
		const bool foundFilename = (textInStatusBar.find(filename) != std::string::npos);
		const std::string filetype("file:");
		const bool foundFiletype = (textInStatusBar.find(filetype) != std::string::npos);

		ASSERT((foundFilename == true), test_enums::error_type_e::STATUSBAR, "Text in statusbar " + textInStatusBar + " is missing the filename " + filename);
		ASSERT((foundFiletype == true), test_enums::error_type_e::STATUSBAR, "Text in statusbar " + textInStatusBar + " is missing the filetype " + filetype);
	}

}
