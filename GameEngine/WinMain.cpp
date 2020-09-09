//#include <Windows.h>
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam) {
//	switch (msg)
//	{
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		break;
//
//	case WM_KEYDOWN:
//		if (wParam == 'F') {
//			SetWindowText(hwnd, L"F");
//		}
//		break;
//	}
//	return DefWindowProc(hwnd, msg, wParam, lparam);
//}
//
//
//int CALLBACK WinMain(
//	HINSTANCE	hInstance,
//	HINSTANCE	hPrevInstance,
//	LPSTR		lpCmdLine,
//	int			nCmdShow)
//{
//	// Register window class
//
//	WNDCLASSEX wc = { 0 };
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_OWNDC;
//	wc.lpfnWndProc = WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = nullptr;
//	wc.hCursor = nullptr;
//	wc.hbrBackground = nullptr;
//	wc.lpszMenuName = nullptr;
//	wc.lpszClassName = L"Main";
//	wc.hIconSm = nullptr;
//	RegisterClassEx(&wc);
//
//	// Create Window
//
//	HWND hwnd = CreateWindowEx(
//		0,
//		L"Main",
//		L"window",
//		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
//		200, 200,
//		640, 480,
//		nullptr,
//		nullptr,
//		hInstance,
//		nullptr
//
//	);
//
//	ShowWindow(hwnd, SW_SHOW);
//
//	//message pump
//	MSG msg;
//	BOOL gResult;
//	while (gResult = GetMessage(&msg,nullptr,0,0) > 0)
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	if (gResult == -1)
//	{
//		return -1;
//	}
//	else {
//		return msg.wParam;
//	}
//	
//}