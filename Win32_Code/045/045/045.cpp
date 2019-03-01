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
		if (pHDR->code == TTN_SHOW)
		{ 
			//MessageBox(hWnd, L"提示框要出来了", L"提示" ,MB_OK);
			OutputDebugString(L"提示框要出来了\n");
		}
		 
	}break;

	case WM_CREATE:
	{
		//创建提示控件
		HWND  hTip = CreateWindow(TOOLTIPS_CLASS, NULL,
			WS_POPUP|TTS_BALLOON, 0, 0, 0, 0, hWnd, NULL/*传入NULL*/, GetModuleHandle(NULL), NULL);
		
		//像提示控件注册  窗口
		TOOLINFO  ti;
		ti.cbSize = sizeof(TOOLINFO);
		ti.hinst = GetModuleHandle(NULL);
		ti.hwnd = hWnd;  //指定在哪个窗口上显示tip
		ti.lpszText = L"这是一个提示控件，用于鼠标移上去之后告诉用户一些信息！";
		GetClientRect(hWnd, &ti.rect/*鼠标移到哪个区域 */); 
		ti.uFlags = TTF_SUBCLASS;
		ti.uId = (UINT_PTR)hTip; //tip的窗口句柄

		//注册需要tip的窗口
		SendMessage(hTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

		//设置tip窗口的宽度
		SendMessage(hTip, TTM_SETMAXTIPWIDTH, 0, (LPARAM)100);

		//设置tip的显示时间(毫秒)
		SendMessage(hTip, TTM_SETDELAYTIME, TTDT_AUTOPOP,  MAKELPARAM( 10*1000, 0 ));

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