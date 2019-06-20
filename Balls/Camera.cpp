#include "DxLib.h"
#include "Camera.h"



Camera::Camera()
{
	SetCameraNearFar(nearCameraPos,farCameraPos);
}


Camera::~Camera()
{
}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -100), VGet(0, 0, 0));
}
