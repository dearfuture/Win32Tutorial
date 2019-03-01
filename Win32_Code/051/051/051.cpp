#include<windows.h>


WNDPROC  oldProc = NULL;

//自定义的编辑框窗口处理函数
LRESULT  CALLBACK    MyEditWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		//处理了感兴趣的消息
	  case WM_LBUTTONDOWN:
		//MessageBox(hWnd, L"我们截获了编辑框的消息", L"提示", MB_OK); 
		  SetWindowText(hWnd, L"我们截获了编辑框的消息");
	 //  return 0; //表示我们自己处理了

	  case  WM_RBUTTONDOWN:
	 
		  break;
	}

	//其它的消息交给它原来的处理过程函数去处理，保证控件的正确性
	return  CallWindowProc(oldProc,hWnd, Msg,wParam,lParam);
}



 
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

		//创建系统预定义的控件（源代码不可修改）
		HWND hEdit = CreateWindow(L"EDIT",
			L"111",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 30,
			200, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		 
		//将控件的窗口过程处理函数改为自定义的，从而捕获控件消息
		oldProc=(WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, (LONG)MyEditWindowProc);

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