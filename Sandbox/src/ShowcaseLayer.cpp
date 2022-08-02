#include "ShowcaseLayer.h"

ShowcaseLayer::ShowcaseLayer()
	: Layer("ShowcaseLayer"), camera(nullptr), model(nullptr)
{
	
}

ShowcaseLayer::~ShowcaseLayer()
{
}

void ShowcaseLayer::OnAttach()
{
	camera = new Cobalt::EditorCamera(glm::vec3(0.0f, 0.0f, 0.0f), 15.0f);
	
	Cobalt::Texture* tex = new Cobalt::Texture("res/Cerberus/Cerberus_A.png");

	Cobalt::Shader* shader = new Cobalt::Shader("res/shaders/Basic.glsl");
	Cobalt::Shader* tex_shader = new Cobalt::Shader("res/shaders/BasicTexture.glsl");

	mat = new Cobalt::BasicMaterial(shader);
	tex_mat = new Cobalt::TextureMaterial(tex_shader, tex);

	model = new Cobalt::Model("res/Cerberus/Cerberus_LP.fbx", tex_mat);
	model->Scale(glm::vec3(0.1f));
	model->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

}

void ShowcaseLayer::OnDetach()
{

}

bool ShowcaseLayer::OnEvent(Cobalt::Event& e)
{
	camera->OnEvent(e);

	if (e.GetEventType() == Cobalt::EventType::KeyReleased)
	{
		switch (((Cobalt::KeyReleasedEvent*)&e)->GetKeyCode())
		{
		case CB_KEY_1:
			model->SetMaterial(mat);
			break;
		case CB_KEY_2:
			model->SetMaterial(tex_mat);
			break;
		}
	}

	return e.IsHandled();
}

void ShowcaseLayer::OnUpdate(float dt)
{
	camera->OnUpdate(0.0f);

	model->GetMaterial()->GetShader()->Bind();
	model->GetMaterial()->GetShader()->SetUniformMat4("camera", camera->GetCameraMatrix());

	model->Draw();
}
