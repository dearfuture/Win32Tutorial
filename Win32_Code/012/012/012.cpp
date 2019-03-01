#include<windows.h>
#include<stdio.h>

  

//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		///////////////////////////��������///////////////////////////////
	case WM_NCCREATE:

		SetWindowTextA(hWnd, "�ı����");

		char str[64];
		sprintf(str, "WM_NCCREATE��Ϣ:%p��\n", hWnd);
		OutputDebugStringA(str);
		return  true;//������뷵��true�����򲻻ᷢWM_CREATE��Ϣ��CreateWindow����NULL

	case WM_CREATE:
	{
		CREATESTRUCT  *p = (CREATESTRUCT*)lParam; 
		sprintf(str, "WM_CREATE��Ϣ:%p��\n", hWnd); 

		OutputDebugStringA(str);
		return true;
	}

		///////////////////////////���ٴ���/////////////////////////////// 
	case WM_CLOSE:
		sprintf(str, "WM_CLOSE��Ϣ:%p��\n", hWnd);
		OutputDebugStringA(str); 
		DestroyWindow(hWnd);//���ٴ��ڣ�����WM_DESTROY��Ϣ
		return 0;

	case WM_DESTROY: 
		sprintf(str, "WM_DESTROY��Ϣ:%p��\n", hWnd);
		OutputDebugStringA(str);
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;
	case WM_NCDESTROY: 
		sprintf(str, "WM_NCDESTROY��Ϣ:%p��\n", hWnd);
		OutputDebugStringA(str);
		return 0;
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
	HWND  hWnd = CreateWindow(L"MrHuang", L"��һ�����ڳ���",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);
	char str[64];
	sprintf(str, "CreateWindow����:%p��\n", hWnd);
	OutputDebugStringA(str); 

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