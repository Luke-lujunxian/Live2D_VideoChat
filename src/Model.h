#pragma once

#include "../lib/Cubism/Framework/src/Model/CubismUserModel.hpp"
#include "../lib/Cubism/Framework/src/ICubismModelSetting.hpp"
#include "../lib/Cubism/Framework/src/Motion/ACubismMotion.hpp"
#include "../lib/nlohmann/json.hpp"

namespace Csm = Live2D::Cubism::Framework;

class Model : public Csm::CubismUserModel {
public:
	Model();
	~Model();
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

public:
	void update(nlohmann::json* data);

private:
	void initialize();
	void draw();

private:
	Csm::ICubismModelSetting* _modelSetting;
	Csm::ACubismMotion* _currentExpression;
};