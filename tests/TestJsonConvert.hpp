#pragma once


#ifdef _TEST_RUN__

#include <nlohmann/json.hpp>
#include <Utils/CubismJson.hpp>
#include <iostream>
#include <iomanip>
#include <LApp/LAppPal.hpp>
#include <fstream>


//////////////////////////////////////////////////////////////////////////
#include <string>
#include <windows.h>

// Source: https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}
//////////////////////////////////////////////////////////////////////////

class TestJsonConvert {
public:
	static void runTest() {
		using namespace Csm;
		using namespace Csm::Utils;

		TestJsonConvert test;

		csmSizeInt size;
		csmByte* buffer = LAppPal::loadNJsonAsBytes(&(test._data1), &size);

		std::cout << buffer << std::endl;
		auto res = CubismJson::Create(buffer, size);
	
		print(*res);

		LAppPal::ReleaseBytes(buffer);
	}

	static void runTest2() {
		using namespace Csm;	using namespace Csm::Utils;
		using namespace std;

		TestJsonConvert test;

		csmSizeInt size;
		csmByte* buffer = LAppPal::LoadFileAsBytes(test._path, &size);
		cout << buffer << endl;
		CubismJson* cuJson = CubismJson::Create(buffer, size);
		print(*cuJson);
		LAppPal::ReleaseBytes(buffer);
	}
	
private:
	TestJsonConvert() {
		_data1 = {
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

		std::fstream file(_path, std::ios::in);
		if (!file.is_open()) {
			std::cerr << getexepath() << std::endl;
			std::cerr << "Cannot open " << _path << std::endl;
			exit(2);
		}
		file >> _data2;
		file.close();
	}

	std::string _path = "..\\..\\res\\Hiyori\\expressions\\F06.exp3.json";
	nlohmann::json _data1, _data2;

private:
	static void print(const Csm::Utils::CubismJson& j){
		using std::cout;

		auto stateFlags = cout.flags();
		cout << std::boolalpha;

		doPrint(&j.GetRoot());

		cout.flags(stateFlags);
	}

	static void doPrint(Csm::Utils::Value* v) {
		using namespace Csm;
		using std::cout;	using std::endl;

		if (v == nullptr) {
			cout << "nullptr";
		}
		else if (v->IsMap()) {
			auto s = dynamic_cast<Utils::Map*>(v)->GetString().GetRawString();
			cout << s;
		}
		else if (v->IsArray()) {
			auto s = dynamic_cast<Utils::Array*>(v)->GetString().GetRawString();
			cout << s;
		}
		else if (v->IsFloat()) {
			auto s = dynamic_cast<Utils::Float*>(v)->GetString().GetRawString();
			cout << s;
		}
		else if (v->IsString()) {
			auto s = dynamic_cast<Utils::String*>(v)->GetString().GetRawString();
			cout << s;
		}
		else {
			cout << v->GetRawString();
		}
		
	}
};

#endif