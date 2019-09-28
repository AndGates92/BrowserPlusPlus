/**
 * @copyright
 * @file open_button_window.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Open Button Window functions
 */

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "open_button_window.h"


// Categories
Q_LOGGING_CATEGORY(openButtonWindowOverall, "openButtonWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowLayout, "openButtonWindow.layout", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowOpen, "openButtonWindow.open_button", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowCancel, "openButtonWindow.cancel_button", MSG_TYPE_LEVEL)

open_button_window::OpenButtonWindow::OpenButtonWindow(QWidget * parent, Qt::WindowFlags flags) : QDialog(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Creating open button window");

	// Set modal because other windows should not be active
	this->setModal(true);

	// Create widgets to put in the window
	this->fillWindow();

	QGridLayout * layout = this->windowLayout();

	this->setLayout(layout);
}

open_button_window::OpenButtonWindow::~OpenButtonWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Destructor");
	delete label;
	delete text;
	delete openButton;
	delete cancelButton;
}

void open_button_window::OpenButtonWindow::openSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Opening " << text->displayText());
	this->close();
}

void open_button_window::OpenButtonWindow::cancelSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowCancel,  "Deleting dialog as Cancel button has been clicked");
	this->close();
}

QGridLayout * open_button_window::OpenButtonWindow::windowLayout() {
	// Layout
	// -------------------------------------
	// |  <label>  |     <text to open>    |
	// |  <open>   |           | <cancel>  |
	// -------------------------------------
	QGridLayout * layout = new QGridLayout(this);
	int labelRowSpan = 1;
	int labelColumnSpan = 1;
	int labelFromRow = 0;
	int labelFromColumn = 0;
	layout->addWidget(this->label, labelFromRow, labelFromColumn, labelRowSpan, labelColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Label: start coordinates: row " << labelFromRow << " and column " << labelFromColumn << " width " << labelColumnSpan << " height " << labelRowSpan);
	int textRowSpan = labelRowSpan;
	int textColumnSpan = 3;
	int textFromRow = labelFromRow;
	int textFromColumn = labelFromColumn + labelColumnSpan;
	layout->addWidget(this->text, textFromRow, textFromColumn, textRowSpan, textColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Text: start coordinates: row " << textFromRow << " and column " << textFromColumn << " width " << textColumnSpan << " height " << textRowSpan);
	int openButtonRowSpan = 1;
	int openButtonColumnSpan = 1;
	int openButtonFromRow = labelFromRow + labelRowSpan;
	int openButtonFromColumn = 0;
	layout->addWidget(this->openButton, openButtonFromRow, openButtonFromColumn, openButtonRowSpan, openButtonColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Open button: start coordinates: row " << openButtonFromRow << " and column " << openButtonFromColumn << " width " << openButtonColumnSpan << " height " << openButtonRowSpan);
	int cancelButtonRowSpan = openButtonRowSpan;
	int cancelButtonColumnSpan = 2;
	int cancelButtonFromRow = openButtonFromRow;
	int cancelButtonFromColumn = textFromColumn + textColumnSpan - cancelButtonColumnSpan;
	layout->addWidget(this->cancelButton, cancelButtonFromRow, cancelButtonFromColumn, cancelButtonRowSpan, cancelButtonColumnSpan);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowLayout,  "Cancel button: start coordinates: row " << cancelButtonFromRow << " and column " << cancelButtonFromColumn << " width " << cancelButtonColumnSpan << " height " << cancelButtonRowSpan);

	return layout;
}

void open_button_window::OpenButtonWindow::fillWindow() {
	this->label = new QLabel(tr("Open -> "), this);
	this->label->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	this->label->setAlignment(Qt::AlignCenter);

	this->text = new QLineEdit(this);
	this->text->setPlaceholderText(tr("<URL or file to open>"));

	this->openButton = new QPushButton("Open", this);
	connect(this->openButton, SIGNAL(pressed()), this, SLOT(openSlot()));
	this->cancelButton = new QPushButton("Cancel", this);
	connect(this->cancelButton, SIGNAL(released()), this, SLOT(cancelSlot()));
}
