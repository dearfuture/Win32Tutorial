#include<windows.h>
#include<CommCtrl.h> 
#include"resource.h" 
//使用Unicode版本必须加入manifest强制让应用程序加载common Control 6.0
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
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
		}break;

		case  WM_NOTIFY:
		{
			NMHDR  * pHDR = (NMHDR  *)lParam;
			if (pHDR->code == TVN_SELCHANGED)
			{
				LPNMTREEVIEW  pnmtv = (LPNMTREEVIEW)lParam;
				TVITEM  &itemNew = pnmtv->itemNew;
				if (itemNew.state  &  TVIS_SELECTED)
				{
					//根据树节点句柄获取文本
					TVITEM tv;
					tv.mask = TVIF_TEXT;
					TCHAR  buf[64] = {0};
					tv.pszText = buf;
					tv.cchTextMax = 64;
					tv.hItem = itemNew.hItem; //查找这个节点的文本
					SendMessage(pHDR->hwndFrom, TVM_GETITEM, 0, (LPARAM)&tv);
					MessageBox(hWnd, tv.pszText, L"提示", MB_OK);
				} 
			}
		}break;

		case WM_CREATE:
		{
			//创建树控件
			HWND  hTreeView = CreateWindow(WC_TREEVIEW, NULL,
				WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT, 30, 30, 300, 300,
				hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);
			//创建图标列表
			HIMAGELIST  hImageList = ImageList_Create(16, 16, ILC_MASK, 3, 1);
			//添加图标到ImageLists
			for (int i = 0; i < 3; ++i)
			{
				HICON  hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1 + i));
				ImageList_AddIcon(hImageList, hIcon);
				DestroyIcon(hIcon);
			}
			//设置树控件的图像列表
			SendMessage(hTreeView, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)hImageList);

			//添加树根节点到控件
			TVINSERTSTRUCT  tvs;
			tvs.hInsertAfter = TVI_ROOT;
			tvs.hParent = NULL;
			
			TVITEM  tv;
			tv.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
			tv.pszText = L"根节点"; 
			tv.iImage = 2;
			tv.iSelectedImage =2;
			tvs.item = tv; 

			HTREEITEM  hRoot=(HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM,  0, (LPARAM)&tvs);

			//插入子节点
			TVINSERTSTRUCT  tvs2;
			tvs2.hInsertAfter = TVI_LAST;
			tvs2.hParent = hRoot;

			TVITEM  tv2;
			tv2.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tv2.pszText = L"子节点1";
			tv2.iImage = 1;
			tv2.iSelectedImage =1;
			tvs2.item = tv2;

			HTREEITEM  hChild1 = (HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvs2);


			//插入子节点
			TVINSERTSTRUCT  tvs3;
			tvs3.hInsertAfter = TVI_LAST;
			tvs3.hParent = hRoot;

			TVITEM  tv3;
			tv3.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tv3.pszText = L"子节点2";
			tv3.iImage = 0;
			tv3.iSelectedImage = 0;
			tvs3.item = tv3;

			HTREEITEM  hChild2 = (HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvs3);



			//展开树节点
			SendMessage(hTreeView, TVM_EXPAND, TVE_EXPAND, (LPARAM)hRoot);

			//选择节点
	     SendMessage(hTreeView, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hChild1);

		 //让树控件有焦点
		 SetFocus(hTreeView);

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