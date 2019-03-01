#include<windows.h> 
#include<stdio.h>


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;

	case  WM_CREATE:
	{
		LPCREATESTRUCT   pcs = (LPCREATESTRUCT)lParam;

		//������Ͽ�
		HWND   hComboBox=CreateWindow(L"comboBOX", L"XXX", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST|CBS_SORT,
			30, 30, 200, 100, hWnd, (HMENU)111, pcs->hInstance, NULL);
		
		//����Ͽ����ѡ�� 
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"C����");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Aơ��");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)L"Bը��");
		//����ѡ��
		SendMessage(hComboBox, CB_INSERTSTRING, 2, (LPARAM)L"���");

		//ѡ��ĳһ��
		SendMessage(hComboBox, CB_SETCURSEL, 3,  0 );


		return 0;
	}

	 

	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//�ؼ�ID
		WORD  code = HIWORD(wParam);//��Ϣ����
		HWND   hCtrl = (HWND)lParam;//���ھ��

		 //�����ڽ��յ��ӿؼ�������Ϣ
		if (id == 111 && code ==CBN_SELCHANGE)
		{
			//��ȡ��ǰѡ�������
			int   index=SendMessage(hCtrl, CB_GETCURSEL, 0, 0);
			//��ȡ������Ӧ���ı�
			TCHAR  buf[64] = {0};
			SendMessage(hCtrl, CB_GETLBTEXT, index, (LPARAM)buf);
			MessageBox(hWnd, buf, L"��ʾ", MB_OK);
		}

	}break;





	default:
		break;
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
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);

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