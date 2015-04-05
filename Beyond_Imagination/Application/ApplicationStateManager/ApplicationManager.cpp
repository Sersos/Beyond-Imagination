#include "ApplicationManager.h"
#include "ApplicationState.h"
#include "SinglePlayerGame.h"

ApplicationManager::ApplicationManager()
{
	//basic initialization
	m_window = 0;
	m_activeState = 0;	

	//initialize directxmanager
	m_directxManager = new DirectxManager();

	//game states
	m_singlePlayerGame = new SinglePlayerGame();
}

void ApplicationManager::initialize(HWND* window)
{
	m_window = window;

	//set id's to game states
	m_applicationState[APPLICATION_SINGLEPLAYER_GAME] = m_singlePlayerGame;

	//set default game states
	switchState(APPLICATION_SINGLEPLAYER_GAME);
}

void ApplicationManager::update()
{
	m_applicationState[m_activeState]->update();
}

void ApplicationManager::render()
{
	m_applicationState[m_activeState]->render(m_directxManager->getDeviceContext());
}

void ApplicationManager::close()
{
	m_applicationState[m_activeState]->close();
}

void ApplicationManager::switchState(int newState)
{
	m_activeState = newState;
	m_applicationState[m_activeState]->initialize(m_directxManager->getDevice(), m_directxManager->getDeviceContext());
}