#ifndef TAB_SCROLL_MANAGER_H
#define TAB_SCROLL_MANAGER_H
/**
 * @copyright
 * @file tab_scroll_manager.h
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager header file
*/

#include <memory>

// Qt libraries
#include <QtWidgets/QTabBar>

#include "common/include/global_enums.h"
#include "base/tabs/include/tab_component_widget.h"
#include "base/tabs/include/tab_shared_types.h"
#include "base/tabs/include/tab_bar.h"
#include "common/include/constructor_macros.h"

/** @defgroup TabScrollManagerGroup Tab Scroll Manager Doxygen Group
 *  Tab Scroll Manager functions and classes
 *  @{
 */

namespace tab_bar {
	class TabBar;
}

namespace tab_scroll_manager {

	/**
	 * @brief TabScrollManager class
	 *
	 */
	class TabScrollManager : public tab_component_widget::TabComponentWidget<tab_shared_types::direction_e> {
		friend class tab::Tab;

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabScrollManager(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar)
			 *
			 * \param parent: parent widget
			 * \param tabBar: tab bar
			 * \param tab: tab
			 *
			 * Tab Scroll Manager constructor
			 */
			explicit TabScrollManager(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar);

			/**
			 * @brief Function: virtual ~TabScrollManager()
			 *
			 * Tab Scroll Manager destructor
			 */
			virtual ~TabScrollManager();

			/**
			 * @brief Function: const QSizeF & getContentsSize() const
			 *
			 * \return size of the content
			 *
			 * This function returns the size of the content
			 */
			const QSizeF & getContentsSize() const;

			/**
			 * @brief Function: const QPointF & getScrollPosition() const
			 *
			 * \return position of the scrolling
			 *
			 * This function returns the position of the scrolling
			 */
			const QPointF & getScrollPosition() const;

			/**
			 * @brief Function: const int & getHorizontalScrollPercentage() const
			 *
			 * \return percentage of the position of the horizontal scrolling
			 *
			 * This function returns the percentage of the position of the horizontal scrolling
			 */
			const int & getHorizontalScrollPercentage() const;

			/**
			 * @brief Function: const int & getVerticalScrollPercentage() const
			 *
			 * \return percentage of the position of the vertical scrolling
			 *
			 * This function returns the percentage of the position of the vertical scrolling
			 */
			const int & getVerticalScrollPercentage() const;

		signals:
			/**
			 * @brief Function: void verticalScrollChanged(const int & vScroll)
			 *
			 * \param vScroll: vertical scroll
			 *
			 * This function is a signal to notify that vertical scroll changed
			 */
			void verticalScrollChanged(const int & vScroll);

			/**
			 * @brief Function: void horizontalScrollChanged(const int & hScroll)
			 *
			 * \param hScroll: horizontal scroll
			 *
			 * This function is a signal to notify that horizontal scroll changed
			 */
			void horizontalScrollChanged(const int & hScroll);

			/**
			 * @brief Function: void scrollRequest(const int x, const int y)
			 *
			 * \param x: scroll on the x axis
			 * \param y: scroll on the y axis
			 *
			 * This function is a signal to request scrolling
			 */
			void scrollRequest(const int x, const int y);

		protected:

			/**
			 * @brief percentage of horizontal scroll
			 *
			 */
			int horizontalScroll;

			/**
			 * @brief percentage of vertical scroll
			 *
			 */
			int verticalScroll;

			/**
			 * @brief Function: void updateHorizontalScrollPercentage()
			 *
			 * This function computes the percentage of the position of the horizontal scrolling
			 */
			void updateHorizontalScrollPercentage();

			/**
			 * @brief Function: void updateVerticalScrollPercentage()
			 *
			 * This function computes the percentage of the position of the vertical scrolling
			 */
			void updateVerticalScrollPercentage();

		protected slots:
			/**
			 * @brief Function: void updateContentsSize(const QSizeF & value)
			 *
			 * \param value: size of the content
			 *
			 * This function sets the size of the content
			 */
			void updateContentsSize(const QSizeF & value);

			/**
			 * @brief Function: void updateScrollPosition(const QPointF & value)
			 *
			 * \param value: position of the scrolling
			 *
			 * This function sets the position of the scrolling
			 */
			void updateScrollPosition(const QPointF & value);

		private:
			/**
			 * @brief position of the scrolling
			 *
			 */
			QPointF scrollPosition;

			/**
			 * @brief size of the content in the webpage
			 *
			 */
			QSizeF contentsSize;

			/**
			 * @brief tab bar the tab belong to
			 *
			 */
			std::shared_ptr<tab_bar::TabBar> bar;

			/**
			 * @brief Function: vortual void execute(const tab_shared_types::direction_e & direction) override final
			 *
			 * \param direction: direction of scrolling
			 *
			 * This function scroll the tab in the direction provided as argument
			 */
			virtual void execute(const tab_shared_types::direction_e & direction) override final;

			/**
			 * @brief Function: void checkScrollValue(const int & scroll, const QString & direction) const
			 *
			 * \param scroll: value of scrolling
			 * \param direction: direction of scrolling
			 *
			 * This function checks that the value of scrolling is within the allowed range defined by tab_scroll_manager::minScrollPercentage and tab_scroll_manager::maxScrollPercentage
			 */
			void checkScrollValue(const int & scroll, const QString & direction) const;

			/**
			 * @brief Function: virtual void canProcessRequests() const override
			 *
			 * \return whether find requests can be processed
			 *
			 * This function check if find requests can be processed
			 */
			virtual bool canProcessRequests() const override;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabScrollManager
			 *
			 */
			DISABLE_COPY_MOVE(TabScrollManager)

	};
}
/** @} */ // End of TabScrollManagerGroup group

#endif // TAB_SCROLL_MANAGER_H
