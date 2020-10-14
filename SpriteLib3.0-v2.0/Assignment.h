#pragma once

#include "Scene.h"
#include <iomanip>

class Assignment : public Scene
{
public:
	Assignment(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:
	bool isJumping;
};
