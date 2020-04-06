#ifndef MAIN_WINDOW_TAB_DATA_H
#define MAIN_WINDOW_TAB_DATA_H
/**
 * @copyright
 * @file main_window_tab_data.h
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Tab Data header file
*/

#include <qt5/QtCore/QLoggingCategory>

#include "main_window_shared_types.h"

/** @defgroup MainWindowTabDataGroup Main Window Tab Data Doxygen Group
 *  Main Window tab data functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabDataOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabDataPrint)

namespace main_window_tab_widget {
	class MainWindowTabWidget;
}

namespace main_window_tab_data {

	class MainWindowTabData {
		friend class main_window_tab_widget::MainWindowTabWidget;

		public:

			/**
			 * @brief Function: static main_window_tab_data::MainWindowTabData * makeTabData(const main_window_shared_types::tab_type_e & type, const void * data)
			 *
			 * \param type: type of the tab
			 * \param data: extra data
			 *
			 * this function constructs a new instance of class MainWindowTabData
			 */
			static main_window_tab_data::MainWindowTabData * makeTabData(const main_window_shared_types::tab_type_e & type, const void * data);

			/**
			 * @brief Function: MainWindowTabData(main_window_shared_types::tab_type_e tabType = main_window_shared_types::tab_type_e::UNKNOWN, const void * tabData = nullptr)
			 *
			 * \param tabType: type of the tab
			 * \param data: extra data
			 *
			 * tab data constructor
			 */
			explicit MainWindowTabData(main_window_shared_types::tab_type_e tabType = main_window_shared_types::tab_type_e::UNKNOWN, const void * tabData = nullptr);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowTabData(const main_window_tab_data::MainWindowTabData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * tab data copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			MainWindowTabData(const main_window_tab_data::MainWindowTabData & rhs);

			/**
			 * @brief Function: MainWindowTabData::MainWindowTabData(main_window_tab_data::MainWindowTabData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * tab data move constructor
			 */
			explicit MainWindowTabData(main_window_tab_data::MainWindowTabData && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowTabData & operator=(const main_window_tab_data::MainWindowTabData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * tab data copy assignment operator
			 */
			MainWindowTabData & operator=(const main_window_tab_data::MainWindowTabData & rhs);

			/**
			 * @brief Function: MainWindowTabData & operator=(main_window_tab_data::MainWindowTabData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * tab data move assignment operator
			 */
			MainWindowTabData & operator=(main_window_tab_data::MainWindowTabData && rhs);

			/**
			 * @brief Function: ~MainWindowTabData()
			 *
			 * tab data structure destructor
			 */
			~MainWindowTabData();

			/**
			 * @brief Function: std::string print() const
			 *
			 * \return tab data converted to std::string
			 *
			 * This functions prints tab data info to std::string
			 */
			std::string print() const;

			/**
			 * @brief Function: QString qprint() const
			 *
			 * \return tab data converted to QString
			 *
			 * This functions prints tab data info to QString
			 */
			const QString qprint() const;

			/**
			 * @brief Function: main_window_shared_types::tab_type_e main_window_tab_data::MainWindowTabData::getType() const
			 *
			 * \return type field of a tab data object
			 *
			 * This functions returns the type field of a tab data object
			 */
			main_window_shared_types::tab_type_e getType() const;

			/**
			 * @brief Function: QString qprint() const
			 *
			 * \return data field of a tab data object
			 *
			 * This functions returns the data field of a tab data object
			 */
			const void * getData() const;

			/**
			 * @brief Function: void main_window_tab_data::MainWindowTabData::setType(const main_window_shared_types::tab_type_e newType)
			 *
			 * \param newType: new type
			 *
			 * This functions sets the type field of a tab data object
			 */
			void setType(const main_window_shared_types::tab_type_e newType);

			/**
			 * @brief Function: void main_window_tab_data::MainWindowTabData::setData(const void * newData)
			 *
			 * \param newData: new data
			 *
			 * This functions sets the data field of a tab data object
			 */
			void setData(const void * newData);
		protected:

		private:
			/**
			 * @brief tab type
			 *
			 */
			main_window_shared_types::tab_type_e type;

			/**
			 * @brief data pointer
			 *
			 */
			const void * data;
	};

}
/** @} */ // End of MainWindowTabDataGroup group

#endif // MAIN_WINDOW_TAB_DATA_H
