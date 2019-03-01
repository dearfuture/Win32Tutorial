#include<windows.h>
#include<stdio.h> 
#include<Richedit.h>//富文本编辑控件的头文件
 
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
		HWND  hCtrl = (HWND)lParam;
		if (CtrlID == 111)
		{
			WORD  code= HIWORD(wParam);
			if (code == EN_CHANGE)
			{
				TCHAR buf[64];
				GetWindowText(hCtrl, buf, 64);
				MessageBox(NULL, buf,L"提示",MB_OK);
			}
		}


	}break;

	case  WM_NOTIFY:
	{
		//先看公共头部
		NMHDR *pHDR = (NMHDR *)lParam;
		if (pHDR->code == EN_SELCHANGE)
		{
			SELCHANGE  * pSC= (SELCHANGE *)lParam;
			TCHAR   buf[64];
			wsprintf(buf, L"选择文本索引%d - %d\n", pSC->chrg.cpMin, pSC->chrg.cpMax);
			OutputDebugString(buf);
		} 

	}break;

	case WM_CREATE:
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		
		//必须加载动态库
		LoadLibrary(L"Msftedit.dll");

		HWND  hRichEdit=CreateWindow(MSFTEDIT_CLASS, L"这是一个富文本编辑控件！！！",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE|ES_AUTOVSCROLL, 30, 30, 200, 200, hWnd, (HMENU)111, pcs->hInstance, NULL);

		//选中索引2-7的文本
		SendMessage(hRichEdit, EM_SETSEL, 2, 7);
		//显示选择背景色
		SendMessage(hRichEdit, EM_HIDESELECTION,0 , 0);

		//先获取默认的字符格式
		CHARFORMAT   cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT));
		cf.cbSize = sizeof(CHARFORMAT);
		SendMessage(hRichEdit, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cf);

		//让选择的文字加粗
		cf.dwMask |= CFM_BOLD;
		cf.dwEffects |= CFE_BOLD;

		//设置下划线
		cf.dwMask |= CFM_UNDERLINE;
		cf.dwEffects |= CFE_UNDERLINE;

		//设置字体大小
		cf.dwMask |= CFM_SIZE;
		cf.yHeight =20*20;

		//设置字体
		cf.dwMask |= CFM_FACE;
		wcscpy(cf.szFaceName ,  L"楷体");

		//设置字体颜色
		cf.dwMask |= CFM_COLOR;
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		cf.crTextColor = RGB(255, 0, 0);

		//设置选择字符的格式
		SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

		//取消选择
		SendMessage(hRichEdit, EM_SETSEL, -1, -1);

		//设置富文本编辑框的背景色
		SendMessage(hRichEdit, EM_SETBKGNDCOLOR, 0, (LPARAM)  RGB(0,255,0));

		//发送控件内容改变事件、选择改变事件掩码
		SendMessage(hRichEdit, EM_SETEVENTMASK, 0, (LPARAM)ENM_CHANGE|  ENM_SELCHANGE);


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