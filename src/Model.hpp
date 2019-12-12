#pragma once

#include "LApp/LAppModel.hpp"
#include <nlohmann/json.hpp>


class Model : public LAppModel {
public:
	Model();
	virtual ~Model();
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

public:
	void update(const nlohmann::json* data);
	//void initialize(ICubismModelSetting* setting)
	void setDefaultExpression();
	void setErrorExpression();

private:
	void setExpression(const nlohmann::json* data);
	void resetCurrentExpression();

private:
	Csm::ACubismMotion* _currentExpression = nullptr;
	Csm::ACubismMotion* _defaultExpression = nullptr;
	Csm::ACubismMotion* _errorExpression = nullptr;

};