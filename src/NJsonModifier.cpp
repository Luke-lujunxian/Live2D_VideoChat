#pragma once

#include "NJsonModifier.hpp"

// A static class of filter functions
class DataFilter {
private:
	using floatType = float;

public:
	// Head
	static floatType filterHeadAngle(floatType headAngleParam) { return f_thirty(headAngleParam); }
	// Eye
	static floatType filterEyeOpen(floatType eyeOpenParam) { return f_two(eyeOpenParam); }
	static floatType filterEyeBall(floatType eyeBallParam) { return f_pnone(eyeBallParam); }
	static floatType filterEyeSmile(floatType eyeSmileParam) { return f_one(eyeSmileParam); }
	static floatType filterEyeForm(floatType eyeFormParam) { return f_pnone(eyeFormParam); }
	static floatType filterEyeBallForm(floatType eyeBallFormParam) { return f_none(eyeBallFormParam); }
	// Brow
	static floatType filterBrow(floatType browParam) { return f_pnone(browParam); }
	// Mouth
	static floatType filterMouthOpen(floatType mouthOpenParam) { return f_one(mouthOpenParam); }
	static floatType filterMouthForm(floatType mouthFormParam) { return f_pnone(mouthFormParam); }

private:
	static floatType f_thirty(floatType x) { 
		if (x > 30.0f)	return 30.0f;
		else if (x < -30.0f) return -30.0f;
		else return x;
	}
	static floatType f_two(floatType x) {
		if (x > 2.0f)	return 2.0f;
		else if (x < 0.0f) return 0.0f;
		else return x;
	}
	static floatType f_one(floatType x) {
		if (x > 1.0f)	return 1.0f;
		else if (x < 0.0f) return 0.0f;
		else return x;
	}
	static floatType f_pnone(floatType x) {
		if (x > 1.0f)	return 1.0f;
		else if (x < -1.0f) return -1.0f;
		else return x;
	}
	static floatType f_none(floatType x) {
		if (x > 0.0f)	return 0.0f;
		else if (x < -1.0f) return -1.0f;
		else return x;
	}

private:
	DataFilter() = delete;
};

nlohmann::json NJsonModifier::modify(const nlohmann::json* src) {
	nlohmann::json ret{};
	
	rewrite(ret, src);
	return std::move(ret);
}

void NJsonModifier::rewrite(nlohmann::json& j, const nlohmann::json* src) {
	j["Type"] = "Live2D Expression";
	auto data = (*src)["data"];

	auto brow = data["brow"];
	auto eye = data["eye"];
	auto head = data["head"];

	// brow data
	auto paramBrowLY = DataFilter::filterBrow(brow["ParamBrowLY"]);
	auto paramBrowRY = DataFilter::filterBrow(brow["ParamBrowRY"]);
	// eyeball data
	auto paramEyeBallX = DataFilter::filterEyeBall(eye["ParamEyeBallX"]);
	auto paramEyeBallY = DataFilter::filterEyeBall(eye["ParamEyeBallY"]);
	auto paramEyeLOpen= DataFilter::filterEyeOpen(eye["ParamEyeLOpen"]);
	auto paramEyeROpen= DataFilter::filterEyeOpen(eye["ParamEyeROpen"]);
	// head angle data
	auto paramAngleX = DataFilter::filterHeadAngle(head["ParamAngleX"]);
	auto paramAngleY = DataFilter::filterHeadAngle(head["ParamAngleY"]);
	auto paramAngleZ = DataFilter::filterHeadAngle(head["ParamAngleZ"]);
	// mouth data
	auto paramMouthOpenY = DataFilter::filterMouthOpen(data["ParamMouthOpenY"]);
	
	j["Parameters"] = {
		// brow data
		{
			{"Id", "ParamBrowLY"}, {"Value", paramBrowLY}, {"Blend", "Add"}
		},
		{
			{"Id", "ParamBrowRY"}, {"Value", paramBrowRY}, {"Blend", "Add"}
		},
		// eye data
		{
			{"Id", "ParamEyeBallX"}, {"Value", paramEyeBallX}, {"Blend", "Add"}
		},
		{
			{"Id", "ParamEyeBallY"}, {"Value", paramEyeBallY}, {"Blend", "Add"}
		},
		{
			{"Id", "ParamEyeLOpen"}, {"Value", paramEyeLOpen}, {"Blend", "Multiply"}
		},
		{
			{"Id", "ParamEyeROpen"}, {"Value", paramEyeROpen}, {"Blend", "Multiply"}
		},
		// head angle data
		{
			{"Id", "ParamAngleX"}, {"Value", paramAngleX}, {"Blend", "Add"}
		},
		{
			{"Id", "ParamAngleY"}, {"Value", paramAngleY}, {"Blend", "Add"}
		},
		{
			{"Id", "ParamAngleZ"}, {"Value", paramAngleZ}, {"Blend", "Add"}
		},
		// mouth data
		{
			{"Id", "ParamMouthOpenY"}, {"Value", paramMouthOpenY}, {"Blend", "Add"}
		}
	};
}
