#pragma once


class Camera
{
public:
	Camera(VECTOR cameraPos);
	~Camera();

	void Update();
	void ChangeRotate(float rotate);
private:
	void SetCameraPosition();
	bool HeadForTargetRotate();
	static const float addRotate;
	//�J�����̎���͈�
	static const float nearCameraPos;
	static const float farCameraPos;
	VECTOR position;
	float rotate;

	float targetRotate;
	bool plusAddRotate;
};

