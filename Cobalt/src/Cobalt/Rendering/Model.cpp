#include "cbpch.h"
#include "Model.h"

namespace Cobalt
{
	Model::Model(const std::string& filename, Material* material)
		: m_ModelMat(glm::mat4(1.0f)), m_Material(material), m_Transpose(glm::mat4(1.0f)), 
			m_Rotation(glm::mat4(1.0f)), m_Scale(glm::mat4(1.0)), m_Position(glm::vec3(0.0f))
	{
		LoadModel(filename);
	}

	Model::~Model()
	{
	}

	void Model::Translate(const glm::vec3& move)
	{
		m_Transpose = glm::translate(move) * m_Transpose;
		
		m_Position += move;
	}

	void Model::Rotate(float angle, const glm::vec3& axis)
	{
		m_Rotation = glm::rotate(glm::radians(angle), axis) * m_Rotation;
	}

	void Model::Scale(const glm::vec3& scale)
	{
		m_Scale = glm::scale(scale) * m_Scale;
	}

	void Model::Draw()
	{
		m_ModelMat = m_Transpose * m_Rotation * m_Scale;
		
		m_Material->GetShader()->Bind();
		m_Material->GetShader()->SetUniformMat4("model", m_ModelMat);

		for (Mesh* m : m_Meshes)
		{
			m->Draw(m_Material);
		}
	}

	void Model::LoadModel(const std::string& filename)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | 
													aiProcess_ImproveCacheLocality | aiProcess_SortByPType | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			CB_ERROR("Failed to load model: {0}!", filename);
			return;
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(const aiNode* node, const aiScene* scene)
	{
		//CB_TRACE("{0}", node->mNumMeshes);
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];

			std::vector<float> vertices;
			std::vector<unsigned int> indicies;

			// Load vertex data
			for (unsigned int j = 0; j < ai_mesh->mNumVertices; j++)
			{
				// Positions
				vertices.push_back((float)ai_mesh->mVertices[j].x);
				vertices.push_back((float)ai_mesh->mVertices[j].y);
				vertices.push_back((float)ai_mesh->mVertices[j].z);
				// Normals
				vertices.push_back((float)ai_mesh->mNormals[j].x);
				vertices.push_back((float)ai_mesh->mNormals[j].y);
				vertices.push_back((float)ai_mesh->mNormals[j].z);
				// Texture coordinates
				vertices.push_back((float)ai_mesh->mTextureCoords[0][j].x);
				vertices.push_back((float)ai_mesh->mTextureCoords[0][j].y);
			}

			// Load index data
			for (unsigned int j = 0; j < ai_mesh->mNumFaces; j++)
			{
				aiFace ai_face = ai_mesh->mFaces[j];
				for (unsigned int k = 0; k < ai_face.mNumIndices; k++)
				{
					indicies.push_back(ai_face.mIndices[k]);
				}
			}

			// TODO: Something else here
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);

			m_Meshes.push_back(new Mesh(vertices.data(), vertices.size(), layout, indicies.data(), indicies.size(), m_Material));

			// TODO: Texture stuff

		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

}