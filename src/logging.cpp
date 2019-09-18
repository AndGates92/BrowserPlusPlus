/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Graphics functions
 */

#include <iostream>

#include <qt5/QtCore/QMessageLogContext>
#include <qt5/QtCore/QTextStream>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QtGlobal>

#include "logging.h"

void logging::handler(QtMsgType type, const QMessageLogContext & context, const QString & message) {

		QString info_str("");

	// CategoryFunction
	if (context.category != Q_NULLPTR) {
		info_str.append("[");
		info_str.append(context.category);
		info_str.append("] ");
	}

	// Filename
	if (context.file != Q_NULLPTR) {
		info_str.append("File ");
		info_str.append(context.file);
	}

	// Function
	if (context.function != Q_NULLPTR) {
		info_str.append(" in function ");
		info_str.append(context.function);
	}

	// @TODO print error message
	if (!logfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		const QString filename(logfile.fileName());
		std::cerr << "Uname to open file " << filename.toStdString() << std::endl;
		exit(EXIT_FAILURE);
	}

	QTextStream ologfile(&logfile);

	switch(type) {
		case QtDebugMsg:
			ologfile << "Debug" << info_str << " " << message << "n";
			break;
		case QtInfoMsg:
			ologfile << "Info" << info_str << " " << message <<  "n";
			break;
		case QtWarningMsg:
			ologfile << "Warning" << info_str << " " << message << "n";
			break;
		case QtCriticalMsg:
			ologfile << "Critical" << info_str << " " << message << "n";
			break;
		case QtFatalMsg:
			ologfile << "Fatal" << info_str << " " << message << "n";
			break;
	}

}
