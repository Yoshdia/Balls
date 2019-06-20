#include "DxLib.h"
#include "Camera.h"



Camera::Camera()
{
	SetCameraNearFar(nearCameraPos,farCameraPos);
	SetLightPosition(CameraPos);
	SetLightDirection(VGet(0,0,1));
}


Camera::~Camera()
{
}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
}
