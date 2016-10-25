#ifndef ATIMELOGGER_H
#define ATIMELOGGER_H

#include <QtGui/QMainWindow>
#include "ui_atimelogger.h"

//Qt
#include <QTimer>
#include <QElapsedTimer>
#include <phonon>

class Phonon::MediaObject;
class Phonon::AudioOutput;

class ATimeLogger : public QMainWindow
{
	Q_OBJECT

public:
	ATimeLogger(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ATimeLogger();

public slots:
	//开始编程
	void StartProgramSlot();
	//暂停编程
	void PauseProgramSlot();
	//结束编程
	void StopProgramSlot();
	//编程 更新时间
	void UpdateProgramTimeSlot();
	//番茄
	void RingProgramTomatoSlot();

private:
	Ui::ATimeLoggerClass ui;

	//编程计时器
	QTimer m_ProgramTimer;
	//番茄计时器
	QTimer m_ProgramTomatoTimer;
	//编程进行时间
	QElapsedTimer m_ProgramElapsedTimer;
	//编程进行秒数
	qint64 m_ProgramSecs;

	//铃声播放器
	Phonon::MediaObject *m_PlayObject;
	Phonon::AudioOutput *m_PlayOutput;
};

#endif // ATIMELOGGER_H
