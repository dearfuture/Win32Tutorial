#include<windows.h>
#include<stdio.h>



//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0; 

		//鼠标消息
	case  WM_LBUTTONDOWN:
		char str[64];
		sprintf(str, "鼠标左键按下:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
	case  WM_LBUTTONUP: 
		sprintf(str, "鼠标左键弹起:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
	case  WM_MOUSEMOVE: 
		sprintf(str, "鼠标移动:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
	case  WM_LBUTTONDBLCLK: 
		sprintf(str, "鼠标左键双击:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
		 //键盘消息
	case  WM_KEYDOWN:
		sprintf(str, "键盘按下:  %X, %c\n", wParam , wParam);
		OutputDebugStringA(str);
		break;
	case  WM_CHAR:
		sprintf(str, "字符消息:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break; 
	case  WM_KEYUP:
		sprintf(str, "键盘弹起:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;

	case  WM_SYSKEYDOWN: //alt同时按下的键
		sprintf(str, "系统按键按下:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;
	case  WM_SYSCHAR:  
		sprintf(str, "系统字符:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;
	case  WM_SYSKEYUP:
		sprintf(str, "系统按键弹起:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;


	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}


int  WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE  hPrevInstance,
	LPSTR lpCmdLine, int  nShowCmd)
{
	//1.注册窗口类
	WNDCLASS  wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));//背景色
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);//光标
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标
												//wnd.lpfnWndProc = DefWindowProc;//默认窗口过程函数，用于处理消息
	wnd.lpfnWndProc = MyWindowProc;//自定义的窗口过程函数
	wnd.lpszClassName = L"MrHuang";//窗口类名
	wnd.lpszMenuName = NULL;//菜单资源名称
	wnd.style = CS_HREDRAW | CS_DBLCLKS;//窗口类、样式
	wnd.hInstance = hInstance;//实例句柄
	RegisterClass(&wnd);

	//创建窗口(返回之前发送WM_CREATE)
	HWND  hWnd = CreateWindow(L"MrHuang", L"第一个窗口程序",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);

	//显示窗口
	ShowWindow(hWnd, nShowCmd);
	//更新窗口(发送WM_PAINT)
	UpdateWindow(hWnd);


	//消息循环（收到WM_QUIT消息退出）
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//翻译消息
		DispatchMessage(&msg);//分发消息到窗口过程
	}
}