#include<windows.h>


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case  WM_DESTROY:
		PostQuitMessage(0);
		return   0;

	default:
		return  DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return 0;
}


int  WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE  hPrevInstance,
	LPSTR lpCmdLine, int  nShowCmd)
{
	//1.ע�ᴰ����
	WNDCLASS  wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));//����ɫ
	wnd.hCursor= LoadCursor(NULL, IDC_ARROW);//���
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//ͼ��
	//wnd.lpfnWndProc = DefWindowProc;//Ĭ�ϴ��ڹ��̺��������ڴ�����Ϣ
	wnd.lpfnWndProc =MyWindowProc;//�Զ���Ĵ��ڹ��̺���
	wnd.lpszClassName = L"MrHuang";//��������
	wnd.lpszMenuName = NULL;//�˵���Դ����
	wnd.style = CS_HREDRAW;//�����ࡢ��ʽ
	wnd.hInstance = hInstance;//ʵ�����
	RegisterClass(&wnd);

	//��������(����֮ǰ����WM_CREATE)
	HWND  hWnd = CreateWindow(L"MrHuang",L"��һ�����ڳ���",
		WS_OVERLAPPEDWINDOW,100,100,300,300,NULL,NULL, hInstance,NULL );

	//��ʾ����
	ShowWindow(hWnd, nShowCmd);

	//���´���(����WM_PAINT)
	UpdateWindow(hWnd);

	 //��Ϣѭ�����յ�WM_QUIT��Ϣ�˳���
	MSG  msg;
	BOOL  bRet = false;
	while (bRet = GetMessage(&msg, hWnd, 0,0 ) )
	{
		 if (bRet == -1)
		 {
			 return -1;
		 } 
		TranslateMessage(&msg);//������Ϣ
		DispatchMessage(&msg);//�ַ���Ϣ�����ڹ���
	}

}