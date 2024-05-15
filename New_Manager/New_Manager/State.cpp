#include "State.h"
#include "SFML_ENGINE/RessourcesManager.h"

State::State(WindowManager& _window, std::list<std::unique_ptr<State>>* stackState) : m_windowManager(_window), m_state(stackState), m_isReady(false), m_initIsStarted(false), m_needToBeDeleted(false), m_name("")
{
}

Test::Test(WindowManager& _window, StateList* _state_list) : State(_window,_state_list)
{
    GET_MANAGER->loadScene("Test");
}

void Test::init()
{
    int screen_number = 3;
    for(int i = 0; i < screen_number; i++)
        m_sprite_map[std::to_string(1 * (i+1))] = {sf::Sprite(GET_MANAGER->getTexture("P4")),1.6f};
    for(int i = 0; i < screen_number; i++)
        m_sprite_map[std::to_string(2 * (i+2))] = {sf::Sprite(GET_MANAGER->getTexture("P3")),1.4f};
    for(int i = 0; i < screen_number; i++)
        m_sprite_map[std::to_string(3 * (i+3))] = {sf::Sprite(GET_MANAGER->getTexture("P2")),1.2f};
    for(int i = 0; i < screen_number; i++)
        m_sprite_map[std::to_string(4 * (i+4))] = {sf::Sprite(GET_MANAGER->getTexture("P1")),1.f};
     for(int i = 0; i < screen_number; i++)
     {
          m_sprite_map[std::to_string(1 * (i+1))].first.setScale({m_sprite_map[std::to_string(1 * (i+1))].second,m_sprite_map[std::to_string(1 * (i+1))].second});
          m_sprite_map[std::to_string(2 * (i+2))].first.setScale({ m_sprite_map[std::to_string(2 * (i+2))].second, m_sprite_map[std::to_string(2 * (i+2))].second});
          m_sprite_map[std::to_string(3 * (i+3))].first.setScale({ m_sprite_map[std::to_string(3 * (i+3))].second, m_sprite_map[std::to_string(3 * (i+3))].second});
          m_sprite_map[std::to_string(4 * (i+4))].first.setScale({ m_sprite_map[std::to_string(4 * (i+4))].second, m_sprite_map[std::to_string(4 * (i+4))].second}); 
         
         m_sprite_map[std::to_string(1 * (i+1))].first.setPosition(sf::Vector2f{0.f + i * 3840.f ,0.f}- m_sprite_map[std::to_string(1 * (i+1))].first.getGlobalBounds().getSize() * (m_sprite_map[std::to_string(1 * (i+1))].second - 1) / 2.f);
         m_sprite_map[std::to_string(2 * (i+2))].first.setPosition(sf::Vector2f{0.f + i * 3840.f,0.f} - m_sprite_map[std::to_string(1 * (i+1))].first.getGlobalBounds().getSize() * (m_sprite_map[std::to_string(2 * (i+2))].second - 1) / 2.f);
         m_sprite_map[std::to_string(3 * (i+3))].first.setPosition(sf::Vector2f{0.f + i * 3840.f,0.f} - m_sprite_map[std::to_string(1 * (i+1))].first.getGlobalBounds().getSize() * (m_sprite_map[std::to_string(3 * (i+3))].second - 1) / 2.f);
         m_sprite_map[std::to_string(4 * (i+4))].first.setPosition(sf::Vector2f{0.f + i * 3840.f,0.f} - m_sprite_map[std::to_string(1 * (i+1))].first.getGlobalBounds().getSize() * (m_sprite_map[std::to_string(4 * (i+4))].second - 1) / 2.f);
         
     }
    m_player_rectangle_shape_ = sf::RectangleShape({175.f,250.f});
    m_player_rectangle_shape_.setOrigin(m_player_rectangle_shape_.getSize()/2.f);
    m_player_rectangle_shape_.setFillColor(sf::Color::Magenta);
    
    m_view_ = sf::View({1920.f,1080.f},{3840.f,2160.f});
    m_parallax_speed_ = 5000.f;
}


void Test::update()
{
    if (KEY(Add))
    {
        m_view_.zoom(0.995f);
    }
    if (KEY(Subtract))
    {
        m_view_.zoom(1.005f);
    }

    if(KEY(D))
    {
        m_view_position_.x += 500.f * Tools::getDeltaTime();

        for(auto& i : m_sprite_map)
            if(i.second.second != 1.f)
                i.second.first.setPosition(i.second.first.getPosition().x + m_parallax_speed_ / (i.second.second) * Tools::getDeltaTime(),i.second.first.getPosition().y);
   
    }
    if(KEY(Q))
    {
        m_view_position_.x -= 500.f * Tools::getDeltaTime();
        for(auto& i : m_sprite_map)
            if(i.second.second != 1.f)
                i.second.first.setPosition(i.second.first.getPosition().x - m_parallax_speed_ / (i.second.second)  * Tools::getDeltaTime(),i.second.first.getPosition().y);
    
    }
    if(KEY(Z))
        m_view_position_.y -= 500.f *Tools::getDeltaTime();
    if(KEY(S))
        m_view_position_.y += 500.f *Tools::getDeltaTime();

       
    m_view_.setCenter(m_view_position_);
    m_player_rectangle_shape_.setPosition(m_view_position_);
}

void Test::render()
{
    m_windowManager.getWindow().setView(m_view_);
    for(auto& sprite : m_sprite_map)
    {
        m_windowManager.draw(sprite.second.first);
        if(sprite.second.second == 1.f)
            m_windowManager.draw(m_player_rectangle_shape_);            
    }
}

void Test::pushState(char data)
{
}

