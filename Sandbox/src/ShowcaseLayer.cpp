#include "ShowcaseLayer.h"

ShowcaseLayer::ShowcaseLayer()
	: Layer("ShowcaseLayer")
{
	camera = new Cobalt::EditorCamera(glm::vec3(0.0f, 0.0f, 0.0f), 15.0f);

	model = new Cobalt::Model("res/Cerberus_LP.fbx");
	model->Scale(glm::vec3(0.1f));
	model->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	shader = new Cobalt::Shader("res/shaders/Basic.glsl");
}

ShowcaseLayer::~ShowcaseLayer()
{
}

void ShowcaseLayer::OnAttach()
{

}

void ShowcaseLayer::OnDetach()
{

}

bool ShowcaseLayer::OnEvent(Cobalt::Event& e)
{
	camera->OnEvent(e);
	return e.IsHandled();
}

void ShowcaseLayer::OnUpdate(float dt)
{
	camera->OnUpdate(0.0f);

	shader->Bind();
	shader->SetUniformMat4("camera", camera->GetCameraMatrix());

	model->Draw(shader);
}
