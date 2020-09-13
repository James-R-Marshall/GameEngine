#pragma once
#include "ModifiedWindow.h"
#include "TrillionException.h"
#include "Keyboard.h"


class Window
{
public: class Exception : public TrillionException
{
public: 
	Exception(int line, const char* file, HRESULT hr) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept override;
	static std::string TranslateErrorCode(HRESULT hr) noexcept;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorString() const noexcept;
private:
	HRESULT hr;
};
	 
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* WndClassName = "Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
public: 
	Keyboard kbd;
};


// macro so I do not have to define this long line again
#define TRIWND_EXCEPT( hr ) Window::Exception( __LINE__,__FILE__,hr )
#define TRIWND_LAST_EXCEPT() Window::Exception( __LINE__,__FILE__,GetLastError() )