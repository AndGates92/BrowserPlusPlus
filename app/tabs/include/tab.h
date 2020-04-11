#ifndef TAB_H
#define TAB_H
/**
 * @copyright
 * @file tab.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "constructor_macros.h"
#include "web_engine_view.h"
#include "tab_load_manager.h"
#include "web_engine_search.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabOverall)

namespace tab {

	/**
	 * @brief Tab class
	 *
	 */
	class Tab : public QWidget {

		public:
			/**
			 * @brief Function: explicit Tab(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Tab constructor
			 */
			explicit Tab(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~Tab()
			 *
			 * Tab destructor
			 */
			virtual ~Tab();

			/**
			 * @brief Function: void setView(web_engine_view::WebEngineView * value)
			 *
			 * \param value: view to use
			 *
			 * This function sets the tab view
			 */
			void setView(web_engine_view::WebEngineView * value);

			/**
			 * @brief Function: web_engine_view::WebEngineView * getView()
			 *
			 * \return tab view
			 *
			 * This function returns the load manager
			 */
			web_engine_view::WebEngineView * getView() const;

			/**
			 * @brief Function: void setLoadManager(tab_load_manager::TabLoadManager * value)
			 *
			 * \param value: load manager to use
			 *
			 * This function sets the load manager
			 */
			void setLoadManager(tab_load_manager::TabLoadManager * value);

			/**
			 * @brief Function: tab_load_manager::TabLoadManager * getLoadManager()
			 *
			 * \return load manager
			 *
			 * This function returns the load manager
			 */
			tab_load_manager::TabLoadManager * getLoadManager() const;

			/**
			 * @brief Function: void setSearch(web_engine_search::WebEngineSearch * value)
			 *
			 * \param value: search to use
			 *
			 * This function sets the tab search
			 */
			void setSearch(web_engine_search::WebEngineSearch * value);

			/**
			 * @brief Function: web_engine_search::WebEngineSearch * getSearch()
			 *
			 * \return tab search
			 *
			 * This function returns the load manager
			 */
			web_engine_search::WebEngineSearch * getSearch() const;

		protected:

			/**
			 * @brief Function: virtual void connectSignals()
			 *
			 * This function connects signals and slots within tabs
			 */
			virtual void connectSignals() = 0;

			/**
			 * @brief Function: virtual void reload()
			 *
			 * This function reloads the content of the tab
			 */
			virtual void reload() = 0;

		private:

			/**
			 * @brief web engine view
			 *
			 */
			web_engine_view::WebEngineView * view;

			/**
			 * @brief load manager
			 *
			 */
			tab_load_manager::TabLoadManager * loadManager;

			/**
			 * @brief seach class
			 *
			 */
			web_engine_search::WebEngineSearch * search;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class Tab
			 *
			 */
			DISABLE_COPY_MOVE(Tab)

	};
}
/** @} */ // End of TabGroup group

#endif // TAB_H
