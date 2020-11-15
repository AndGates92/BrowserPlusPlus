#ifndef BROWSER_SETTINGS_H
#define BROWSER_SETTINGS_H
/**
 * @copyright
 * @file browser_settings.h
 * @author Andrea Gianarda
 * @date 28th October 2020
 * @brief Browser settings header file
 */

#include "common/include/constructor_macros.h"
#include "utility/log/include/printable_object.h"

#include "settings/include/types.h"
#include "utility/stl/include/singleton.h"

/** @defgroup BrowserSettingsGroup Browser Settings Group
 *  Browser settings functions and classes
 *  @{
 */

namespace command_line {
	class CommandLineParser;
}

namespace settings {

	/**
	 * @brief BrowserSettings class
	 *
	 */
	class BrowserSettings : public singleton::Singleton<settings::BrowserSettings>, public printable_object::PrintableObject {

		public:
			/**
			 * @brief Function: void setLogPath(int & argc, char** argv)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 *
			 * This function initializes the value of the log path
			 * It is necessary to treat log file as a special case because the logger needs this value to default the output file
			 */
			static void setLogPath(int & argc, char** argv);

			/**
			 * @brief Function: static const std::string & getLogFilePath()
			 *
			 * \return the path towards the logfile set in the settings
			 *
			 * This functions returns the path towards the default logfile
			 */
			static const std::string & getLogFilePath();

			/**
			 * @brief Function: explicit BrowserSettings()
			 *
			 * Browser Settings constructor
			 */
			explicit BrowserSettings();

			/**
			 * @brief Function: virtual ~BrowserSettings()
			 *
			 * Browser Settings destructor
			 */
			virtual ~BrowserSettings();

			/**
			 * @brief Function: void initialize(int & argc, char** argv)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 *
			 * This function initializes settings of the browser
			 */
			void initialize(int & argc, char** argv);

			/**
			 * @brief Function: const std::string print() const override
			 *
			 * \return settings informations to std::string
			 *
			 * This functions prints settings informations to std::string
			 */
			const std::string print() const override;

			/**
			 * @brief Function: const command_line::argument_map_t & getSettingsMap() const
			 *
			 * \return a map of settings
			 *
			 * This function returns a map of settings
			 */
			const command_line::argument_map_t & getSettingsMap() const;

			/**
			 * @brief Function: void addArguments(const command_line::argument_map_t & arguments, const bool enableOverride = false)
			 *
			 * \param arguments: arguments to add or override
			 * \param enableOverride: if the decoded argument map already contains some keys, they will be overridden
			 *
			 * This function merges the map of arguments provided as argument with the map locally stored.
			 */
			void addArguments(const command_line::argument_map_t & arguments, const bool enableOverride = false);

			/**
			 * @brief Function: void addArgument(const std::string & key, const std::string & value)
			 *
			 * \param key: key to add
			 * \param value: new value of key provided as argument
			 *
			 * This function adds a key and its value to the argument map.
			 * It will throw an exception if the key is already in the map before adding it.
			 */
			void addArgument(const std::string & key, const std::string & value);

			/**
			 * @brief Function: void overrideArgumentValue(const std::string & key, const std::string & value)
			 *
			 * \param key: key whose value has to be changed
			 * \param value: new value of key provided as argument
			 *
			 * This function changes the value of an argument.
			 * It will throw an exception if the key is not found.
			 */
			void overrideArgumentValue(const std::string & key, const std::string & value);

		protected:

		private:

			/**
			 * @brief path toward logfile
			 *
			 */
			static std::string logFilePath;

			/**
			 * @brief Function: explicit BrowserSettings(int argc, char** argv)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 *
			 * Browser Settings constructor
			 */
			explicit BrowserSettings(int argc, char** argv);

			/**
			 * @brief command line parser
			 *
			 */
			std::unique_ptr<command_line::CommandLineParser> parser;

			/**
			 * @brief Function: void initialize()
			 *
			 * This function initializes settings of the browser
			 */
			void initialize();

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class BrowserSettings
			 *
			 */
			DISABLE_COPY_MOVE(BrowserSettings)

	};


}
/** @} */ // End of BrowserSettingsGroup group

#endif // BROWSER_SETTINGS_H
