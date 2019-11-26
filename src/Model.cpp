#include "Model.hpp"
#include "buffer.hpp"
#include <cstring>
#include <exception>

using namespace Csm;

Model::Model()
	: CubismUserModel() { }

void Model::setup(const csmString& modelHomeDir, ICubismModelSetting* setting) {
	_updating = true;
	_initialized = false;

	_modelSetting = setting;

	// Load model from the model file
	if (strcmp(_modelSetting->GetModelFileName(), "" == 0) {
		throw std::exception("Empty model file name!");
	}
	else {
		csmString path = modelHomeDir + _modelSetting->GetModelFileName();
		
		// TODO
	}

	throw std::exception("This function is not implemented yet");
}