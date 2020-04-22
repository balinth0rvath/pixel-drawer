#include "src/pixel_gl_program_manager.h"

PixelGLProgramManager::PixelGLProgramManager()
{
	initShaders();
}

const GLuint PixelGLProgramManager::loadShader(const GLenum& type, const std::string& source)
{
	GLuint shader = 0;

	shader = glCreateShader(type);
	if (!shader)
		return 0;

	const char* c = source.c_str();
	glShaderSource(shader, 1, &c, NULL);
	glCompileShader(shader);
	int compiled=0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		int len=0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if (len)
		{
			char info[1000];
			glGetShaderInfoLog(shader, 1000, NULL, info);
			std::cout << "Error compiling shader: " << info << std::endl;
		}
		glDeleteShader(shader);
		return 0;
	}		
	return shader;
}
	
void PixelGLProgramManager::initShaders()
{
	this->vertexShaderSource = 
		   "#version 300 es													\n\
			layout (location = 0) in vec3 vPos;								\n\
			layout (location = 1) in vec4 vColor;							\n\
			out vec4 interpColor;											\n\
			uniform mat4 model;												\n\
			void main()														\n\
			{																\n\
				gl_Position = model * vec4(vPos.x, vPos.y, vPos.z, 1.0);    \n\
			 	interpColor = vColor;										\n\
			}";

	this->fragmentShaderSource = 
			"#version 300 es							\n\
			precision mediump float;					\n\
			in vec4 interpColor;						\n\
			out vec4 fragColor;							\n\
			void main()								 	\n\
			{											\n\
				fragColor = interpColor;				\n\
			}";
}

const int PixelGLProgramManager::init()
{
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, this->vertexShaderSource);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, this->fragmentShaderSource);

	this->programObject = glCreateProgram();

	if (!programObject)
		return 0;

	glAttachShader(this->programObject, vertexShader);
	glAttachShader(this->programObject, fragmentShader);

	glLinkProgram(this->programObject);

	int linked = 0;
	glGetProgramiv(this->programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		int len = 0;
		glGetProgramiv(this->programObject, GL_INFO_LOG_LENGTH, &len);
		if (len)
		{	
			char info[1000]; 
			glGetProgramInfoLog(this->programObject, 1000, NULL, info); 	
			std::cout << "Error linking program: " << info << std::endl;
		
		}
		glDeleteProgram(this->programObject);
		return 0;
	}
	this->uniformModel = glGetUniformLocation(this->programObject, "model");
	this->uniformProjection = glGetUniformLocation(this->programObject, "projection");
	std::cout << "Program created successfuly" << std::endl;
	return 1;
}


