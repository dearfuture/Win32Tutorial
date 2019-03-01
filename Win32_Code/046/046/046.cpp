#include<windows.h>
#include<CommCtrl.h>  
//#include"resource.h"
//使用Unicode版本必须加入manifest强制让应用程序加载common Control 6.0
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
//#pragma comment(lib,"Comctl32.lib")


//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;

	case  WM_SIZE://窗口尺寸改变时
	{
	  //获取状态栏的句柄
		HWND   hStatus=GetDlgItem(hWnd, 111);
		SendMessage(hStatus, WM_SIZE, 0, 0);//通知状态栏重绘
	}break;

	case  WM_COMMAND:
	{
		WORD  CtrlID = LOWORD(wParam);
		WORD   code = HIWORD(wParam);
		if (code == 0)
		{

		}

	}break;

	case  WM_NOTIFY:
	{
		NMHDR  * pHDR = (NMHDR  *)lParam;
		if (pHDR->code == NM_CLICK  &&  pHDR->idFrom==111)
		{ 
			MessageBox(hWnd, L"状态栏被点击！", L"提示", MB_OK);
		}

	}break;

	case WM_CREATE:
	{
		//创建状态栏控件
		HWND  hStatusBar = CreateWindow(STATUSCLASSNAME, NULL,
			WS_CHILD|WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);
		 
		//设置状态栏的文本
		SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"状态栏文本");

		//将状态栏分区域
		int  arr[3] = { 100,200,-1}; //代表起始x坐标
		SendMessage(hStatusBar, SB_SETPARTS, 3, (LPARAM)arr );

		//设置其他区域状态栏的文本
		SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)L"第二区域");
		SendMessage(hStatusBar, SB_SETTEXT, 2, (LPARAM)L"第三区域");


		//设置状态栏的高度
		SendMessage(hStatusBar, SB_SETMINHEIGHT, 50,  0);
		SendMessage(hStatusBar, WM_SIZE, 0, 0); //让状态栏重绘



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