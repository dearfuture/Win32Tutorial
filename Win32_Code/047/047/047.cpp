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
		if (pHDR->code == RBN_CHILDSIZE)
		{
			LPNMREBARCHILDSIZE  pNM = (LPNMREBARCHILDSIZE)lParam;
			RECT  rcBand= pNM->rcBand;
			RECT  rcChild = pNM->rcChild; 
			TCHAR  buf[64] = { 0 };
			wsprintf(buf, L" %drcBand  %d ,%d,%d ,%d\n", pNM->wID,rcBand.left, rcBand.top, rcBand.right, rcBand.bottom);
			OutputDebugString(buf);


		}

	}break;

	case WM_CREATE:
	{
		//创建Rebar控件
		HWND  hRebar = CreateWindow(REBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | RBS_VARHEIGHT,
			0, 0, 0, 0, hWnd, NULL, GetModuleHandle(NULL), NULL);


		//子控件
		HWND hBtn = CreateWindow(WC_BUTTON,
			L"按钮控件",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0,
			0, 0,
			hRebar, //父窗口是Rebar
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);


		HWND hEdit = CreateWindow(WC_EDIT,
			L"编辑控件",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			0, 0,
			0, 0,
			hRebar, //父窗口是Rebar
			(HMENU)222,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		//创建带区
		REBARBANDINFO  rb;
		rb.cbSize = sizeof(REBARBANDINFO);
		rb.lpText = L"控件条1";
		rb.fMask = RBBIM_ID |RBBIM_TEXT|RBBIM_STYLE |RBBIM_CHILDSIZE| RBBIM_CHILD;
		rb.fStyle = RBBS_GRIPPERALWAYS;
		rb.cxMinChild = 100;
		rb.cyMinChild = 30;
		rb.hwndChild = hBtn; 
		rb.wID = 1000;
		SendMessage(hRebar, RB_INSERTBAND, 0, (LPARAM)&rb);


		//创建带区2
		REBARBANDINFO  rb2;
		rb2.cbSize = sizeof(REBARBANDINFO);
		rb2.lpText = L"控件条2";
		rb2.fMask = RBBIM_ID | RBBIM_TEXT | RBBIM_STYLE | RBBIM_CHILDSIZE | RBBIM_CHILD;
		rb2.fStyle = RBBS_GRIPPERALWAYS;
		rb2.cxMinChild = 100;
		rb2.cyMinChild =30;
		rb2.hwndChild = hEdit;
		rb2.wID = 2000;
		SendMessage(hRebar, RB_INSERTBAND, -1, (LPARAM)&rb2);


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