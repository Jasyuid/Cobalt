#pragma once

#include "Cobalt.h"

#include "Cobalt/Rendering/Light.h"

class ShowcaseLayer : public Cobalt::Layer
{
public:
	ShowcaseLayer();
	~ShowcaseLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	
	bool OnEvent(Cobalt::Event& e) override;
	void OnUpdate(float dt) override;

private:
	Cobalt::Model* model;
	Cobalt::EditorCamera* camera;

	std::shared_ptr<Cobalt::Material> mat;
	std::shared_ptr<Cobalt::Material> tex_mat;

	Cobalt::Light* light;
};