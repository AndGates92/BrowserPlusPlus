#ifndef ACTION_H
#define ACTION_H
/**
 * @copyright
 * @file action.h
 * @author Andrea Gianarda
 * @date 12th of June 2020
 * @brief Action class header file
*/

#include <list>

// Qt libraries
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>

#include "app/shared/constructor_macros.h"

#include "app/utility/log/printable_object.h"

/** @defgroup ActionGroup Action Widget Doxygen Group
 *  Action menu functions and classes
 *  @{
 */
namespace app {

	namespace commands {

		class KeySequence;

		/**
		 * @brief Action class
		 *
		 */
		class Action final : public QAction, public app::printable_object::PrintableObject {

			public:
				/**
				 * @brief Function: static app::commands::Action * createSeparator(QObject * parent)
				 *
				 * \param parent: parent object
				 *
				 * This function creates an action separator
				 */
				static app::commands::Action * createSeparator(QObject * parent);

				/**
				 * @brief Function: explicit Action(QObject * parent, const QString & text = QString(), const QIcon & icon = QIcon())
				 *
				 * \param parent: parent window
				 * \param text: descriptive text
				 * \param icon: icon linked to the action
				 *
				 * Action constructor
				 */
				explicit Action(QObject * parent, const QString & text = QString(), const QIcon & icon = QIcon());

				/**
				 * @brief Function: ~Action()
				 *
				 * Action destructor
				 */
				virtual ~Action();

				/**
				 * @brief Function: void setShortcut(const app::commands::KeySequence & shortcut)
				 *
				 * \param shortcut: primary shortcut key
				 *
				 * This function sets the primary shortcut key
				 */
				 void setShortcut(const app::commands::KeySequence & shortcut);

				/**
				 * @brief Function: void setShortcuts(const std::list<app::commands::KeySequence> & shortcuts)
				 *
				 * \param shortcuts: list of shortcuts that trigger the action
				 *
				 * This function sets the primary shortcut key
				 */
				 void setShortcuts(const std::list<app::commands::KeySequence> & shortcuts);

				/**
				 * @brief Function: app::commands::KeySequence shortcut() const
				 *
				 * \return primary shortcut key
				 *
				 * This function returns the primary shortcut key
				 */
				app::commands::KeySequence shortcut() const;

				/**
				 * @brief Function: std::list<app::commands::KeySequence> shortcuts() const
				 *
				 * \return a list of shortcuts
				 *
				 * This function returns a list of shortcuts where the primary one is at the head of the list
				 */
				std::list<app::commands::KeySequence> shortcuts() const;

				/**
				 * @brief Function: virtual const std::string print() const override
				 *
				 * \return action to print converted to std::string
				 *
				 * This functions prints action to print info to std::string
				 */
				virtual const std::string print() const override;

			protected:

			private:
				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class Action
				 *
				 */
				DISABLE_COPY_MOVE(Action)

		};

	}

}

/** @} */ // End of ActionGroup group

#endif // ACTION_H
