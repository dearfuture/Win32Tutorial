#include<windows.h> 
#include<windowsx.h>  //Button_GetCheck的头文件
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

		//创建控件或者子窗口

		//普通按钮BS_PUSHBUTTON
		HWND  hBtn=CreateWindow(L"button", L"普通按钮", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON ,30, 30, 80, 30, hWnd,
			(HMENU)1000,//控件ID
			pcs->hInstance, NULL); 

		//单选按钮
		HWND  hBtn1 = CreateWindow(L"button", L"单选按钮", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 30, 70, 80, 30, hWnd,
			(HMENU)1001,//控件ID
			pcs->hInstance, NULL);

		//复选按钮
		HWND  hBtn2 = CreateWindow(L"button", L"复选按钮", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 110, 80, 30, hWnd,
			(HMENU)1002,//控件ID
			pcs->hInstance, NULL);


		return 0;
      }


	case   WM_COMMAND:
	{
	     WORD  id = LOWORD(wParam);
		 WORD  code= HIWORD(wParam);
		 HWND   hCtrl = (HWND)lParam;
		 if (id == 1000 &&  code ==  BN_CLICKED)
		 {
			 MessageBox(hWnd, L"普通按钮被单击！", L"提示",MB_OK); 
		 }
		 else if (id == 1001)
		 {
			 MessageBox(hWnd, L"单选按钮被单击！", L"提示", MB_OK);
 
			 if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_CHECKED)
			 {
				 MessageBox(hWnd, L"被选中！", L"提示", MB_OK); 
			 }
			 else  if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			 {
				 MessageBox(hWnd, L"没选中！", L"提示", MB_OK);
			 }
		 }
		 else if (id == 1002)
		 {
			 MessageBox(hWnd, L"复选按钮被单击！", L"提示", MB_OK);
/*
			 if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_CHECKED)
			 {
				 MessageBox(hWnd, L"被选中！", L"提示", MB_OK);
			 }
			 else  if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			 {
				 MessageBox(hWnd, L"没选中！", L"提示", MB_OK);
			 }
			 */
			  

			 //简写形式((int)(DWORD)SNDMSG((hwndCtl), BM_GETCHECK, 0L, 0L))
			 if (Button_GetCheck(hCtrl) == BST_CHECKED)
			 {
				 MessageBox(hWnd, L"被选中！", L"提示", MB_OK);
			 }
			 else  if (Button_GetCheck(hCtrl) == BST_UNCHECKED)
			 {
				 MessageBox(hWnd, L"没选中！", L"提示", MB_OK);
			 }
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