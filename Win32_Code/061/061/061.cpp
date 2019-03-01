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

	case WM_RBUTTONDOWN:
	{
	    //创建弹出菜单
		HMENU  hPop=CreatePopupMenu();
		AppendMenu(hPop, MF_STRING, 111, L"新建");
		AppendMenu(hPop, MF_STRING, 222, L"打开");

		//转换坐标
		POINT pt = { LOWORD(lParam)  ,HIWORD(lParam) }; //自己窗口的客户区
		ClientToScreen(hWnd,&pt);

		//在指定位置弹出菜单(这里的x，y是相对于屏幕左上角的坐标)
		TrackPopupMenu(hPop, TPM_CENTERALIGN|TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);

		//释放菜单资源
		DestroyMenu(hPop);


	}break;

	case WM_COMMAND:
	{
		//菜单ID
		WORD  menuId = LOWORD(wParam);
		switch (menuId)
		{
		case 222:
			MessageBox(hWnd, L"打开菜单点击", L"提示", MB_OK);
			break;
		case 111:
			MessageBox(hWnd, L"新建菜单点击", L"提示", MB_OK);
			break; 
		}

	}  break;

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