/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QShortcut>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	QWidget * mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	// main window body
	this->fillMainWindow(mainWidget);

	// Menu bar
	this->fillMenuBar();

	// main window layout
	this->mainWindowLayout(mainWidget);

	// Shortcuts
	this->createShortcuts();

	QString msg(tr("status bar message"));
	statusBar()->showMessage(msg);

	setWindowTitle(tr("Browser"));

	QSize winSize(320,400);
	resize(winSize);
}

void main_window::MainWindow::fillMainWindow(QWidget * mainWidget) {
	this->topWidget = new QWidget(mainWidget);
	// size policy horintally and vertically to expanding
	this->topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->centerWindow = new QLabel(tr("Example"), mainWidget);
	this->centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->centerWindow->setAlignment(Qt::AlignCenter);

	this->bottomWidget = new QWidget(mainWidget);
	// size policy horintally and vertically to expanding
	this->bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void main_window::MainWindow::mainWindowLayout(QWidget * mainWidget) {
	// Layout
	// -------------------------------------------------
	// |  <label>  |     <text to open>    | <browse>  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------

	QVBoxLayout * layout = new QVBoxLayout(mainWidget);
	layout->setContentsMargins(5,5,5,5);
	layout->addWidget(this->topWidget);
	layout->addWidget(this->centerWindow);
	layout->addWidget(this->bottomWidget);

	mainWidget->setLayout(layout);
}

void main_window::MainWindow::fillMenuBar() {
	this->fileMenu = new file_menu::FileMenu(this, this->menuBar(), "File", Qt::Key_F);
	connect(this->fileMenu, &file_menu::FileMenu::updateCenterWindow, this, &main_window::MainWindow::setCenterWindow);
	this->editMenu = new edit_menu::EditMenu(this, this->menuBar(), "Edit", Qt::Key_E);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::createShortcuts() {
	// m will hide/show the menu bar
	QShortcut * hideMenuBar = new QShortcut(this);
	hideMenuBar->setKey(Qt::Key_M);
	connect(hideMenuBar, &QShortcut::activated, this, &main_window::MainWindow::disableMenubar);
}

void main_window::MainWindow::disableMenubar() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	this->centerWindow->setText(str);
	this->centerWindow->repaint();
}
