#include "App.h"

App::App()
	:
	wnd(800, 600, "GameEngine")
{}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float b = sin(timer.Peek()) / 2.0f + .5f;
	const float r = cos(timer.Peek()) / 2.0f + .5f;
	const float g = sin(timer.Peek()) / 2.0f + .5f;
	wnd.GFX().ClearBuffer(b, r, g);
	wnd.GFX().DrawTestTriangle();
	wnd.GFX().EndFrame();
}