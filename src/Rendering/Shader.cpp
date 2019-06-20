#include "Shader.h"
#include <fstream>
#include <sstream>

using namespace Shaders;

//static struct declarations
//GLSLShaderManager::VertexShaderGLSL   NULL_VERT_SHADER;
//GLSLShaderManager::FragmentShaderGLSL NULL_FRAG_SHADER;

void GLSLShaderManager::FragmentShaderGLSL::loadShader(const std::string& filePath, const std::string& optionalShaderName)
{
	// Create the shaders
	ID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(filePath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", filePath.c_str());
		getchar();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(filePath, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	path = filePath;
	if (optionalShaderName == "") name = filePath;
	else name = optionalShaderName;
	code = FragmentShaderCode;
	isLoaded = true;

}

void GLSLShaderManager::FragmentShaderGLSL::compileShader()
{
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", this->name);
	char const* FragmentSourcePointer = code.c_str();
	glShaderSource(ID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(ID);

	// Check Fragment Shader
	glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	this->isCompiled = true;
}

void GLSLShaderManager::VertexShaderGLSL::loadShader(const std::string& filePath, const std::string& optionalShaderName)
{
	// Create the shaders
	ID = glCreateShader(GL_VERTEX_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(filePath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", filePath.c_str());
		getchar();
	}

	path = filePath;
	if (optionalShaderName == "") name = filePath;
	else name = optionalShaderName;
	code = VertexShaderCode;
	isLoaded = true;
}
void GLSLShaderManager::VertexShaderGLSL::compileShader()
{
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", name);
	char const* VertexSourcePointer = code.c_str();
	glShaderSource(ID, 1, &VertexSourcePointer, NULL);
	glCompileShader(ID);

	// Check Vertex Shader
	glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	isCompiled = true;
}

//shader manager code
const GLSLShaderManager::VertexShaderGLSL& GLSLShaderManager::getVertexShaderByName(const std::string& name)
{
	return GLSLShaderManager::NULL_VERT_SHADER;
}
const GLSLShaderManager::FragmentShaderGLSL& GLSLShaderManager::getFragmentShaderByName(const std::string& name)
{
	return GLSLShaderManager::NULL_FRAG_SHADER;
}
bool GLSLShaderManager::addVertexShader(const std::string& filePath, const std::string& optionalShaderName)
{
	return true;
}
bool GLSLShaderManager::addFragmentShader(const std::string& filePath, const std::string& optionalShaderName)
{
	return true;
}
bool GLSLShaderManager::compileShader(const std::string& shaderName, SHADER_TYPE)
{
	return true;
}

GLuint GLSLShaderManager::createProgram(const std::string& programName, const std::string& vertShaderName, const std::string& fragShaderName)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, this->getVertexShaderByName(vertShaderName).ID);
	glAttachShader(ProgramID, this->getFragmentShaderByName(fragShaderName).ID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, this->getVertexShaderByName(vertShaderName).ID);
	glDetachShader(ProgramID, this->getFragmentShaderByName(fragShaderName).ID);

	glDeleteShader(this->getVertexShaderByName(vertShaderName).ID);
	glDeleteShader(this->getFragmentShaderByName(fragShaderName).ID);

	return ProgramID;
}