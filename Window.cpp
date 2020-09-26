#include "Window.h"

Window::Window()
	: mIsFullscreen(false), mIsDone(false)
{
	mEventManager.AddCallback(StateType(0), "Close", &Window::EndProgram, this);
	mEventManager.AddCallback(StateType(0), "ToggleFullscreen", &Window::ToggleFullscreen, this);
	Open();
}

Window::~Window()
{
	Close();
}

void Window::Open()
{
	sf::Uint32 style = { mIsFullscreen ? (sf::Uint32)sf::Style::Fullscreen : (sf::Uint32)sf::Style::Titlebar | sf::Style::Close};
	mWindow.create(sf::VideoMode(854, 480, 32), "MazeGame", style);
	mWindow.setFramerateLimit(60);
}

void Window::Close()
{
	mWindow.close();
}

bool Window::IsDone()
{
	return mIsDone;
}

void Window::Draw(const sf::Drawable & lSprite)
{
	mWindow.draw(lSprite);
}

void Window::BeginDrawing()
{
	mWindow.clear(sf::Color::Black);
}

void Window::EndDrawing()
{
	mWindow.display();
}

void Window::ToggleFullscreen()
{
	mIsFullscreen = !mIsFullscreen;
	Close();
	Open();
}

void Window::EndProgram()
{
	mIsDone = true;
}

void Window::Update()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::GainedFocus)
		{
			mEventManager.SetFocus(true);
		}
		else if (event.type == sf::Event::LostFocus)
		{
			mEventManager.SetFocus(false);
		}

		mEventManager.HandleEvent(event);
	}
	mEventManager.Update();
}

EventManager * Window::GetEventManager()
{
	return &mEventManager;
}