#include<windows.h>
#include<CommCtrl.h> 


WNDPROC  oldProc = NULL;

LRESULT CALLBACK  MyEditWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// �������������ʾһ����Ϣ�� 
	case WM_LBUTTONDOWN:
	{
		//MessageBox(0, L"���������������Ϊ", L"��ʾ", MB_OK);
		SetWindowText(hWnd, L"�������˱༭���������Ϊ");
		//return 0; //�Լ�������Ϣ���ͱ��뷵��0��
	} break;

	}
	return    CallWindowProc(oldProc, hWnd, msg, wParam, lParam);
}



//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;

	case WM_CREATE:
	{ 

		//�Ȼ�ȡϵͳ�ؼ���WNDCLASS��Ϣ
		WNDCLASS  wc;
		GetClassInfo(NULL, WC_EDIT, &wc); 
		oldProc = wc.lpfnWndProc;//����ϵͳ�Ĵ��ڴ�����
		wc.lpfnWndProc = MyEditWndProc;//��Ϊ�Զ���Ĵ��ڴ�����
		bool  ret=RegisterClass(&wc); //����ע�ᴰ���࣬ʵ��ȫ�ֵ���Ч

		//��ע��Ҳ���Ը�Ϊ�Լ��Ĵ�������������������ʱ�����Լ��Ĵ��������Ϳ��Դ����༭��

		//ϵͳԤ����Ŀؼ����޷��޸�
		HWND hEdit = CreateWindow(WC_EDIT,
			L"111",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 30,
			200, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL); 


		//ϵͳԤ����Ŀؼ����޷��޸�
		HWND hEdit2 = CreateWindow(WC_EDIT,
			L"222",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 100,
			200, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		 

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