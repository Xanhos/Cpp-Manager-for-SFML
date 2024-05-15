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
#include <any>
#include <functional>

#include "Tools.h"

class SFMLENGINE_API WindowManager
{
	sf::RenderWindow m_window_;
	sf::View m_view_;
	bool m_is_fullscreen_;
	float m_timer_;
	bool m_is_done_;	
	bool m_update_is_stopped_;
	sf::Vector2i m_size_;
	std::string m_title_;
	sf::Event m_event_;
	

	std::map<std::string,float> m_map_sound_;
	std::map<std::string,std::pair<std::any,std::function<void(WindowManager*,const std::any&)>>> m_custom_param_;
public:

	////////////////////////////////////////////////////////////
	/// \brief constructor of windowManager()
	/// \default view with auto resize as set on windows (if you change view please reset with setDefaultView)
	////////////////////////////////////////////////////////////
	WindowManager();
	WindowManager(int width, int height, std::string title, bool fullscreen, unsigned int antialiasing);
	WindowManager(int width, int height, std::string title, bool fullscreen,const std::function<void(sf::RenderWindow*)>& custom_window_create);

	////////////////////////////////////////////////////////////
	/// \brief return if the window is in fullscreen or not
	///
	////////////////////////////////////////////////////////////
	bool isFullscreen() const;

	////////////////////////////////////////////////////////////
	/// \brief enable/disable full screen mode
	///
	////////////////////////////////////////////////////////////
	void toggleFullscreen();

	////////////////////////////////////////////////////////////
	/// \brief return the window timer. Useful when you want to manage input in differents state with the same timer 
	///
	////////////////////////////////////////////////////////////
	float timer() const;

	////////////////////////////////////////////////////////////
	/// \brief reset the window timer
	///
	////////////////////////////////////////////////////////////
	void resetTimer();

	////////////////////////////////////////////////////////////
	/// \brief make the basic event update (check if the window need to be closed)
	///
	////////////////////////////////////////////////////////////
	void EventUpdate();

	////////////////////////////////////////////////////////////
	/// \brief return the event of the window
	///
	////////////////////////////////////////////////////////////
	sf::Event& getEvent();

	////////////////////////////////////////////////////////////
	/// \brief make the poll event of the window and return true if an event is detected
	///
	////////////////////////////////////////////////////////////
	bool pollEvent();

	////////////////////////////////////////////////////////////
	/// \brief return a ref of the renderwindow
	///
	////////////////////////////////////////////////////////////
	sf::RenderWindow& getWindow();

	////////////////////////////////////////////////////////////
	/// \brief return the size of the renderwindow
	///
	////////////////////////////////////////////////////////////
	sf::Vector2i getSize() const;

	////////////////////////////////////////////////////////////
	/// \brief set default view on the window
	///
	////////////////////////////////////////////////////////////
	void setDefaultView();

	////////////////////////////////////////////////////////////
	/// \brief set vsync on the window
	///
	////////////////////////////////////////////////////////////
	void setVsync(bool OnOff);

	////////////////////////////////////////////////////////////
	/// \brief return a ref of the view
	///
	////////////////////////////////////////////////////////////
	sf::View& getView();

	////////////////////////////////////////////////////////////
	/// \brief clear the window
	///
	/// \param clearColor Color of the clear
	/// 
	////////////////////////////////////////////////////////////
	void clear(sf::Color clearColor = sf::Color::White);

	////////////////////////////////////////////////////////////
	/// \brief draw a drawable on the window
	///
	/// \param drawable thing to draw
	/// \param rener_ renderstate apply to the drawable
	/// 
	////////////////////////////////////////////////////////////
	void draw(const sf::Drawable& drawable_, const sf::RenderStates& render_ = sf::RenderStates::Default);

	////////////////////////////////////////////////////////////
	/// \brief return the position of the window relative to the window
	///
	/// \param mapPixelToCoord convert the pixel position to the world position
	/// 
	////////////////////////////////////////////////////////////
	template<typename T>
	T getMousePos(bool mapPixelToCoord = true) { return (mapPixelToCoord ? T(m_window_.mapPixelToCoords(sf::Mouse::getPosition(m_window_))) : T(sf::Mouse::getPosition(m_window_))); }

	////////////////////////////////////////////////////////////
	/// \brief display all the things draw on a window
	/// 
	////////////////////////////////////////////////////////////
	void display();

	////////////////////////////////////////////////////////////
	/// \brief return if the window is done or not
	/// 
	////////////////////////////////////////////////////////////
	bool isDone();

	////////////////////////////////////////////////////////////
	/// \brief return if the basic event update is stopped
	/// 
	////////////////////////////////////////////////////////////
	bool EventUpdateIsStopped();

	////////////////////////////////////////////////////////////
	/// \brief set if the eventUpdate is stopped
	/// 
	////////////////////////////////////////////////////////////
	void StopEventUpdate(bool stop);
	
	////////////////////////////////////////////////////////////
	/// \brief set the Music volume of the window
	/// 
	////////////////////////////////////////////////////////////
	float get_Volume(std::string name);

	////////////////////////////////////////////////////////////
	/// \brief set the Movie volume of the window
	/// 
	////////////////////////////////////////////////////////////
	void set_Volume(std::string name,float volume);

	template <typename T>
	void AddCustomParam(std::string param_name, T type, std::function<void(WindowManager*,const std::any&)> update_func);

	
	template <typename T>
	void SetCustomParam(std::string param_name, T type);
	
	template <typename T>
	T GetCustomParam(std::string param_name);
};

template <typename T>
void WindowManager::AddCustomParam(std::string param_name, T type, std::function<void(WindowManager*,const std::any&)> update_func)
{
	if(m_custom_param_.contains(param_name))
		return;

	m_custom_param_[param_name].first = type;
	m_custom_param_[param_name].second = update_func;
	m_custom_param_[param_name].second(this,m_custom_param_[param_name].first);
}

template <typename T>
void WindowManager::SetCustomParam(std::string param_name, T type)
{
	if(m_custom_param_.contains(param_name))
	{
		m_custom_param_[param_name].first = type;
		m_custom_param_[param_name].second(this,m_custom_param_[param_name].first);
	}
}

template <typename T>
T WindowManager::GetCustomParam(std::string param_name)
{
	if(m_custom_param_.contains(param_name))
		return std::any_cast<T>(m_custom_param_[param_name].first);
	return T();
}
