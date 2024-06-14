#include "Game.h"
#include <cstdlib>
#include <ctime>

void Game::OnInit()
{
	m_guessedLetters.clear();
	srand(std::time(NULL));
	int randomIndex = rand() % m_wordsPool.size();
	m_word = m_wordsPool[randomIndex];
}

void Game::OnInput()
{

}

bool Game::OnUpdate(float deltaTime)
{




	return false;
}

void Game::OnRender()
{

}

void Game::OnShutdown()
{
	m_guessedLetters.clear();

}