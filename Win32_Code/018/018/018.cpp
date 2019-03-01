#include<windows.h>  
#include<stdio.h>
#include"resource.h"

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

		//创建位图按钮
		HWND   hBtn = CreateWindow(L"BuTtOn" /*不区分大小写*/, 
			L"XXX", WS_CHILD | WS_VISIBLE | BS_BITMAP,//指定为图片
			30, 30, 217, 46, hWnd, (HMENU)1000, pcs->hInstance, NULL);

		//LoadImage加载位图
		//HBITMAP  hBmp=(HBITMAP)LoadImage(NULL, L"C:\\Users\\35497\\Desktop\\code\\016\\Debug\\btn1.bmp",
		//	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


		//采用LoadBitmap加载位图资源(必须在rc文件中定义)
		HBITMAP  hBmp= LoadBitmap(pcs->hInstance, MAKEINTRESOURCE(IDB_BITMAP1) );

		//向控件发送BM_SETIMAGE消息设置按钮图片
		LRESULT  ret=SendMessage(hBtn, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmp);


		return 0;
	}


	case   WM_COMMAND:
	{
		WORD  id = LOWORD(wParam);
		WORD  code = HIWORD(wParam);
		HWND   hCtrl = (HWND)lParam;
		if (id == 1000 && code == BN_CLICKED)
		{
			MessageBox(hWnd, L"普通按钮被单击！", L"提示", MB_OK);
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
	  //加载系统光标，第一个参数为NULL
	//wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	//加载资源中的光标
	wnd.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));


	 //加载系统图标，第一个参数为NULL
	//wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	//加载资源中的图标
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));


	//wnd.lpfnWndProc = DefWindowProc;//默认窗口过程函数，用于处理消息
	wnd.lpfnWndProc = MyWindowProc;//自定义的窗口过程函数
	wnd.lpszClassName = L"MrHuang";//窗口类名
	wnd.lpszMenuName = NULL;//菜单资源名称
	wnd.style = CS_HREDRAW | CS_DBLCLKS;//窗口类、样式
	wnd.hInstance = hInstance;//实例句柄
	RegisterClass(&wnd);


	//加载字符串资源
	TCHAR  buf[64] = {0};
	LoadString(hInstance, IDS_STRING1, buf, sizeof(buf));
	LoadString(GetModuleHandle(NULL), IDS_STRING2, buf, sizeof(buf));

	//创建窗口(返回之前发送WM_CREATE)
	HWND    hWnd = CreateWindow(L"MrHuang", buf,
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