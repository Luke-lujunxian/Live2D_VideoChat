#include "Model.hpp"
#include <cstring>
#include <exception>
#include <LApp/LAppPal.hpp>
#include <JsonConverter.hpp>
#include <LApp/LAppDefine.hpp>

#include <QDebug>

using namespace Csm;

Model::Model()
	: LAppModel() { }

Model::~Model() {
	_currentExpression = nullptr;
}

//void Model::initialize(ICubismModelSetting* setting) {
//	_updating = true;
//	_initialized = false;
//
//	_modelSetting = setting;
//
//	csmByte* buffer;
//	csmSizeInt size;
//
//	//////////////////////////////////////////////////////////////////////////
//	// Load model from the model file
//	if (strcmp(_modelSetting->GetModelFileName(), "" == 0)) {
//		throw std::exception("Empty model file name.");
//	}
//	else {
//		csmString path = __modelHomeDir + _modelSetting->GetModelFileName();
//		
//		buffer = loadFileAsBytes(path.GetRawString(), &size);
//		LoadModel(buffer, size);
//		releaseBytes(buffer);
//	}
//
//	// Load expressions (Default & Error)
//	if (_modelSetting->GetExpressionCount() == 0) {
//		throw std::exception("No expression file found. Need a default expression file.");
//	}
//	else {
//		// 0 refers to the first expression file found in the directory.
//		// Assume that it is the default expression.
//		csmString name0 = _modelSetting->GetExpressionName(0);
//		csmString path0 = _modelHomeDir + _modelSetting->GetExpressionFileName(0);
//
//		buffer = loadFileAsBytes(path0.GetRawString(), &size);
//		_defaultExpression = LoadExpression(buffer, size, name0.GetRawString());
//		releaseBytes(buffer);
//
//		// 1 refers to the second expression file found in the directory.
//		// Assume that it is the error expression.
//		csmString name1 = _modelSetting->GetExpressionName(1);
//		csmString path1 = _modelHomeDir + _modelSetting->GetExpressionFileName(1);
//
//		buffer = loadFileAsBytes(path1.GetRawString(), &size);
//		_errorExpression = LoadExpression(buffer, size, name1.GetRawString());
//		releaseBytes(buffer);
//
//		setDefaultExpression();
//	}
//
//	// Load poses
//	if (strcmp(_modelSetting->GetPoseFileName(), "") != 0)
//	{
//		csmString path = _modelHomeDir + _modelSetting->GetPoseFileName();
//
//		buffer = loadFileAsBytes(path.GetRawString(), &size);
//		LoadPose(buffer, size);
//		releaseBytes(buffer);
//	}
//
//	// Load eyeblinks if the auto-eyeblink switch is on
//	{
//		csmInt32 eyeBlinkIdCount = _modelSetting->GetEyeBlinkParameterCount();
//
//		if (eyeBlinkIdCount > 0)
//		{
//			_eyeBlink = CubismEyeBlink::Create(_modelSetting);
//
//			for (csmInt32 i = 0; i < eyeBlinkIdCount; ++i)
//			{
//				_eyeBlinkIds.PushBack(_modelSetting->GetEyeBlinkParameterId(i));
//			}
//		}
//	}
//
//	// Load LipSyncIds
//	{
//		csmInt32 lipSyncIdCount = _modelSetting->GetLipSyncParameterCount();
//		for (csmInt32 i = 0; i < lipSyncIdCount; ++i)
//		{
//			_lipSyncIds.PushBack(_modelSetting->GetLipSyncParameterId(i));
//		}
//	}
//	//////////////////////////////////////////////////////////////////////////
//
//	_model->SaveParameters();
//
//	_motionManager->StopAllMotions();
//
//	_updating = false;
//	_initialized = true;
//}

void Model::update(const nlohmann::json* data) {
	const csmFloat32 deltaTimeSeconds = LAppPal::GetDeltaTime();
	_userTimeSeconds += deltaTimeSeconds;

	// Expression
	_model->LoadParameters();	// For unknown reasons, if this line is removed the model will become ÕÅ ×ì ±Õ ÑÛ ÈË
	if (data == nullptr) {
		// Case: No new facial data
		if (_currentExpression != nullptr) {
			// Replay the last obtained facial data
			//_expressionManager->StartMotionPriority(_currentExpression, false, 3);
		}
		else {
			// Do nothing
		}
	}
	else {
		// Case: New facial data obtained
		setExpression(data);
		_expressionManager->StartMotionPriority(_currentExpression, true, 3);	// Level3 is the highest 'Force' level
		//SetRandomExpression();
	}
	_model->SaveParameters();
	//////////////////////////////////////////////////////////////////////////

	_expressionManager->UpdateMotion(_model, deltaTimeSeconds);

	// Auto breathing
	if (_breath != nullptr)
	{
		_breath->UpdateParameters(_model, deltaTimeSeconds);
	}

	// Set pose
	if (_pose != nullptr)
	{
		_pose->UpdateParameters(_model, deltaTimeSeconds);
	}

	_model->Update();
}

void Model::setExpression(const nlohmann::json* data) {
	//resetCurrentExpression();
	qDebug().noquote() << "[Model] Set new facial data";

	csmSizeInt size;
	csmByte* buffer;

	auto _ = JsonConverter::convert(data, &buffer, &size);

	_currentExpression = LoadExpression(buffer, size, "dummy");

	DeleteBuffer(buffer, "[Live expression data]");
}

