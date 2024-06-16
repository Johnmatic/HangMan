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
	lastInput = input;
}

bool Game::OnUpdate(float deltaTime)
{
	m_guessedLetters.push_back(lastInput);

	return false;
}

void Game::OnRender()
{

}

void Game::OnShutdown()
{
	m_guessedLetters.clear();

}