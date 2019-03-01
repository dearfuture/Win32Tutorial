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

	 case WM_CREATE:
	  {  

		  HWND hBtn = CreateWindow(WC_BUTTON,
			  L"按钮控件",
			  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			  30, 30,
			  100, 30,
			  hWnd,
			  (HMENU)111,
			  ((LPCREATESTRUCT)lParam)->hInstance,
			  NULL); 

		  HWND hEdit = CreateWindow(WC_EDIT,
			  L"123",
			  WS_CHILD | WS_VISIBLE | WS_BORDER,
			  30, 100,
			  200, 30,
			  hWnd,
			  (HMENU)222,
			  ((LPCREATESTRUCT)lParam)->hInstance,
			  NULL);

		  //通过控件ID获取句柄
		  HWND   h1= GetDlgItem(hWnd, 111);
		  bool  b = (h1 == hBtn);
		  HWND   h2 = GetDlgItem(hWnd, 222);
		  bool  b2 = (h2 == hEdit);

		  //获取控件的文本或标题
		  TCHAR  buf[64] = {0};
		  GetDlgItemText(hWnd, 111, buf, 64);
		  GetDlgItemText(hWnd, 222, buf, 64);
		  OutputDebugString(buf);

		  //获取控件文本并转化为整数
		  BOOL  bSuccess = FALSE;
		  int  v1=GetDlgItemInt(hWnd, 111, &bSuccess, true);
		  bSuccess = FALSE;
		  int  v2 = GetDlgItemInt(hWnd, 222, &bSuccess, true);
		   
		  //根据控件句柄获取ID
		  UINT  id1= GetDlgCtrlID(hBtn);
		  UINT  id2 = GetDlgCtrlID(hEdit);
		  UINT  id3 = GetDlgCtrlID(hWnd); //顶层窗口没有ID，返回0
		  id3 = id3;

		  //根据ID设置控件的文本或者标题
		  SetDlgItemText(hWnd, 111, L"你好啊！");
		  SetDlgItemText(hWnd, 222, L"456");

		  //根据ID将整数设置控件的文本或者标题
		  SetDlgItemInt(hWnd, 111, 666, true);
		  SetDlgItemInt(hWnd, 222, -888, true);

		  //根据控件ID向控件发送指定的消息
		  SendDlgItemMessage(hWnd, 222, WM_SETTEXT, 0,(LPARAM) L"这是消息！");
		   

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