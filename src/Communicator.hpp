#ifndef COMMUNICATOR_HPP_
#define COMMUNICATOR_HPP_

#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>
#include <QObject>

class Communicator : public QObject {
	Q_OBJECT;

public:
	static void releaseInstance();
	static Communicator* getInstance();

public:
	// Fetch and return a nlohmann-style json object valid for conversion
	// Return nullptr if the attempt fails
	const nlohmann::json* getSelfFacialData();

private:
	Communicator();
	Communicator(const Communicator&) = delete;
	~Communicator() {}
	
private:
	bool _isSelfUpdated = false;
	const nlohmann::json* _selfFacialData = nullptr;

private slots:
	void fetchSelfFacialData();
};

#endif