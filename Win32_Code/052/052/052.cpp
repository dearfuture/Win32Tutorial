#include<windows.h>
#include<CommCtrl.h> 


WNDPROC  oldProc = NULL;

LRESULT CALLBACK  MyEditWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// 点击鼠标左键，显示一个消息框。 
	case WM_LBUTTONDOWN:
	{
		//MessageBox(0, L"我拦截了左键的行为", L"提示", MB_OK);
		SetWindowText(hWnd, L"我拦截了编辑框左键的行为");
		//return 0; //自己处理消息，就必须返回0。
	} break;

	}
	return    CallWindowProc(oldProc, hWnd, msg, wParam, lParam);
}



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

		//先获取系统控件的WNDCLASS信息
		WNDCLASS  wc;
		GetClassInfo(NULL, WC_EDIT, &wc); 
		oldProc = wc.lpfnWndProc;//保存系统的窗口处理函数
		wc.lpfnWndProc = MyEditWndProc;//改为自定义的窗口处理函数
		bool  ret=RegisterClass(&wc); //重新注册窗口类，实现全局的生效

		//备注：也可以改为自己的窗口类名，后续创建的时候用自己的窗口类名就可以创建编辑框

		//系统预定义的控件，无法修改
		HWND hEdit = CreateWindow(WC_EDIT,
			L"111",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 30,
			200, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL); 


		//系统预定义的控件，无法修改
		HWND hEdit2 = CreateWindow(WC_EDIT,
			L"222",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 100,
			200, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		 

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