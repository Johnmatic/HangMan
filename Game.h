#pragma once
#include <string>
#include <vector>


class Game
{
	enum class GameState
	{
		START,
		UPDATE,
		FINISH
	};

public:
	void OnInit();
	void OnInput();
	bool OnUpdate(float deltaTime);
	void OnRender();
	void OnShutdown();

private:
	std::string m_word;
	std::vector<std::string> m_wordsPool = { "kolor", "silnik", "wzorzec", "silnie", "kanapka" };
	std::vector<bool> m_guessedLetters;
	GameState m_gameState = GameState::START;
	char m_lastInput;
	bool* m_lettersFound;
	int m_strikes;
};