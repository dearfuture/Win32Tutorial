#include<windows.h>
#include<stdio.h>

//�Զ�����Ϣ
#define  WM_AAA    WM_USER+1

HWND  hWnd; 
HWND  hWnd2;


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0; 

	case WM_AAA:
		MessageBoxA(NULL, "���ڹ��̣�WM_AAA", "����", MB_OK);
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
	wnd.style = CS_HREDRAW;//�����ࡢ��ʽ
	wnd.hInstance = hInstance;//ʵ�����
	RegisterClass(&wnd);

	//��������(����֮ǰ����WM_CREATE)
	hWnd = CreateWindow(L"MrHuang", L"��һ�����ڳ���",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);

	//��ʾ����
	ShowWindow(hWnd, nShowCmd);
	//���´���(����WM_PAINT)
	UpdateWindow(hWnd);


	//��������2(����֮ǰ����WM_CREATE)
	hWnd2 = CreateWindow(L"MrHuang", L"�ڶ������ڳ���",
		WS_OVERLAPPEDWINDOW, 100, 500, 300, 300, NULL, NULL, hInstance, NULL);
	//��ʾ����
	ShowWindow(hWnd2, nShowCmd);
	//���´���(����WM_PAINT)
	UpdateWindow(hWnd2);

	 
	//��Ϣѭ�����յ�WM_QUIT��Ϣ�˳���
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//˵���������ڹ���һ����Ϣѭ�����߳���Ϣ����
		if (msg.message == WM_LBUTTONDOWN)
		{
			//char str[64];
			//sprintf(str,"���ھ��:%p", msg.hwnd);
			//MessageBoxA(NULL, str,"����", MB_OK);


			//SendMessageֱ�ӷ������ڹ��̺������������������Ǳ����ڹ��̴���ŷ���
			//SendMessage(hWnd, WM_AAA, 0, 0);

			//PostMessage�ŵ��߳���Ϣ����������������أ�ͨ����Ϣѭ�������ڹ��̴���
			//PostMessage(hWnd, WM_AAA, 0, 0);

			//PostThreadMessage�ŵ��߳���Ϣ����������봰�ڹ���
			//PostThreadMessage(GetCurrentThreadId(), WM_AAA, 0, 0);
			
			//PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
			PostQuitMessage(0);//�ȼ��������һ�е���

			int  a = 100;
		}

		if (msg.message == WM_AAA)
		{
		    MessageBoxA(NULL, "��Ϣѭ��:WM_AAA","����", MB_OK); 
		}



		TranslateMessage(&msg);//������Ϣ
		DispatchMessage(&msg);//�ַ���Ϣ�����ڹ���
	}
}