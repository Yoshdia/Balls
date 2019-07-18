#pragma once
class Score
{
public:
	struct ScoreTime
	{
		int time;
		int score;
	};
	Score() { scoreTime = { 0,0 }; };
	~Score() {};
	void PlusScore(int point) { scoreTime.time += point; };
	void PlusTime() { scoreTime.score++; };
	ScoreTime GetScore() { return scoreTime; }
private:
	ScoreTime scoreTime;
};

