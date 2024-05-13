#include "State.h"
#include "SFML_ENGINE/SteamManager.h"

class Game
{
    WindowManager m_windowManager;
    StateList m_state;

    void update();
    void render();
public:
    Game();
    Game(int width, int height, std::string title, bool fullscreen,unsigned int antialiasing);
    ~Game();

    void runGame();


};