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

		//�����б��ؼ�
		HWND   hListBox=CreateWindow(L"listBOX", L"XXX", WS_CHILD | WS_VISIBLE|LBS_SORT|LBS_NOTIFY,
			30, 30, 200, 100, hWnd, (HMENU)111, GetModuleHandle(NULL),  NULL);
 
		//��ĩβ���ѡ��
		SendMessage(hListBox, LB_ADDSTRING, 0,(LPARAM) L"B����");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"Aơ��");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"Cơ��");
		//�����ַ���
		SendMessage(hListBox, LB_INSERTSTRING, 1, (LPARAM)L"ը��");

		//ѡ������һ��,ѡ������Ϊ2�ģ���ѡģʽ����Ч
		SendMessage(hListBox, LB_SETCURSEL, 2, 0 );

		return 0;
	}

	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//�ؼ�ID
		WORD  code = HIWORD(wParam);//��Ϣ����
		HWND   hCtrl = (HWND)lParam;//���ھ��

		 //�����ڽ��յ��ӿؼ�������Ϣ
		if (id == 111 && code == LBN_SELCHANGE)//����ʱ��ָ��LBS_NOTIFY��ʽ
		{
			// ��ȡ��ǰѡ�������
			int  index=SendMessage(hCtrl, LB_GETCURSEL, 0,0);
			
			//��ȡ������Ӧ���ַ��� 
			TCHAR  buf[64] = { 0 };
			SendMessage(hCtrl, LB_GETTEXT, index, (LPARAM)buf); 
			MessageBox(NULL, buf, L"��ʾ", MB_OK);
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