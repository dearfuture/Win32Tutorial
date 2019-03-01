#include<windows.h>
#include<CommCtrl.h> 
#include"resource.h"   //����ͼ����ԴID
#pragma comment(lib, "Comctl32.lib") //����lib�ļ�

//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;


	case  WM_NOTIFY:
	{
		NMHDR  *pHDR = (NMHDR*)lParam;
		if ((pHDR->code == LVN_ITEMCHANGED) && (pHDR->idFrom == 111))
		{
			LPNMLISTVIEW	pnmv = (LPNMLISTVIEW)lParam;
			if (pnmv->uChanged == LVIF_STATE)//�ǲ���ѡ��״̬�ı���
			{
				if (pnmv->uNewState &  LVIS_SELECTED)
				{
					//��������pnmv->iItem��ȡ�ı� 
					LVITEM  lv;
					TCHAR  buf[64] = { 0 };
					lv.iSubItem = 0;
					lv.pszText = buf; //��ϵͳ�ṩд���ڴ�
					lv.cchTextMax = sizeof(buf);//buf�ĳ���
					SendMessage(pHDR->hwndFrom, LVM_GETITEMTEXT, pnmv->iItem, (LPARAM)&lv);
					MessageBox(hWnd, buf, L"��ʾ", MB_OK);
				}
			}

		}

	}break;

	case WM_CREATE:
	{
		//�����б���ͼ LVS_SMALLICON Сͼ����ͼ 
		/*HWND  hListView = CreateWindow(WC_LISTVIEW, L"XXX",
			WS_CHILD | WS_VISIBLE | LVS_SMALLICON, 30, 30, 300, 300, hWnd, (HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);*/

	 //�����б���ͼ LVS_LIST �б���ͼ 
		HWND  hListView = CreateWindow(WC_LISTVIEW, L"XXX",
			WS_CHILD | WS_VISIBLE | LVS_LIST, 30, 30, 300, 300, hWnd, (HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		//����Image  Lists (Сͼ��SM_CXSMICON)
		UINT  x = GetSystemMetrics(SM_CXSMICON);
		UINT  y = GetSystemMetrics(SM_CXSMICON);
		HIMAGELIST  hSmall = ImageList_Create(x, y, ILC_MASK, 3, 2);

		//��ͼ����뵽 ImageListsȥ
		for (int i = 0; i < 3; ++i)
		{
			HICON  hIcon = LoadIcon(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDI_ICON1 + i));
			ImageList_AddIcon(hSmall, hIcon);
			DestroyIcon(hIcon);
		}

		//��image Lists�� listView ����� LVSIL_SMALL
		SendMessage(hListView, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)hSmall);

		//������Ŀ
		for (int i = 0; i < 3; ++i)
		{
			LVITEM  lv;
			lv.pszText = (i == 0) ? L"����" : ((i == 1) ? L"ơ��" : L"ը��");
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE; //��Щֵ��Ч�ı����
			lv.iItem = i;  //�����λ��
			lv.iImage = i;//ͼ�������
			lv.state = (i == 2) ? LVIS_SELECTED : 0; //�Ƿ�ѡ��
			lv.iSubItem = 0;
			SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&lv);
		}

		//���ÿؼ��н���
		SetFocus(hListView);

		//�����ı���ɫ
		SendMessage(hListView, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(255, 0, 0));
		//���ñ�����ɫ
		SendMessage(hListView, LVM_SETBKCOLOR, 0, (LPARAM)RGB(0, 255, 0));
		//�����ı�������ɫ
		SendMessage(hListView, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(0, 0, 255));


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