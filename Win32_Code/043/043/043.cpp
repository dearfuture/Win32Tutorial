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
	case  WM_COMMAND:
	{
		WORD  CtrlID = LOWORD(wParam);
		WORD   code = HIWORD(wParam);
	}break;

	case  WM_NOTIFY:
	{
		NMHDR  * pHDR = (NMHDR  *)lParam;
		if (pHDR->code == PGN_CALCSIZE)
		{
			//设置包含窗口的大小
			LPNMPGCALCSIZE   pNM = (LPNMPGCALCSIZE)lParam;
			if (pNM->dwFlag == PGF_CALCWIDTH)//水平风格的的计算宽度，垂直的则需要计算高度
			{
				pNM->iWidth = 600;
				pNM->iHeight = 30;
			}
			return 0;
		}
		if (pHDR->code == PGN_SCROLL)
		{
			//通知一次滚动多少
			LPNMPGSCROLL   pNM = (LPNMPGSCROLL)lParam;
			pNM->iScroll = 500;  //修改滚动步长
		}


	}break;

	case WM_CREATE:
	{
		//创建分页控件
		HWND   hPage = CreateWindow(WC_PAGESCROLLER, NULL,
			WS_CHILD | WS_VISIBLE | PGS_HORZ, 30, 30, 200, 50, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);
		
		//创建一个内容比较长的按钮 
		HWND hBtn=CreateWindow(WC_BUTTON,  L"开始，这是一个标题很长很长很长很长很长很长很长很长很长很长的按钮，现在才结束！",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hPage/*父窗口是分页控件*/, (HMENU)222, GetModuleHandle(NULL), NULL);

		//设置分页控件的子窗口
		SendMessage(hPage, PGM_SETCHILD, 0, (LPARAM)hBtn);

		//设置按钮箭头的宽度
		SendMessage(hPage, PGM_SETBUTTONSIZE, 0, (LPARAM) 30);

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