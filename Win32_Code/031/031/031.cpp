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

	case WM_CREATE:
	{  
		//创建刻度条控件
		HWND   hTackbar = CreateWindow(TRACKBAR_CLASS, L"XXX",
			WS_CHILD | WS_VISIBLE|  TBS_TOP|TBS_AUTOTICKS|TBS_ENABLESELRANGE, 30, 30, 200, 70, hWnd, (HMENU)111,
			GetModuleHandle(NULL), NULL);

		//设置测量条的范围
		SendMessage(hTackbar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10));

		//设置测量条的滑块位置
		SendMessage(hTackbar, TBM_SETPOS, TRUE,  5 );
		 
		//设置滑块的选择区域
		SendMessage(hTackbar, TBM_SETSEL, TRUE,   MAKELPARAM(1,3));


	}break;

	case  WM_HSCROLL:
	{
		WORD  code = LOWORD(wParam);//指示用户的滚动行为
		WORD  value = HIWORD(wParam);//仅当code是TB_THUMBPOSITION或TB_THUMBTRACK ，HIWORD(wParam)指定在滚动框的当前位置，否则忽略！
		HWND   hCtrl =(HWND) lParam;//控件句柄
  
/*  code的值：
#define TB_LINEUP               0
#define TB_LINEDOWN             1
#define TB_PAGEUP               2
#define TB_PAGEDOWN             3
#define TB_THUMBPOSITION        4
#define TB_THUMBTRACK           5
#define TB_TOP                  6
#define TB_BOTTOM               7
#define TB_ENDTRACK             8
		*/

		UINT  v = SendMessage(hCtrl, TBM_GETPOS, 0, 0);

		TCHAR  buf[64] = {0};
		wsprintf(buf, L"当前位置: %d   LOWORD: %d   HIWORD: %d\n" ,  v, code ,value);
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