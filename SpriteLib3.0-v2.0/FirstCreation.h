#pragma once

#include "Scene.h"

class FirstCreation : public Scene
{
public:
	FirstCreation(std::string name);

	void Unload();

	void InitScene(float widnowWidth, float windowHeight) override;

	void Update() override;

	void AdjustScrollOffset();

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;
};
