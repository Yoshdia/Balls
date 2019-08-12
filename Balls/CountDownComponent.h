#pragma once


class CountDownComponent
{
public:
	CountDownComponent(int max);
	~CountDownComponent();

	bool CountEnd();
	void ResetCount();
private:
	int maxCount;
	int nowCount;
	bool updating;
};

