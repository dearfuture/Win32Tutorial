#include<windows.h> 
#include"resource.h"  
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

		//��̬�ı��ؼ�
	 HWND  hStatic=	CreateWindow(L"Static", L"����һ����̬�ı�", WS_CHILD | WS_VISIBLE |WS_BORDER|SS_BITMAP|SS_NOTIFY,
			30, 30,200, 30, hWnd, (HMENU)111, pcs->hInstance, NULL);
	 //���Ĵ��ڱ���
	 SetWindowText(hWnd, L"�´��ڱ���");
	 //���ÿؼ����Ӵ��ڣ�����
	 SetWindowText(hStatic, L"���ĺ�����ݣ�");


	 //����λͼ
	HBITMAP  hBmp= LoadBitmap(pcs->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	
	//��ؼ�����STM_SETIMAGE��Ϣ���þ�̬�ؼ���λͼ
	SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);




		return 0;
	}


	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//�ؼ�ID
		WORD  code = HIWORD(wParam);//��Ϣ����
		HWND   hCtrl = (HWND)lParam;//���ھ��

		//�����ڽ��յ��ӿؼ�������Ϣ
		if (id == 111  &&  code ==  STN_CLICKED)
		{
			MessageBox(NULL, L"��̬�ı��������", L"��ʾ", MB_OK);
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