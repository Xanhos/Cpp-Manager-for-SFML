#include "State.h"
#include "SFML_ENGINE/RessourcesManager.h"

State::State(WindowManager& _window, std::list<std::unique_ptr<State>>* stackState) : m_windowManager(_window), m_listState(stackState), m_isReady(false), m_initIsStarted(false), m_needToBeDeleted(false), m_name("")
{
}

