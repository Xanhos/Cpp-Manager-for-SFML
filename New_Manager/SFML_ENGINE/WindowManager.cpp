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
#include "WindowManager.h"

WindowManager::WindowManager() : m_size_(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), m_event_(), m_is_done_(false), m_is_fullscreen_(true), m_title_("SFML Window"), m_timer_(0.f), m_update_is_stopped_(false)
{
	m_window_.create(sf::VideoMode::getDesktopMode(), "SFML Window", m_is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);

	if (m_size_.x <= 1920.f && m_size_.y <= 1080.f)
		m_view_.setCenter(1920.f / 2.f, 1080.F / 2.F);
	else if (m_size_.x <= 1920.f)
		m_view_.setCenter(1920.f / 2.f, m_size_.y / 2.F);
	else if (m_size_.y <= 1080.f)
		m_view_.setCenter(m_size_.x / 2.f, 1080.F / 2.F);
	else
		m_view_.setCenter(m_size_.x / 2.f, m_size_.y / 2.F);

	if (m_size_.x >= 1920.f && m_size_.y >= 1080.f)
		m_view_.setSize(static_cast<float>(m_size_.x), static_cast<float>(m_size_.y));
	else if (m_size_.x >= 1920.f)
		m_view_.setSize(static_cast<float>(m_size_.x), 1080.f);
	else if (m_size_.y >= 1080.f)
		m_view_.setSize(1920.f, static_cast<float>(m_size_.y));
	else
		m_view_.setSize(1920.f, 1080.f);

	m_window_.setView(m_view_);
}

WindowManager::WindowManager(int width, int height, std::string title, bool fullscreen, unsigned int antialiasing) :
m_size_(width, height), m_event_(), m_is_done_(false), m_is_fullscreen_(fullscreen), m_title_(title), m_timer_(0.f), m_update_is_stopped_(false)
{
	m_window_.create(sf::VideoMode(width, height), title, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(0,0,antialiasing));

	if (m_size_.x <= 1920.f && m_size_.y <= 1080.f)
		m_view_.setCenter(1920.f / 2.f, 1080.F / 2.F);
	else if (m_size_.x <= 1920.f)
		m_view_.setCenter(1920.f / 2.f, m_size_.y / 2.F);
	else if (m_size_.y <= 1080.f)
		m_view_.setCenter(m_size_.x / 2.f, 1080.F / 2.F);
	else
		m_view_.setCenter(m_size_.x / 2.f, m_size_.y / 2.F);

	if (m_size_.x >= 1920.f && m_size_.y >= 1080.f)
		m_view_.setSize(static_cast<float>(m_size_.x), static_cast<float>(m_size_.y));
	else if (m_size_.x >= 1920.f)
		m_view_.setSize(static_cast<float>(m_size_.x), 1080.f);
	else if (m_size_.y >= 1080.f)
		m_view_.setSize(1920.f, static_cast<float>(m_size_.y));
	else
		m_view_.setSize(1920.f, 1080.f);

	m_window_.setView(m_view_);
}

WindowManager::WindowManager(int width, int height, std::string title, bool fullscreen,const std::function<void(sf::RenderWindow* _window)>& custom_window_create) 
: m_size_(width, height), m_event_(), m_is_done_(false), m_is_fullscreen_(fullscreen), m_title_(title), m_timer_(0.f), m_update_is_stopped_(false)
{
	custom_window_create(&this->m_window_);
	
	if (m_size_.x <= 1920.f && m_size_.y <= 1080.f)
		m_view_.setCenter(1920.f / 2.f, 1080.F / 2.F);
	else if (m_size_.x <= 1920.f)
		m_view_.setCenter(1920.f / 2.f, m_size_.y / 2.F);
	else if (m_size_.y <= 1080.f)
		m_view_.setCenter(m_size_.x / 2.f, 1080.F / 2.F);
	else
		m_view_.setCenter(m_size_.x / 2.f, m_size_.y / 2.F);

	if (m_size_.x >= 1920.f && m_size_.y >= 1080.f)
		m_view_.setSize(static_cast<float>(m_size_.x), static_cast<float>(m_size_.y));
	else if (m_size_.x >= 1920.f)
		m_view_.setSize(static_cast<float>(m_size_.x), 1080.f);
	else if (m_size_.y >= 1080.f)
		m_view_.setSize(1920.f, static_cast<float>(m_size_.y));
	else
		m_view_.setSize(1920.f, 1080.f);

	m_window_.setView(m_view_);
	
}


bool WindowManager::isFullscreen() const
{
	return m_is_fullscreen_;
}

void WindowManager::toggleFullscreen()
{
	m_is_fullscreen_ = !m_is_fullscreen_;
	m_window_.close();
	m_window_.create(sf::VideoMode(m_size_.x, m_size_.y), m_title_, m_is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);
}

float WindowManager::timer() const
{
	return m_timer_;
}

void WindowManager::resetTimer()
{
	m_timer_ = 0.f;
}

void WindowManager::EventUpdate()
{
	m_timer_ += Tools::getDeltaTime();
	if (!m_update_is_stopped_)
		while (m_window_.pollEvent(m_event_))
			if (m_event_.type == m_event_.Closed)
				m_is_done_ = 1;
	if (m_is_done_)
		m_window_.close();

}

sf::Event& WindowManager::getEvent()
{
	return m_event_;
}

bool WindowManager::pollEvent()
{
	return m_window_.pollEvent(m_event_);
}

sf::RenderWindow& WindowManager::getWindow()
{
	return m_window_;
}

sf::Vector2i WindowManager::getSize() const
{
	return m_size_;
}

void WindowManager::setDefaultView()
{
	m_window_.setView(m_view_);
}

void WindowManager::setVsync(bool OnOff)
{
	m_window_.setVerticalSyncEnabled(OnOff);
}

sf::View& WindowManager::getView()
{
	return m_view_;
}

void WindowManager::clear(sf::Color clearColor)
{
	m_window_.clear(clearColor);
}

void WindowManager::draw(const sf::Drawable& drawable_, const sf::RenderStates& render_)
{
	m_window_.draw(drawable_, render_);
}

void WindowManager::display()
{
	m_window_.display();
}

bool WindowManager::isDone()
{
	return m_is_done_;
}

bool WindowManager::EventUpdateIsStopped()
{
	return m_update_is_stopped_;
}

void WindowManager::StopEventUpdate(bool stop)
{
	m_update_is_stopped_ = stop;
}

float WindowManager::get_Volume(std::string name)
{
	return m_map_sound_[name];
}

void WindowManager::set_Volume(std::string name, float volume)
{
	m_map_sound_[name] = volume;
}
