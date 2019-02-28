#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint normalAttribute;
	GLint binormalAttribute;
	GLint tangentAttribute;
	GLint textureAttribute;
	GLuint translationUniform;
	int m_RmShaderID;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	Shaders();	
	~Shaders();
};