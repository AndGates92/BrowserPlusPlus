/**
 * @copyright
 * @file main_window_tab_widget.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Widget functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_web_engine_page.h"
#include "main_window_tab_widget.h"
#include "main_window_tab.h"
#include "type_print_macros.h"
#include "exception_macros.h"
#include "global_functions.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabWidgetOverall, "mainWindowTabWidget.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabWidgetTabs, "mainWindowTabWidget.tabs", MSG_TYPE_LEVEL)

main_window_tab_widget::MainWindowTabWidget::MainWindowTabWidget(QWidget * parent): tab_widget::TabWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget constructor");

}

main_window_tab_widget::MainWindowTabWidget::~MainWindowTabWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Main Window Tab widget destructor");

	const int idx = 0;

	// Delete all tabs until the count reaches 0
	// Always delete the first tab as for every deletion, all subsequents are shifted back
	while(this->count() > 0) {
		const main_window_shared_types::tab_type_e type = this->getTabType(idx);

		Q_ASSERT_X(((type == main_window_shared_types::tab_type_e::LABEL) || (type == main_window_shared_types::tab_type_e::WEB_ENGINE)), "Invalid tab type", "Unable to delete provided tab as type is not recognized");
		this->removeTab(idx);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetOverall,  "Removing tab type " << type);
	}
}

void main_window_tab_widget::MainWindowTabWidget::removeTab(const int & index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Close tab " << index);
	tab_widget::TabWidget::removeTab(index);
	emit this->numberTabsChanged(this->currentIndex());
}

void main_window_tab_widget::MainWindowTabWidget::moveTab(const int & indexFrom, const int & indexTo) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Move tab from " << indexFrom << " to " << indexTo);
	this->bar->moveTab(indexFrom, indexTo);
}

QWidget * main_window_tab_widget::MainWindowTabWidget::widget(const int & index, bool checkError) const {
	QWidget * requestedWidget = tab_widget::TabWidget::widget(index, checkError);

	return requestedWidget;
}

const main_window_tab_data::MainWindowTabData * main_window_tab_widget::MainWindowTabWidget::getTabData(const int & index) const {

	const int tabCount = this->count();

	QEXCEPTION_ACTION_COND(((index < 0) || (index >= tabCount)), throw,  "Unable to retrieve tab type as index must be larger or equal to 0 and smaller than the number of tabs " << tabCount << ". Got " << index << ".");

	const main_window_tab_data::MainWindowTabData * tabData = nullptr;

	if (tabCount > 0) {
		const main_window_tab::MainWindowTab * tab = dynamic_cast<main_window_tab::MainWindowTab *>(this->widget(index, true));
		const main_window_web_engine_page::MainWindowWebEnginePage * page = dynamic_cast<main_window_web_engine_page::MainWindowWebEnginePage *>(tab->widgetView->page());
		tabData = page->getTabData();
	}

	return tabData;
}

main_window_shared_types::tab_type_e main_window_tab_widget::MainWindowTabWidget::getTabType(const int & index) const {
	const main_window_tab_data::MainWindowTabData * tabData = this->getTabData(index);
	return tabData->getType();
}

const void * main_window_tab_widget::MainWindowTabWidget::getTabExtraData(const int & index) const {
	const main_window_tab_data::MainWindowTabData * tabData = this->getTabData(index);
	return tabData->getData();
}

void main_window_tab_widget::MainWindowTabWidget::changeTabType(const int & index, const main_window_shared_types::tab_type_e newType, const void * data) {

	const main_window_shared_types::tab_type_e currentType = this->getTabType(index);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs, "Current tab index is " << index << " and it is of type " << currentType << ". Desired type is " << newType);

	if (currentType != newType) {
		this->removeTab(index);
		const QString content(QString::null);
		const int tabIndex = this->insertTab(index, QString::null, &content, newType, data);
		QEXCEPTION_ACTION_COND((tabIndex != index), throw, "Requested index (" << index << ") is different from tab index (" << tabIndex);
	}
}

int main_window_tab_widget::MainWindowTabWidget::insertTab(const int & index, const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data, const QIcon & icon) {

	const void * body = nullptr;
	QUrl url = QUrl();

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		const QString * search = static_cast<const QString *>(content);
		url = this->createUrl(*search);
		body = &url;
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		body = content;
	} else {
		QEXCEPTION_ACTION(throw, "Unable to insert new empty tab at index " << index << " as the provided tab type " << type << " is not recognized");
	}

	main_window_tab::MainWindowTab * tab = new main_window_tab::MainWindowTab(type, data, body, this->parentWidget());

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabWidgetTabs,  "Insert tab with label " << label << " at position " << index);

	const int tabIndex = tab_widget::TabWidget::insertTab(index, tab, label, icon);

	// Move to the newly opened tab
	this->setCurrentIndex(tabIndex);

	return tabIndex;
}

int main_window_tab_widget::MainWindowTabWidget::addEmptyTab(const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data, const QIcon & icon) {

	const int index = this->count();
	int tabIndex = this->insertTab(index, label, content, type, data, icon);

	return tabIndex;
}

const QUrl main_window_tab_widget::MainWindowTabWidget::createUrl(const QString & search) const {
	const bool containsSpace = search.contains(" ");
	const bool containsWww = search.contains(main_window_tab_widget::www);
	const int numberDots = search.count(".");

	QString urlStr(QString::null);

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		urlStr = main_window_tab_widget::https;
		if (containsWww == true) {
			urlStr += search;
		} else {
			urlStr += main_window_tab_widget::www + search;
		}
	} else {
		urlStr = main_window_tab_widget::defaultSearchEngine.arg(search);
	}

	const QUrl url(urlStr);

	return url;
}
