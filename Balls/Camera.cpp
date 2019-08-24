#include"DxLib.h"
#include "Camera.h"
#include "InputKey.h"

const float Camera::nearCameraPos = 1;
const float Camera::farCameraPos = 1000;
const float Camera::addRotate = 0.01f;

Camera::Camera(VECTOR cameraPos) :
	position(cameraPos),
	rotate(0),
	targetRotate(0),
	plusAddRotate(false)
{
	//ƒJƒƒ‰‚ÌŽ‹–ì”ÍˆÍ‚ðÝ’è
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//ƒJƒƒ‰‚ÌêŠ‚ðÝ’è
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
		ChangeRotate(-0.1);
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
	SetCameraPositionAndAngle(position, 0.3, 0, rotate);
}

#include"main.h"

bool Camera::HeadForTargetRotate()
{
	if (int(rotate * 10)  == int(targetRotate * 10))
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
