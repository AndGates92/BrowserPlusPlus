/**
 * @copyright
 * @file logging_functions.cpp
 * @author Andrea Gianarda
 * @date 17th of April 2020
 * @brief Logging function definition
 */

#include <QtCore/QDateTime>
#include <QtCore/QTimeZone>

#include "common/include/logging_functions.h"

QString logging_functions::getDateTime() {
	QString datetimeStr = QString();

	QLocale locale(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
	QDateTime datetime = QDateTime::currentDateTime();
	datetime.setTimeSpec(Qt::TimeZone);
	datetimeStr.append(locale.toString(datetime, QLocale::ShortFormat));
	datetimeStr.append(" ");
	datetimeStr.append(datetime.timeZoneAbbreviation());

	return datetimeStr;
}
