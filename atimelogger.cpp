#include "atimelogger.h"

#include <phonon/audiooutput.h>
#include <phonon/backendcapabilities.h>
#include <phonon/effect.h>
#include <phonon/effectparameter.h>
#include <phonon/effectwidget.h>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include <phonon/videowidget.h>
#include <phonon/volumeslider.h>

ATimeLogger::ATimeLogger(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	//设置图标
	this->setWindowIcon(QIcon(":/Resources/clock.png"));

	//铃声播放
	m_PlayObject = new Phonon::MediaObject();
	m_PlayOutput = new Phonon::AudioOutput(Phonon::MusicCategory,this);
	Phonon::createPath(m_PlayObject,m_PlayOutput);

	//初始化
	m_ProgramSecs = 0;

	QObject::connect(ui.pushButton_Start_Program,SIGNAL(clicked(bool)),this,SLOT(StartProgramSlot()));
	QObject::connect(ui.pushButton_Pause_Program,SIGNAL(clicked(bool)),this,SLOT(PauseProgramSlot()));
	QObject::connect(ui.pushButton_Stop_Program,SIGNAL(clicked(bool)),this,SLOT(StopProgramSlot()));
	QObject::connect(&m_ProgramTimer,SIGNAL(timeout()),this,SLOT(UpdateProgramTimeSlot()));
	QObject::connect(&m_ProgramTomatoTimer,SIGNAL(timeout()),this,SLOT(RingProgramTomatoSlot()));
}

ATimeLogger::~ATimeLogger()
{

}

void ATimeLogger::StartProgramSlot()
{
	m_ProgramTimer.start(1000);

	ui.pushButton_Start_Program->setDisabled(true);
	ui.pushButton_Pause_Program->setDisabled(false);

	if (/*ui.checkBox_Program->isChecked() && */ui.spinBox_Clock_Program->value() > 0)
	{
		int mins = ui.spinBox_Clock_Program->value();
		int countSecs = mins * 60;

		int ival = countSecs;

		if (countSecs > m_ProgramSecs)
		{
			ival = countSecs - m_ProgramSecs;
		}
		m_ProgramTomatoTimer.start(ival * 1000);
	}
}

void ATimeLogger::PauseProgramSlot()
{
	m_ProgramTimer.stop();

	ui.pushButton_Pause_Program->setDisabled(true);
	ui.pushButton_Start_Program->setDisabled(false);

	int countSecs = ui.spinBox_Clock_Program->value() * 60;
	//如果还没到响铃时间，则减去已过去的时间，然后重新开始计时器
}

void ATimeLogger::StopProgramSlot()
{
	m_ProgramTimer.stop();
	m_ProgramSecs = 0;

	ui.pushButton_Pause_Program->setDisabled(true);
	ui.pushButton_Start_Program->setDisabled(false);

	ui.lineEdit_ProgramTime->setText("");
}

void ATimeLogger::UpdateProgramTimeSlot()
{
	qint64 sec = ++m_ProgramSecs;
	qint64 min = sec / 60;
	qint64 hour = min / 60;
	min = min % 60;
	sec = sec % 60;

	QString text = QString("%1-%2-%3").arg(hour).arg(min).arg(sec);
	ui.lineEdit_ProgramTime->setText(text);
}

void ATimeLogger::RingProgramTomatoSlot()
{
	m_PlayObject->setCurrentSource(Phonon::MediaSource(":/Resources/westlife.mp3"));

	m_PlayObject->play();

	m_ProgramTomatoTimer.stop();
}