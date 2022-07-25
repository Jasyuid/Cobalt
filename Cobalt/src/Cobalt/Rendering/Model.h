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
		Model(const std::string& filename);
		~Model();

		void Translate(const glm::vec3& move);
		void Rotate(float angle, const glm::vec3& axis);
		void Scale(const glm::vec3& scale);

		void Draw(Shader* shader);

	private:
		void LoadModel(const std::string& filename);
		void ProcessNode(const aiNode* node, const aiScene* scene);
		Texture* LoadTexture(aiMaterial* mat, aiTextureType type);

	private:
		std::vector<Mesh*> m_Meshes;

		std::string m_Directory;
		std::unordered_map<std::string, Texture*> m_LoadedTextures;
		TextureMap m_Tmap;

		glm::mat4 m_ModelMat;
		glm::mat4 m_Transpose;
		glm::mat4 m_Scale;
		glm::mat4 m_Rotation;

		glm::vec3 m_Position;

	};
}