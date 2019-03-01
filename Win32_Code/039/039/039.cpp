#include<windows.h>
#include<CommCtrl.h> 
#include"resource.h"   //����ͼ����ԴID
#pragma comment(lib, "Comctl32.lib") //����lib�ļ�

//����ָ��ı�ؼ��ķ��
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  


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
					lv.iSubItem = 2;
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
		//�����б���ͼ LVS_REPORT ������ͼ 
		HWND  hListView = CreateWindow(WC_LISTVIEW, L"XXX",
			WS_CHILD | WS_VISIBLE | LVS_REPORT, 30, 30, 300, 300, hWnd, (HMENU)111,
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


		//���ÿؼ�����չ��ʽ
		SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0,			(LPARAM)(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES));


		//������
		for (int i = 0; i < 3; ++i)
		{
			LVCOLUMN   lvc;
			lvc.pszText = (i == 0 ? L"����" : (i == 1 ? L"�Ա�" : L"����"));
			lvc.mask= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;			lvc.iSubItem = 0; //�ڼ���
			lvc.cx = 100;//�еĿ��
			lvc.fmt = (i == 0 ? LVCFMT_LEFT : LVCFMT_CENTER); //�ı����뷽ʽ

			SendMessage(hListView, LVM_INSERTCOLUMN, i , (LPARAM) &lvc   );
		}

		  
		//����һ������
		for (int i = 0; i < 3; ++i)
		{
			LVITEM  lv;
			lv.pszText = (i == 0) ? L"����" : ((i == 1) ? L"��" : L"13");
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE; //��Щֵ��Ч�ı����
			lv.iItem = 0;  //�����0��
			lv.iImage = i;//ͼ�������
			lv.state = (i == 2) ? LVIS_SELECTED : 0; //�Ƿ�ѡ��
			lv.iSubItem = i; //�ڼ��е��ı�
			//��ʾ����һ��
			if(i==0) SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&lv); 
			//��ʾ����ڼ��е��ı�
			else  SendMessage(hListView, LVM_SETITEMTEXT, 0, (LPARAM)&lv); 
		}

		//���ÿؼ��н���
		SetFocus(hListView);

		//�����ı���ɫ
		//SendMessage(hListView, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(255, 0, 0));
		//���ñ�����ɫ
		//SendMessage(hListView, LVM_SETBKCOLOR, 0, (LPARAM)RGB(0, 255, 0));
		//�����ı�������ɫ
		//SendMessage(hListView, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(0, 0, 255));


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