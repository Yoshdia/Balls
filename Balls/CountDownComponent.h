#pragma once


class CountDownComponent
{
public:
	CountDownComponent(float max);
	~CountDownComponent();

	bool CountEnd();
	void ResetCount();
	void ResetCount(float resetCount);
private:
	float maxCount;
	float nowCount;
	bool updating;
};

