#ifndef TAB_COMPONENT_WIDGET_H
#define TAB_COMPONENT_WIDGET_H
/**
 * @copyright
 * @file tab_component_widget.h
 * @author Andrea Gianarda
 * @date 13th of May 2020
 * @brief Tab Component Widget header file
*/

#include <queue>

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "function_macros.h"
#include "tab_shared_types.h"
#include "constructor_macros.h"

/** @defgroup TabComponentWidgetGroup Tab Component Widget Doxygen Group
 *  Tab Component Widget functions and classes
 *  @{
 */

namespace tab {
	class Tab;
}


Q_DECLARE_LOGGING_CATEGORY(tabComponentWidgetOverall)

namespace tab_component_widget {

	/**
	 * @brief TabComponentWidget class
	 *
	 */
	template<typename type>
	class TabComponentWidget : public QWidget {
		public:
			/**
			 * @brief Function: explicit TabComponentWidget(QWidget * parent, QWidget * attachedTab)
			 *
			 * \param parent: parent widget
			 *
			 * Tab Component Widget constructor
			 */
			explicit TabComponentWidget(QWidget * parent, QWidget * attachedTab);

			/**
			 * @brief Function: virtual ~TabComponentWidget()
			 *
			 * Tab Component Widget destructor
			 */
			virtual ~TabComponentWidget();

		protected:
			/**
			 * @brief Function: virtual void popRequestQueue()
			 *
			 * This function empties the queue of scroll requests
			 */
			virtual void popRequestQueue() = 0;

			/**
			 * @brief Function: virtual void pushRequestQueue(const type & entry)
			 *
			 * \param entry: direction of scrolling
			 *
			 * This function pushes a new entry to the queue
			 */
			virtual void pushRequestQueue(const type & entry) = 0;

			/**
			 * @brief Function: virtual bool canProcessRequests() const
			 *
			 * \return whether requests can be processed
			 *
			 * This function check if requests can be processed
			 */
			virtual bool canProcessRequests() const = 0;

			/**
			 * @brief Function: void setTab(QWidget * newTab)
			 *
			 * \param tab: tab the component belongs to
			 *
			 * This function sets the tab the component belongs to
			 * This is a convenience function. The argument must be able to be casted as tab::Tab
			 */
			void setTab(QWidget * newTab);

			/**
			 * @brief Function: void setTab(tab::Tab * value)
			 *
			 * \param tab: tab the component belongs to
			 *
			 * This function sets the tab the component belongs to
			 */
			void setTab(tab::Tab * value);

			/**
			 * @brief Function: tab::Tab * getTab() const
			 *
			 * \return tab the component belongs to
			 *
			 * This function returns the tab the component belongs to
			 */
			tab::Tab * getTab() const;

			/**
			 * @brief queue of outstanding scroll requests
			 *
			 */
			std::queue<type> requestQueue;

		private:
			/**
			 * @brief tab the scroll manager belongs to
			 *
			 */
			tab::Tab * browserTab;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overscrolling for class TabComponentWidget
			 *
			 */
			DISABLE_COPY_MOVE(TabComponentWidget)

	};
}
/** @} */ // End of TabComponentWidgetGroup group

template<typename type>
tab_component_widget::TabComponentWidget<type>::TabComponentWidget(QWidget * parent, QWidget * attachedTab): QWidget(parent), browserTab(Q_NULLPTR) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabComponentWidgetOverall,  "TabComponentWidget constructor");

	// Make widget invisible
	this->setVisible(false);

	this->setTab(attachedTab);
}

template<typename type>
tab_component_widget::TabComponentWidget<type>::~TabComponentWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabComponentWidgetOverall,  "TabComponentWidget destructor");
}

template<typename type>
void tab_component_widget::TabComponentWidget<type>::setTab(QWidget * newTab) {
	try {
		tab::Tab * thisTab = dynamic_cast<tab::Tab *>(newTab);
		this->setTab(thisTab);
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

template<typename type>
PTR_SETTER(tab_component_widget::TabComponentWidget<type>::setTab, tab::Tab, this->browserTab)

template<typename type>
PTR_GETTER(tab_component_widget::TabComponentWidget<type>::getTab, tab::Tab, this->browserTab)

#endif // TAB_COMPONENT_WIDGET_H
