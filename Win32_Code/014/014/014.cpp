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

		//�����Ϣ
	case  WM_LBUTTONDOWN:
		char str[64];
		sprintf(str, "����������:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
	case  WM_LBUTTONUP: 
		sprintf(str, "����������:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
	case  WM_MOUSEMOVE: 
		sprintf(str, "����ƶ�:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
	case  WM_LBUTTONDBLCLK: 
		sprintf(str, "������˫��:  %d, %d\n", LOWORD(lParam), HIWORD(lParam));
		OutputDebugStringA(str);
		break;
		 //������Ϣ
	case  WM_KEYDOWN:
		sprintf(str, "���̰���:  %X, %c\n", wParam , wParam);
		OutputDebugStringA(str);
		break;
	case  WM_CHAR:
		sprintf(str, "�ַ���Ϣ:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break; 
	case  WM_KEYUP:
		sprintf(str, "���̵���:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;

	case  WM_SYSKEYDOWN: //altͬʱ���µļ�
		sprintf(str, "ϵͳ��������:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;
	case  WM_SYSCHAR:  
		sprintf(str, "ϵͳ�ַ�:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
		break;
	case  WM_SYSKEYUP:
		sprintf(str, "ϵͳ��������:  %X, %c\n", wParam, wParam);
		OutputDebugStringA(str);
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
	HWND  hWnd = CreateWindow(L"MrHuang", L"��һ�����ڳ���",
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