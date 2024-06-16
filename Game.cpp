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
	for (int i = 0; i < m_word.length(); ++i)
	{
		m_lettersFound[i] = false;
	}
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
	system("cls");
	//Render hangman
	if (m_strikes >= 2)
	{
		cout << "________" << endl;
	}
	else
	{
		cout << "        " << endl;
	}

	if (m_strikes >= 1)
	{
		cout << "|";
		if (m_strikes >= 2) cout << "/     ";
		if (m_strikes >= 3) cout << "|";
		cout << endl;

		cout << "|      ";
		if (m_strikes >= 4) cout << "O";
		cout << endl;

		cout << "|     ";
		if (m_strikes >= 5) cout << "/|\\";
		cout << endl;

		cout << "|      ";
		if (m_strikes >= 6) cout << "M";
		cout << endl;

		cout << "|     ";
		if (m_strikes >= 7) cout << "/ \\";
		cout << endl;

		cout << "|" << endl;

		cout << "|\\" << endl;
	}
	
	cout << "^^^^^^^^^^^^^" << endl; //"grass" always visible

	// Render word to be guessed
	int counter = 0;
	for (char c : m_word)
	{
		cout << " ";
		if (m_lettersFound[counter])
		{
			cout << c;
		}
		else
		{
			cout << '_';
		}
		cout << " ";
	}
	cout << endl;

	//Render guessed letters
	for (char c : m_guessedLetters)
	{
		cout << c << " ";
	}
	cout << endl;

}

void Game::OnShutdown()
{
	m_guessedLetters.clear();

}