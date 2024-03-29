#include"DxLib.h"
#include "Camera.h"
#include "InputKey.h"

const float Camera::nearCameraPos = 1;
const float Camera::farCameraPos = 1000;
const float Camera::addRotate = 0.001f;

Camera::Camera(VECTOR cameraPos) :
	position(cameraPos),
	rotate(0),
	targetRotate(0),
	plusAddRotate(false)
{
	//カメラの視野範囲を設定
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//カメラの場所を設定
	//SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
	SetCameraPosition();
	//SetCameraPositionAndAngle(cameraPos, 0.3, 0, 0.1);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_Z] > 0)
	{
		ChangeRotate(-0.1f);
	}
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_X] > 0)
	{
		ChangeRotate(0.0f);
	}
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_C] > 0)
	{
		ChangeRotate(0.1f);
	}
	bool noChangedRotate = HeadForTargetRotate();
	if (!noChangedRotate)
	{
		SetCameraPosition();
	}
}

void Camera::ChangeRotate(float rotate)
{
	targetRotate = rotate;
	plusAddRotate = this->rotate < targetRotate ? true : false;
}

void Camera::SetCameraPosition()
{
	SetCameraPositionAndAngle(position, 0.3f, 0, rotate);
}

#include"main.h"

bool Camera::HeadForTargetRotate()
{
	if (int(rotate * 100)  == int(targetRotate * 100))
	{
		rotate = targetRotate;
		return true;
	}

	if (plusAddRotate)
	{
		rotate += addRotate;
	}
	else
	{
		rotate -= addRotate;
	}


	return false;
}
