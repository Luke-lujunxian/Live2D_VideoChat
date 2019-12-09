#pragma once

#ifndef _TEST_RUN__
#define _TEST_RUN__

#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>
#include <iostream>
#include <iomanip>
#include <LApp/LAppPal.hpp>


class TestJsonConvert {
public:
	static void runTest() {
		using namespace Csm;
		using namespace Csm::Utils;

		TestJsonConvert test;

		csmSizeInt size;
		csmByte* buffer = LAppPal::loadNJsonAsBytes(&(test._data), &size);

		auto res = CubismJson::Create(buffer, size);
		print(*res);

		LAppPal::ReleaseBytes(buffer);
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
	static void print(const Csm::Utils::CubismJson& j){
		using std::cout;

		auto stateFlags = cout.flags();
		cout << std::boolalpha;

		doPrint(&j);

		cout.flags(stateFlags);
	}

	static void doPrint(const Csm::Utils::CubismJson* j) {
		using std::cout;	using std::endl;

		cout << j->GetRoot().GetRawString() << endl;
	}
};

#endif