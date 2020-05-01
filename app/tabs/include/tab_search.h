#ifndef WEB_ENGINE_SEARCH_H
#define WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file tab_search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab Search header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtCore/QString>
#include <qt5/QtWebEngineWidgets/QWebEnginePage>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup TabSearchGroup Tab Search Doxygen Group
 *  Tab Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabSearchOverall)
Q_DECLARE_LOGGING_CATEGORY(tabSearchFind)

namespace tab_search {

	/**
	 * @brief TabSearch class
	 *
	 */
	class TabSearch : public QObject {

		public:
			/**
			 * @brief Function: explicit TabSearch(QWidget * attachedTab, QObject * parent = Q_NULLPTR)
			 *
			 * \param attachedTab: tab attached to the search instance
			 * \param parent: parent object
			 *
			 * Tab search constructor
			 */
			explicit TabSearch(QWidget * attachedTab, QObject * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~TabSearch()
			 *
			 * Tab search destructor
			 */
			virtual ~TabSearch();

			// clear
			// search
			// find prev
			// find next

		protected:
			/**
			 * @brief tab attached to the web search instance
			 *
			 */
			QWidget * tab;

			/**
			 * @brief text to search
			 *
			 */
			QString text;

			/**
			 * @brief search flags
			 *
			 */
			QWebEnginePage::FindFlag flags;

			/**
			 * @brief Function: virtual void findTabContent(const int & index, const QString & search, const bool & reverse, const bool & caseSensitive) final
			 *
			 * \param search: text to search.
			 * \param reverse: true if searching in the reverse direction, false otherwise.
			 * \param caseSensitive: true if case sensitive search, false otherwise.
			 * \param callback: callback to call
			 *
			 * This function searches text in a webpage
			 */
			virtual void findTabContent(const QString & search, const bool & reverse, const bool & caseSensitive, void (* callback)(bool) = nullptr) final;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabSearch
			 *
			 */
			DISABLE_COPY_MOVE(TabSearch)

	};
}
/** @} */ // End of TabSearchGroup group

#endif // WEB_ENGINE_SEARCH_H
