// logger.cpp
#include "logger.h"
#include "logworker.h"

#include <QDateTime>
#include <QDir>
#include <cstdio>

Logger *Logger::instance_ = nullptr;
QMutex Logger::instanceMutex_;

Logger::Logger(QObject *parent) : QObject(parent), isLogging_(false), threadInit_(false), logFlushSize_(0)
{
}

Logger::~Logger()
{
	workerThread_.quit();
	workerThread_.wait();
}

Logger *Logger::instance()
{
	QMutexLocker locker(&instanceMutex_);
	if (!instance_)
	{
		instance_ = new Logger();
	}
	return instance_;
}

bool Logger::isLogging() const
{
	return isLogging_;
}

void Logger::startLogging()
{
	if (!threadInit_)
	{
		LogWorker *worker = new LogWorker();
		worker->moveToThread(&workerThread_);
		connect(&workerThread_, &QThread::finished, worker, &QObject::deleteLater);
		connect(this, &Logger::WriteLog, worker, &LogWorker::onWriteLog);
		connect(this, &Logger::SetLogFlushSize, worker, &LogWorker::onSetLogFlushSize);
		workerThread_.start();
		threadInit_ = true;
	}

	isLogging_ = true;
}

void Logger::suspendLogging()
{
	isLogging_ = false;
}

void Logger::setLogFlushSize(quint64 size)
{
	emit SetLogFlushSize(size);
}

void Logger::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	if (!instance_ || !instance_->isLogging())
	{
		return;
	}

	QByteArray userMsg = msg.toLocal8Bit();
	QString logMsg;		// Final log message to be written to the log file
	QString logMsgTemp; // Temporary log message to be written to the log file
	const QString strDateTime = QDateTime::currentDateTime().toLocalTime().toString("MM-dd-yyyy hh:mm:ss.zzz-AP");

	// Get the parent folder name of the file by splitting the absolute path and getting the second last element
	QString parentFolder = QDir(context.file)
							   .absolutePath()
							   .split("/")
							   .at(QDir(context.file).absolutePath().split("/").size() - 2);
	QString fileName = parentFolder + "/" + QFileInfo(context.file).fileName();

	switch (type)
	{
	case QtDebugMsg:
		logMsgTemp = QString("[Debug]: %1 (%2:%3, %4)")
						 .arg(userMsg.constData())
						 .arg(fileName)
						 .arg(context.line)
						 .arg(context.function);
		break;
	case QtInfoMsg:
		logMsgTemp = QString("[Info]: %1 (%2:%3, %4)")
						 .arg(userMsg.constData())
						 .arg(fileName)
						 .arg(context.line)
						 .arg(context.function);
		break;
	case QtWarningMsg:
		logMsgTemp = QString("[Warning]: %1 (%2:%3, %4)")
						 .arg(userMsg.constData())
						 .arg(fileName)
						 .arg(context.line)
						 .arg(context.function);
		break;
	case QtCriticalMsg:
		logMsgTemp = QString("[Critical]: %1 (%2:%3, %4)")
						 .arg(userMsg.constData())
						 .arg(fileName)
						 .arg(context.line)
						 .arg(context.function);
		break;
	case QtFatalMsg:
		logMsgTemp = QString("[Fatal]: %1 (%2:%3, %4)")
						 .arg(userMsg.constData())
						 .arg(fileName)
						 .arg(context.line)
						 .arg(context.function);
		break;
	}

	// format:
	// 06-25-2024 11:16:35.845-PM [Info]: start This is a info message (LogByThread/main.cpp:32, int main(int, char**))

	logMsg.append(strDateTime + " ");
	logMsg.append(logMsgTemp + "\n");

	emit instance_->WriteLog(logMsg);

	if (type == QtFatalMsg)
	{
		// Write the log message to the log file before aborting the application
		abort();
	}
}
