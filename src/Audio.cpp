#include <Audio.h>
#define MAX_AUDIO_LEN 960000 //������ջ��������������ֵ�ͼ���
#define FRAME_LEN_60ms 960 //ÿһ������֡������960�ֽ�
Audio* Audio::audio = nullptr;

Audio* Audio::getInstance()
{
	if (audio == nullptr)
		audio = new Audio();
	return audio;
}

bool Audio::audioStart()
{
    int port = Setting::getSetting()->getAudioPort();
    if (m_Output != nullptr && m_Input != nullptr)
        return false;
    return audioRestart();
}
bool Audio::audioRestart() {
    if (m_Output != nullptr && m_Input != nullptr) {
        delete m_Output;
        delete m_Input;
    }
    int port = Setting::getSetting()->getAudioPort();
    audioSocket->bind(QHostAddress::Any, port);
    setaudioformat(8000, 1, 16);//TODO:add setting
    inputDevice = m_Input->start();
    outputDevice = m_Output->start();
    timer->start(60);
    QObject::connect(inputDevice, &QIODevice::readyRead, this, &Audio::onReadyRecord);
    QObject::connect(timer, &QTimer::timeout, this, &Audio::play);
    QObject::connect(audioSocket, &QUdpSocket::readyRead, this, &Audio::receiveData);
    return true;
}

Audio::Audio()
{
	audioSocket = new QUdpSocket();
    timer = new QTimer();
	audioStart();
}

void Audio::setaudioformat(int samplerate, int channelcount, int samplesize) {
    format.setSampleRate(samplerate);
    format.setChannelCount(channelcount);
    format.setSampleSize(samplesize);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    QAudioDeviceInfo info = Setting::getSetting()->getInputDevice();
    QAudioDeviceInfo outfo = Setting::getSetting()->getOutputDevice();//XD
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    m_Input = new QAudioInput(info,format, this);
    m_Output = new QAudioOutput(outfo,format);

}
void Audio::onReadyRecord() {
    stream vp;
    memset(&vp.data, 0, sizeof(vp));

    // read audio from input device
    vp.lens = inputDevice->read(vp.data, 960);
    for (CallObj* callobj : *Network_QT::getInstance()->getCallObjs()) {
        if(callobj->getSocket()->state() == QTcpSocket::ConnectedState)
            audioSocket->writeDatagram((const char*)&vp, sizeof(vp), callobj->getSocket()->peerAddress(), callobj->getSocket()->peerPort());
    }

}

void Audio::play() {
    if (m_PCMDataBuffer.size() < m_CurrentPlayIndex + FRAME_LEN_60ms) {//��������������60ms��Ƶ
        return;
    }
    char* writeData = new char[FRAME_LEN_60ms];
    memcpy(writeData, &m_PCMDataBuffer.data()[m_CurrentPlayIndex], FRAME_LEN_60ms);
    // д����Ƶ����
    outputDevice->write(writeData, FRAME_LEN_60ms);
    m_CurrentPlayIndex += FRAME_LEN_60ms;
    qDebug() << m_CurrentPlayIndex;
    delete[]writeData;

    //������ȳ�����MAX_AUDIO_LEN�ʹ�
    if (m_CurrentPlayIndex > MAX_AUDIO_LEN) {
        m_PCMDataBuffer = m_PCMDataBuffer.right(m_PCMDataBuffer.size() - MAX_AUDIO_LEN);
        m_CurrentPlayIndex -= MAX_AUDIO_LEN;
    }
}

void Audio::receiveData() {
    while (audioSocket->hasPendingDatagrams()) {
        QHostAddress senderip;
        quint16 senderport;
        qDebug() << "audio is being received..." << endl;
        stream vp;
        memset(&vp, 0, sizeof(vp));
        audioSocket->readDatagram((char*)&vp, sizeof(vp), &senderip, &senderport);
        //outputDevice->write(vp.data,vp.lens);
        addAudioBuffer(vp.data, vp.lens);
    }
}
void Audio::addAudioBuffer(char* pData, int len)
{
    //QMutexLocker locker(&m_Mutex);

    m_PCMDataBuffer.append(pData, len);
    //m_IsPlaying = true;
}

Audio::~Audio() {
    delete m_Input;
    delete inputDevice;
    delete m_Output;
    delete outputDevice;
    delete timer;
}