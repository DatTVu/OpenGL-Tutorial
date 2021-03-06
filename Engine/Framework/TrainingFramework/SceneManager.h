#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "CubeTexture.h"
#include "LightSource.h"

class SceneManager
{
private:
	////////////////////
	Object *m_SmObjectPointer;	
	Mesh *m_SmObjectMeshPointer;	
	TextureData *m_SmObject2DTexturePointer;
	CubeTexture *m_SmObjectCubeTexturePointer;
	Shaders* m_SmObjectShaderPointer;	
	LightSource *m_SmLightSourcePointer;
	int m_SmObjectCount;
	float m_TimeUniform=0.0f;
	////////////////////	
protected:	
	SceneManager();
	~SceneManager();
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	SceneManager(const SceneManager &) {}
	SceneManager& operator =(const SceneManager &) {}

public:
	static void CreateInstance()
	{
		if (ms_SceneInstance == NULL)
			ms_SceneInstance = new SceneManager;
	}
	static SceneManager * GetInstance()
	{
		return ms_SceneInstance;
	}
	static void DestroyInstance()
	{
		if (ms_SceneInstance)
		{
			delete ms_SceneInstance;
			ms_SceneInstance = NULL;
		}
	}

	void LoadAndAllocateSceneData(const char* scenceManagerDataPath);
	void SetMeshPointerToRM(Mesh* SmMeshPointer);
	void SetTextPointerToRM(TextureData *SmObject2DTexturePointer, CubeTexture *SmObjectCubeTexturePointer);	
	void SetShaderPointerToRM(Shaders* SmObjectShaderPointer);
	void SetLightPointerToRM(LightSource* SmLightPointer);
	void SetUpMeshforObject();	
	void SetUpTextureforObject();
	void SetUpShaderforObject();
	void SetUpLightforObject();
	void Draw(Matrix mvp, Vector3 camPos);
	void UpDateTimeUniform(float dtime);
	float GetTimeUniform();

protected:
	static SceneManager * ms_SceneInstance;
};
