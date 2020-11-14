#ifndef MAIN_WINDOW_CTRL_WRAPPER_H
#define MAIN_WINDOW_CTRL_WRAPPER_H
/**
 * @copyright
 * @file main_window_ctrl_wrapper.h
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

#include "windows/main_window/common/include/main_window_shared_types.h"
#include "windows/main_window/window/include/main_window_ctrl.h"
#include "windows/main_window/window/include/main_window_ctrl_tab.h"
#include "common/include/constructor_macros.h"

/** @defgroup MainWindowCtrlWrapperGroup Main Window Doxygen Group
 *  Main Window control wrapper functions and classes
 *  @{
 */

namespace main_window {
	class MainWindow;
}

namespace main_window_ctrl_wrapper {

	/**
	 * @brief MainWindowCtrlWrapper class
	 *
	 */
	class MainWindowCtrlWrapper final : public QWidget, public main_window_base::MainWindowBase {
		friend class main_window::MainWindow;

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlWrapper(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrlWrapper(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core);

			/**
			 * @brief Function: virtual ~MainWindowCtrlWrapper()
			 *
			 * Main window control constructor
			 */
			virtual ~MainWindowCtrlWrapper();

			/**
			 * @brief Function: void keyReleaseEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			void keyReleaseEvent(QKeyEvent * event) override;

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event) override;

		protected:

		private:

			/**
			 * @brief Main window control
			 *
			 */
			std::unique_ptr<main_window_ctrl::MainWindowCtrl> winctrl;

			/**
			 * @brief main window tab control
			 *
			 */
			std::unique_ptr<main_window_ctrl_tab::MainWindowCtrlTab> tabctrl;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowCtrlWrapper
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowCtrlWrapper)

	};

}
/** @} */ // End of MainWindowCtrlWrapperGroup group

#endif // MAIN_WINDOW_CTRL_WRAPPER_H
