#pragma once

#include "Cobalt.h"

#include "Cobalt/Rendering/Light.h"

typedef std::shared_ptr<Cobalt::Material> CobaltMaterial;

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

	CobaltMaterial mat;
	CobaltMaterial tex_mat;
	CobaltMaterial texl_mat;
	CobaltMaterial pbr_mat;
	CobaltMaterial pbrt_mat;

	Cobalt::Light* light;
	float light_int;
};