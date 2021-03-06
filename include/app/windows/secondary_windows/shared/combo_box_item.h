#ifndef COMBO_BOX_ITEM_H
#define COMBO_BOX_ITEM_H
/**
 * @copyright
 * @file combo_box_item.h
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Item file
*/

#include <memory>

// Qt libraries
#include <QtCore/QVariant>
#include <QtGui/QIcon>

#include "app/shared/enums.h"
#include "app/widgets/commands/action.h"

/** @defgroup ComboBoxItemGroup Combo Box Item Doxygen Group
 *  Combo Box Item header functions and class
 *  @{
 */
namespace app {

	namespace commands {

		class Action;

	}

	namespace combo_box_item {

		/**
		 * @brief Combo box item class
		 *
		 */
		class ComboBoxItem {
			public:

				/**
				 * @brief Function: explicit ComboBoxItem(const QIcon itemIcon, const QVariant itemUserData, std::unique_ptr<app::commands::Action> & itemAction)
				 *
				 * \param itemIcon: icon of the combo box item
				 * \param itemUserData: user data of the combo box item
				 * \param itemAction: user data of the combo box item
				 *
				 * Combo box item constructor
				 */
				explicit ComboBoxItem(const QIcon itemIcon, const QVariant itemUserData, std::unique_ptr<app::commands::Action> & itemAction);

				/**
				 * @brief Function: virtual ~ComboBoxItem()
				 *
				 * Combo box find destructor
				 */
				virtual ~ComboBoxItem();

				// Move and copy constructor
				/**
				 * @brief Function: ComboBoxItem(ComboBoxItem && rhs)
				 *
				 * \param rhs: right hand side operand
				 *
				 * Combo box item move constructor
				 */
				ComboBoxItem(app::combo_box_item::ComboBoxItem && rhs);

				// Move and copy assignment operators
				/**
				 * @brief Function: ComboBoxItem & operator=(app::combo_box_item::ComboBoxItem && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * Command Combo box item move assignment operator
				 */
				ComboBoxItem & operator=(app::combo_box_item::ComboBoxItem && rhs);

				/**
				 * @brief Function: const QIcon & getIcon() const
				 *
				 * \return the icon of a combo box item
				 *
				 * This function returns the icon of a combo box item
				 */
				const QIcon & getIcon() const;

				/**
				 * @brief Function: const std::string getText() const
				 *
				 * \return the text of the action of a combo box item
				 *
				 * This function returns the text of the action of a combo box item
				 */
				const std::string getText() const;

				/**
				 * @brief Function: const QIcon & getUserData() const
				 *
				 * \return the user data of a combo box item
				 *
				 * This function returns the user data of a combo box item
				 */
				const QVariant & getUserData() const;

				/**
				 * @brief Function: const std::unique_ptr<app::commands::Action> & getAction() const
				 *
				 * \return the action of a combo box item
				 *
				 * This function returns the action of a combo box item
				 */
				const std::unique_ptr<app::commands::Action> & getAction() const;

			protected:

			private:
				/**
				 * @brief Function: ComboBoxItem()
				 *
				 * Combo box item default constructor
				 */
				ComboBoxItem() = delete;

				/**
				 * @brief Function: ComboBoxItem(const ComboBoxItem && rhs)
				 *
				 * \param rhs: right hand side operand
				 *
				 * Combo box item copy constructor
				 */
				ComboBoxItem(const app::combo_box_item::ComboBoxItem & rhs) = delete;

				/**
				 * @brief Function: ComboBoxItem & operator=(const app::combo_box_item::ComboBoxItem & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * Command Combo box item copy assignment operator
				 */
				ComboBoxItem & operator=(const app::combo_box_item::ComboBoxItem & rhs) = delete;

				/**
				 * @brief icon of the combo box item
				 *
				 */
				QIcon icon;

				/**
				 * @brief user data of the combo box item
				 *
				 */
				QVariant userData;

				/**
				 * @brief action of the combo box item
				 *
				 */
				std::unique_ptr<app::commands::Action> action;

		};

	}

}
/** @} */ // End of ComboBoxItemGroup group

#endif // COMBO_BOX_ITEM_H
