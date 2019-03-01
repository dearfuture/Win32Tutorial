#include<windows.h> 


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;

	case WM_PAINT:
	{ 
		//1.ʹ��BeginPaint�����ܽ���Ч��������Ч�����������Ч����ϵͳ��һֱ����WM_PAINT��
		/*PAINTSTRUCT  ps;
		HDC  hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, L"��ð���", lstrlen(L"��ð���"));
		EndPaint(hWnd, &ps);*/

		//2.ʹ��GetDC��ȡ�ͻ���DC���������ܽ���Ч��������Ч,����WM_PAINTһֱ���ͣ�����һֱ��˸
		/*
		HDC  hdc = GetDC(hWnd);
		TextOut(hdc, 0, 0, L"��ð���", lstrlen(L"��ð���"));
		ReleaseDC(hWnd, hdc);
		//return 0; //ȥ��֮�󽻸�Ĭ��DefWindowProc����WM_PAINT��Ϣ�������BeginPaint��EndPaint
		*/ 

	}
	break;

    case WM_NCPAINT:
	{
		//3.��ȡ�������ڵ�DC����������������������
		HDC  hdc = GetWindowDC(hWnd);
		RECT  r = {0,0,400,20};
		HBRUSH  brh = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(hdc, &r, brh);
		DeleteObject(brh);
		ReleaseDC(hWnd, hdc);//�ͷŵ�DC
		return  true;


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