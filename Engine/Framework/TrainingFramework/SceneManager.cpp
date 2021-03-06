#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>

using namespace std;


SceneManager * SceneManager::ms_SceneInstance = NULL;

SceneManager::SceneManager() {}

SceneManager::~SceneManager()
{
	for (int i = 0; i < m_SmObjectCount; i++) {
		
			delete[] m_SmObjectPointer[i].m_ObjectTextID;	
			m_SmObjectPointer->m_ObjectTextID = nullptr;
	}
	delete[] m_SmObjectMeshPointer;
	m_SmObjectMeshPointer = nullptr;
	delete[] m_SmObject2DTexturePointer;
	m_SmObject2DTexturePointer = nullptr;
	delete[] m_SmObjectShaderPointer;
	m_SmObjectShaderPointer = nullptr;
}

void SceneManager::LoadAndAllocateSceneData(const char* scenceManagerDataPath) {
	FILE* sceneFile;
	if (fopen_s(&sceneFile, scenceManagerDataPath, "r") != 0)
	{
		cout << "Failed to open Scene Manager Data file" << endl;
		return;
	}
	/////////
	char linebuffer[100];
	/////////

	fgets(linebuffer, sizeof(linebuffer), sceneFile);
	sscanf_s(linebuffer, "#Objects: %d", &m_SmObjectCount);
	m_SmObjectPointer = new Object[m_SmObjectCount];
	int i = 0;

	while (!feof(sceneFile) && i < m_SmObjectCount) {
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "ID %d", &m_SmObjectPointer[i].m_ObjectID);
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "MODEL %d", &m_SmObjectPointer[i].m_ObjectModelID);
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "TEXTURES %d", &m_SmObjectPointer[i].m_ObjectTextCount);
		m_SmObjectPointer[i].m_ObjectTextID = new int[m_SmObjectPointer[i].m_ObjectTextCount];
			for (int j = 0; j < m_SmObjectPointer[i].m_ObjectTextCount; j++) {
				fgets(linebuffer, sizeof(linebuffer), sceneFile);
				sscanf_s(linebuffer, "TEXTURE %d", &m_SmObjectPointer[i].m_ObjectTextID[j]);
				}
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "CUBETEXTURES %d", &m_SmObjectPointer[i].m_ObjectCubeTextCount);
		m_SmObjectPointer[i].m_ObjectCubeTextID = new int[m_SmObjectPointer[i].m_ObjectCubeTextCount];
			for (int k = 0; k < m_SmObjectPointer[i].m_ObjectCubeTextCount; k++) {
				fgets(linebuffer, sizeof(linebuffer), sceneFile);
				sscanf_s(linebuffer, "CUBETEXTURE %d", &m_SmObjectPointer[i].m_ObjectCubeTextID[k]);
			}
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "SHADER %d", &m_SmObjectPointer[i].m_ObjectShaderID);
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "LIGHTS %d", &m_SmObjectPointer[i].m_ObjectLightCount);
		m_SmObjectPointer[i].m_ObjectLightID = new int[m_SmObjectPointer[i].m_ObjectLightCount];
			for (int l = 0; l < m_SmObjectPointer[i].m_ObjectLightCount; l++) {
				fgets(linebuffer, sizeof(linebuffer), sceneFile);
				sscanf_s(linebuffer, "LIGHT %d", &m_SmObjectPointer[i].m_ObjectLightID[l]);
			}
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "POSITION %f , %f , %f", &m_SmObjectPointer[i].m_ObjectPosition.x, &m_SmObjectPointer[i].m_ObjectPosition.y, &m_SmObjectPointer[i].m_ObjectPosition.z);
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "ROTATION %f , %f , %f", &m_SmObjectPointer[i].m_ObjectRotation.x, &m_SmObjectPointer[i].m_ObjectRotation.y, &m_SmObjectPointer[i].m_ObjectRotation.z);
		fgets(linebuffer, sizeof(linebuffer), sceneFile);
		sscanf_s(linebuffer, "SCALE %f , %f , %f", &m_SmObjectPointer[i].m_ObjectScale.x, &m_SmObjectPointer[i].m_ObjectScale.y, &m_SmObjectPointer[i].m_ObjectScale.z);
		i++;
	}
	i = 0;
	fclose(sceneFile);
}

void SceneManager::SetMeshPointerToRM(Mesh* SmMeshPointer) {
	this->m_SmObjectMeshPointer = SmMeshPointer;	
}

void SceneManager::SetTextPointerToRM(TextureData *SmObject2DTexturePointer, CubeTexture *SmObjectCubeTexturePointer) {
	this->m_SmObject2DTexturePointer = SmObject2DTexturePointer;
	this->m_SmObjectCubeTexturePointer = SmObjectCubeTexturePointer;
}

void SceneManager::SetShaderPointerToRM(Shaders* SmObjectShaderPointer) {
	this->m_SmObjectShaderPointer = SmObjectShaderPointer;
}

void SceneManager::SetLightPointerToRM(LightSource* SmLightPointer) {
	this->m_SmLightSourcePointer = SmLightPointer;
}

void SceneManager::SetUpMeshforObject() {
	for (int i = 0; i < this->m_SmObjectCount; i++)
	{
		m_SmObjectPointer[i].SetUpMesh(m_SmObjectMeshPointer[m_SmObjectPointer[i].m_ObjectModelID]);
	}
}

void SceneManager::SetUpTextureforObject() {
	for (int i = 0; i < this->m_SmObjectCount; i++)
	{
		m_SmObjectPointer[i].SetUpTexture(m_SmObject2DTexturePointer);
		m_SmObjectPointer[i].SetUpCubeTexture(m_SmObjectCubeTexturePointer);
	}
}

void SceneManager::SetUpShaderforObject() {
	for (int i = 0; i < this->m_SmObjectCount; i++)
	{
		m_SmObjectPointer[i].SetUpShader(m_SmObjectShaderPointer);
	}
}
void SceneManager::SetUpLightforObject() {
	for (int i = 0; i < this->m_SmObjectCount; i++) {
		m_SmObjectPointer[i].SetUpLight(m_SmLightSourcePointer);
	}
}

void SceneManager::Draw(Matrix mvp, Vector3 camPos) {
	for (int i = 0; i < this->m_SmObjectCount; i++)
	{		
		m_SmObjectPointer[i].Draw(mvp, m_TimeUniform, camPos);
	}
}

void SceneManager::UpDateTimeUniform(float time) {
	m_TimeUniform += time;
}

float SceneManager::GetTimeUniform(){
	return m_TimeUniform;
}
