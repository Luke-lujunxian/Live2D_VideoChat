#pragma once

#include <Cubism/Framework/src/Type/CubismBasicType.hpp>
#include <nlohmann/json.hpp>
#include <string>

// Utilities for buffer manipulation required by Cubism

namespace Csm = Live2D::Cubism::Framework;


Csm::csmByte* loadFileAsBytes(const std::string& filePath, Csm::csmSizeInt* outSize);

void releaseBytes(Csm::csmByte* byteData);

Csm::csmByte* convertJsonToBytes(nlohmann::json* data, Csm::csmSizeInt* outSize);

Csm::csmFloat32 getDeltaTime();

void updateTime();