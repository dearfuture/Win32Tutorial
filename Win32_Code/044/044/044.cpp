#include<windows.h>
#include<CommCtrl.h>  
#include"resource.h"
//ʹ��Unicode�汾�������manifestǿ����Ӧ�ó������common Control 6.0
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
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
		if(code==0)
		{
			TCHAR  buf[64];
			wsprintf(buf, L"ID %d ��ť�������", CtrlID);
			MessageBox(hWnd, buf, L"��ʾ", MB_OK);
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
		//�����������ؼ�
		HWND  hToolBar = CreateWindow(TOOLBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE, 0,0, 0, 0, hWnd, (HMENU)111,
			GetModuleHandle(NULL), NULL);

		//����ͼ���б�
		HIMAGELIST  hImageList = ImageList_Create(32, 32,  //����λͼ�ĳߴ� 
			ILC_COLOR32 | ILC_MASK /*ȷ��͸������*/, 3, 1);

		for (int i = 0; i< 3; i++)
		{
			HICON  hIcon = LoadIcon(GetModuleHandle(NULL),
				MAKEINTRESOURCE(IDI_ICON1 + i));
			ImageList_AddIcon(hImageList, hIcon);
			DestroyIcon(hIcon);
		}
		 
		//���ù�������ͼƬ�б� 
		SendMessage(hToolBar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);

		//���һЩ��ť����������ȥ

		TBBUTTON  btn1 , btn2; 
		btn1.fsState = TBSTATE_ENABLED;
		btn1.iString = (INT_PTR)L"��ť1";
		btn1.fsStyle = TBSTYLE_BUTTON;
		btn1.idCommand = 2000;
		btn1.iBitmap = 1;

		btn2.iString = (INT_PTR)L"��ť2";
		btn2.fsState = TBSTATE_ENABLED;
		btn2.fsStyle = TBSTYLE_BUTTON;
		btn2.idCommand = 3000;
		btn2.iBitmap=2;

		TBBUTTON arr[2] = { btn1,btn2 };
		SendMessage(hToolBar, TB_ADDBUTTONS, 2, (LPARAM)&arr);

		//�Զ������������Ĵ�С����ʾ
	   SendMessage(hToolBar, TB_AUTOSIZE, 0, 0);
	   ShowWindow(hToolBar, true);

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