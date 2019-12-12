#pragma once
#include <QtNetwork/qudpsocket.h>
#include <Network_QT.h>
#include <Setting.h>
#include <QtMultimedia/qaudio>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>
#include <qtimer.h>
#include <qmutex.h>
class Audio: public QObject {

	Q_OBJECT;
public:
	QUdpSocket* audioSocket;
	static Audio* audio;
	Audio* getInstance();
	bool audioStart(int port);
private:
	Audio();
	Audio(Audio&) = delete;
	Audio& operator=(Audio) = delete;

	void setaudioformat(int samplerate, int channelcount, int samplesize);

	QAudioInput* input;
	QIODevice* inputDevice;
	QAudioOutput* m_OutPut = nullptr;
	QIODevice* outputDevice = nullptr;

	QAudioFormat format;
	QTimer* timer;
	QByteArray m_PCMDataBuffer;
	int m_CurrentPlayIndex = 0;
	QMutex m_Mutex;
	void addAudioBuffer(char* pData, int len);

	~Audio();

private slots:
	void onReadyRecord();
	void play();
	void receiveData();
};
struct stream {
	int lens;
	char data[960];
};
/*
Some code and idea from 
https://blog.csdn.net/hanzhen7541/article/details/98794555
https://github.com/Wzing0421/QTAudio


*/