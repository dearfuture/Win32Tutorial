#include<windows.h>
#include<CommCtrl.h>  
//使用Unicode版本必须加入manifest强制让应用程序加载common Control 6.0
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
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
		 
	case  WM_LBUTTONDOWN:
		{
			//获取当前活动的窗口
			HWND  hActive = GetActiveWindow();
			TCHAR buf[64] = { 0 };
			GetWindowText(hActive, buf, 64);
			MessageBox(NULL, buf, L"提示", MB_OK);

		}break;


	case WM_CREATE:
	{

		HWND hEdit1 = CreateWindow(WC_EDIT,
			L"编辑控件",
			WS_CHILD | WS_VISIBLE ,
			30, 30,
			100, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		HWND hEdit2 = CreateWindow(WC_EDIT,
			L"123",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 100,
			200, 30,
			hWnd,
			(HMENU)222,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		//根据窗口句柄禁用或启用窗口
		EnableWindow(hEdit1,false);
		EnableWindow(hEdit1, true);
		//EnableWindow(hWnd, false);//禁用父窗口


		//根据窗口类名、窗口标题查找顶层窗口(父窗口)
		HWND   h1 = FindWindow(L"MrHuang", NULL);
		bool  b1 = (h1 == hWnd);
		HWND   h2 = FindWindow(NULL, L"第一个窗口程序");
		bool  b2 = (h2 == hWnd);
		HWND   h3 = FindWindow(L"Mr", L"第一个窗口程序");
		bool  b3 = (h3 == hWnd);
		HWND   h4 = FindWindow(WC_EDIT,  NULL);//不能用于子窗口与控件
		bool  b4 = (h4 == hEdit2);
	 
		HWND   hTxt= FindWindow(NULL, L"新建文本文档.txt - 记事本");//查找记事本
		SendMessage(hTxt, WM_SETTEXT, 0,(LPARAM)L"篡改你的标题");

		//根据窗口句柄设置窗口标题
		//SetWindowText(hWnd, L"改掉标题");
		//SetWindowText(hEdit1, L"改掉标题");

		//根据窗口句柄获取窗口标题
		TCHAR buf[64] = {0};
		GetWindowText(hEdit2, buf, 64);
		OutputDebugString(buf);

		//获取窗口的矩形区域
		RECT  r;
		GetWindowRect(hWnd, &r);
		 
		//获取窗口的客户区域
		RECT  r2;
		GetClientRect(hWnd, &r2);

      //设置控件具有焦点
		SetFocus(hEdit1);

		//根据窗口句柄移动窗口
		//MoveWindow(hWnd, 0, 0, 600, 600, true);//移动父窗口
		//MoveWindow(hEdit2, 300, 300, 100, 100, true);//移动控件

		//获取当前活动的窗口
		HWND  hActive = GetActiveWindow();
		bool  b8 = (hActive == hWnd);
		 

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


	//创建窗口(返回之前发送WM_CREATE)
	HWND    hWnd2 = CreateWindow(L"MrHuang", L"第二个窗口程序",
		WS_OVERLAPPEDWINDOW, 500, 100, 400, 400, NULL, NULL, hInstance, NULL);

	//显示窗口
	ShowWindow(hWnd2, nShowCmd);
	//更新窗口(发送WM_PAINT)
	UpdateWindow(hWnd2);



	//消息循环（收到WM_QUIT消息退出）
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//翻译消息
		DispatchMessage(&msg);//分发消息到窗口过程
	}
}