#pragma once

#include <nlohmann/json.hpp>

// A helper class
// Modify detected nlohmann-style json data to fit with Cubism-style json
class NJsonModifier {
public:
	static nlohmann::json modify(const nlohmann::json* src);

private:
	static void rewrite(nlohmann::json& ret, const nlohmann::json* src);	// Rearrange the nodes to be compatible with Cubism-style json
};