#include<windows.h>
#include<CommCtrl.h> 

//#pragma  comment(lib, "COMCTL32.LIB")

//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;

	case WM_NOTIFY:
	{
		NMHDR  *pHDR = (NMHDR  *)lParam;
		if (pHDR->code == DTN_DATETIMECHANGE)
		{
			LPNMDATETIMECHANGE  pDT = (LPNMDATETIMECHANGE)lParam;
			SYSTEMTIME  st = pDT->st;
			TCHAR  buf[64] = {0};
			wsprintf(buf, L"%04d-%02d-%02d %02d:%02d:%02d ",
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			MessageBox(hWnd, buf, L"提示", MB_OK);
		}  
	}break;

	case WM_CREATE:
	{
		//创建一个日期时间选择控件
		HWND   hDatetime = CreateWindow(DATETIMEPICK_CLASS, L"XXX",
			WS_CHILD | WS_VISIBLE| DTS_SHOWNONE, 30, 30, 200, 30, hWnd, (HMENU)111, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		//设置控件的显示格式
		SendMessage(hDatetime, DTM_SETFORMAT, 0, (LPARAM)L"yyyy-MM-dd  hh:mm:ss  tt");

		//设置控件的显示时间
		SYSTEMTIME  st;
		st.wYear = 1999;
		st.wMonth = 8;
		st.wDay = 7;
		st.wHour = 6;
		st.wMinute = 5;
		st.wSecond = 4;
		st.wMilliseconds = 3;
		SendMessage(hDatetime, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);

		//设置时间为无
		//SendMessage(hDatetime, DTM_SETSYSTEMTIME, GDT_NONE, 0);


	}break;

	 
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