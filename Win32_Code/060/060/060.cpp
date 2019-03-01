#include<windows.h>
#include"Resource.h"


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
		//���ز˵���Դ
		HMENU  hTop=LoadMenu(GetModuleHandle(NULL),  MAKEINTRESOURCE( IDR_MENU1));
	   
		//���ò˵�������
		SetMenu(hWnd,  hTop);


		//��ȡĳ�����ڵĶ���˵�
		HMENU hMenuTop=  GetMenu(hWnd);
		//��ȡ����˵��ĵ����˵�
		HMENU  hPop = GetSubMenu(hMenuTop, 0);
	    //��ȡ�˵����е�����
		MENUITEMINFO   mii = {0};
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_TYPE|MIIM_ID;
		mii.fType = MFT_STRING;
		mii.dwTypeData = new  TCHAR[64];
		mii.cch =64 ;
		GetMenuItemInfo(hPop, 2, true, &mii);
		MessageBox(hWnd, mii.dwTypeData, L"��ʾ", MB_OK);


	}break;

	case WM_COMMAND:
	{
		//�˵�ID
		WORD  menuId = LOWORD(wParam);
		switch (menuId)
		{ 
		case ID_OPEN:
			MessageBox(hWnd, L"�򿪲˵����", L"��ʾ", MB_OK);
			break;
		case ID_NEW:
			MessageBox(hWnd, L"�½��˵����", L"��ʾ", MB_OK);
			break;
		case 2000:
			MessageBox(hWnd, L"���߲˵����", L"��ʾ", MB_OK);
			break;
		}

	}  break;

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