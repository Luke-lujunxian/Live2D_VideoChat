#pragma once

#include <QObject>
#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>

class Communicator : public QObject {
	Q_OBJECT;
public:
	static void initialize();
	static void dispose();
	static const Communicator* getInstance();

public:
	const nlohmann::json* getNJson() const;

private:
	Communicator();
	Communicator(const Communicator&) = delete;
	~Communicator() {}

private:
	static Communicator* s_instance;

	// temporary trick
	const nlohmann::json* _current_received_json = nullptr;
	const nlohmann::json* _last_received_json = nullptr;

private slots:
	void fetchJson();	// Get the newly written json object
};