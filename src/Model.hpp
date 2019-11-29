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
	void setDefaultExpression();
	void setErrorExpression();

private:
	void setExpression(nlohmann::json* data);
	void initialize(const Csm::csmString& modelHomeDir, Csm::ICubismModelSetting* setting);
	void resetCurrentExpression();

private:
	Csm::csmFloat32 _userTimeSeconds = 0.0f;
	Csm::ICubismModelSetting* _modelSetting = nullptr;
	Csm::ACubismMotion* _currentExpression = nullptr;
	Csm::ACubismMotion* _defaultExpression = nullptr;
	Csm::ACubismMotion* _errorExpression = nullptr;


private:
	Csm::csmVector<Csm::CubismIdHandle> _eyeBlinkIds;
	Csm::csmVector<Csm::CubismIdHandle> _lipSyncIds;
};