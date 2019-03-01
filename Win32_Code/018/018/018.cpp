#include<windows.h>  
#include<stdio.h>
#include"resource.h"

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

		//����λͼ��ť
		HWND   hBtn = CreateWindow(L"BuTtOn" /*�����ִ�Сд*/, 
			L"XXX", WS_CHILD | WS_VISIBLE | BS_BITMAP,//ָ��ΪͼƬ
			30, 30, 217, 46, hWnd, (HMENU)1000, pcs->hInstance, NULL);

		//LoadImage����λͼ
		//HBITMAP  hBmp=(HBITMAP)LoadImage(NULL, L"C:\\Users\\35497\\Desktop\\code\\016\\Debug\\btn1.bmp",
		//	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


		//����LoadBitmap����λͼ��Դ(������rc�ļ��ж���)
		HBITMAP  hBmp= LoadBitmap(pcs->hInstance, MAKEINTRESOURCE(IDB_BITMAP1) );

		//��ؼ�����BM_SETIMAGE��Ϣ���ð�ťͼƬ
		LRESULT  ret=SendMessage(hBtn, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmp);


		return 0;
	}


	case   WM_COMMAND:
	{
		WORD  id = LOWORD(wParam);
		WORD  code = HIWORD(wParam);
		HWND   hCtrl = (HWND)lParam;
		if (id == 1000 && code == BN_CLICKED)
		{
			MessageBox(hWnd, L"��ͨ��ť��������", L"��ʾ", MB_OK);
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
	  //����ϵͳ��꣬��һ������ΪNULL
	//wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	//������Դ�еĹ��
	wnd.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));


	 //����ϵͳͼ�꣬��һ������ΪNULL
	//wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	//������Դ�е�ͼ��
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));


	//wnd.lpfnWndProc = DefWindowProc;//Ĭ�ϴ��ڹ��̺��������ڴ�����Ϣ
	wnd.lpfnWndProc = MyWindowProc;//�Զ���Ĵ��ڹ��̺���
	wnd.lpszClassName = L"MrHuang";//��������
	wnd.lpszMenuName = NULL;//�˵���Դ����
	wnd.style = CS_HREDRAW | CS_DBLCLKS;//�����ࡢ��ʽ
	wnd.hInstance = hInstance;//ʵ�����
	RegisterClass(&wnd);


	//�����ַ�����Դ
	TCHAR  buf[64] = {0};
	LoadString(hInstance, IDS_STRING1, buf, sizeof(buf));
	LoadString(GetModuleHandle(NULL), IDS_STRING2, buf, sizeof(buf));

	//��������(����֮ǰ����WM_CREATE)
	HWND    hWnd = CreateWindow(L"MrHuang", buf,
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