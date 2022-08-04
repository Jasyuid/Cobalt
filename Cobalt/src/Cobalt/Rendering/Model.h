#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Cobalt
{
	class Model
	{
	public:
		Model(const std::string& filename, std::shared_ptr<Material> material);
		Model(Mesh* m, std::shared_ptr<Material> material);
		~Model();

		// Model matrix transformation functions
		void Translate(const glm::vec3& move);
		void Rotate(float angle, const glm::vec3& axis);
		void Scale(const glm::vec3& scale);

		// Draw Model
		void Draw();

		inline const std::shared_ptr<Material> GetMaterial() const { return m_Material; };
		inline void SetMaterial(std::shared_ptr<Material> mat) { m_Material = mat; }

		// Return a model of a sphere
		static Model* CreateSphere(std::shared_ptr<Material> material, unsigned int segments = 64);

	private:
		void LoadModel(const std::string& filename);
		void ProcessNode(const aiNode* node, const aiScene* scene);

	private:
		std::vector<Mesh*> m_Meshes; // List of meshes in model
		std::shared_ptr<Material> m_Material; // Material for model

		// Model and transformation matrices
		glm::mat4 m_ModelMat;
		glm::mat4 m_Transpose;
		glm::mat4 m_Scale;
		glm::mat4 m_Rotation;

		glm::vec3 m_Position; // Position of model origin

	};
}