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

		//1.�����ڴ����DC��1px  X  1px��
		HDC  hMemDC = CreateCompatibleDC(hdc);

		//2.����λͼ��Դ
		HBITMAP hBmp= (HBITMAP)LoadImage(NULL, L"bg.bmp", IMAGE_BITMAP, 800, 800, LR_LOADFROMFILE);

		//3.��λͼѡ�뵽�����ڴ�DC
		SelectObject(hMemDC, hBmp);

		//���ˮӡ
		TextOut(hMemDC, 100, 100, L"��Ϳ�һ�", lstrlen(L"��Ϳ�һ�"));
		 
		//����ͼ������ģʽ
		//SetStretchBltMode(hdc, COLORONCOLOR);//ɾ����������
		SetStretchBltMode(hdc, HALFTONE); 

		//4.������DC�е�ͼ��һ���Կ���������DC��
		 //BitBlt(hdc, 0, 0, 800, 800, hMemDC, 0, 0, SRCCOPY);
		//������ʾ
		 StretchBlt(hdc, 0, 0, 400, 400, hMemDC, 0, 0, 800,800,SRCCOPY);

		//5.�ͷ�DC��λͼ��Դ
		DeleteObject(hBmp);
		DeleteDC(hMemDC);
	  
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