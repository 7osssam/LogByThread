// logworker.h

#ifndef LOGWORKER_H
#define LOGWORKER_H

#include <QObject>
#include <QFile>
#include <QMutex>

class LogWorker : public QObject
{
	Q_OBJECT
public:
	explicit LogWorker(QObject *parent = nullptr);
	~LogWorker();

public slots:
	void onWriteLog(const QString &logStr);
	void onSetLogFlushSize(quint64 size);

private:
	bool initLoggingFile(QFile &fileHandler);

	QFile logFile_;
	bool flagFileIsInit_;
	quint64 fileFlushSize_;
	quint64 writtenDataLength_;
	QMutex fileMutex_;
};

#endif // LOGWORKER_H
