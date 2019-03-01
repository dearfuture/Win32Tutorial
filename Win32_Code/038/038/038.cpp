#include<windows.h>
#include<CommCtrl.h> 
#include"resource.h"   //包含图标资源ID
#pragma comment(lib, "Comctl32.lib") //加入lib文件

//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;


	case  WM_NOTIFY:
	{
		NMHDR  *pHDR = (NMHDR*)lParam;
		if ((pHDR->code == LVN_ITEMCHANGED) && (pHDR->idFrom == 111))
		{
			LPNMLISTVIEW	pnmv = (LPNMLISTVIEW)lParam;
			if (pnmv->uChanged == LVIF_STATE)//是不是选中状态改变了
			{
				if (pnmv->uNewState &  LVIS_SELECTED)
				{
					//根据索引pnmv->iItem获取文本 
					LVITEM  lv;
					TCHAR  buf[64] = { 0 };
					lv.iSubItem = 0;
					lv.pszText = buf; //向系统提供写入内存
					lv.cchTextMax = sizeof(buf);//buf的长度
					SendMessage(pHDR->hwndFrom, LVM_GETITEMTEXT, pnmv->iItem, (LPARAM)&lv);
					MessageBox(hWnd, buf, L"提示", MB_OK);
				}
			}

		}

	}break;

	case WM_CREATE:
	{
		//创建列表视图 LVS_SMALLICON 小图标视图 
		/*HWND  hListView = CreateWindow(WC_LISTVIEW, L"XXX",
			WS_CHILD | WS_VISIBLE | LVS_SMALLICON, 30, 30, 300, 300, hWnd, (HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);*/

	 //创建列表视图 LVS_LIST 列表视图 
		HWND  hListView = CreateWindow(WC_LISTVIEW, L"XXX",
			WS_CHILD | WS_VISIBLE | LVS_LIST, 30, 30, 300, 300, hWnd, (HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		//创建Image  Lists (小图标SM_CXSMICON)
		UINT  x = GetSystemMetrics(SM_CXSMICON);
		UINT  y = GetSystemMetrics(SM_CXSMICON);
		HIMAGELIST  hSmall = ImageList_Create(x, y, ILC_MASK, 3, 2);

		//把图标加入到 ImageLists去
		for (int i = 0; i < 3; ++i)
		{
			HICON  hIcon = LoadIcon(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDI_ICON1 + i));
			ImageList_AddIcon(hSmall, hIcon);
			DestroyIcon(hIcon);
		}

		//把image Lists与 listView 相关联 LVSIL_SMALL
		SendMessage(hListView, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)hSmall);

		//插入项目
		for (int i = 0; i < 3; ++i)
		{
			LVITEM  lv;
			lv.pszText = (i == 0) ? L"音乐" : ((i == 1) ? L"啤酒" : L"炸鸡");
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE; //哪些值有效的标记码
			lv.iItem = i;  //插入的位置
			lv.iImage = i;//图像的索引
			lv.state = (i == 2) ? LVIS_SELECTED : 0; //是否选中
			lv.iSubItem = 0;
			SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&lv);
		}

		//设置控件有焦点
		SetFocus(hListView);

		//设置文本颜色
		SendMessage(hListView, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(255, 0, 0));
		//设置背景颜色
		SendMessage(hListView, LVM_SETBKCOLOR, 0, (LPARAM)RGB(0, 255, 0));
		//设置文本背景颜色
		SendMessage(hListView, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(0, 0, 255));


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