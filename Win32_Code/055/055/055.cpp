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
 
		//��������
		HPEN  hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
		//����ѡ�뵽�豸������(ʹ����֧��)
		SelectObject(hdc, hPen);

		//1.��ֱ��(������)
		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 200, 100);

		//������ˢ
		HBRUSH hBsh = CreateSolidBrush(RGB(0, 255, 0));
		//����ˢѡ�뵽�豸������(ʹ����֧��ˢ)
		SelectObject(hdc, hBsh);
		 
		//2.������(������)
		Rectangle(hdc, 200, 200, 400, 400);


		//��ȡ͸����ˢ
		HGDIOBJ hBsh2  =GetStockObject(NULL_BRUSH);
		SelectObject(hdc, hBsh2);
		Rectangle(hdc,  100, 100, 200, 150);

		//3.����Բ��Բ�Σ�
		Ellipse(hdc, 200, 200, 400, 400);
		Ellipse(hdc, 100, 100, 200, 150);


		//4.����ͼ 
/*			
        //��ͼ�����Ĳ���ֽ�
        Ellipse(hdc, 500, 100, 800, 400); 
		 //��Բ�ĵ���һ���������
		 MoveToEx(hdc, 650, 250, NULL);
		 LineTo(hdc,1000, 300);  
		 //��Բ�ĵ��ڶ����������
		 MoveToEx(hdc, 650, 250, NULL);
		 LineTo(hdc, 400, 400);
 */		
		 Pie(hdc, 500, 100, 800, 400, 1000, 300,400, 400);


		//ɾ��GDI����
		DeleteObject(hPen);
		DeleteObject(hBsh);

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