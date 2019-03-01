#include<windows.h>
#include<CommCtrl.h> 


//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;


	case  WM_NOTIFY:
	{
		//WM_NOTIFY参数的公共头部
		NMHDR  *pHDR = (NMHDR*)lParam; 
		if ((pHDR->code == MCN_SELCHANGE) && (pHDR->idFrom == 111))
		{
			LPNMSELCHANGE   pSelect = (LPNMSELCHANGE)lParam;

			SYSTEMTIME   st0 = pSelect->stSelStart;
			SYSTEMTIME   st1 = pSelect->stSelEnd;

			TCHAR  buf[64] = { 0 };
			wsprintf(buf, L"%04d-%02d-%02d %02d:%02d:%02d 至 %04d-%02d-%02d %02d:%02d:%02d",
				st0.wYear, st0.wMonth, st0.wDay, st0.wHour, st0.wMinute, st0.wSecond,
				st1.wYear, st1.wMonth, st1.wDay, st1.wHour, st1.wMinute, st1.wSecond);
		
			MessageBox(hWnd, buf, L"提示", MB_OK);
		}

	}break;

	case WM_CREATE:
	{
       //创建日历控件
		HWND   hCalendar = CreateWindow(MONTHCAL_CLASS,
			L"XXX", WS_CHILD | WS_VISIBLE , 30, 30, 600, 600,
			hWnd, (HMENU)111, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
	
	//设置可选择日期的范围 
		SYSTEMTIME st[2];//0放最小值，1放最大值
		st[0].wYear = 2018;
		st[0].wMonth = 1;
		st[0].wDay = 1;
		st[1].wYear = 2018;
		st[1].wMonth = 1;
		st[1].wDay = 7;
		SendMessage(hCalendar, MCM_SETRANGE, GDTR_MAX | GDTR_MIN, (LPARAM)st);
	
		//选择某个日期值20180107
		 SendMessage(hCalendar, MCM_SETCURSEL,  0 , (LPARAM)&st[1]);

	
	}
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
		WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);

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