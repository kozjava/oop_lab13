#include <Windows.h>

HINSTANCE HINST;
HWND CreateChildWindow();




//WNDCLASS RegClass()
//{
//
//}


int COL_WINDOW = 0;

BOOL MWindow(HWND hWnd, int x,int y,int w,int h)
{
	return MoveWindow(hWnd,x,y,w,h,NULL);
}




LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PS;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		//PostQuitMessage(1);
		COL_WINDOW--;
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &PS);
		EndPaint(hWnd, &PS);
		break;
	case WM_CHAR:
		DestroyWindow(hWnd); break;//
	case WM_LBUTTONDOWN:CreateChildWindow(); break;;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND CreateChildWindow()
{
	if (COL_WINDOW == 7) return NULL;
	//Создаем класс окна
	WNDCLASS WindowClass;

	//Заполняем структуру 
	WindowClass.style = CS_DBLCLKS;
	WindowClass.lpfnWndProc = (WNDPROC)WndProcChild;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = HINST;
	WindowClass.hIcon = LoadIcon(HINST,
		(LPCTSTR)IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = 0;
	WindowClass.lpszClassName = TEXT("ChildWClass");

	//Зарегистируем класс окна
	RegisterClass(&WindowClass);

	//Создаем переменную, в которой поместим идентификатор окна
	HWND hWndC;

	hWndC = CreateWindow(TEXT("ChildWClass"), TEXT("Дочернее окно"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, HINST, NULL);

	//показать окно
	ShowWindow(hWndC, SW_NORMAL);

	//обновить содержимое окна
	UpdateWindow(hWndC);
	COL_WINDOW++;
	return hWndC;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PS;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &PS);
		EndPaint(hWnd, &PS);
		break;
	case WM_CHAR:
		MWindow(hWnd,300,500,500,300); break;//
	case WM_CLOSE:MessageBox(
		NULL,
		(LPCWSTR)"",
		(LPCWSTR)L"WM_CLOSE",
		MB_OKCANCEL| MB_DEFBUTTON2
		);
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_LBUTTONDOWN: CreateChildWindow(); break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}













int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HINST = hInstance;
	//Создаем класс окна
	WNDCLASS WindowClass;

	//Заполняем структуру 
	WindowClass.style = CS_DBLCLKS;
	WindowClass.lpfnWndProc = (WNDPROC)WndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(hInstance,
		(LPCTSTR)IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = 0;
	WindowClass.lpszClassName = TEXT("Class");

	//Зарегистируем класс окна
	RegisterClass(&WindowClass);

	//Создаем переменную, в которой поместим идентификатор окна
	HWND hWnd;

	hWnd = CreateWindow(TEXT("Class"), TEXT("Главное окно"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, NULL, NULL, hInstance, NULL);

	//показать окно
	ShowWindow(hWnd, nCmdShow);

	//обновить содержимое окна
	UpdateWindow(hWnd);

	//Создадим переменную для храненния сообщений
	MSG msg;

	//Создадим цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
