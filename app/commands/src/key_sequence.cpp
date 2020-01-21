/**
 * @copyright
 * @file key_sequence.cpp
 * @author Andrea Gianarda
 * @date 11th January 2020
 * @brief Key Sequence functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>

#include "global_types.h"
#include "global_macros.h"
#include "key_info.h"
#include "key_sequence.h"

// Categories
Q_LOGGING_CATEGORY(keySequenceOverall, "keySequence.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(keySequenceString, "keySequence.string", MSG_TYPE_LEVEL)

key_sequence::KeySequence::KeySequence(const QString & keyStr, QKeySequence::SequenceFormat format) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceOverall,  "Key Sequence constructor");

	// Split key sequence string into individual key sequences
	QStringList keySeqList = keyStr.split(",", QString::SkipEmptyParts);

	for (QStringList::const_iterator cIter = keySeqList.cbegin(); cIter != keySeqList.cend(); cIter++) {
		QKeySequence keySeq(*cIter, format);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceOverall,  "Adding " << (*cIter) << " to key sequence vector");
		this->keySeqVec.append(keySeq);
	}
}

key_sequence::KeySequence::KeySequence(const QKeySequence & qKeySeq) {
	unsigned int thisSize = qKeySeq.count();

	for (unsigned int idx; idx < thisSize; idx++) {
		int key = qKeySeq[idx];
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceOverall,  "Key Sequence constructor. Keys are 0x" << QString("%1").arg(key, 0, 16));
		this->keySeqVec.append(key);
	}
}

key_sequence::KeySequence::KeySequence(int key0, int key1, int key2, int key3) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceOverall,  "Key Sequence constructor: key0 0x" << QString("%1").arg(key0, 0, 16) << " key1 0x" << QString("%1").arg(key1, 0, 16) << " key2 0x" << QString("%1").arg(key2, 0, 16) << " key3 0x" << QString("%1").arg(key3, 0, 16));
	this->addKey(key0);
	this->addKey(key1);
	this->addKey(key2);
	this->addKey(key3);
}

key_sequence::KeySequence::KeySequence(const key_sequence::KeySequence & keySeq) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceOverall,  "Key Sequence copy constructor. Keys are " << keySeq.toString());
	this->keySeqVec = keySeq.getSeqVec();
}

void key_sequence::KeySequence::addKey(int key, QKeySequence::SequenceFormat format) {
	if (key != Qt::Key_unknown) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceOverall,  "Adding 0x" << QString("%1").arg(int(key), 0, 16) << " to key sequence vector");
		QKeySequence keySeq(key, format);
		this->keySeqVec.append(keySeq);
	}
}

unsigned int key_sequence::KeySequence::count() const {
	return this->keySeqVec.size();
}

QString key_sequence::KeySequence::toString(QKeySequence::SequenceFormat format) const {

	QStringList keySeqList;

	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(); cIter != this->keySeqVec.cend(); cIter++) {
		// Retrieve sequence to:
		// - split the key from the modifier (using Qt::KeyboardModifierMask)
		// - if the sequence is only a special character then print string from the lookup table
		// - if the sequence contains also a non-special character then call QKeySequence method toString
		key_info::KeyInfo seqInfo(*cIter);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, keySequenceString,  "Processing key " << seqInfo.toString(format));
		keySeqList.append(seqInfo.toString(format));
	}

	QString separator(",");
	QString keyStr(keySeqList.join(separator));

	return keyStr;
}

QVector<QKeySequence> key_sequence::KeySequence::getSeqVec() const {
	return this->keySeqVec;
}

QKeySequence::SequenceMatch key_sequence::KeySequence::matches(const key_sequence::KeySequence & otherSeq) {
	unsigned int thisSize = this->count();
	unsigned int otherSize = otherSeq.count();

	// if this object vector has more than elements than the other one, then there is no match
	if (thisSize > otherSize) {
		return QKeySequence::NoMatch;
	}

	QVector<QKeySequence> otherKeySeq(otherSeq.getSeqVec());

	//for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), QVector<QKeySequence>::const_iterator cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
		// if elements are different. then return NoMatch
		if (*cIter != *cOtherIter) {
			return QKeySequence::NoMatch;
		}
	}

	QKeySequence::SequenceMatch match = QKeySequence::ExactMatch;

	// if this object has less elements than the other one, we can have a partial match
	if (thisSize < otherSize) {
		match = QKeySequence::PartialMatch;
	}

	return match;
}

// Operator overloading
bool key_sequence::KeySequence::operator< (const key_sequence::KeySequence & otherSeq) const {
	QVector<QKeySequence> otherKeySeq(otherSeq.getSeqVec());
	bool cmp = std::lexicographical_compare(this->keySeqVec.cbegin(), this->keySeqVec.cend(), otherKeySeq.cbegin(), otherKeySeq.cend());
	return cmp;
}

bool key_sequence::KeySequence::operator> (const key_sequence::KeySequence & otherSeq) const {
	return (otherSeq < *this);
}

bool key_sequence::KeySequence::operator>= (const key_sequence::KeySequence & otherSeq) const {
	return !(*this < otherSeq);
}

bool key_sequence::KeySequence::operator<= (const key_sequence::KeySequence & otherSeq) const {
	return !(otherSeq < *this);
}

bool key_sequence::KeySequence::operator== (const key_sequence::KeySequence & otherSeq) const {
	// If the length of the two key sequences are different, they cannot be equal
	if (this->count() != otherSeq.count()) {
		return false;
	}

	QVector<QKeySequence> otherKeySeq(otherSeq.getSeqVec());

	bool equal = true;

	//for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), QVector<QKeySequence>::const_iterator cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
		// if elements are different. then set equal to false
		if (*cIter != *cOtherIter) {
			equal = false;
		}
	}
	return equal;
}

bool key_sequence::KeySequence::operator!= (const key_sequence::KeySequence & otherSeq) const {
	return !(*this == otherSeq);
}

