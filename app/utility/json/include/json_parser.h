#ifndef JSON_PARSER_H
#define JSON_PARSER_H
/**
 * @copyright
 * @file json_parser.h
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Parser header file
*/

// Qt libraries
#include <QtCore/QString>

#include "json_wrapper.h"

/** @defgroup JsonParserGroup JSON Parser Doxygen Group
 *  JSON Parser control functions and classes
 *  @{
 */

namespace json_parser {

	/**
	 * @brief JsonParser class
	 *
	 */
	class JsonParser final : public json_wrapper::JsonWrapper {

		public:

			/**
			 * @brief Function: explicit JsonParser(QString fileName, QIODevice::OpenModeFlag openFlags)
			 *
			 * \param fileName: filename of the JSON file
			 * \param openFlags: flags used to open the file (It must be QIODevice::ReadOnly, QIODevice::WriteOnly QIODevice::ReadWrite and optionally additional flags)
			 *
			 * JSON parser constructor
			 */
			explicit JsonParser(QString fileName, QIODevice::OpenModeFlag openFlags);

			// Move and copy constructor
			/**
			 * @brief Function: explicit JsonParser(const json_parser::JsonParser & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON parser copy constructor
			 */
			explicit JsonParser(const json_parser::JsonParser & rhs);

			/**
			 * @brief Function: explicit JsonParser(json_parser::JsonParser && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON parser move constructor
			 */
			explicit JsonParser(json_parser::JsonParser && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: JsonParser & operator=(const json_parser::JsonParser & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON parser copy assignment operator
			 */
			JsonParser & operator=(const json_parser::JsonParser & rhs);

			/**
			 * @brief Function: JsonParser & operator=(json_parser::JsonParser && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON parser move assignment operator
			 */
			JsonParser & operator=(json_parser::JsonParser && rhs);

			/**
			 * @brief Function: ~JsonParser()
			 *
			 * JSON parser destructor
			 */
			virtual ~JsonParser();

			/**
			 * @brief Function: QMap<QString, QString> findKeyAllValues(const QString & key) const
			 *
			 * \param key: key to look for in the JSON file
			 *
			 * \return a map of all the pairs key-value that match
			 *
			 * This function finds all values matching the key in the JSON file
			 */
			QMap<QString, QString> findKeyAllValues(const QString & key) const;

			/**
			 * @brief Function: const QString findKeyValue(const QString & treeRoot, const QString & key) const
			 *
			 * \param treeRoot: tree under which the key has to be searched
			 * \param key: key to look for in the JSON file
			 *
			 * \return value of the key or an empty string if not found
			 *
			 * This function find the value of a key under a root tree
			 */
			const QString findKeyValue(const QString & treeRoot, const QString & key) const;

			/**
			 * @brief Function: const QStringList getJsonKeys() const
			 *
			 * \return a list of keys of the JSON file if it is of type object
			 *
			 * This function returns the key of a JSON file
			 */
			const QStringList getJsonKeys() const;

		protected:

		private:

			/**
			 * @brief Function: QString searchJson(const QJsonValue & content, const QString & key) const
			 *
			 * \param content: content to search for the key
			 * \param key: key to search for
			 *
			 * \return value of the key
			 *
			 * This function iterates over a JSON value and looks for a key
			 */
			QString searchJson(const QJsonValue & content, const QString & key) const;

			/**
			 * @brief Function: QString searchJsonObject(const QJsonObject & object, QString key) const
			 *
			 * \param object: object to look the key into
			 * \param key: key to search for
			 *
			 * \return value of the key
			 *
			 * This function searches a key in the current JSON object or keep looking for it
			 */
			QString searchJsonObject(const QJsonObject & content, const QString & key) const;
	};

}
/** @} */ // End of JsonParserGroup group

#endif // JSON_PARSER_H
