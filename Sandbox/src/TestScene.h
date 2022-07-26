#pragma once

#include "Cobalt.h"

class TestScene : public Cobalt::Scene
{
public:
	TestScene();
	~TestScene() override;

	void OnEvent(Cobalt::Event& e) override;
	void OnUpdate(float dt) override;

private:

};
