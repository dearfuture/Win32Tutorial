#include<windows.h> 
#include"resource.h"  
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

	case  WM_CREATE:
	{
		LPCREATESTRUCT   pcs = (LPCREATESTRUCT)lParam; 

		//静态文本控件
	 HWND  hStatic=	CreateWindow(L"Static", L"这是一个静态文本", WS_CHILD | WS_VISIBLE |WS_BORDER|SS_BITMAP|SS_NOTIFY,
			30, 30,200, 30, hWnd, (HMENU)111, pcs->hInstance, NULL);
	 //更改窗口标题
	 SetWindowText(hWnd, L"新窗口标题");
	 //设置控件（子窗口）内容
	 SetWindowText(hStatic, L"更改后的内容！");


	 //加载位图
	HBITMAP  hBmp= LoadBitmap(pcs->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	
	//向控件发送STM_SETIMAGE消息设置静态控件的位图
	SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);




		return 0;
	}


	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//控件ID
		WORD  code = HIWORD(wParam);//消息类型
		HWND   hCtrl = (HWND)lParam;//窗口句柄

		//父窗口接收到子控件发的消息
		if (id == 111  &&  code ==  STN_CLICKED)
		{
			MessageBox(NULL, L"静态文本被点击！", L"提示", MB_OK);
		}
	  
	}break;




	default:
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
	HWND    hWnd = CreateWindow(L"MrHuang", L"第一个窗口程序",
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