#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
const double cameraRotationSpeed = 1.5;
const double cameraMovementSpeed = 2.5;

Camera::Camera(Vector3 worldCamPos, Vector3 worldTargetPos)
{
	cameraPos = worldCamPos;
	targetPos = worldTargetPos;
	upVector = Vector3(0.0, 1.0, 0.0);
	aspectRatio = (float)(Globals::screenWidth / Globals::screenHeight);


	Matrix camTranMat;
	camTranMat.SetTranslation(cameraPos);
	Matrix camRotMat;

	Vector3 zaxis = (cameraPos - targetPos).Normalize();
	Vector3 xaxis = (upVector.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	camRotMat.m[0][0] = xaxis.x; camRotMat.m[0][1] = xaxis.y; camRotMat.m[0][2] = xaxis.z; camRotMat.m[0][3] = 0.0;
	camRotMat.m[1][0] = yaxis.x; camRotMat.m[1][1] = yaxis.y; camRotMat.m[1][2] = yaxis.z; camRotMat.m[1][3] = 0.0;
	camRotMat.m[2][0] = zaxis.x; camRotMat.m[2][1] = zaxis.y; camRotMat.m[2][2] = zaxis.z; camRotMat.m[2][3] = 0.0;
	camRotMat.m[3][0] = 0.0; camRotMat.m[3][1] = 0.0; camRotMat.m[3][2] = 0.0; camRotMat.m[3][3] = 1.0;

	worldMatrix = camTranMat*camRotMat;
}


Camera::~Camera()
{
}

Matrix Camera::CalculateViewMatrix() {
	Matrix inverseCamTranMat;
	/*inverseCamTranMat.m[3][0] = -cameraPos.x;
	inverseCamTranMat.m[3][1] = -cameraPos.y;
	inverseCamTranMat.m[3][2] = -cameraPos.z;*/
	inverseCamTranMat.SetTranslation(-cameraPos);

	Matrix inverseCamRotMat;
	
	Vector3 zaxis = (cameraPos-targetPos).Normalize();
	Vector3 xaxis = (upVector.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	inverseCamRotMat.m[0][0] = xaxis.x; inverseCamRotMat.m[0][1] = yaxis.x; inverseCamRotMat.m[0][2] = zaxis.x; inverseCamRotMat.m[0][3] = 0.0;
	inverseCamRotMat.m[1][0] = xaxis.y; inverseCamRotMat.m[1][1] = yaxis.y; inverseCamRotMat.m[1][2] = zaxis.y; inverseCamRotMat.m[1][3] = 0.0;
	inverseCamRotMat.m[2][0] = xaxis.z; inverseCamRotMat.m[2][1] = yaxis.z; inverseCamRotMat.m[2][2] = zaxis.z; inverseCamRotMat.m[2][3] = 0.0;
	inverseCamRotMat.m[3][0] = 0.0; inverseCamRotMat.m[3][1] = 0.0; inverseCamRotMat.m[3][2] =0.0; inverseCamRotMat.m[3][3] = 1.0;
	
	viewMatrix = inverseCamTranMat * inverseCamRotMat;


	return viewMatrix;
}



void Camera::CalculateWorlMatrixofCam() {

	Matrix camRotationMatrix;
	Vector3 zaxis = (cameraPos - targetPos).Normalize();
	Vector3 xaxis = (upVector.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	camRotationMatrix.m[0][0] = xaxis.x; camRotationMatrix.m[0][1] = xaxis.y; camRotationMatrix.m[0][2] = xaxis.z; camRotationMatrix.m[0][3] = 0.0;
	camRotationMatrix.m[1][0] = yaxis.x; camRotationMatrix.m[1][1] = yaxis.y; camRotationMatrix.m[1][2] = yaxis.z; camRotationMatrix.m[1][3] = 0.0;
	camRotationMatrix.m[2][0] = zaxis.x; camRotationMatrix.m[2][1] = zaxis.y; camRotationMatrix.m[2][2] = zaxis.z; camRotationMatrix.m[2][3] = 0.0;
	camRotationMatrix.m[3][0] = 0.0; camRotationMatrix.m[3][1] = 0.0; camRotationMatrix.m[3][2] = 0.0; camRotationMatrix.m[3][3] = 1.0;
	Matrix camTranslationMatrix;
	camTranslationMatrix.SetTranslation(cameraPos);
	worldMatrix = camRotationMatrix * camTranslationMatrix;
}

void Camera::MoveStraight(float delTime) {
	Vector3 delMove = -(cameraPos - targetPos).Normalize()*delTime*cameraMovementSpeed;
	cameraPos += delMove;
	targetPos += delMove;	
}

void Camera::MoveSideWay(float delTime) {
	Vector3 delMove = (cameraPos-targetPos).Cross(upVector).Normalize()*delTime*cameraMovementSpeed;
	cameraPos += delMove;
	targetPos += delMove;
}

void Camera::RotateAroundY(float delTime) {
	
	Vector4 localTarget = Vector4(0, 0, -(cameraPos - targetPos).Length(), 1.0);
	Matrix rotationaroundY;
	
	Vector4 pivot(0, 1, 0, 0);
	pivot = pivot * viewMatrix;
	rotationaroundY.SetRotationAngleAxis(delTime*cameraRotationSpeed, pivot.x, pivot.y, pivot.z);
	Vector4 localNewTarget = localTarget * rotationaroundY;
		
	
	Vector4 im = (localNewTarget * worldMatrix);
	targetPos.x = im.x;
	targetPos.y = im.y;
	targetPos.z = im.z;	
}

void Camera::RotateAroundX(float delTime) {
	float speed = delTime*2.5;
	Vector4 localTarget = Vector4(0, 0, -(cameraPos - targetPos).Length(), 1.0);
	Matrix rotationaroundX;

	rotationaroundX.SetRotationX(delTime*cameraRotationSpeed);
	Vector4 localNewTarget = localTarget*rotationaroundX;

	Vector4 im = localNewTarget*worldMatrix;
	targetPos.x = im.x;
	targetPos.y = im.y;
	targetPos.z = im.z;
	
}

Vector3 Camera::GetPos() {
	return cameraPos;
}

Vector3 Camera::GetTargetPos() {
	return targetPos;
}
