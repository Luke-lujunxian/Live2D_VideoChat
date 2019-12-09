#pragma once

#ifndef _TEST_RUN__
#define _TEST_RUN__

#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>
#include <iostream>
#include <iomanip>


class TestJsonConvert {
private:
	using std::cout;	
	using std::endl;

public:
	static void runTest() {
		auto dump = _data.dump();
		csmByte* buffer = reinterpret_cast<csmByte*>(const_cast<char*>(dump.c_str()));
		csmSizeInt size = dump.length();

		auto res = CubismJson::Create(buffer, size);
		print(res);
	}
	
private:
	TestJsonConvert() {
		_data = {
			{"pi", 3.141},
			{"happy", true},
			{"name", "Niels"},
			{"nothing", nullptr},
			{"answer", {
			  {"everything", 42}
			}},
			{"list", {1, 0, 2}},
			{"object", {
			  {"currency", "USD"},
			  {"value", 42.99}
			}}
		};
	}

	nlohmann::json _data;

private:
	void print(const Csm::Utils::CubismJson& j) const {
		auto stateFlags = cout.flags();
		cout << std::boolalpha;

		doPrint(j);

		cout.flags(stateFlags);
	}

	void doPrint(const Csm::Utils::CubismJson& j) const {
		auto root = j.GetRoot();
		auto jMap = root.GetMap();
		for (auto it = jMap->Begin(); it != jMap->End(); ++it) {
			cout << it->First << ": ";
			cout << it->Second->GetString() << endl;
		}
	}
};

#endif