/**
 * @copyright
 * @file main_window_tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWebEngineWidgets/QWebEngineView>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "exception_macros.h"
#include "main_window_tab_widget.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): tab_widget::TabWidget(parent), tabTypes(QList<main_window_shared_types::tab_type_e>()) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");

}

main_window_tab_widget::MainWindowTabWidget::~MainWindowTabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

	const int idx = 0;

	// Delete all tabs until the count reaches 0
	// Always delete the first tab as for every deletion, all subsequents are shifted back
	while(this->count() > 0) {
		main_window_shared_types::tab_type_e type = this->getTabType(idx);

		Q_ASSERT_X(((type == main_window_shared_types::tab_type_e::LABEL) || (type == main_window_shared_types::tab_type_e::WEB_ENGINE)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
		this->removeTab(idx);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Removing tab type " << type);
	}

	for(QList<main_window_shared_types::tab_type_e>::const_iterator it = this->tabTypes.constBegin(); it != this->tabTypes.constEnd(); it++) {
		QWARNING_PRINT(mainWindowTabWidgetOverall,  "Tab type still not deleted " << (*it));
	}

	Q_ASSERT_X((this->tabTypes.empty() == true), "tab type list not empty", "List of tab types is not empty");

	this->tabTypes.clear();
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	this->tabTypes.append(type);
	int tabIndex = tab_widget::TabWidget::addTab(page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addTab(QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Open tab with label " << label);

	this->tabTypes.append(type);
	int tabIndex = tab_widget::TabWidget::addTab(page, icon, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(int index, QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	this->tabTypes.insert(index, type);
	int tabIndex = tab_widget::TabWidget::insertTab(index, page, label);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(int index, QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	this->tabTypes.insert(index, type);
	int tabIndex = tab_widget::TabWidget::insertTab(index, page, icon, label);

	return tabIndex;
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	tab_widget::TabWidget::removeTab(index);
	this->deleteListElement(index);
}

void main_window_tab_widget::MainWindowTabWidget::deleteListElement(int index) {

	QEXCEPTION_ACTION_COND(((index < 0) || (index >= this->tabTypes.count())), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << this->tabTypes.count() << ". Got " << index << ".");
	if (this->tabTypes.isEmpty() == false) {
		this->tabTypes.removeAt(index);
	}
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(int indexFrom, int indexTo) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Move tab from " << indexFrom << " to " << indexTo);
	this->bar->moveTab(indexFrom, indexTo);
	this->tabTypes.move(indexFrom, indexTo);
}

QWidget * main_window_tab_widget::MainWindowTabWidget::widget(int index, bool checkError) {
	QWidget * requestedWidget = tab_widget::TabWidget::widget(index, checkError);

	return requestedWidget;
}

main_window_shared_types::tab_type_e main_window_tab_widget::MainWindowTabWidget::getTabType(int index) {

	main_window_shared_types::tab_type_e tabType = main_window_shared_types::tab_type_e::UNKNOWN;

	QEXCEPTION_ACTION_COND(((index < 0) || (index >= this->tabTypes.count())), throw,  "Index must be larger or equal to 0 and smaller than the number of elements in the QList " << this->tabTypes.count() << ". Got " << index << ".");

	if (this->tabTypes.isEmpty() == false) {
		tabType = this->tabTypes.at(index);
	}

	return tabType;
}

void main_window_tab_widget::MainWindowTabWidget::changeTabType(int index, main_window_shared_types::tab_type_e newType) {

	main_window_shared_types::tab_type_e currentType = this->getTabType(index);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and it is of type " << currentType << ". Desired type is " << newType);

	if (currentType != newType) {
		this->removeTab(index);
		int tabIndex = this->insertEmptyTab(index, QString::null, newType);
		QEXCEPTION_ACTION_COND((tabIndex != index), throw, "Requested index (" << index << ") is different from tab index (" << tabIndex);

		// Move to the newly recreated tab
		this->setCurrentIndex(index);

	}
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(int index, const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, label, type);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::insertEmptyTab(int index, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->insertTab(index, centerWindow, icon, label, type);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type) {

	int tabIndex = -1;

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		QWebEngineView * centerWindow = new QWebEngineView(this->parentWidget());
		tabIndex = this->addTab(centerWindow, icon, label, type);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		QLabel * centerWindow = new QLabel(this->parentWidget());
		tabIndex = this->addTab(centerWindow, label, type);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add new empty tab as the provided tab type " << type << " is not recognized");
	}

	return tabIndex;
}
