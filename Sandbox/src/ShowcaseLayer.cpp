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
	
	Cobalt::Texture* gun_a = new Cobalt::Texture("res/Cerberus/Cerberus_A.png");
	Cobalt::Texture* gun_n = new Cobalt::Texture("res/Cerberus/Cerberus_N.png");
	Cobalt::Texture* gun_r = new Cobalt::Texture("res/Cerberus/Cerberus_R.png");
	Cobalt::Texture* gun_m = new Cobalt::Texture("res/Cerberus/Cerberus_M.png");
	Cobalt::Texture* gun_ao = new Cobalt::Texture("res/Cerberus/Cerberus_AO.png");

	Cobalt::Texture* rust_a = new Cobalt::Texture("res/Rust/albedo.png");
	Cobalt::Texture* rust_n = new Cobalt::Texture("res/Rust/normal.png");
	Cobalt::Texture* rust_r = new Cobalt::Texture("res/Rust/roughness.png");
	Cobalt::Texture* rust_m = new Cobalt::Texture("res/Rust/metallic.png");
	Cobalt::Texture* rust_ao = new Cobalt::Texture("res/Rust/ao.png");

	Cobalt::Shader* shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/Basic.frag");
	Cobalt::Shader* tex_shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/BasicTexture.frag");
	Cobalt::Shader* texl_shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/LightTexture.frag");
	Cobalt::Shader* pbr_shader = new Cobalt::Shader("res/shaders/Basic.vert", "res/shaders/PBR.frag");
	Cobalt::Shader* pbrt_shader = new Cobalt::Shader("res/shaders/Tangent.vert", "res/shaders/TexturePBR.frag");

	mat = CobaltMaterial(new Cobalt::BasicMaterial(shader));
	tex_mat = CobaltMaterial(new Cobalt::TextureMaterial(tex_shader, gun_a));
	texl_mat = CobaltMaterial(new Cobalt::TextureMaterial(texl_shader, gun_a));
	pbr_mat = CobaltMaterial(new Cobalt::ColorMaterial(pbr_shader, glm::vec3(1.0f, 0.01f, 0.01f), 0.5f, 0.5f, 0.1f));
	gun_mat = CobaltMaterial(new Cobalt::PBRMaterial(pbrt_shader, gun_a, gun_n, gun_r, gun_m, gun_ao));
	rust_mat = CobaltMaterial(new Cobalt::PBRMaterial(pbrt_shader, rust_a, rust_n, rust_r, rust_m, rust_ao));

	Cobalt::Model* gun = new Cobalt::Model("res/Cerberus/Cerberus_LP.fbx", gun_mat);
	gun->Scale(glm::vec3(0.1f));
	gun->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	Cobalt::Model* sphere = Cobalt::Model::CreateSphere(rust_mat);

	model = sphere;

	light = new Cobalt::Light(glm::vec3(10.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	light_int = 500.0f;

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
	//light_int += 50.0f * dt;

	camera->OnUpdate(dt);

	model->GetMaterial()->GetShader()->Bind();
	model->GetMaterial()->GetShader()->SetUniformMat4("camera", camera->GetCameraMatrix());
	model->GetMaterial()->GetShader()->SetUniformFloat3("viewPos", camera->GetPosition());
	model->GetMaterial()->GetShader()->SetUniformFloat3("lightPos", light->GetPosition());
	model->GetMaterial()->GetShader()->SetUniformFloat3("lightCol", light->GetColor());
	model->GetMaterial()->GetShader()->SetUniformFloat("lightInt", light_int);

	model->Draw();
}
