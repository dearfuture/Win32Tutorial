#include<windows.h>
#include<stdio.h>

  

//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		///////////////////////////创建窗口///////////////////////////////
	case WM_NCCREATE:

		SetWindowTextA(hWnd, "改变标题");

		char str[64];
		sprintf(str, "WM_NCCREATE消息:%p！\n", hWnd);
		OutputDebugStringA(str);
		return  true;//这里必须返回true，否则不会发WM_CREATE消息，CreateWindow返回NULL

	case WM_CREATE:
	{
		CREATESTRUCT  *p = (CREATESTRUCT*)lParam; 
		sprintf(str, "WM_CREATE消息:%p！\n", hWnd); 

		OutputDebugStringA(str);
		return true;
	}

		///////////////////////////销毁窗口/////////////////////////////// 
	case WM_CLOSE:
		sprintf(str, "WM_CLOSE消息:%p！\n", hWnd);
		OutputDebugStringA(str); 
		DestroyWindow(hWnd);//销毁窗口，发出WM_DESTROY消息
		return 0;

	case WM_DESTROY: 
		sprintf(str, "WM_DESTROY消息:%p！\n", hWnd);
		OutputDebugStringA(str);
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;
	case WM_NCDESTROY: 
		sprintf(str, "WM_NCDESTROY消息:%p！\n", hWnd);
		OutputDebugStringA(str);
		return 0;
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
	char str[64];
	sprintf(str, "CreateWindow返回:%p！\n", hWnd);
	OutputDebugStringA(str); 

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