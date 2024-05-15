/*
    Based on Coffee Engine

    Author: GRALLAN Yann

    Description: SFML-Engine

    Date: 2024/01/31

    MIT License

    Copyright (c) 2024 GRALLAN Yann


    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include "SFML_ENGINE/WindowManager.h"
#include "SFML_ENGINE/Sprite.h"

#define PUSH_STATE(Type) m_state.push_back(std::make_unique<Type>(Type(m_windowManager, m_state))


class State;
typedef std::list<std::unique_ptr<State>> StateList;

class State
{
protected:
    StateList* m_state;
    WindowManager& m_windowManager;
    static bool m_manetteMode;
    bool m_isReady;
    bool m_initIsStarted;
    bool m_needToBeDeleted;
    std::string m_name;
public:
    State(WindowManager& _window, StateList* listState);
    bool& getIsReady() { return m_isReady; }
    bool& getNeedToBeDeleted() { return m_needToBeDeleted; }
    bool& getIsStarted() { return m_initIsStarted; }
    static bool getManetteMode() { return m_manetteMode; }
    void virtual init() = 0;
    void virtual update() = 0;
    void virtual render() = 0;
    void virtual pushState(char data) = 0;
    std::string virtual getName() { return m_name; }
};

class Test : public State
{
protected:
    std::unordered_map<std::string, std::pair<sf::Sprite,float>> m_sprite_map;
    sf::RectangleShape m_player_rectangle_shape_;
    sf::View m_view_;
    sf::Vector2f m_view_position_;
    float m_parallax_speed_;
public:
    Test(WindowManager& _window,StateList* _state_list);
    void init() override;
    void update() override;
    void render() override;
    void pushState(char data) override;
    
};

