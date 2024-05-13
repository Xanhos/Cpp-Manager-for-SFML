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

WindowManager::WindowManager() : m_size(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), m_event(), m_isDone(false), m_isFullscreen(true), m_title("SFML Window"), m_timer(0.f), m_UpdateIsStopped(false)
{
	m_window.create(sf::VideoMode::getDesktopMode(), "SFML Window", m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

	if (m_size.x <= 1920.f && m_size.y <= 1080.f)
		m_view.setCenter(1920.f / 2.f, 1080.F / 2.F);
	else if (m_size.x <= 1920.f)
		m_view.setCenter(1920.f / 2.f, m_size.y / 2.F);
	else if (m_size.y <= 1080.f)
		m_view.setCenter(m_size.x / 2.f, 1080.F / 2.F);
	else
		m_view.setCenter(m_size.x / 2.f, m_size.y / 2.F);

	if (m_size.x >= 1920.f && m_size.y >= 1080.f)
		m_view.setSize(static_cast<float>(m_size.x), static_cast<float>(m_size.y));
	else if (m_size.x >= 1920.f)
		m_view.setSize(static_cast<float>(m_size.x), 1080.f);
	else if (m_size.y >= 1080.f)
		m_view.setSize(1920.f, static_cast<float>(m_size.y));
	else
		m_view.setSize(1920.f, 1080.f);

	m_window.setView(m_view);
}

WindowManager::WindowManager(int width, int height, std::string title, bool fullscreen, unsigned int antialiasing)
{
	m_window.create(sf::VideoMode(width, height), title, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(0,0,antialiasing));

	if (m_size.x <= 1920.f && m_size.y <= 1080.f)
		m_view.setCenter(1920.f / 2.f, 1080.F / 2.F);
	else if (m_size.x <= 1920.f)
		m_view.setCenter(1920.f / 2.f, m_size.y / 2.F);
	else if (m_size.y <= 1080.f)
		m_view.setCenter(m_size.x / 2.f, 1080.F / 2.F);
	else
		m_view.setCenter(m_size.x / 2.f, m_size.y / 2.F);

	if (m_size.x >= 1920.f && m_size.y >= 1080.f)
		m_view.setSize(static_cast<float>(m_size.x), static_cast<float>(m_size.y));
	else if (m_size.x >= 1920.f)
		m_view.setSize(static_cast<float>(m_size.x), 1080.f);
	else if (m_size.y >= 1080.f)
		m_view.setSize(1920.f, static_cast<float>(m_size.y));
	else
		m_view.setSize(1920.f, 1080.f);

	m_isFullscreen = fullscreen;
	m_window.setView(m_view);
}


bool WindowManager::isFullscreen() const
{
	return m_isFullscreen;
}

void WindowManager::toggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	m_window.create(sf::VideoMode(m_size.x, m_size.y), m_title, m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
}

float WindowManager::timer() const
{
	return m_timer;
}

void WindowManager::resetTimer()
{
	m_timer = 0.f;
}

void WindowManager::EventUpdate()
{
	m_timer += Tools::getDeltaTime();
	if (!m_UpdateIsStopped)
		while (m_window.pollEvent(m_event))
			if (m_event.type == m_event.Closed)
				m_isDone = 1;
	if (m_isDone)
		m_window.close();

}

sf::Event& WindowManager::getEvent()
{
	return m_event;
}

bool WindowManager::pollEvent()
{
	return m_window.pollEvent(m_event);
}

sf::RenderWindow& WindowManager::getWindow()
{
	return m_window;
}

sf::Vector2i WindowManager::getSize() const
{
	return m_size;
}

void WindowManager::setDefaultView()
{
	m_window.setView(m_view);
}

void WindowManager::setVsync(bool OnOff)
{
	m_window.setVerticalSyncEnabled(OnOff);
}

sf::View& WindowManager::getView()
{
	return m_view;
}

void WindowManager::clear(sf::Color clearColor)
{
	m_window.clear(clearColor);
}

void WindowManager::draw(const sf::Drawable& drawable_, const sf::RenderStates& render_)
{
	m_window.draw(drawable_, render_);
}

void WindowManager::display()
{
	m_window.display();
}

bool WindowManager::isDone()
{
	return m_isDone;
}

bool WindowManager::EventUpdateIsStopped()
{
	return m_UpdateIsStopped;
}

void WindowManager::StopEventUpdate(bool stop)
{
	m_UpdateIsStopped = stop;
}

float WindowManager::get_Volume(std::string name)
{
	return m_map_sound[name];
}

void WindowManager::set_Volume(std::string name, float volume)
{
	m_map_sound[name] = volume;
}
