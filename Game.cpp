#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <conio.h>

using namespace std;

void Game::OnInit()
{
	m_guessedLetters.clear();
	srand(std::time(NULL));
	int randomIndex = rand() % m_wordsPool.size();
	m_word = m_wordsPool[randomIndex];
	m_lettersFound = new bool[m_word.length()];
	m_strikes = 0;
}

void Game::OnInput()
{
	char input;
	//Validate input 
	bool inputValid = false;
	while (!inputValid)
	{
		input = _getch();
		if (input >= 'a' && input <= 'z')
		{
			inputValid = true;
		}
		else if (input >= 'A' && input <= 'Z')
		{
			input += ('a' - 'A'); //to lowercase
			inputValid = true;
		}
		else
		{
			cout << input << " Input not valid!" << endl;
		}
	}
	m_lastInput = input;
}

bool Game::OnUpdate(float deltaTime)
{
	bool foundAny = false;
	int counter = 0;
	m_guessedLetters.push_back(m_lastInput);
	for (char c : m_word)
	{
		if ((c == m_lastInput) && (m_lettersFound[counter] == false))
		{
			foundAny = true;
			m_lettersFound[counter] = true;
		}
		counter++;
	}

	if (!foundAny)
	{
		m_strikes++;
	}

	return false;
}

void Game::OnRender()
{

}

void Game::OnShutdown()
{
	m_guessedLetters.clear();

}