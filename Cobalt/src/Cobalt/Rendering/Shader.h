#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Stores raw shaders
struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath); // TODO: Allow differant files for each shader type
	~Shader();

	// Bind functions
	void Bind() const;
	void Unbind() const;

	// Set shader uniforms
	void SetUniformInt(const std::string& name, const int& val);
	void SetUniformFloat(const std::string& name, const float& val);
	void SetUniformFloat3(const std::string& name, const glm::vec3& vec);
	void SetUniformFloat4(const std::string& name, const glm::vec4& vec);
	void SetUniformMat4(const std::string& name, const glm::mat4& mat);

private:
	// Create shaders from source files
	ShaderSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	// Get the location of a uniform in a shader
	int GetUniformLocation(const std::string& name);

private:
	unsigned int m_RendererID; // Shader ID
	std::string m_FilePath; // File path for debugging purposes

	std::unordered_map<std::string, int> m_UniformLocations; // Store uniform locations previously looked up
};