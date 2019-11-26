#pragma once

#include <Cubism/Framework/src/Model/CubismUserModel.hpp>
#include <Cubism/Framework/src/ICubismModelSetting.hpp>
#include <Cubism/Framework/src/Motion/ACubismMotion.hpp>
#include <nlohmann/json.hpp>

namespace Csm = Live2D::Cubism::Framework;

class Model : public Csm::CubismUserModel {
public:
	Model();
	virtual ~Model();
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

public:
	void update(nlohmann::json* data);

private:
	void setup(const Csm::csmString& modelHomeDir, Csm::ICubismModelSetting* setting);

private:
	Csm::ICubismModelSetting* _modelSetting = nullptr;
	Csm::ACubismMotion* _currentExpression = nullptr;
};