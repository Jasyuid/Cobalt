#include "cbpch.h"
#include "Model.h"

namespace Cobalt
{
	Model::Model(const std::string& filename, std::shared_ptr<Material> material, const bool gen_tangents)
		: m_ModelMat(glm::mat4(1.0f)), m_Material(material), m_Transpose(glm::mat4(1.0f)), 
			m_Rotation(glm::mat4(1.0f)), m_Scale(glm::mat4(1.0)), m_Position(glm::vec3(0.0f))
	{
		// Use assimp to load model vertices from file
		LoadModel(filename, gen_tangents);
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

	void Model::LoadModel(const std::string& filename, const bool gen_tangents)
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
		ProcessNode(scene->mRootNode, scene, gen_tangents);
	}

	void Model::ProcessNode(const aiNode* node, const aiScene* scene, const bool gen_tangents)
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
				if (gen_tangents)
				{
					// Tangent vertices
					vertices.push_back((float)ai_mesh->mTangents[i].x);
					vertices.push_back((float)ai_mesh->mTangents[i].y);
					vertices.push_back((float)ai_mesh->mTangents[i].z);
					// Bitangent vertices
					vertices.push_back((float)ai_mesh->mBitangents[i].x);
					vertices.push_back((float)ai_mesh->mBitangents[i].y);
					vertices.push_back((float)ai_mesh->mBitangents[i].z);
				}
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
			// Set vertex layout
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			if (gen_tangents)
			{
				layout.Push<float>(3);
				layout.Push<float>(3);
			}

			// TODO: Make these smart pointers
			// Push mesh to mesh stack
			m_Meshes.push_back(new Mesh(vertices.data(), vertices.size(), layout, indicies.data(), indicies.size(), m_Material));
		}

		// Process child nodes if they exist
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, gen_tangents);
		}
	}

	Model* Model::CreateSphere(std::shared_ptr<Material> material, unsigned int segments, const bool gen_tangents)
	{
		// Store vertex and index data
		std::vector<float> vertices;
		std::vector<unsigned int> indicies;

		std::vector<glm::vec3> vertex_data;
		std::vector<glm::vec3> normal_data;
		std::vector<glm::vec2> tc_data;

		std::vector<std::vector<glm::vec3>> tangents;
		std::vector<std::vector<glm::vec3>> bitangents;

		// Create a grid of vertices
		for (unsigned int y = 0; y < segments; ++y)
		{
			for (unsigned int x = 0; x < segments; ++x)
			{
				// Calculate segment for texture mapping
				float x_segment = (float)x / (float)(segments-1);
				float y_segment = (float)y / (float)(segments-1);
				// Calculate location on unit sphere
				float x_pos = glm::cos(x_segment * 2.0f*glm::pi<float>()) * glm::sin(y_segment * glm::pi<float>());
				float y_pos = glm::cos(y_segment * glm::pi<float>());
				float z_pos = glm::sin(x_segment * 2.0f*glm::pi<float>()) * glm::sin(y_segment * glm::pi<float>());
				
				// Position
				vertex_data.push_back(glm::vec3(x_pos, y_pos, z_pos));
				// Normal
				normal_data.push_back(glm::vec3(x_pos, y_pos, z_pos));
				// Texture Coordinate
				tc_data.push_back(glm::vec2(x_segment, y_segment));

				std::vector<glm::vec3> v;
				tangents.push_back(v);
				bitangents.push_back(v);
			}
		}		

		for(unsigned int y = 0; y < segments - 1; ++y)
		{
			for (unsigned int x = 0; x < segments; ++x)
			{
				unsigned int v1 = y * (segments) + x;
				unsigned int v2 = y * (segments) + ((x + 1) % segments);
				unsigned int v3 = (y + 1) * (segments) + x;
				unsigned int v4 = (y + 1) * (segments)+((x + 1) % segments);

				indicies.push_back(v1);
				indicies.push_back(v2);
				indicies.push_back(v3);

				indicies.push_back(v2);
				indicies.push_back(v4);
				indicies.push_back(v3);


				glm::vec3 pos1 = vertex_data[v1];
				glm::vec3 pos2 = vertex_data[v2];
				glm::vec3 pos3 = vertex_data[v3];
				glm::vec2 uv1 = tc_data[v1];
				glm::vec2 uv2 = tc_data[v2];
				glm::vec2 uv3 = tc_data[v3];

				glm::vec3 edge1 = pos2 - pos1;
				glm::vec3 edge2 = pos3 - pos1;
				glm::vec2 deltaUV1 = uv2 - uv1;
				glm::vec2 deltaUV2 = uv3 - uv1;

				glm::vec3 tangent, bitangent;
				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
				tangent = f * (deltaUV2.y * edge1 - deltaUV1.y * edge2);

				bitangent = f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2);

				tangents.at(v1).push_back(tangent);
				tangents.at(v2).push_back(tangent);
				tangents.at(v3).push_back(tangent);
				tangents.at(v4).push_back(tangent);
				bitangents.at(v1).push_back(bitangent);
				bitangents.at(v2).push_back(bitangent);
				bitangents.at(v3).push_back(bitangent);
				bitangents.at(v4).push_back(bitangent);
			}
		}

		for (int i = 0; i < vertex_data.size(); ++i)
		{
			vertices.push_back(vertex_data[i].x);
			vertices.push_back(vertex_data[i].y);
			vertices.push_back(vertex_data[i].z);

			vertices.push_back(normal_data[i].x);
			vertices.push_back(normal_data[i].y);
			vertices.push_back(normal_data[i].z);

			vertices.push_back(tc_data[i].x);
			vertices.push_back(tc_data[i].y);

			glm::vec3 tangent, bitangent;
			for (int j = 0; j < tangents.at(i).size(); ++j)
			{
				tangent += tangents.at(i).at(j);
				bitangent += bitangents.at(i).at(j);
			}

			tangent = tangent / (float)tangents.at(i).size();
			bitangent = bitangent / (float)bitangents.at(i).size();

			vertices.push_back(tangent.x);
			vertices.push_back(tangent.y);
			vertices.push_back(tangent.z);

			vertices.push_back(bitangent.x);
			vertices.push_back(bitangent.y);
			vertices.push_back(bitangent.z);
		}

		// TODO: Something else here
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);
		layout.Push<float>(3);

		// TODO: Make these a smart pointers
		return new Model(new Mesh(vertices.data(), vertices.size(), layout, indicies.data(), indicies.size(), material), material);
	}

}