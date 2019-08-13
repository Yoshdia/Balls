#pragma once
class Score
{
public:
	Score() { ClearScore(); };
	~Score() {};

	void AddScore() { score++; }
	void AddScore(int point) { score += point; }
	const int& GetScore() { return score; }
	void ClearScore() { score = 0; }
	static const int PlusWallScore;
	static const int PlusBreakScore;
	static const int PlusAvoidScore;
private:
	int score;
};

