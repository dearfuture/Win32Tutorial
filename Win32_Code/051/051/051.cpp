#include<windows.h>


WNDPROC  oldProc = NULL;

//�Զ���ı༭�򴰿ڴ�����
LRESULT  CALLBACK    MyEditWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		//�����˸���Ȥ����Ϣ
	  case WM_LBUTTONDOWN:
		//MessageBox(hWnd, L"���ǽػ��˱༭�����Ϣ", L"��ʾ", MB_OK); 
		  SetWindowText(hWnd, L"���ǽػ��˱༭�����Ϣ");
	 //  return 0; //��ʾ�����Լ�������

	  case  WM_RBUTTONDOWN:
	 
		  break;
	}

	//��������Ϣ������ԭ���Ĵ�����̺���ȥ������֤�ؼ�����ȷ��
	return  CallWindowProc(oldProc,hWnd, Msg,wParam,lParam);
}



 
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

		//����ϵͳԤ����Ŀؼ���Դ���벻���޸ģ�
		HWND hEdit = CreateWindow(L"EDIT",
			L"111",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 30,
			200, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		 
		//���ؼ��Ĵ��ڹ��̴�������Ϊ�Զ���ģ��Ӷ�����ؼ���Ϣ
		oldProc=(WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, (LONG)MyEditWindowProc);

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