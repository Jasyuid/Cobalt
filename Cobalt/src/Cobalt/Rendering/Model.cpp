#include "cbpch.h"
#include "Model.h"

namespace Cobalt
{
	Model::Model(const std::string& filename, std::shared_ptr<Material> material)
		: m_ModelMat(glm::mat4(1.0f)), m_Material(material), m_Transpose(glm::mat4(1.0f)), 
			m_Rotation(glm::mat4(1.0f)), m_Scale(glm::mat4(1.0)), m_Position(glm::vec3(0.0f))
	{
		// Use assimp to load model vertices from file
		LoadModel(filename);
	}

	Model::Model(Mesh* m, std::shared_ptr<Material> material)
		: m_ModelMat(glm::mat4(1.0f)), m_Material(material), m_Transpose(glm::mat4(1.0f)),
		m_Rotation(glm::mat4(1.0f)), m_Scale(glm::mat4(1.0)), m_Position(glm::vec3(0.0f))
	{
		// 
		m_Meshes.push_back(m);
	}

	Model::~Model()
	{
	}

	void Model::Translate(const glm::vec3& move)
	{
		m_Transpose = glm::translate(move) * m_Transpose;
		// Update position
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
		// Calculate model matrix
		m_ModelMat = m_Transpose * m_Rotation * m_Scale;
		
		// Send model matrix to material shader
		m_Material->GetShader()->Bind();
		m_Material->GetShader()->SetUniformMat4("model", m_ModelMat);

		// Draw each mesh object
		for (Mesh* m : m_Meshes)
		{
			m->Draw(m_Material);
		}
	}

	void Model::LoadModel(const std::string& filename)
	{
		// Import model using assimp
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | 
													aiProcess_ImproveCacheLocality | aiProcess_SortByPType | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			CB_ERROR("Failed to load model: {0}!", filename);
			return;
		}

		// Process each mesh node from assimp
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(const aiNode* node, const aiScene* scene)
	{
		// Loop through each mesh at current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// Get mesh
			aiMesh* ai_mesh = scene->mMeshes[node->mMeshes[i]];

			// Used to store vertex and index data
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
				// Loop through faces and get indicies from each one
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

			// TODO: Make these smart pointers
			// Push mesh to mesh stack
			m_Meshes.push_back(new Mesh(vertices.data(), vertices.size(), layout, indicies.data(), indicies.size(), m_Material));
		}

		// Process child nodes if they exist
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Model* Model::CreateSphere(std::shared_ptr<Material> material, unsigned int segments)
	{
		// Store vertex and index data
		std::vector<float> vertices;
		std::vector<unsigned int> indicies;

		for (unsigned int y = 0; y < segments; ++y)
		{
			for (unsigned int x = 0; x < segments; ++x)
			{
				float x_segment = (float)x / (float)(segments-1);
				float y_segment = (float)y / (float)(segments-1);
				float x_pos = glm::cos(x_segment * 2.0f*glm::pi<float>()) * glm::sin(y_segment * glm::pi<float>());
				float y_pos = glm::cos(y_segment * glm::pi<float>());
				float z_pos = glm::sin(x_segment * 2.0f*glm::pi<float>()) * glm::sin(y_segment * glm::pi<float>());
				
				// Position
				vertices.push_back(x_pos);
				vertices.push_back(y_pos);
				vertices.push_back(z_pos);
				// Normal
				vertices.push_back(x_pos);
				vertices.push_back(y_pos);
				vertices.push_back(z_pos);
				// Texture Coordinate
				vertices.push_back(x_segment);
				vertices.push_back(y_segment);

				if (y == 0 || y == segments - 1)
					break;
			}
		}

		for(unsigned int y = 0; y < segments - 1; ++y)
		{
			if (y == 0)
			{
				for (unsigned int x = 0; x < segments; ++x)
				{
					indicies.push_back(y * (segments));
					indicies.push_back((y + 1) * (segments)+((x + 1) % segments));
					indicies.push_back((y + 1) * (segments)+x);
				}
			}
			else if (y == segments - 2)
			{
				for (unsigned int x = 0; x < segments; ++x)
				{
					indicies.push_back(y * (segments)+x - (segments-1));
					indicies.push_back(y * (segments)+((x + 1) % segments) - (segments - 1));
					indicies.push_back((y + 1) * (segments)-(segments - 1));

				}
			}
			else
			{
				for (unsigned int x = 0; x < segments; ++x)
				{
					indicies.push_back(y * (segments) + x - (segments - 1));
					indicies.push_back(y * (segments) + ((x + 1) % segments) - (segments - 1));
					indicies.push_back((y + 1) * (segments) + x - (segments - 1));

					indicies.push_back(y * (segments) + ((x + 1) % segments) - (segments - 1));
					indicies.push_back((y + 1) * (segments) + ((x + 1) % segments) - (segments - 1));
					indicies.push_back((y + 1) * (segments) + x - (segments - 1));
				}
			}
		}

		// TODO: Something else here
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		// TODO: Make these a smart pointers
		return new Model(new Mesh(vertices.data(), vertices.size(), layout, indicies.data(), indicies.size(), material), material);
	}

}