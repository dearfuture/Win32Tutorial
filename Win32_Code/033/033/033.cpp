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

	case WM_COMMAND:
	{
		HWND  hCtrl = (HWND)lParam;
		WORD   CtrlID = LOWORD(wParam);
		WORD    code=HIWORD(wParam);
		if (code == EN_CHANGE)
		{
			//获取组合键的内容
			WORD  key = SendMessage(hCtrl, HKM_GETHOTKEY, 0, 0);
			BYTE  l = LOBYTE(LOWORD(key));//字母等
			BYTE  h = HIBYTE(LOWORD(key));//CTRL | ALT |SHIFT 

			TCHAR  buf[64] = { 0 };
			wsprintf(buf, L"%c  +   %d  +  %d\n", l, bool(h & HOTKEYF_CONTROL), bool(h & HOTKEYF_ALT));
			OutputDebugString(buf);
		} 
	
	}break;

	case WM_CREATE:
	{
		//创建热键控件
		HWND  hHotkey = CreateWindow(HOTKEY_CLASS,L"XXX",
			WS_CHILD | WS_VISIBLE, 30, 30, 200, 30, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);

		//设置组合键的内容(CTRL+ALT+A)
		SendMessage(hHotkey, HKM_SETHOTKEY, MAKEWORD('A', HOTKEYF_ALT| HOTKEYF_CONTROL), 0);

		//获取组合键的内容
		WORD  key=SendMessage(hHotkey, HKM_GETHOTKEY, 0, 0);
		BYTE  l = LOBYTE(LOWORD(key));//字母等
		BYTE  h =HIBYTE(LOWORD(key));//CTRL | ALT |SHIFT 

		TCHAR  buf[64] = {0};
		wsprintf(buf, L"%c  +   %d  +  %d\n", l,   bool( h & HOTKEYF_CONTROL), bool(h & HOTKEYF_ALT));
	    OutputDebugString(buf);

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