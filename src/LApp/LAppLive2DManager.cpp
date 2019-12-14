﻿/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "LAppLive2DManager.hpp"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Rendering/CubismRenderer.hpp>
#include "LAppPal.hpp"
#include "LAppDefine.hpp"
#include "LAppDelegate.hpp"
#include "LAppModel.hpp"
#include "LAppView.hpp"

#include "Communicator.hpp"
#include "JsonConverter.hpp"

using namespace Csm;
using namespace LAppDefine;
using namespace std;

namespace {
    LAppLive2DManager* s_instance = NULL;
}

LAppLive2DManager* LAppLive2DManager::GetInstance()
{
    if (s_instance == NULL)
    {
        s_instance = new LAppLive2DManager();
    }

    return s_instance;
}

void LAppLive2DManager::ReleaseInstance()
{
    if (s_instance != NULL)
    {
        delete s_instance;
    }

    s_instance = NULL;
}

LAppLive2DManager::LAppLive2DManager()
    : _viewMatrix(NULL), _self_model(new Model())
{
    ChangeScene(0);
}

LAppLive2DManager::~LAppLive2DManager()
{
    ReleaseAllModel();
}

void LAppLive2DManager::ReleaseAllModel()
{


	delete _self_model;
}

void LAppLive2DManager::OnUpdate() const
{
    CubismMatrix44 projection;
    int width, height;
    glfwGetWindowSize(LAppDelegate::GetInstance()->GetWindow(), &width, &height);
    projection.Scale(1.0f, static_cast<float>(width) / static_cast<float>(height));

    if (_viewMatrix != NULL)
    {
        projection.MultiplyByMatrix(_viewMatrix);
    }

    const CubismMatrix44    saveProjection = projection;
    //csmUint32 modelCount = _models.GetSize();
    //for (csmUint32 i = 0; i < modelCount; ++i)
    //{
    //    LAppModel* model = GetModel(i);
    //    projection = saveProjection;

    //    // モデル1体描画前コール
    //    LAppDelegate::GetInstance()->GetView()->PreModelDraw(*model);

    //    model->Update();
    //    model->Draw(projection);///< 参照渡しなのでprojectionは変質する

    //    // モデル1体描画後コール
    //    LAppDelegate::GetInstance()->GetView()->PostModelDraw(*model);
    //}

	projection = saveProjection;


	// Pre-call before a model is drawn
	LAppDelegate::GetInstance()->GetView()->PreModelDraw(*_self_model);

	// Fetch the facial data json.
	auto nj =  Communicator::getInstance()->getFacialData();
	if (nj == nullptr) {
		_self_model->update(nullptr);
	}
	else {
		// Make a copy in case the original json is overwritten by other threads.
		nlohmann::json njCopy(*nj);
		_self_model->update(&njCopy);
	}
	_self_model->Draw(projection);

	// Post-call after a model is drawn
	LAppDelegate::GetInstance()->GetView()->PostModelDraw(*_self_model);
}

void LAppLive2DManager::NextScene()
{
    //csmInt32 no = (_sceneIndex + 1) % ModelDirSize;
    //ChangeScene(no);

	// Do nothing
}

void LAppLive2DManager::ChangeScene(Csm::csmInt32 index)
{
    //_sceneIndex = index;
    //if (DebugLogEnable)
    //{
    //    LAppPal::PrintLog("[APP]model index: %d", _sceneIndex);
    //}

    // ModelDir[]に保持したディレクトリ名から
    // model3.jsonのパスを決定する.
    // ディレクトリ名とmodel3.jsonの名前を一致させておくこと.
    std::string model = ModelDir[index];
    std::string modelPath = ResourcesPath + model + "\\";
    std::string modelJsonName = ModelDir[index];
    modelJsonName += ".model3.json";

    //ReleaseAllModel();
    //_models.PushBack(new LAppModel());
    //_models[0]->LoadAssets(modelPath.c_str(), modelJsonName.c_str());
	_self_model->LoadAssets(modelPath.c_str(), modelJsonName.c_str());

    /*
     * モデル半透明表示を行うサンプルを提示する。
     * ここでUSE_RENDER_TARGET、USE_MODEL_RENDER_TARGETが定義されている場合
     * 別のレンダリングターゲットにモデルを描画し、描画結果をテクスチャとして別のスプライトに張り付ける。
     */
    {
#if defined(USE_RENDER_TARGET)
        // LAppViewの持つターゲットに描画を行う場合、こちらを選択
        LAppView::SelectTarget useRenderTarget = LAppView::SelectTarget_ViewFrameBuffer;
#elif defined(USE_MODEL_RENDER_TARGET)
        // 各LAppModelの持つターゲットに描画を行う場合、こちらを選択
        LAppView::SelectTarget useRenderTarget = LAppView::SelectTarget_ModelFrameBuffer;
#else
        // デフォルトのメインフレームバッファへレンダリングする(通常)
        LAppView::SelectTarget useRenderTarget = LAppView::SelectTarget_None;
#endif

#if defined(USE_RENDER_TARGET) || defined(USE_MODEL_RENDER_TARGET)
        // モデル個別にαを付けるサンプルとして、もう1体モデルを作成し、少し位置をずらす
        _models.PushBack(new LAppModel());
        _models[1]->LoadAssets(modelPath.c_str(), modelJsonName.c_str());
        _models[1]->GetModelMatrix()->TranslateX(0.2f);
#endif

        LAppDelegate::GetInstance()->GetView()->SwitchRenderingTarget(useRenderTarget);

        // 別レンダリング先を選択した際の背景クリア色
        float clearColor[3] = { 1.0f, 1.0f, 1.0f };
        LAppDelegate::GetInstance()->GetView()->SetRenderTargetClearColor(clearColor[0], clearColor[1], clearColor[2]);
    }
}

//csmUint32 LAppLive2DManager::GetModelNum() const
//{
//    return _models.GetSize();
//}
