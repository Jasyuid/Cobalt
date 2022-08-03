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

	Cobalt::Shader* shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
	Cobalt::Shader* tex_shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/BasicTexture.frag");
	Cobalt::Shader* texl_shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/LightTexture.frag");

	mat = std::shared_ptr<Cobalt::Material>(new Cobalt::BasicMaterial(shader));
	tex_mat = std::shared_ptr<Cobalt::Material>(new Cobalt::TextureMaterial(tex_shader, tex));
	texl_mat = std::shared_ptr<Cobalt::Material>(new Cobalt::TextureMaterial(texl_shader, tex));

	model = new Cobalt::Model("res/Cerberus/Cerberus_LP.fbx", texl_mat);
	model->Scale(glm::vec3(0.1f));
	model->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	light = new Cobalt::Light(glm::vec3(10.0f), glm::vec3(0.5f, 0.8f, 1.0f));
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
	//model->Rotate(10.0f * dt, glm::vec3(0.0f, 1.0f, 0.0f));

	camera->OnUpdate(0.0f);

	model->GetMaterial()->GetShader()->Bind();
	model->GetMaterial()->GetShader()->SetUniformMat4("camera", camera->GetCameraMatrix());
	model->GetMaterial()->GetShader()->SetUniformFloat3("viewPos", camera->GetPosition());
	model->GetMaterial()->GetShader()->SetUniformFloat3("lightPos", light->GetPosition());
	model->GetMaterial()->GetShader()->SetUniformFloat3("lightCol", light->GetColor());

	//CB_TRACE("Camera: ({0}, {1}, {2})", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

	model->Draw();
}
