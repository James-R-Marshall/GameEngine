#include "Window.h"
Window::WindowClass Window::WindowClass::wndClass;
// Constructor for out window class object inside our window object. 
// we are passing nullpointer to getmodulehandle so it will return the current handle for this applicaition
Window::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))
{
	// filling our window class struct so it can be registered
	WNDCLASSEX wc = { 0 };
	wc.cbSize		= sizeof(wc);
	wc.style		= CS_OWNDC;
	wc.lpfnWndProc	= HandleMsgSetup;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= GetInstance();
	wc.hIcon = 0;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = 0;
	RegisterClassEx(&wc);

}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(WndClassName, GetInstance());
}

// get name
const char* Window::WindowClass::GetName() noexcept
{
	return WndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


Window::Window(int width, int height, const char* name) noexcept
{
	// calculate window size based on desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	hWnd = CreateWindow(WindowClass::GetName(), name, WS_CAPTION |
		WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr,
		WindowClass::GetInstance(), this);// *this is important, we are passing a pointer to this window for later use to link the handler below
											// this allows us to alter data set in the constructor

	// show Window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// this windows procedure is only to be used once, it will pass off the message hanhdling after it
	// catches the message WM_NCCreate
	if (msg == WM_NCCREATE)
	{
		// we will take the pointer that we passed at this point. 
		// reinterperate cast makes the pointer cast to a different data type
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// now that we have a pointer to the window and the handle of our window class 
		// with this information we can send this pointer to the custom userdata so we can access members inside the class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		// forward  message to the next handler.
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// now we can leave all message handling to the window class since we have a pointer to it.
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

