#pragma once

#include <QObject>
#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>

class Communicator {
	Q_OBJECT
public:
	static void initialize();
	static void dispose();
	static const Communicator* getInstance() { return s_self; }

public:
	const nlohmann::json* getValidNJson() const;

private:
	Communicator();
	Communicator(const Communicator&) = delete;
	~Communicator() {}

private:
	static Communicator* s_self;

	// temporary trick
	nlohmann::json* _current_received_json = nullptr;
	nlohmann::json* _last_received_json = nullptr;

private slots:
	void fetchJson();	// Get the newly written json object
};