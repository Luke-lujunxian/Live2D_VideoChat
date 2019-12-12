#pragma once
#ifndef NETWORK_QT_H_
#define NETWORK_QT_H_


#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <guiddef.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <Base64.h>
//https://lowrey.me/guid-generation-in-c-11/
#include <sstream>
#include <random>
#include <string>
#include <qobject.h>
#include <qthread.h>
#include <QtNetwork/qtcpsocket.h>
#include <QtNetwork/qtcpserver.h>
#include <Setting.h>
#include <detection.h>
#include <quuid.h>
#include <helper.hpp>
#include <QtNetwork/qudpsocket.h>
#include <Audio.h>
using namespace nlohmann;
std::string GenerateGuid();

typedef enum LatencyState { NORMAL, DELAY, DISCONNECTED };
class CallObj;
class MotionObject {
private:
	std::string sessionId;
	json motion;
	clock_t lastSuccessful;
	cv::Mat profile;
	const std::string modelID;
public:
	std::string name;
	bool alive;
	MotionObject() {
		this->alive = true;
		this->sessionId = GenerateGuid();
		lastSuccessful = clock();
	}
	MotionObject(std::string sessionId) {
		this->alive = true;
		this->sessionId = sessionId;
	}

	void writeObject(std::string received) {
		json jtemp;
		try {
			jtemp = json::parse(received);

		}
		catch (json::exception e) {
			if (e.id == 101) {
				if (received == "") {
					//not Receiving
				}
				else {
					//data incorrect
				}
			}
			else {
				//unknown error
			}

			return;
		}
		motion.erase("data");
		motion.emplace("data", jtemp["data"]);
		lastSuccessful = clock();
	}

	json* getMotion() {
		return &motion;
	}

	LatencyState getLatencyState() {
		int delay = clock(); -lastSuccessful;
		if (delay <= 300) {
			return NORMAL;
		}
		else if (delay > 300 && delay < 3000) {
			return DELAY;
		}
		else {
			return DISCONNECTED;
		}
	}

	void setProfileByBase64(std::string base64) {
		try {
			profile = Base2Mat(base64);
		}
		catch (int e) {
			//prifile = dafault
			return;
		}
	}

};

class Network_QT:public QObject {
	Q_OBJECT;
public:
	bool networkInit();
	void updateMotion(json& motion);
	std::vector<MotionObject*>* getDisplayObjects();
	json* getSendJson();
	bool shouldStop() {
		return stopFlag;
	}
	static Network_QT* getInstance() {
		if (network_QT == nullptr)
			network_QT = new Network_QT();
		return network_QT;
	}
	void call(std::string, int);
	void call(std::string target);
	std::vector<CallObj*>* getCallObjs() {
		return &callObjs;
	}

private:
	std::vector<MotionObject*> displayObjects;
	json sendObject;
	Network_QT();
	Network_QT(Network_QT&) = delete;
	Network_QT& operator=(Network_QT) = delete;
	QTcpServer* listener;
	bool stopFlag;
	static Network_QT* network_QT;
	std::vector<QThread*> calls = std::vector<QThread*>(5);
	std::vector<CallObj*> callObjs = std::vector<CallObj*>(5);
	//Warning: All Network will end
	void stop() {
		stopFlag = true;
	}
	private slots:
		void ConnectHandler();
};


class CallObj :public QObject {
	Q_OBJECT;
	MotionObject* motion;
	QTcpSocket* s;
public:
	CallObj(MotionObject* motion, QTcpSocket* s);
	QTcpSocket* getSocket() {
		return s;
	}


private slots:
	void sendObject() {
		s->write(Network_QT::getInstance()->getSendJson()->dump().c_str(), Network_QT::getInstance()->getSendJson()->dump().length());
	}
	void writeObject() {
		if(s->canReadLine())
			motion->writeObject(s->readLine().toStdString());
	}
};


#endif // !NETWORK_QT_H_