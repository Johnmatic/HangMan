#pragma once
#include <string>
#include <vector>


class Game
{
	enum class GameState
	{
		START,
		UPDATE,
		FINISH_LOST,
		FINISH_WON
	};

public:
	void OnInit();
	void OnInput();
	bool OnUpdate(float deltaTime);
	void OnRender();
	void OnShutdown();

private:
	std::string m_word;
	std::vector<std::string> m_wordsPool;
	std::vector<char> m_guessedLetters;
	GameState m_gameState = GameState::START;
	char m_lastInput;
	bool* m_lettersFound;
	int m_strikes;
};