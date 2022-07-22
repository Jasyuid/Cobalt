#include "cbpch.h"
#include "Shader.h"

#include "OpenGL.h"

Shader::Shader(const std::string& filepath)
	: m_RendererID(0), m_FilePath(filepath)
{
	// Load and parse shader source file
	ShaderSource source = ParseShader(filepath);
	// Create shader from shader source
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderSource Shader::ParseShader(const std::string& filepath)
{
	// Open file stream
	std::ifstream stream(filepath);

	// Shader types
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	// Go through each line of shader file
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		// Check if the shader type has changed
		if (line.find("#SHADER") != std::string::npos)
		{
			if (line.find("VERTEX") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("FRAGMENT") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			// Print line to current shader type
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Compile shaders
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Attach shader to program
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	// Delete the shaders now that the program is done
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	// Create shader
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	// Compile error checking
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		// Print errors
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char)); // Allocate char array on stack
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		CB_CORE_ERROR("Failed to compile {0} shader!", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		CB_CORE_ERROR(message);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

// Bind functions
void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

// Shader uniform helper functions
void Shader::SetUniformInt(const std::string& name, const int& val)
{
	GLCall(glUniform1i(GetUniformLocation(name), val));
}
void Shader::SetUniformFloat(const std::string& name, const float& val)
{
	GLCall(glUniform1f(GetUniformLocation(name), val));
}
void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& vec)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec)));
}
void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& vec)
{
	GLCall(glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vec)));
}
void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

// Gets and stores shader uniform locations
int Shader::GetUniformLocation(const std::string& name)
{
	// Check if location was already found
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];

	// Find and store the location of the uniform
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		CB_CORE_WARN("Uniform '{0}' does not exist!", name);

	m_UniformLocations[name] = location;
	return location;
}