#pragma once


class CountDownComponent
{
public:
	CountDownComponent(int max);
	~CountDownComponent();

	bool CountEnd();
	void ResetCount() { nowCount = maxCount; }
private:
	int maxCount;
	int nowCount;
};

