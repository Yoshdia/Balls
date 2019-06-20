#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void Update();
private:
	const float nearCameraPos = 0;
	const float farCameraPos = 1000.0f;

	const VECTOR CameraPos=VGet(0,0,0);
};

