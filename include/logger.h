// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>
#include <QtGlobal>
#include <QMutex>
#include <QQueue>

class Logger : public QObject
{
	Q_OBJECT
public:
	explicit Logger(QObject *parent = nullptr);
	~Logger();

	static Logger *instance();
	bool isLogging() const;
	void startLogging();
	void suspendLogging();
	void setLogFlushSize(quint64 size);

signals:
	void WriteLog(const QString &str);
	void SetLogFlushSize(quint64 size);

public:
	static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
	static Logger *instance_;
	static QMutex instanceMutex_;
	QThread workerThread_;
	bool isLogging_;
	bool threadInit_;
	quint64 logFlushSize_;
};

#endif // LOGGER_H
