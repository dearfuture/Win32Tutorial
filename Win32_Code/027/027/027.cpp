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

	case  WM_CREATE:
	{
		LPCREATESTRUCT   pcs = (LPCREATESTRUCT)lParam;

		//创建滚动条控件
		HWND hScrollBar = CreateWindow(L"scrollBAR", L"XXX", WS_CHILD | WS_VISIBLE | SBS_HORZ,
			30, 30, 200, 30, hWnd, (HMENU)111, pcs->hInstance, NULL);

		//设置滚动条的范围
		SendMessage(hScrollBar, SBM_SETRANGE, 0, 100);

		//设置滚动条的滑块位置
		SendMessage(hScrollBar, SBM_SETPOS, 40, 1);


		return 0;
	}
	 
	case  WM_CTLCOLORSCROLLBAR:
	{
		HDC    hdc = (HDC)wParam;
		HWND  hCtrl = (HWND)lParam;
		LONG   CtrlID=GetWindowLong(hCtrl, GWL_ID);

		if (CtrlID == 111)
		{
			HBRUSH  bsh = CreateSolidBrush(RGB(255, 0, 0));
			return  (LRESULT)bsh;
		}  
	
	}break;


	//水平滚动条发送的消息
	case   WM_HSCROLL:
	{

		WORD  code = LOWORD(wParam);//操作码
		HWND   hCtrl = (HWND)lParam;//控件句柄
									//获取滚动条的滑块位置
		int   pos = SendMessage(hCtrl, SBM_GETPOS, 0, 0);

		switch (code)
		{
			//点击左边箭头
		case SB_LINELEFT:
			OutputDebugString(L"SB_LINELEFT\n");
			pos -= 1;
			break;
			//点击右边箭头
		case SB_LINERIGHT:
			OutputDebugString(L"SB_LINERIGHT\n");
			pos += 1;
			break;
			//点击左空白区
		case SB_PAGELEFT:
			OutputDebugString(L"SB_PAGELEFT\n");
			pos -= 10;
			break;
			//点击右空白区
		case SB_PAGERIGHT:
			OutputDebugString(L"SB_PAGERIGHT\n");
			pos += 10;
			break;
			//拖动滑块时的消息
		case  SB_THUMBPOSITION:
			pos = HIWORD(wParam);//拖拽位置，仅当SB_THUMBPOSITION有用 
			char str[64];
			sprintf(str, "SB_THUMBPOSITION   %d\n", pos);
			OutputDebugStringA(str);
			break;
		}

		//设置滚动条的滑块位置
		SendMessage(hCtrl, SBM_SETPOS, pos, 1);

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