#include<windows.h>
#include<stdio.h>

//自定义消息
#define  WM_AAA    WM_USER+1

HWND  hWnd; 
HWND  hWnd2;


//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0; 

	case WM_AAA:
		MessageBoxA(NULL, "窗口过程：WM_AAA", "测试", MB_OK);
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
	wnd.style = CS_HREDRAW;//窗口类、样式
	wnd.hInstance = hInstance;//实例句柄
	RegisterClass(&wnd);

	//创建窗口(返回之前发送WM_CREATE)
	hWnd = CreateWindow(L"MrHuang", L"第一个窗口程序",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);

	//显示窗口
	ShowWindow(hWnd, nShowCmd);
	//更新窗口(发送WM_PAINT)
	UpdateWindow(hWnd);


	//创建窗口2(返回之前发送WM_CREATE)
	hWnd2 = CreateWindow(L"MrHuang", L"第二个窗口程序",
		WS_OVERLAPPEDWINDOW, 100, 500, 300, 300, NULL, NULL, hInstance, NULL);
	//显示窗口
	ShowWindow(hWnd2, nShowCmd);
	//更新窗口(发送WM_PAINT)
	UpdateWindow(hWnd2);

	 
	//消息循环（收到WM_QUIT消息退出）
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//说明两个窗口公用一个消息循环和线程消息队列
		if (msg.message == WM_LBUTTONDOWN)
		{
			//char str[64];
			//sprintf(str,"窗口句柄:%p", msg.hwnd);
			//MessageBoxA(NULL, str,"测试", MB_OK);


			//SendMessage直接发给窗口过程函数，并且阻塞，除非被窗口过程处理才返回
			//SendMessage(hWnd, WM_AAA, 0, 0);

			//PostMessage放到线程消息队列里，并且立即返回，通过消息循环到窗口过程处理
			//PostMessage(hWnd, WM_AAA, 0, 0);

			//PostThreadMessage放到线程消息队列里，不进入窗口过程
			//PostThreadMessage(GetCurrentThreadId(), WM_AAA, 0, 0);
			
			//PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
			PostQuitMessage(0);//等价于上面的一行调用

			int  a = 100;
		}

		if (msg.message == WM_AAA)
		{
		    MessageBoxA(NULL, "消息循环:WM_AAA","测试", MB_OK); 
		}



		TranslateMessage(&msg);//翻译消息
		DispatchMessage(&msg);//分发消息到窗口过程
	}
}