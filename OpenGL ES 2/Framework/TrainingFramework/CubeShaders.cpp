#include "stdafx.h"
#include "CubeShaders.h"

int CubeShaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	iPosVertexLoc = glGetAttribLocation(program, "a_CubeVertexPos");
	iTransUniformLoc = glGetUniformLocation(program, "u_CubeMVPMatrix");
	return 0;
}

CubeShaders::~CubeShaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
