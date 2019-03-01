#include<windows.h>
#include<CommCtrl.h>  
#include"resource.h"
//使用Unicode版本必须加入manifest强制让应用程序加载common Control 6.0
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#pragma comment(lib,"Comctl32.lib")


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
		if(code==0)
		{
			TCHAR  buf[64];
			wsprintf(buf, L"ID %d 按钮被点击！", CtrlID);
			MessageBox(hWnd, buf, L"提示", MB_OK);
		}

	}break;

	case  WM_NOTIFY:
	{
		NMHDR  * pHDR = (NMHDR  *)lParam;
		if (pHDR->code == PGN_CALCSIZE)
		{ 
			//LPNMPGCALCSIZE   pNM = (LPNMPGCALCSIZE)lParam;
		 
		} 


	}break;

	case WM_CREATE:
	{
		//创建工具条控件
		HWND  hToolBar = CreateWindow(TOOLBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE, 0,0, 0, 0, hWnd, (HMENU)111,
			GetModuleHandle(NULL), NULL);

		//创建图像列表
		HIMAGELIST  hImageList = ImageList_Create(32, 32,  //单个位图的尺寸 
			ILC_COLOR32 | ILC_MASK /*确保透明背景*/, 3, 1);

		for (int i = 0; i< 3; i++)
		{
			HICON  hIcon = LoadIcon(GetModuleHandle(NULL),
				MAKEINTRESOURCE(IDI_ICON1 + i));
			ImageList_AddIcon(hImageList, hIcon);
			DestroyIcon(hIcon);
		}
		 
		//设置工具条的图片列表 
		SendMessage(hToolBar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);

		//添加一些按钮到工具条上去

		TBBUTTON  btn1 , btn2; 
		btn1.fsState = TBSTATE_ENABLED;
		btn1.iString = (INT_PTR)L"按钮1";
		btn1.fsStyle = TBSTYLE_BUTTON;
		btn1.idCommand = 2000;
		btn1.iBitmap = 1;

		btn2.iString = (INT_PTR)L"按钮2";
		btn2.fsState = TBSTATE_ENABLED;
		btn2.fsStyle = TBSTYLE_BUTTON;
		btn2.idCommand = 3000;
		btn2.iBitmap=2;

		TBBUTTON arr[2] = { btn1,btn2 };
		SendMessage(hToolBar, TB_ADDBUTTONS, 2, (LPARAM)&arr);

		//自动调整工具条的大小并显示
	   SendMessage(hToolBar, TB_AUTOSIZE, 0, 0);
	   ShowWindow(hToolBar, true);

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