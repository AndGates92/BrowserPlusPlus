#ifndef KEY_INFO_H
#define KEY_INFO_H
/**
 * @copyright
 * @file key_info.h
 * @author Andrea Gianarda
 * @date 13th January 2020
 * @brief Key Info header file
*/

#include <unordered_map>
#include <functional>

#include <QtCore/QLoggingCategory>
#include <QtGui/QKeySequence>
#include <QtCore/QString>

/**
 * @brief QINFO_PRINT(KEY, STR)
 *
 * \param KEY  : key name
 * \param STR  : string to be printed when the key is pressed
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define ADD_KEY_TO_MAP(KEY, STR)\
	{ Qt::Key_##KEY, #STR }

/** @defgroup KeyInfoGroup Key Info Doxygen Group
 *  Key Info functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(keyInfoOverall)
Q_DECLARE_LOGGING_CATEGORY(keyInfoString)

namespace key_info {

	/**
	 * @brief KeyInfo class
	 *
	 */
	class KeyInfo {

		public:
			/**
			 * @brief Function: explicit KeyInfo(const QKeySequence & keySeq, QKeyInfo::SequenceFormat format = QKeyInfoNativeText)
			 *
			 * \param keySeq: key sequence
			 *
			 * Key Info constructor
			 */
			explicit KeyInfo(const QKeySequence & keySeq);

			// Move and copy constructor
			/**
			 * @brief Function: KeyInfo(const key_info::KeyInfo & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON parser copy constructor
			 */
			explicit KeyInfo(const key_info::KeyInfo & rhs);

			/**
			 * @brief Function: KeyInfo::KeyInfo(key_info::KeyInfo && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON parser move constructor
			 */
			explicit KeyInfo(key_info::KeyInfo && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: KeyInfo & operator=(const key_info::KeyInfo & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON parser copy assignment operator
			 */
			KeyInfo & operator=(const key_info::KeyInfo & rhs);

			/**
			 * @brief Function: KeyInfo & operator=(key_info::KeyInfo && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON parser move assignment operator
			 */
			KeyInfo & operator=(key_info::KeyInfo && rhs);

			/**
			 * @brief Function: virtual ~KeyInfo()
			 *
			 * JSON parser destructor
			 */
			virtual ~KeyInfo();

			/**
			 * @brief Function: QString toString(QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
			 *
			 * \param format: format of key string
			 *
			 * \return a string with all key sequences
			 *
			 * This function returns a string with the key sequences
			 */
			QString toString(QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

		private:
			/**
			 * @brief key
			 *
			 */
			Qt::Key key;

			/**
			 * @brief modifier
			 *
			 */
			Qt::KeyboardModifier modifier;

			/**
			 * @brief Function: QString keyToString(const Qt::Key keyPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
			 *
			 * \param keyPrint: key
			 * \param format: format of key string
			 *
			 * \return a string with all key sequences
			 *
			 * This function returns a string with the key converted to a string
			 */
			QString keyToString(const Qt::Key keyPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

			/**
			 * @brief Function: QString modifierToString(const Qt::KeyboardModifier keyPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
			 *
			 * \param modifierPrint: modifier
			 * \param format: format of key string
			 *
			 * \return a string with all key sequences
			 *
			 * This function returns a string with the modifier converted to a string 
			 */
			QString modifierToString(const Qt::KeyboardModifier modifierPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

			/**
			 * @brief Function: bool isKeyPrintable(const Qt::Key keyCheck) const
			 *
			 * \param keyCheck: key
			 *
			 * \return a boolean value depending on whether the character is printable or not
			 *
			 * This function returns whether a key is printable (i.e. character) or not
			 */
			bool isKeyPrintable(const Qt::Key keyCheck) const;
	};

}
/** @} */ // End of KeyInfoGroup group

#endif // KEY_INFO_H