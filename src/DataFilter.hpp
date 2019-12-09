#pragma once


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
