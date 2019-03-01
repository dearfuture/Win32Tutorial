#include<windows.h> 
#include"resource.h"

HBRUSH  bsh=NULL;

//自定义的对话框过程
INT_PTR  CALLBACK    MyDlgProc(HWND hDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case  WM_INITDIALOG://在对话框显示之前立即发送
	{

		HWND hEdit = CreateWindow(L"EdiT",
			L"这是一个编辑框控件哈哈哈",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_NOHIDESEL,
			30, 100, 200, 100, hDlg, (HMENU)1111,
			GetModuleHandle(NULL), NULL);

		return  TRUE;//处理了消息
	}

	case  WM_CTLCOLORDLG :  //回忆前面学习的WM_CTLCOLORBTN
	{
		//创建画刷
	    bsh=  CreateSolidBrush(RGB(255, 0, 0));
		return  (INT_PTR)bsh;
	}


	case  WM_COMMAND://菜单点击，按钮点击的消息
	{
		switch ( LOWORD(wParam))
		{
		case IDOK:
			//销毁对话框
			EndDialog(hDlg, 666 ); //这里的666将作为DialogBox的返回值
			DeleteObject(bsh);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 999);
			DeleteObject(bsh);
			break;
		}

		return  TRUE;
	}
	 
	}
		
	return FALSE;//没处理此消息
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
		 
	case WM_LBUTTONDOWN:
	{
		//根据对话框资源创建模态对话框 
		int ret= DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDlgProc);
		ret = ret; 
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