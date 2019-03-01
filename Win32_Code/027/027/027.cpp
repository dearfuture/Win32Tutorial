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

	case  WM_CREATE:
	{
		LPCREATESTRUCT   pcs = (LPCREATESTRUCT)lParam;

		//�����������ؼ�
		HWND hScrollBar = CreateWindow(L"scrollBAR", L"XXX", WS_CHILD | WS_VISIBLE | SBS_HORZ,
			30, 30, 200, 30, hWnd, (HMENU)111, pcs->hInstance, NULL);

		//���ù������ķ�Χ
		SendMessage(hScrollBar, SBM_SETRANGE, 0, 100);

		//���ù������Ļ���λ��
		SendMessage(hScrollBar, SBM_SETPOS, 40, 1);


		return 0;
	}
	 
	case  WM_CTLCOLORSCROLLBAR:
	{
		HDC    hdc = (HDC)wParam;
		HWND  hCtrl = (HWND)lParam;
		LONG   CtrlID=GetWindowLong(hCtrl, GWL_ID);

		if (CtrlID == 111)
		{
			HBRUSH  bsh = CreateSolidBrush(RGB(255, 0, 0));
			return  (LRESULT)bsh;
		}  
	
	}break;


	//ˮƽ���������͵���Ϣ
	case   WM_HSCROLL:
	{

		WORD  code = LOWORD(wParam);//������
		HWND   hCtrl = (HWND)lParam;//�ؼ����
									//��ȡ�������Ļ���λ��
		int   pos = SendMessage(hCtrl, SBM_GETPOS, 0, 0);

		switch (code)
		{
			//�����߼�ͷ
		case SB_LINELEFT:
			OutputDebugString(L"SB_LINELEFT\n");
			pos -= 1;
			break;
			//����ұ߼�ͷ
		case SB_LINERIGHT:
			OutputDebugString(L"SB_LINERIGHT\n");
			pos += 1;
			break;
			//�����հ���
		case SB_PAGELEFT:
			OutputDebugString(L"SB_PAGELEFT\n");
			pos -= 10;
			break;
			//����ҿհ���
		case SB_PAGERIGHT:
			OutputDebugString(L"SB_PAGERIGHT\n");
			pos += 10;
			break;
			//�϶�����ʱ����Ϣ
		case  SB_THUMBPOSITION:
			pos = HIWORD(wParam);//��קλ�ã�����SB_THUMBPOSITION���� 
			char str[64];
			sprintf(str, "SB_THUMBPOSITION   %d\n", pos);
			OutputDebugStringA(str);
			break;
		}

		//���ù������Ļ���λ��
		SendMessage(hCtrl, SBM_SETPOS, pos, 1);

	}break;





	default:
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