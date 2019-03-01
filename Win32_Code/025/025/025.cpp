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

		//创建组合框
		HWND   hComboBox=CreateWindow(L"comboBOX", L"XXX", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST|CBS_SORT,
			30, 30, 200, 100, hWnd, (HMENU)111, pcs->hInstance, NULL);
		
		//向组合框添加选项 
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"C音乐");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"A啤酒");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"B炸鸡");
		//插入选项
		SendMessage(hComboBox, CB_INSERTSTRING, 2, (LPARAM)L"编程");

		//选择某一项
		SendMessage(hComboBox, CB_SETCURSEL, 3,  0 );


		return 0;
	}

	 

	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//控件ID
		WORD  code = HIWORD(wParam);//消息类型
		HWND   hCtrl = (HWND)lParam;//窗口句柄

		 //父窗口接收到子控件发的消息
		if (id == 111 && code ==CBN_SELCHANGE)
		{
			//获取当前选择的索引
			int   index=SendMessage(hCtrl, CB_GETCURSEL, 0, 0);
			//获取索引对应的文本
			TCHAR  buf[64] = {0};
			SendMessage(hCtrl, CB_GETLBTEXT, index, (LPARAM)buf);
			MessageBox(hWnd, buf, L"提示", MB_OK);
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