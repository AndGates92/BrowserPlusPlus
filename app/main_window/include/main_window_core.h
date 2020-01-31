#ifndef MAIN_WINDOW_CORE_H
#define MAIN_WINDOW_CORE_H
/**
 * @copyright
 * @file main_window_core.h
 * @author Andrea Gianarda
 * @date 30th of January 2019
 * @brief Main Window core class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtWidgets/QWidget>

#include "file_menu.h"
#include "edit_menu.h"
#include "tab_widget.h"
#include "command_menu.h"
#include "main_window_shared_types.h"

/** @defgroup MainWindowCoreGroup Main Window Core Doxygen Group
 *  Main Window core functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCoreOverall)

namespace main_window_core {

	/**
	 * @brief MainWindowCore class
	 *
	 */
	class MainWindowCore {

		public:

			/**
			 * @brief Function: explicit MainWindowCore()
			 *
			 * Main window core constructor
			 */
			explicit MainWindowCore();

			/**
			 * @brief Function: ~MainWindowCore()
			 *
			 * Main window core destructor
			 */
			~MainWindowCore();

			// main widget
			/**
			 * @brief main widget
			 *
			 */
			QWidget * mainWidget;

			/**
			 * @brief Tabs of browser
			 *
			 */
			tab_widget::TabWidget * tabs;

			// File dropdown menu
			/**
			 * @brief File menu
			 *
			 */
			file_menu::FileMenu * fileMenu;

			// Edit dropdown menu
			/**
			 * @brief Edit menu
			 *
			 */
			edit_menu::EditMenu * editMenu;

			/**
			 * @brief Command menu 
			 *
			 */
			command_menu::CommandMenu * cmdMenu;

			// Labels placed at the bottom of the window
			/**
			 * @brief user input
			 *
			 */
			QLabel * userInputText;

			/**
			 * @brief website
			 *
			 */
			QLabel * websiteText;

			/**
			 * @brief info
			 *
			 */
			QLabel * infoText;

			// Control members
			/**
			 * @brief state of the main window
			 *
			 */
			main_window_shared_types::state_e mainWindowState;

			/**
			 * @brief type of value of movements in tab bar
			 *
			 */
			main_window_shared_types::move_value_e moveValueType;

			/**
			 * @brief Text typed by the user
			 *
			 */
			QString userText;

			/**
			 * @brief Function: void createTabInfo()
			 *
			 * \return QString with the information
			 *
			 * This function creates the string with the tab information to be displayed at the bottom of the window
			 */
			QString createTabInfo();

	};

}
/** @} */ // End of MainWindowCoreGroup group

#endif // MAIN_WINDOW_CORE_H
