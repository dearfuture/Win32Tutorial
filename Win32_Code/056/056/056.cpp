#include<windows.h> 


//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		//获取设备上下文句柄
		HDC   hdc = BeginPaint(hWnd, &ps);

		//改变文本的背景色
		SetBkColor(hdc, RGB(255, 0, 0));
		//设置文本背景模式 
		SetBkMode(hdc, TRANSPARENT);//透明

		//设置文本的颜色
		SetTextColor(hdc, RGB(255, 0, 0));


		//设置文本的参考点
		SetTextAlign(hdc, TA_TOP);

		//1.界面上画文本
		TextOut(hdc,250, 200, L"你好啊，这是画的文本！", lstrlen(L"你好啊，这是画的文本！"));

		//2.在矩形范围中画文本
		RECT  r = {250,400,300,500};
		Rectangle(hdc, r.left, r.top, r.right, r.bottom);
		DrawText(hdc, L"你好啊，这是画的文本！", lstrlen(L"你好啊，这是画的文本！")
			, &r,  DT_BOTTOM|DT_SINGLELINE);




		EndPaint(hWnd, &ps);
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
		WS_OVERLAPPEDWINDOW, 100, 100, 1000, 700, NULL, NULL, hInstance, NULL);

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