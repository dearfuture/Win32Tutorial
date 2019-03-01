#include<windows.h>
#include<CommCtrl.h> 


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
		PAINTSTRUCT ps;
		HDC   hdc = BeginPaint(hWnd, &ps);
 
		 //1.���������ڴ�DC,��ʱ���Ĵ�Сʱ1X1����С�����ܻ���
		HDC  hMemDC=CreateCompatibleDC(hdc);

		//2.��������λͼ���ṩ�滭����
		HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, 100, 100);

		//3.�Ѽ���λͼѡ�������ڴ�DC��,�˿�DC�Ĵ�С��λͼһ�£����Ի���
		SelectObject(hMemDC, hMemBmp);

		//4.�ڼ����ڴ�DC�Ͻ��л�ͼ����
		SetTextColor(hMemDC, RGB(255, 0, 0));
		TextOut(hMemDC, 0, 0, L"˫���弼�����ƣ�", lstrlen(L"˫���弼�����ƣ�")); 
		Rectangle(hMemDC, 30, 30, 80, 80);

		//5.���ڴ�DC�е�ͼ��һ���Ի�������DC��
		 //������
		 BitBlt(hdc, 0, 0, 100, 100, hMemDC, 0, 0, SRCCOPY);
		
		 //����(Ŀ����δ���Դ����)
		 StretchBlt(hdc, 0, 0, 400, 400, hMemDC, 0, 0,100,100, SRCCOPY);
		 //ѹ��(Ŀ�����С��Դ����)
		 StretchBlt(hdc, 0, 0, 50, 50, hMemDC, 0, 0, 100, 100, SRCCOPY);


		 //�ͷ���Դ
		 DeleteDC(hMemDC);
		 DeleteObject(hMemBmp);


		EndPaint(hWnd, &ps);
	}
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