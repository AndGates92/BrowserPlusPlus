/**
 * @copyright
 * @file key_info.cpp
 * @author Andrea Gianarda
 * @date 13th January 2020
 * @brief Key Info functions
 */

#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/widgets/commands/key_info.h"

// Categories
LOGGING_CONTEXT(keyInfoOverall, keyInfo.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(keyInfoString, keyInfo.string, TYPE_LEVEL, INFO_VERBOSITY)

/** @addtogroup KeyInfoGroup Key Info Doxygen Group
 *  @{
 */
/**
 * @brief ADD_KEY_TO_MAP(KEY, STR)
 *
 * \param KEY  : key name
 * \param STR  : string to be printed when the key is pressed
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define ADD_KEY_TO_MAP(KEY, STR)\
	{ Qt::Key_##KEY, #STR }

/** @} */ // End of KeyInfoGroup group

namespace app {

	namespace commands {

		namespace key_info {

			namespace {

				class KeyInfoHash {
					public :
						std::size_t operator()(const Qt::Key & key) const {
							int keyInt = (int) key;
							std::size_t keyHash = std::hash<int>()(keyInt);
							return keyHash;
						}
				};

				class KeyInfoEqualTo {
					public :
						bool operator()(const Qt::Key & key0, const Qt::Key & key1) const {
							return (((int) key0) == ((int) key1));
						}
				};

				typedef std::unordered_map<Qt::Key, Qt::KeyboardModifier, KeyInfoHash, KeyInfoEqualTo> modifierKeyMap;
				static const modifierKeyMap modifierKeys = {
					{ Qt::Key_Shift, Qt::ShiftModifier },
					{ Qt::Key_Control, Qt::ControlModifier },
					{ Qt::Key_Alt, Qt::AltModifier },
					{ Qt::Key_Meta, Qt::MetaModifier },
					{ Qt::Key_AltGr, Qt::GroupSwitchModifier },
					{ Qt::Key_Mode_switch, Qt::GroupSwitchModifier }
				};
			
				typedef std::unordered_map<Qt::Key, QString, KeyInfoHash, KeyInfoEqualTo> specialKeyMap;
				static const specialKeyMap specialKeys = {
					ADD_KEY_TO_MAP(Super_L, Super L),
					ADD_KEY_TO_MAP(Super_R, Super R),
					ADD_KEY_TO_MAP(Hyper_L, Hyper L),
					ADD_KEY_TO_MAP(Hyper_R, Hyper R),
					ADD_KEY_TO_MAP(Direction_L, Direction L),
					ADD_KEY_TO_MAP(Direction_R, Direction R),
					
					ADD_KEY_TO_MAP(Shift, Shift),
					ADD_KEY_TO_MAP(Control, Control),
					ADD_KEY_TO_MAP(Meta, Meta),
					ADD_KEY_TO_MAP(Alt, Alt),
					
					ADD_KEY_TO_MAP(AltGr, AltGr),
					ADD_KEY_TO_MAP(Multi_key, Multi key),
					ADD_KEY_TO_MAP(SingleCandidate, Single Candidate),
					ADD_KEY_TO_MAP(Mode_switch, Mode switch),
					ADD_KEY_TO_MAP(Dead_Grave, `),
					ADD_KEY_TO_MAP(Dead_Acute, ´),
					ADD_KEY_TO_MAP(Dead_Circumflex, ^),
					ADD_KEY_TO_MAP(Dead_Tilde, ~),
					ADD_KEY_TO_MAP(Dead_Macron, ¯),
					ADD_KEY_TO_MAP(Dead_Breve, ˘),
					ADD_KEY_TO_MAP(Dead_Abovedot, ˙),
					ADD_KEY_TO_MAP(Dead_Diaeresis, ¨),
					ADD_KEY_TO_MAP(Dead_Abovering, ˚),
					ADD_KEY_TO_MAP(Dead_Doubleacute, ˝),
					ADD_KEY_TO_MAP(Dead_Caron, ˇ),
					ADD_KEY_TO_MAP(Dead_Cedilla, ¸),
					ADD_KEY_TO_MAP(Dead_Ogonek, ˛),
					ADD_KEY_TO_MAP(Dead_Iota, Iota),
					ADD_KEY_TO_MAP(Dead_Voiced_Sound, Voiced Sound),
					ADD_KEY_TO_MAP(Dead_Semivoiced_Sound, Semivoiced Sound),
					ADD_KEY_TO_MAP(Dead_Belowdot, Belowdot),
					ADD_KEY_TO_MAP(Dead_Hook, Hook),
					ADD_KEY_TO_MAP(Dead_Horn, Horn),
					
					ADD_KEY_TO_MAP(Dead_Stroke, "\u0335"),  // '̵'
					ADD_KEY_TO_MAP(Dead_Abovecomma, "\u0313"),  // '̓'
					ADD_KEY_TO_MAP(Dead_Abovereversedcomma, "\u0314"),  // '̔'
					ADD_KEY_TO_MAP(Dead_Doublegrave, "\u030f"),  // '̏'
					ADD_KEY_TO_MAP(Dead_Belowring, "\u0325"),  // '̥'
					ADD_KEY_TO_MAP(Dead_Belowmacron, "\u0331"),  // '̱'
					ADD_KEY_TO_MAP(Dead_Belowcircumflex, "\u032d"),  // '̭'
					ADD_KEY_TO_MAP(Dead_Belowtilde, "\u0330"),  // '̰'
					ADD_KEY_TO_MAP(Dead_Belowbreve, "\u032e"),  // '̮'
					ADD_KEY_TO_MAP(Dead_Belowdiaeresis, "\u0324"),  // '̤'
					ADD_KEY_TO_MAP(Dead_Invertedbreve, "\u0311"),  // '̑'
					ADD_KEY_TO_MAP(Dead_Belowcomma, "\u0326"),  // '̦'
					ADD_KEY_TO_MAP(Dead_Currency, "\u00a4"), // '¤'
					ADD_KEY_TO_MAP(Dead_a, a),
					ADD_KEY_TO_MAP(Dead_A, A),
					ADD_KEY_TO_MAP(Dead_e, e),
					ADD_KEY_TO_MAP(Dead_E, E),
					ADD_KEY_TO_MAP(Dead_i, i),
					ADD_KEY_TO_MAP(Dead_I, I),
					ADD_KEY_TO_MAP(Dead_o, o),
					ADD_KEY_TO_MAP(Dead_O, O),
					ADD_KEY_TO_MAP(Dead_u, u),
					ADD_KEY_TO_MAP(Dead_U, U),
					ADD_KEY_TO_MAP(Dead_Small_Schwa, "\u0259"), // 'ə'
					ADD_KEY_TO_MAP(Dead_Capital_Schwa, "\u018f"), // 'Ə'
					ADD_KEY_TO_MAP(Dead_Greek, Greek),
					ADD_KEY_TO_MAP(Dead_Lowline, "\u0332"),  // '̲'
					ADD_KEY_TO_MAP(Dead_Aboveverticalline, "\u030d"),  // '̍'
					ADD_KEY_TO_MAP(Dead_Belowverticalline, "\u0329"), // ' ̩'
					ADD_KEY_TO_MAP(Dead_Longsolidusoverlay, "\u0338"),  // '̸'
					
					ADD_KEY_TO_MAP(Memo, Memo),
					ADD_KEY_TO_MAP(ToDoList, To Do List),
					ADD_KEY_TO_MAP(Calendar, Calendar),
					ADD_KEY_TO_MAP(ContrastAdjust, Contrast Adjust),
					ADD_KEY_TO_MAP(LaunchG, Launch (G)),
					ADD_KEY_TO_MAP(LaunchH, Launch (H)),
					
					ADD_KEY_TO_MAP(MediaLast, Media Last),
					
					ADD_KEY_TO_MAP(unknown, Unknown),
					
					// For some keys, we just want a different name
					ADD_KEY_TO_MAP(Escape, Escape),
				};

			}

		}

	}

}

#undef ADD_KEY_TO_MAP

app::commands::KeyInfo::KeyInfo(const QKeySequence & keySeq) {

	// Assert that only1 key is stored in the QKeySequence
	Q_ASSERT_X((keySeq.count() == 1), "key sequence length", "QKeySequence passed to KeyInfo class instance must contain one key sequence");

	// Cast first element of key sequence to int in order to extract the key and the modifier
	int keyInt = keySeq[0];

	this->key = Qt::Key(keyInt & ~(Qt::KeyboardModifierMask));
	this->modifier = Qt::KeyboardModifier(keyInt & Qt::KeyboardModifierMask);

	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoOverall, "Key Info constructor (key " << this->key << " (0x" << QString("%1").arg(int(this->key), 0, 16) << "), modifier " << this->modifierToString(this->modifier) << " (0x" << QString("%1").arg(this->modifier, 0, 16) << "))");

}

app::commands::KeyInfo::KeyInfo(const app::commands::KeyInfo & rhs) : key(rhs.key), modifier(rhs.modifier) {

	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoOverall, "Copy constructor key info");

}

app::commands::KeyInfo & app::commands::KeyInfo::operator=(const app::commands::KeyInfo & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoOverall, "Copy assignment operator for key info");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->key != rhs.key) {
		this->key = rhs.key;
	}

	if (this->modifier != rhs.modifier) {
		this->modifier = rhs.modifier;
	}

	return *this;
}

app::commands::KeyInfo::KeyInfo(app::commands::KeyInfo && rhs) : key(std::exchange(rhs.key, Qt::Key_unknown)), modifier(std::exchange(rhs.modifier, Qt::NoModifier)) {

	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoOverall, "Move constructor key info");

}

app::commands::KeyInfo & app::commands::KeyInfo::operator=(app::commands::KeyInfo && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoOverall, "Move assignment operator for key info");

	if (&rhs != this) {
		this->key = std::exchange(rhs.key, Qt::Key_unknown);
		this->modifier = std::exchange(rhs.modifier, Qt::NoModifier);
	}

	return *this;
}

app::commands::KeyInfo::~KeyInfo() {
	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoOverall, "Destructor of KeyInfo class");

}

QString app::commands::KeyInfo::toString(QKeySequence::SequenceFormat format) const {

	// Convert key to string
	QString keyStr(this->keyToString(this->key, format));
	QString commentStr = QString();

	int tmpModifier = int(this->modifier);
	app::commands::key_info::modifierKeyMap::const_iterator modifierKey = app::commands::key_info::modifierKeys.find(this->key);

	if (modifierKey == app::commands::key_info::modifierKeys.end()) {
		// If key is not only a special character, then act based on the modifier if the key is printable
		if (isKeyPrintable(this->key)) {
			if (this->modifier == Qt::ShiftModifier) {
				keyStr = keyStr.toUpper();
				tmpModifier &= ~Qt::ShiftModifier;
				commentStr.append("(Shift+" + keyStr.toLower() + ")");
			} else {
				// Make string lowercase
				keyStr = keyStr.toLower();
			}
		}
	} else {
		// If key is only a special character, then cancel out modifier
		tmpModifier &= ~(modifierKey->second);
	}

	const QString modifierStr(this->modifierToString(Qt::KeyboardModifier(tmpModifier), format));

	QString keySeqStr = QString();
	keySeqStr.append(modifierStr);
	keySeqStr.append(keyStr);
	// If commentStr is not empty, then add a space and print it
	if (!commentStr.isEmpty()) {
		keySeqStr.append(" " + commentStr);
	}

	LOG_INFO(app::logger::info_level_e::ZERO, keyInfoString, "Key sequence (key " << this->key << " (0x" << QString("%1").arg(int(this->key), 0, 16) << "), modifier " << this->modifierToString(this->modifier) << " (0x" << QString("%1").arg(this->modifier, 0, 16) << ")) to " << keySeqStr);

	return keySeqStr;

}

QString app::commands::KeyInfo::keyToString(const Qt::Key keyPrint, const QKeySequence::SequenceFormat format) const {
	app::commands::key_info::specialKeyMap::const_iterator specialKey = app::commands::key_info::specialKeys.find(keyPrint);

	QString keyStr = QString();

	// key no found in specialKeys unordered map
	if (specialKey == app::commands::key_info::specialKeys.end()) {
		QKeySequence keySeq = QKeySequence(int(keyPrint));
		keyStr.append(keySeq.toString(format));
	} else {
		keyStr.append(QString(specialKey->second));
	}

	return keyStr;
}

QString app::commands::KeyInfo::modifierToString(const Qt::KeyboardModifier modifierPrint, const QKeySequence::SequenceFormat format) const {
	QString modifierStr = QString();

	// Concert to key sequence
	QKeySequence modifierSeq(modifierPrint);

	modifierStr.append(modifierSeq.toString(format));

	return modifierStr;

}

bool app::commands::KeyInfo::isKeyPrintable(const Qt::Key keyCheck) const {
	bool isPrintable = false;

	if ((keyCheck >= Qt::Key_A) && (keyCheck <= Qt::Key_ydiaeresis)) {
		isPrintable = true;
	}

	return isPrintable;
}
