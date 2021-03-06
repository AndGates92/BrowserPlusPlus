#ifndef SECONDARY_WINDOW_UTILITY_H
#define SECONDARY_WINDOW_UTILITY_H
/**
 * @copyright
 * @file utility.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Secondary Window Utility header file
*/

#include <type_traits>
#include <string>
#include <memory>

#include <QtCore/QDir>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileSystemModel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>

#include "app/utility/qt/qt_operator.h"
#include "app/widgets/commands/action.h"
#include "app/windows/secondary_windows/shared/combo_box_item.h"

/** @defgroup SecondaryWindowUtilityGroup Secondary Window Utility Doxygen Group
 *  Secondary Window Utility functions and classes
 *  @{
 */

EXPORT_CONTEXT(secondaryWindowUtilityOverall)

namespace app {

	namespace commands {

		class KeySequence;

	}

	namespace secondary_window {

		/**
		 * @brief Function: std::unique_ptr<app::commands::Action> createAction(QObject * parent, const std::string & text, const std::string & tip, const app::commands::KeySequence & shortcut)
		 *
		 * \param parent: parent object
		 * \param text: descriptive text of the action
		 * \param tip: action status tip
		 * \param shortcut: shortcut linked to the action
		 *
		 * This function creates a new action
		 */
		std::unique_ptr<app::commands::Action> createAction(QObject * parent, const std::string & text, const std::string & tip, const app::commands::KeySequence & shortcut);

		/**
		 * @brief Function: std::shared_ptr<QLineEdit> createLineEdit(QWidget * parent, const std::string & text, const std::unique_ptr<app::commands::Action> & focusAction)
		 *
		 * \param parent: parent widget
		 * \param text: text to show on the line edit
		 * \param focusAction: action that sets the focus to the line edit
		 *
		 * This function creates a new QLineEdit
		 */
		std::shared_ptr<QLineEdit> createLineEdit(QWidget * parent, const std::string & text, const std::unique_ptr<app::commands::Action> & focusAction);

		/**
		 * @brief Function: std::unique_ptr<QFileSystemModel> createFileModel(QWidget * parent, const QStringList & filters, const QDir & directory)
		 *
		 * \param parent: parent widget
		 * \param filters: file dialog filters
		 * \param directory: current dialog directory
		 *
		 * This function creates a new QFileSystemModel
		 */
		std::unique_ptr<QFileSystemModel> createFileModel(QWidget * parent, const QStringList & filters, const QDir & directory);

		/**
		 * @brief Function: std::unique_ptr<QTreeView> createFileView(std::unique_ptr<QFileSystemModel> & model, QWidget *parent, const QStringList & filters, const QDir & directory)
		 *
		 * \param model: model of the fileview
		 * \param parent: parent widget
		 * \param filters: file dialog filters
		 * \param directory: current dialog directory
		 *
		 * This function creates a new QTreeView to display the content of the model. If the pointer to the model is null, this method will construct one based on the informations provided
		 */
		std::unique_ptr<QTreeView> createFileView(std::unique_ptr<QFileSystemModel> & model, QWidget *parent, const QStringList & filters = QStringList(), const QDir & directory = QDir::currentPath());

		/**
		 * @brief Function: std::unique_ptr<QPushButton> createPushButton(QWidget *parent, const std::unique_ptr<app::commands::Action> & actionPtr)
		 *
		 * \param parent: parent widget
		 * \param actionPtr: action to link to the push button
		 *
		 * This function creates a new QPushButton
		 */
		std::unique_ptr<QPushButton> createPushButton(QWidget *parent, const std::unique_ptr<app::commands::Action> & actionPtr);

		/**
		 * @brief Function: std::shared_ptr<QComboBox> createComboBox(QWidget *parent, const std::list<BoxItem> & items)
		 *
		 * \param parent: parent widget
		 * \param items: items of the comboBox
		 *
		 * This function creates a new QComboBox
		 */
		template<class BoxItem, typename std::enable_if<std::is_base_of<app::combo_box_item::ComboBoxItem, BoxItem>::value, void>::type* = nullptr>
		std::shared_ptr<QComboBox> createComboBox(QWidget *parent, const std::list<BoxItem> & items);

		/**
		 * @brief Function: std::unique_ptr<QGroupBox> createGroupBox(QWidget *parent, const std::string title)
		 *
		 * \param parent: parent widget
		 * \param title: title of the group box
		 *
		 * This function creates a new QGroupBox
		 */
		std::unique_ptr<QGroupBox> createGroupBox(QWidget *parent, const std::string title);

		/**
		 * @brief Function: std::unique_ptr<QCheckBox> createCheckBox(QWidget *parent, const std::unique_ptr<app::commands::Action> & toggleAction)
		 *
		 * \param parent: parent widget
		 * \param toggleAction: action that toggles the check in the check box
		 *
		 * This function creates a new QCheckBox
		 */
		std::unique_ptr<QCheckBox> createCheckBox(QWidget *parent, const std::unique_ptr<app::commands::Action> & toggleAction);

	}

}
/** @} */ // End of SecondaryWindowUtilityGroup group

// Enable this function only if the template class BoxItem inherits app::combo_box_item::ComboBoxItem
template<class BoxItem, typename std::enable_if<std::is_base_of<app::combo_box_item::ComboBoxItem, BoxItem>::value, void>::type* = nullptr>
std::shared_ptr<QComboBox> app::secondary_window::createComboBox(QWidget *parent, const std::list<BoxItem> & items) {

	LOG_INFO(app::logger::info_level_e::ZERO, secondaryWindowUtilityOverall, "Creating Combo Box object");

	std::shared_ptr<QComboBox> comboBox = std::make_shared<QComboBox>(parent);
	comboBox->setFrame(false);
	comboBox->setEditable(false);
	comboBox->setDuplicatesEnabled(false);
	comboBox->setInsertPolicy(QComboBox::InsertAlphabetically);
	comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	constexpr int comboBoxVSpacing = 5;
	comboBox->setFixedHeight(comboBox->fontMetrics().height() + 2 * comboBoxVSpacing);

	for (auto item = items.cbegin(); item != items.cend(); item++) {
		LOG_INFO(app::logger::info_level_e::ZERO, secondaryWindowUtilityOverall, "Adding item " << item->getText() << " to Combo Box");
		comboBox->addItem(item->getIcon(), QComboBox::tr(item->getText().c_str()), item->getUserData());
		if (item->getAction() != nullptr) {
			comboBox->addAction(const_cast<app::commands::Action *>(item->getAction().get()));

			QObject::connect(item->getAction().get(), &app::commands::Action::triggered, comboBox.get(), [comboBox, item]() {
				comboBox->setCurrentText(QString::fromStdString(item->getText()));
			});
		}
	}

	return comboBox;
}


#endif // SECONDARY_WINDOW_UTILITY_H
