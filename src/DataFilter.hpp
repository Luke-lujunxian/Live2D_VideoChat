#pragma once


// A static class of filter functions
class DataFilter {
public:
	// Head
	static float filterHeadAngle(float headAngleParam) { return f_thirty(headAngleParam); }
	// Eye
	static float filterEyeOpen(float eyeOpenParam) { return f_two(eyeOpenParam); }
	static float filterEyeBall(float eyeBallParam) { return f_pnone(eyeBallParam); }
	static float filterEyeSmile(float eyeSmileParam) { return f_one(eyeSmileParam); }
	static float filterEyeForm(float eyeFormParam) { return f_pnone(eyeFormParam); }
	static float filterEyeBallForm(float eyeBallFormParam) { return f_none(eyeBallFormParam); }
	// Brow
	static float filterBrow(float browParam) { return f_pnone(browParam); }
	// Mouth
	static float filterMouthOpen(float mouthOpenParam) { return f_one(mouthOpenParam); }
	static float filterMouthForm(float mouthFormParam) { return f_pnone(mouthFormParam); }

private:
	static float f_thirty(float x) { 
		if (x > 30.0f)	return 30.0f;
		else if (x < -30.0f) return -30.0f;
		else return x;
	}
	static float f_two(float x) {
		if (x > 2.0f)	return 2.0f;
		else if (x < 0.0f) return 0.0f;
		else return x;
	}
	static float f_one(float x) {
		if (x > 1.0f)	return 1.0f;
		else if (x < 0.0f) return 0.0f;
		else return x;
	}
	static float f_pnone(float x) {
		if (x > 1.0f)	return 1.0f;
		else if (x < -1.0f) return -1.0f;
		else return x;
	}
	static float f_none(float x) {
		if (x > 0.0f)	return 0.0f;
		else if (x < -1.0f) return -1.0f;
		else return x;
	}

private:
	DataFilter() = delete;
};