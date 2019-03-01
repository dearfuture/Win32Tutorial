#include<windows.h>
#include<CommCtrl.h> 
#include"resource.h" 
//ʹ��Unicode�汾�������manifestǿ����Ӧ�ó������common Control 6.0
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#pragma comment(lib,"Comctl32.lib")


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);//����ʹGetMessage����0    
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
					//�������ڵ�����ȡ�ı�
					TVITEM tv;
					tv.mask = TVIF_TEXT;
					TCHAR  buf[64] = {0};
					tv.pszText = buf;
					tv.cchTextMax = 64;
					tv.hItem = itemNew.hItem; //��������ڵ���ı�
					SendMessage(pHDR->hwndFrom, TVM_GETITEM, 0, (LPARAM)&tv);
					MessageBox(hWnd, tv.pszText, L"��ʾ", MB_OK);
				} 
			}
		}break;

		case WM_CREATE:
		{
			//�������ؼ�
			HWND  hTreeView = CreateWindow(WC_TREEVIEW, NULL,
				WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT, 30, 30, 300, 300,
				hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);
			//����ͼ���б�
			HIMAGELIST  hImageList = ImageList_Create(16, 16, ILC_MASK, 3, 1);
			//���ͼ�굽ImageLists
			for (int i = 0; i < 3; ++i)
			{
				HICON  hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1 + i));
				ImageList_AddIcon(hImageList, hIcon);
				DestroyIcon(hIcon);
			}
			//�������ؼ���ͼ���б�
			SendMessage(hTreeView, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)hImageList);

			//��������ڵ㵽�ؼ�
			TVINSERTSTRUCT  tvs;
			tvs.hInsertAfter = TVI_ROOT;
			tvs.hParent = NULL;
			
			TVITEM  tv;
			tv.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
			tv.pszText = L"���ڵ�"; 
			tv.iImage = 2;
			tv.iSelectedImage =2;
			tvs.item = tv; 

			HTREEITEM  hRoot=(HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM,  0, (LPARAM)&tvs);

			//�����ӽڵ�
			TVINSERTSTRUCT  tvs2;
			tvs2.hInsertAfter = TVI_LAST;
			tvs2.hParent = hRoot;

			TVITEM  tv2;
			tv2.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tv2.pszText = L"�ӽڵ�1";
			tv2.iImage = 1;
			tv2.iSelectedImage =1;
			tvs2.item = tv2;

			HTREEITEM  hChild1 = (HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvs2);


			//�����ӽڵ�
			TVINSERTSTRUCT  tvs3;
			tvs3.hInsertAfter = TVI_LAST;
			tvs3.hParent = hRoot;

			TVITEM  tv3;
			tv3.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tv3.pszText = L"�ӽڵ�2";
			tv3.iImage = 0;
			tv3.iSelectedImage = 0;
			tvs3.item = tv3;

			HTREEITEM  hChild2 = (HTREEITEM)SendMessage(hTreeView, TVM_INSERTITEM, 0, (LPARAM)&tvs3);



			//չ�����ڵ�
			SendMessage(hTreeView, TVM_EXPAND, TVE_EXPAND, (LPARAM)hRoot);

			//ѡ��ڵ�
	     SendMessage(hTreeView, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hChild1);

		 //�����ؼ��н���
		 SetFocus(hTreeView);

		}break;
	
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}


int  WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE  hPrevInstance,
	LPSTR lpCmdLine, int  nShowCmd)
{

	//1.ע�ᴰ����
	WNDCLASS  wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));//����ɫ
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);//���
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//ͼ��
												//wnd.lpfnWndProc = DefWindowProc;//Ĭ�ϴ��ڹ��̺��������ڴ�����Ϣ
	wnd.lpfnWndProc = MyWindowProc;//�Զ���Ĵ��ڹ��̺���
	wnd.lpszClassName = L"MrHuang";//��������
	wnd.lpszMenuName = NULL;//�˵���Դ����
	wnd.style = CS_HREDRAW | CS_DBLCLKS;//�����ࡢ��ʽ
	wnd.hInstance = hInstance;//ʵ�����
	RegisterClass(&wnd);

	//��������(����֮ǰ����WM_CREATE)
	HWND    hWnd = CreateWindow(L"MrHuang", L"��һ�����ڳ���",
		WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);

	//��ʾ����
	ShowWindow(hWnd, nShowCmd);
	//���´���(����WM_PAINT)
	UpdateWindow(hWnd);


	//��Ϣѭ�����յ�WM_QUIT��Ϣ�˳���
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//������Ϣ
		DispatchMessage(&msg);//�ַ���Ϣ�����ڹ���
	}
}