#ifndef WEB_ENGINE_PAGE_H
#define WEB_ENGINE_PAGE_H
/**
 * @copyright
 * @file web_engine_page.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Page header file
*/

// Qt libraries
#include <QtWebEngineWidgets/QWebEnginePage>

#include "base/tabs/include/web_engine_profile.h"
#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"

/** @defgroup WebEnginePageGroup Web Engine Page Doxygen Group
 *  Web Engine Page functions and classes
 *  @{
 */

namespace tab {
	class Tab;
}

namespace web_engine_page {

	/**
	 * @brief WebEnginePage class
	 *
	 */
	class WebEnginePage : public QWebEnginePage {
		friend class tab::Tab;

		public:
			/**
			 * @brief Function: explicit WebEnginePage(QWidget * parent, WebEngineProfile * profile = web_engine_profile::WebEngineProfile::defaultProfile())
			 *
			 * \param profile: profile of the page
			 * \param parent: parent widget
			 *
			 * Web engine page constructor
			 */
			explicit WebEnginePage(QWidget * parent, web_engine_profile::WebEngineProfile * profile = web_engine_profile::WebEngineProfile::defaultProfile());

			/**
			 * @brief Function: virtual ~WebEnginePage()
			 *
			 * Web engine page destructor
			 */
			virtual ~WebEnginePage();

			/**
			 * @brief Function: web_engine_profile::WebEngineProfile * profile() const
			 *
			 * \return profile of the page
			 *
			 * This function returns the profile of this web engine page
			 */
			web_engine_profile::WebEngineProfile * profile() const;

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class WebEnginePage
			 *
			 */
			DISABLE_COPY_MOVE(WebEnginePage)

	};
}
/** @} */ // End of WebEnginePageGroup group

#endif // WEB_ENGINE_PAGE_H
