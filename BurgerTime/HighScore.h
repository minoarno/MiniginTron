#pragma once
class HighScore final
{
public:
	HighScore(const std::string& filepath);
	HighScore(const HighScore&) = delete;
	HighScore& operator=(const HighScore&) = delete;
	HighScore(HighScore&&) = delete;
	HighScore& operator=(HighScore&&) = delete;
	~HighScore() = default;

	void AddScore(int score);

	void WriteHighScoreListToFile();
private:
	std::vector<int> m_HighScores;
	std::string m_Filepath;
};