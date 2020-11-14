/**
 * @copyright
 * @file shared_functions.cpp
 * @author Andrea Gianarda
 * @date 2nd June 2020
 * @brief Main Window Shared Functions
 */

// Qt libraries
#include <QtCore/QFile>
#include <QtCore/QUrl>

#include "common/include/global_constants.h"
#include "windows/main_window/common/include/shared_functions.h"

bool app::main_window::isUrl(const QString & text) {

	const bool containsWww = text.contains(app::shared::www);
	const bool containsHttps = text.contains(app::shared::https);

	// Check also the number of dots in the argument text.
	// In fact QUrl considers as valid an URL that is missing the .TLD (example .com)
	// For example, if text is "cc", the URL built by this method is https://www.cc. It is considered a valid URL by QT whereas it is not
	QString urlStr = QString();

	if (containsHttps == false) {
		urlStr += app::shared::https;
	}

	if (containsWww == false) {
		urlStr += app::shared::www;
	}

	urlStr += text;

	QUrl url(urlStr, QUrl::StrictMode);

	const int numberDots = text.count(".");

	return ((url.isValid() == true) && (numberDots > 0));
}

bool app::main_window::isFile(const QString & text) {
	QFile file(text);
	return file.exists();
}

bool app::main_window::isText(const QString & text) {
	bool validUrl = app::main_window::isUrl(text);
	bool validFile = app::main_window::isFile(text);

	return ((validUrl == false) && (validFile == false));
}
