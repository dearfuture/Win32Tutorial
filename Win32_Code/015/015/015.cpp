#include<windows.h> 
#include<windowsx.h>  //Button_GetCheck��ͷ�ļ�
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

		//�����ؼ������Ӵ���

		//��ͨ��ťBS_PUSHBUTTON
		HWND  hBtn=CreateWindow(L"button", L"��ͨ��ť", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON ,30, 30, 80, 30, hWnd,
			(HMENU)1000,//�ؼ�ID
			pcs->hInstance, NULL); 

		//��ѡ��ť
		HWND  hBtn1 = CreateWindow(L"button", L"��ѡ��ť", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 30, 70, 80, 30, hWnd,
			(HMENU)1001,//�ؼ�ID
			pcs->hInstance, NULL);

		//��ѡ��ť
		HWND  hBtn2 = CreateWindow(L"button", L"��ѡ��ť", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 110, 80, 30, hWnd,
			(HMENU)1002,//�ؼ�ID
			pcs->hInstance, NULL);


		return 0;
      }


	case   WM_COMMAND:
	{
	     WORD  id = LOWORD(wParam);
		 WORD  code= HIWORD(wParam);
		 HWND   hCtrl = (HWND)lParam;
		 if (id == 1000 &&  code ==  BN_CLICKED)
		 {
			 MessageBox(hWnd, L"��ͨ��ť��������", L"��ʾ",MB_OK); 
		 }
		 else if (id == 1001)
		 {
			 MessageBox(hWnd, L"��ѡ��ť��������", L"��ʾ", MB_OK);
 
			 if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_CHECKED)
			 {
				 MessageBox(hWnd, L"��ѡ�У�", L"��ʾ", MB_OK); 
			 }
			 else  if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			 {
				 MessageBox(hWnd, L"ûѡ�У�", L"��ʾ", MB_OK);
			 }
		 }
		 else if (id == 1002)
		 {
			 MessageBox(hWnd, L"��ѡ��ť��������", L"��ʾ", MB_OK);
/*
			 if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_CHECKED)
			 {
				 MessageBox(hWnd, L"��ѡ�У�", L"��ʾ", MB_OK);
			 }
			 else  if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			 {
				 MessageBox(hWnd, L"ûѡ�У�", L"��ʾ", MB_OK);
			 }
			 */
			  

			 //��д��ʽ((int)(DWORD)SNDMSG((hwndCtl), BM_GETCHECK, 0L, 0L))
			 if (Button_GetCheck(hCtrl) == BST_CHECKED)
			 {
				 MessageBox(hWnd, L"��ѡ�У�", L"��ʾ", MB_OK);
			 }
			 else  if (Button_GetCheck(hCtrl) == BST_UNCHECKED)
			 {
				 MessageBox(hWnd, L"ûѡ�У�", L"��ʾ", MB_OK);
			 }
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