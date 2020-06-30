#ifndef TAB_WIDGET_H
#define TAB_WIDGET_H
/**
 * @copyright
 * @file tab_widget.h
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Widget header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QTabWidget>
#include <qt5/QtGui/QIcon>

#include "logging_macros.h"
#include "global_types.h"
#include "tab_bar.h"
#include "constructor_macros.h"

/** @defgroup TabWidgetGroup Tab Widget Doxygen Group
 *  Tab Widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabWidgetOverall)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetSize)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetSearch)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetVisibility)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetTabs)

namespace tab_widget {

	/**
	 * @brief TabWidget class
	 *
	 */
	class TabWidget : public QTabWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabWidget(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Tab widget constructor
			 */
			explicit TabWidget(QWidget * parent);

			/**
			 * @brief Function: virtual ~TabWidget()
			 *
			 * Tab widget destructor
			 */
			virtual ~TabWidget();

			/**
			 * @brief Function: int addTab(QWidget * page, const QString & label, const QIcon & icon = QIcon())
			 *
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 * \param icon: icon of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QString & label, const QIcon & icon = QIcon());

			/**
			 * @brief Function: int insertTab(const int & index, QWidget * page, const QString & label, const QIcon & icon = QIcon())
			 *
			 * \param index: index to insert tab to
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 * \param icon: icon of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(const int & index, QWidget * page, const QString & label, const QIcon & icon = QIcon());

			/**
			 * @brief Function: void removeTab(const int & index)
			 *
			 * \param index: index of the tab to remove
			 *
			 * remove a tab from tab widget
			 */
			void removeTab(const int & index);

			/**
			 * @brief Function: QWidget * widget(const int & index, const bool & checkError = true) const
			 *
			 * \param index: index of the tab to return the widget of
			 * \param checkError: error out if widget is null
			 *
			 * \return widget of tab page
			 *
			 * returns a tab from tab widget
			 */
			QWidget * widget(const int & index, const bool & checkError = true) const;

		protected:
			/**
			 * @brief Function: void resizeEvent(QResizeEvent * event) override
			 *
			 * \param event: resize event
			 *
			 * Reimplement resize event
			 */
			void resizeEvent(QResizeEvent * event) override;

			/**
			 * @brief Function: void setTabBar(tab_bar::TabBar * tabBar)
			 *
			 * \param tabBar: tab bar linked to the tab widget
			 *
			 * add tab bar to tab widget
			 */
			void setTabBar(tab_bar::TabBar * tabBar);

			/**
			 * @brief tab bar
			 *
			 */
			tab_bar::TabBar * bar;

		private:
			/**
			 * @brief Function: void setVisibleAttribute()
			 *
			 * Set tab visible attribute
			 */
			void setVisibleAttribute();

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: key event
			 *
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabWidget
			 *
			 */
			DISABLE_COPY_MOVE(TabWidget)

		signals:

	};
}
/** @} */ // End of TabWidgetGroup group

#endif // TAB_WIDGET_H