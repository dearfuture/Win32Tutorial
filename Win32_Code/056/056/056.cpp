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
		PAINTSTRUCT ps;
		//��ȡ�豸�����ľ��
		HDC   hdc = BeginPaint(hWnd, &ps);

		//�ı��ı��ı���ɫ
		SetBkColor(hdc, RGB(255, 0, 0));
		//�����ı�����ģʽ 
		SetBkMode(hdc, TRANSPARENT);//͸��

		//�����ı�����ɫ
		SetTextColor(hdc, RGB(255, 0, 0));


		//�����ı��Ĳο���
		SetTextAlign(hdc, TA_TOP);

		//1.�����ϻ��ı�
		TextOut(hdc,250, 200, L"��ð������ǻ����ı���", lstrlen(L"��ð������ǻ����ı���"));

		//2.�ھ��η�Χ�л��ı�
		RECT  r = {250,400,300,500};
		Rectangle(hdc, r.left, r.top, r.right, r.bottom);
		DrawText(hdc, L"��ð������ǻ����ı���", lstrlen(L"��ð������ǻ����ı���")
			, &r,  DT_BOTTOM|DT_SINGLELINE);




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
		WS_OVERLAPPEDWINDOW, 100, 100, 1000, 700, NULL, NULL, hInstance, NULL);

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