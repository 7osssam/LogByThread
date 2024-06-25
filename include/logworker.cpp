// logworker.cpp

#include "logworker.h"
#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QTextStream>

#include <QThread>

#define APP_LOGS_DIRNAME "Logs"
#define APP_LOGS_FILENUM (10)

LogWorker::LogWorker(QObject *parent) : QObject(parent), flagFileIsInit_(false), fileFlushSize_(0), writtenDataLength_(0)
{
	setObjectName("LogWorker");
}

LogWorker::~LogWorker()
{
	// Ensure log file is properly flushed and closed upon destruction
	if (logFile_.isOpen())
	{
		logFile_.flush();
		logFile_.close();
	}
}

// Slot function to write a log string to the log file
void LogWorker::onWriteLog(const QString &logStr)
{
	QMutexLocker locker(&fileMutex_); // Lock mutex to ensure thread safety

	// Initialize log file if not already initialized
	if (!flagFileIsInit_)
	{
		flagFileIsInit_ = initLoggingFile(logFile_);
	}

	// Write log string to file if it's not empty and file is open
	if (!logStr.isEmpty() && logFile_.isOpen())
	{
		// Write log string to file and update written data length counter
		auto ret = logFile_.write(logStr.toLocal8Bit().constData(), logStr.length());

		// If write operation is successful, update written data length counter
		if (ret > 0)
		{
			writtenDataLength_ += static_cast<quint64>(ret);
			// Flush the log file if flush size is reached or exceeded
			if (fileFlushSize_ == 0 || writtenDataLength_ >= fileFlushSize_)
			{
				logFile_.flush();
				writtenDataLength_ = 0;
			}
		}
	}
}

// Slot function to set the log flush size
void LogWorker::onSetLogFlushSize(quint64 size)
{
	QMutexLocker locker(&fileMutex_); // Lock mutex to ensure thread safety
	fileFlushSize_ = size;			  // Set the new log flush size
	logFile_.flush();				  // Flush the log file to apply changes
	writtenDataLength_ = 0;			  // Reset the written data length counter
}

// Function to initialize the logging file
bool LogWorker::initLoggingFile(QFile &fileHandler)
{
	const QString appDir = QCoreApplication::applicationDirPath(); // Get application directory path
	QDir logsDir(appDir);										   // Create a QDir object for the application directory

	// Check if the Logs directory exists, create it if it doesn't
	if (!logsDir.exists(APP_LOGS_DIRNAME))
	{
		if (!logsDir.mkdir(APP_LOGS_DIRNAME))
		{
			return false; // Return false if directory creation fails
		}
	}

	logsDir.cd(APP_LOGS_DIRNAME); // Navigate to the Logs directory

	// Remove old log files if the number exceeds APP_LOGS_FILENUM
	QStringList logFiles = logsDir.entryList(QDir::Files, QDir::Time);
	while (logFiles.size() >= APP_LOGS_FILENUM)
	{
		logsDir.remove(logFiles.takeLast());
	}

	// Generate a new log file name based on current date and time
	const QString logFileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".log";
	fileHandler.setFileName(logsDir.filePath(logFileName)); // Set the file name/path for the log file

	// Open the log file in append mode, create if it doesn't exist, and in text mode
	return fileHandler.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
}
