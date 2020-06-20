#include "ShaderLoader.h"
#include <fstream>
#include <vector>

std::string ShaderLoader::readShader(const char* filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in); //todo find out what does ios::in
	if (!file.good()) // todo find what is file.good() 
	{
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg()); // todo find out what is file.tellg()
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	printf("returning shaderCode");
	return shaderCode;
}

GLuint ShaderLoader::createShader(GLenum shaderType, std::string source, const char* shaderName)
{
	int compile_result = 0;
	GLuint shader = glCreateShader(shaderType);
	const char* shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{
		int info_log_lenght = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_lenght);

		std::vector<char> shader_log(info_log_lenght);
		glGetShaderInfoLog(shader, info_log_lenght, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	printf("retruning Shader");
	return shader;
}

GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	// loads vertex shader and fragment shader code
	std::string vertex_shader_code = readShader(vertexShaderFilename);

	std::string fragment_shader_code = readShader(fragmentShaderFilename);

	// create shaders:
	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");

	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	// linking the shader:
	int link_result = 0;
	
	// create the program handel, attach the shader and links it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	// check for link errors
	if (link_result == GL_FALSE)
	{
		int info_log_lengh = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_lengh);
		std::vector<char>program_log(info_log_lengh);
		
		glGetProgramInfoLog(program, info_log_lengh, NULL, &program_log[0]); //index 0 to start writing log

		std::cout << "Shader Loader:: link ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	printf("returning program");
	return program;
}
