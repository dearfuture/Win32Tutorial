#include<windows.h>
#include<CommCtrl.h> 

//#pragma  comment(lib, "COMCTL32.LIB")

//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;

	case WM_COMMAND:
	{
		HWND  hCtrl = (HWND)lParam;
		WORD   CtrlID = LOWORD(wParam);
		WORD    code=HIWORD(wParam);
		if (code == EN_CHANGE)
		{
			//��ȡ��ϼ�������
			WORD  key = SendMessage(hCtrl, HKM_GETHOTKEY, 0, 0);
			BYTE  l = LOBYTE(LOWORD(key));//��ĸ��
			BYTE  h = HIBYTE(LOWORD(key));//CTRL | ALT |SHIFT 

			TCHAR  buf[64] = { 0 };
			wsprintf(buf, L"%c  +   %d  +  %d\n", l, bool(h & HOTKEYF_CONTROL), bool(h & HOTKEYF_ALT));
			OutputDebugString(buf);
		} 
	
	}break;

	case WM_CREATE:
	{
		//�����ȼ��ؼ�
		HWND  hHotkey = CreateWindow(HOTKEY_CLASS,L"XXX",
			WS_CHILD | WS_VISIBLE, 30, 30, 200, 30, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);

		//������ϼ�������(CTRL+ALT+A)
		SendMessage(hHotkey, HKM_SETHOTKEY, MAKEWORD('A', HOTKEYF_ALT| HOTKEYF_CONTROL), 0);

		//��ȡ��ϼ�������
		WORD  key=SendMessage(hHotkey, HKM_GETHOTKEY, 0, 0);
		BYTE  l = LOBYTE(LOWORD(key));//��ĸ��
		BYTE  h =HIBYTE(LOWORD(key));//CTRL | ALT |SHIFT 

		TCHAR  buf[64] = {0};
		wsprintf(buf, L"%c  +   %d  +  %d\n", l,   bool( h & HOTKEYF_CONTROL), bool(h & HOTKEYF_ALT));
	    OutputDebugString(buf);

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