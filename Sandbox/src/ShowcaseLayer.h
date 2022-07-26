#pragma once

#include "Cobalt.h"

class ShowcaseLayer : public Cobalt::Layer
{
public:
	ShowcaseLayer();
	~ShowcaseLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	
	void OnEvent(Cobalt::Event& e) override;
	void OnUpdate(float dt) override;

private:
	Cobalt::Model* model;
	Cobalt::Shader* shader;
	Cobalt::EditorCamera* camera;

};