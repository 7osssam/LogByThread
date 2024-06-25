#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

#include <QThread>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include "logger.h"

#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// set object name
	QThread::currentThread()->setObjectName("Main Thread");

	qInfo() << "This is a info message";
	qDebug() << "This is a debug message1";
	qWarning() << "This is a warning message";
	qCritical() << "This is a critical message";

	std::cout << "Thread: " << QThread::currentThread()->objectName().toStdString()
			  << " ID: " << QThread::currentThread()->currentThreadId() << std::endl;

	qInstallMessageHandler(Logger::myMessageOutput);
	qInfo() << "Before start This is a info message";
	Logger::instance()->startLogging();

	qInfo() << "start This is a info message";
	qDebug() << "start This is a debug message1";
	qWarning() << "start This is a warning message";
	qCritical() << "start This is a critical message";

	Logger::instance()->suspendLogging();

	qInfo() << "suspend This is a info message";
	qDebug() << "suspend This is a debug message1";
	qWarning() << "suspend This is a warning message";
	qCritical() << "suspend This is a critical message";

	Logger::instance()->startLogging();
	qInfo() << "ِAfter reStart This is a info message";
	qDebug() << "After reStart This is a debug message1";
	qWarning() << "After reStart This is a warning message";
	qCritical() << "After reStart This is a critical message";

	// QTimer::singleShot(1000, &a, &QCoreApplication::quit);
	return a.exec();
}
