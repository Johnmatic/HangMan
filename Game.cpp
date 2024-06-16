#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

#define MAX_STRIKES 10
#define FILENAME "words.txt"

void Game::OnInit()
{
	ifstream inputFile;
	string line;
	inputFile.open(FILENAME, ios::in);
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			m_wordsPool.push_back(line);
		}
		inputFile.close();
	}
	srand(std::time(NULL));
	m_guessedLetters.clear();
	int randomIndex = rand() % m_wordsPool.size();
	m_word = m_wordsPool[randomIndex];
	m_lettersFound = new bool[m_word.length()];
	for (int i = 0; i < m_word.length(); ++i)
	{
		m_lettersFound[i] = false;
	}
	m_strikes = 0;

	OnRender();

	m_gameState = GameState::UPDATE;
}

void Game::OnInput()
{
	char input;
	//Validate input 
	bool inputValid = false;

	cout << "Provide your letter: " << endl;
	// Checking if input is letter, duplicated guesses are counted as valid, but will be strike
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
	bool retValue = false;
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
	else
	{
		bool won = true;
		for (int i = 0; i < m_word.length(); ++i)
		{
			if (m_lettersFound[i] == false)
			{
				won = false;
			}
		}

		if (true == won)
		{
			m_gameState = GameState::FINISH_WON;
			retValue = true;
		}
	}
	
	if (m_strikes > MAX_STRIKES)
	{
		m_gameState = GameState::FINISH_LOST;
		retValue = true;
	}

	return retValue;
}

void Game::OnRender()
{
	system("cls");

	switch (m_gameState)
	{
	case Game::GameState::START:
		cout << "Welcome to HangMan game! Provide your first letter to start guessing the word!" << endl;
		break;
	case Game::GameState::UPDATE:
		cout << "Provide your next letter!" << endl;
		break;
	case Game::GameState::FINISH_LOST:
		cout << "You lost! Your word was: " << m_word << endl;
		break;
	case Game::GameState::FINISH_WON:
		cout << "You won!" << endl;
		break;
	default:
		break;
	}

	//Render hangman
	if (m_strikes >= 3)
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
		if (m_strikes >= 4) cout << "/     ";
		if (m_strikes >= 5) cout << "|";
		cout << endl;

		cout << "|      ";
		if (m_strikes >= 6) cout << "O";
		cout << endl;

		cout << "|     ";
		if (m_strikes >= 8) cout << "/|\\";
		else if (m_strikes >= 7) cout << " | ";
		cout << endl;

		cout << "|      ";
		if (m_strikes >= 9) cout << "M";
		cout << endl;

		cout << "|     ";
		if (m_strikes >= 10) cout << "/ \\";
		cout << endl;

		cout << "|" << endl;

		if(m_strikes >= 2) cout << "|\\" << endl;
		else cout << "|" << endl;
	}
	else
	{
		cout << endl << endl << endl << endl << endl << endl << endl;
	}
	
	cout << "^^^^^^^^^^^^^" << endl; //"grass" always visible
	cout << endl;

	// Render word to be guessed
	int counter = 0;
	for (char c : m_word)
	{
		if (m_lettersFound[counter])
		{
			cout << c;
		}
		else
		{
			cout << '_';
		}
		cout << " ";
		counter++;
	}
	cout << endl;
	cout << endl;

	//Render guessed letters
	cout << "Guess history:" << endl;
	for (char c : m_guessedLetters)
	{
		cout << c << " ";
	}
	cout << endl;
	cout << endl;

}

void Game::OnShutdown()
{
	m_guessedLetters.clear();
	delete[] m_lettersFound;
}
