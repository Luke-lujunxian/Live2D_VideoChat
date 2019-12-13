#pragma once

#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>

class Communicator{
public:
	static void initialize();
	static void dispose();
	static const Communicator* getInstance();

public:
	// Fetch and return a nlohmann-style json object valid for conversion
	// Return nullptr if the attempt fails
	const nlohmann::json* getNJson() const;

private:
	Communicator();
	Communicator(const Communicator&) = delete;
	~Communicator() {}

private:
	static Communicator* s_instance;

};