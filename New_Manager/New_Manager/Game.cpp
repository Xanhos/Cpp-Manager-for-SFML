#include "Game.h"
#include "SFML_ENGINE/RessourcesManager.h"


Game::Game() : m_windowManager()
{
}

Game::Game(int width, int height, std::string title, bool fullscreen, unsigned int antialiasing) : m_windowManager(width, height, title, fullscreen,antialiasing)
{
    //m_windowManager.getWindow().setVerticalSyncEnabled(true);
    m_windowManager.getWindow().setFramerateLimit(240);
    m_windowManager.set_Volume("Music",50.f);
    m_windowManager.set_Volume("SFX",50.f);
}

Game::~Game()
{
    m_state.clear();
}

void Game::update()
{
    Tools::restartClock();
    m_windowManager.EventUpdate();

    if (KEY(F11) && m_windowManager.timer() > 0.25f && m_windowManager.getWindow().hasFocus())
    {
        m_windowManager.toggleFullscreen();
        m_windowManager.resetTimer();
        m_windowManager.getWindow().setMouseCursorVisible(false);
    }
    if (!m_state.empty())
    {
        if (!m_state.front().get()->getIsReady() and GET_MANAGER->IsReady())
        {
            if (!m_state.front().get()->getIsStarted())
            {
                std::thread t([&] {m_state.front().get()->init(); m_state.front()->getIsReady() = true;});
                t.detach();
                m_state.front().get()->getIsStarted() = true;
            }
        }
        else if (m_state.front().get()->getIsReady())
                m_state.front().get()->update();

        if (static_cast<int>(m_state.size()) > 1)
            m_state.erase(std::remove_if(m_state.begin(), m_state.end(), [](std::unique_ptr<State>& _state)
                {
                    return _state->getNeedToBeDeleted();
                }), m_state.end());
    }
}

void Game::render()
{
    m_windowManager.clear(sf::Color::White);
   
    if(!m_state.empty())
    {
        if (GET_MANAGER->IsReady() and m_state.front().get()->getIsReady())
            m_state.front().get()->render();
        else if (!GET_MANAGER->IsReady() or !m_state.front().get()->getIsReady())
        {
            m_windowManager.getWindow().setView(m_windowManager.getWindow().getDefaultView());
            GET_MANAGER->showLoadingScreen(m_windowManager.getWindow());
        }
    }

    m_windowManager.display();
}

void Game::runGame()
{
    /*TODO : Modifier la texture de l'écran de chargement*/
    GET_MANAGER->getLoadingScreen() = Animation(GET_MANAGER->getTexture("loading"), sf::IntRect(0, 0, 140, 170), 0.1f, 7);
    GET_MANAGER->getLoadingScreen().getSprite().setPosition({ (m_windowManager.getWindow().getSize().x - 140.f) / 2, (m_windowManager.getWindow().getSize().y - GET_MANAGER->getLoadingScreen().getSprite().getGlobalBounds().height) / 2 });

    /*TODO : Modifier le state de départ de l'application*/
    m_state.push_back(std::make_unique<Test>(Test(m_windowManager,&m_state)));
    
    m_windowManager.AddCustomParam("FPS",1500u,[](WindowManager* _window,const std::any& param)
    {
        const unsigned int fps = std::any_cast<unsigned int>(param);
        _window->getWindow().setFramerateLimit(fps);
    });

   
    while (!m_windowManager.isDone())
    {
        if (GET_MANAGER->IsReady())
        {
            GET_MANAGER->setVolumeForAllMusic(m_windowManager.get_Volume("Music"));
            GET_MANAGER->setVolumeForAllSound(m_windowManager.get_Volume("SFX"));
        }

        update();

     

        render();
    }

    GET_MANAGER->getSteam().~SteamManager();
}