#ifndef MENU_H
#define MENU_H
/**
 * @copyright
 * @file menu.h
 * @author Andrea Gianarda
 * @date 23th of September 2019
 * @brief Menu header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtGui/QKeySequence>

Q_DECLARE_LOGGING_CATEGORY(menuOverall)

/** @defgroup MenuGroup Menu Doxygen Group
 *  Menu functions and classes
 *  @{
 */
namespace menu {

	class Menu : public QObject {

		Q_OBJECT

		public:
			explicit Menu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR, const char* menuName = "Unknown", const QKeySequence & key = QKeySequence::UnknownKey);

		protected:
			QWidget * window;
			QMenuBar * menuBar;
			QMenu * winMenu;
			const char * menuName;
			const QKeySequence key;

			void createMenu();
			void createShortcuts();

		private slots:
			void expandSlot();

		private:
	};
}
/** @} */ // End of MenuGroup group

#endif // GRAPHICS_H
