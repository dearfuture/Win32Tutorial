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

		//创建编辑框控件
		HWND   hEdit = CreateWindow(L"ediT", L"这是一个编辑框", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL,
			30, 30, 200, 100, hWnd, (HMENU)111, pcs->hInstance, NULL);

		//向编辑框发送选择字符串的消息
		SendMessage(hEdit, EM_SETSEL, 2, 6);

		//剪切刚刚选择的文字
		//SendMessage(hEdit, WM_CUT, 0, 0); 

		//撤销
		//SendMessage(hEdit, EM_UNDO, 0, 0);

		return 0;
	}

	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//控件ID
		WORD  code = HIWORD(wParam);//消息类型
		HWND   hCtrl = (HWND)lParam;//窗口句柄

									//父窗口接收到子控件发的消息
		if (id == 111 && code == EN_CHANGE)
		{
			//MessageBox(NULL, L"编辑框的文本被改变！", L"提示", MB_OK);

			TCHAR  buf[64] = { 0 };
			GetWindowText(hCtrl, buf, sizeof(buf));
			MessageBox(NULL, buf, L"提示", MB_OK);
		}

	}break;

	case  WM_CTLCOLOREDIT:
	{
		HDC  hdc = (HDC)wParam;
		HWND   hCtrl = (HWND)lParam;
		//获取编辑框控件的ID
		UINT  CtrlID = GetWindowLong(hCtrl, GWL_ID);
		if (CtrlID == 111)
		{
			SetTextColor(hdc, RGB(255, 0, 0));//文字颜色
			SetBkMode(hdc,  TRANSPARENT);//文字背景色透明
		}  
		HBRUSH   hbr = CreateSolidBrush(RGB(255, 255, 0));
		return   (LRESULT)hbr;//控件的背景色
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