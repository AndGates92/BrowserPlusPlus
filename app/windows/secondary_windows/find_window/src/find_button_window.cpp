/**
 * @copyright
 * @file find_button_window.cpp
 * @author Andrea Gianarda
 * @date 17th of July 2020
 * @brief Find Button Window functions
 */

#include <string>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLayoutItem>

#include "logging_macros.h"
#include "find_button_window.h"
#include "exception_macros.h"
#include "secondary_window_utility.h"

// Categories
Q_LOGGING_CATEGORY(findButtonWindowOverall, "findButtonWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(findButtonWindowCancel, "findButtonWindow.cancel_button", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(findButtonWindowFind, "findButtonWindow.find_button", MSG_TYPE_LEVEL)

namespace find_button_window {

	namespace {
		/**
		 * @brief default layout stretch
		 *
		 */
		static constexpr int defaultStretch = 0;

		/**
		 * @brief vertical spacing between widgets
		 *
		 */
		static constexpr int widgetVSpacing = 10;

		/**
		 * @brief horizontal spacing between widgets
		 *
		 */
		static constexpr int widgetHSpacing = 10;
	}

}

find_button_window::FindButtonWindow::FindButtonWindow(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findButtonWindowOverall,  "Creating find button window");

	// Set modal because no other windows should be active
	this->setWindowModality(Qt::ApplicationModal);

	// Create action
	this->createActions();

	// Create widgets to put in the window
	this->fillWindow();

	// define window layout
	this->windowLayout();

	// Connect signals and slots
	this->connectSignals();

	// Set focus to the window
	// Don't allow other widgets to grab the focus - by default QLineEdit grabs it first
	this->setFocus();

	this->setFixedHeight(this->sizeHint().height());
}

find_button_window::FindButtonWindow::~FindButtonWindow() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findButtonWindowOverall,  "Destructor of FindButtonWindow class");
}

void find_button_window::FindButtonWindow::cancel() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findButtonWindowCancel,  "Closing dialog as Cancel button has been clicked");
	if (this->textToFind->hasFocus() == true) {
		this->setFocus();
	} else {
		this->close();
	}
}

void find_button_window::FindButtonWindow::close() {
	QWidget::close();
}

void find_button_window::FindButtonWindow::apply() {

	const QString & textToFind = this->textToFind->text();
	const global_enums::offset_type_e direction = this->settingsBox->getSearchDirection();
	const bool & caseSensitive = this->settingsBox->isCaseSensitiveSearch();
	const bool & matchFullWord = this->settingsBox->isMatchFullWordSearch();

	const find_settings::FindSettings settings(textToFind, direction, caseSensitive, matchFullWord);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findButtonWindowFind,  "Settings:" << settings);

	emit find(settings);

}

void find_button_window::FindButtonWindow::windowLayout() {

	// Layout
	// -------------------------------------------------
	// |                <text to find>                 |
	// |         <settings group box title>            |
	// |    <direction drop down>    |     <case>      |
	// |    <direction drop down>    |   <full word>   |
	// |         <find>         |       <cancel>       |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(find_button_window::widgetVSpacing);
		this->setLayout(layout);
	}

	try {
		// Remove all widgets in the layout in order to redraw it
		QVBoxLayout * layout = dynamic_cast<QVBoxLayout *>(this->layout());
		const int layoutSize = layout->count();
		for (int idx = 0; idx < layoutSize; idx++) {

			QLayoutItem * item(layout->takeAt(idx));

			if (item != nullptr) {
				QWidget * itemWidget = item->widget();
				// If item manages a widget, then itemWidget will not be null
				if (item->widget() == nullptr) {
					layout->removeItem(item);
				} else {
					layout->removeWidget(itemWidget);
				}
				delete item;
			}
		}

		QHBoxLayout * lastRow = new QHBoxLayout(this);
		// find button
		lastRow->addWidget(this->findButton.get(), find_button_window::defaultStretch, Qt::AlignLeft);
		lastRow->addSpacing(find_button_window::widgetHSpacing);
		// cancel button
		lastRow->addWidget(this->cancelButton.get(), find_button_window::defaultStretch, Qt::AlignRight);

		// Add layouts to main layout
		layout->addWidget(this->textToFind.get(), find_button_window::defaultStretch);
		layout->addWidget(this->settingsBox.get(), find_button_window::defaultStretch);
		layout->addLayout(lastRow);

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void find_button_window::FindButtonWindow::createActions() {

	this->findAction = std::move(secondary_window_utility::createAction(this, "Find", "Find text in the current page", key_sequence::KeySequence(Qt::Key_F)));
	this->cancelAction = std::move(secondary_window_utility::createAction(this, "Cancel", "Cancel operation", key_sequence::KeySequence(Qt::Key_Escape)));
	this->typeAction = std::move(secondary_window_utility::createAction(this, "Insert", "Insert", key_sequence::KeySequence(Qt::Key_I)));

}

void find_button_window::FindButtonWindow::fillWindow() {

	this->textToFind = secondary_window_utility::createLineEdit(this, "<text to search>", this->typeAction);
	this->textToFind->setText(QString());

	this->findButton = std::move(secondary_window_utility::createPushButton(this, this->findAction));
	this->cancelButton = std::move(secondary_window_utility::createPushButton(this, this->cancelAction));

	this->settingsBox = std::make_unique<find_button_window_settings::FindButtonWindowSettings>(this);

}

void find_button_window::FindButtonWindow::connectSignals() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findButtonWindowOverall,  "Connect signals");

	connect(this->findAction.get(), &action::Action::triggered, this, &find_button_window::FindButtonWindow::apply);
	connect(this->findButton.get(), &QPushButton::pressed, this, &find_button_window::FindButtonWindow::apply);
	connect(this->cancelAction.get(), &action::Action::triggered, this, &find_button_window::FindButtonWindow::cancel);
	connect(this->cancelButton.get(), &QPushButton::pressed, this, &find_button_window::FindButtonWindow::cancel);
}

QSize find_button_window::FindButtonWindow::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 4 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between 2 rows of widgets
	int height = this->textToFind->height() + this->settingsBox->height() + this->findButton->height() + 4 * find_button_window::widgetVSpacing;

	return QSize(width,height);
}