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

		//�����༭��ؼ�
		HWND   hEdit = CreateWindow(L"ediT", L"����һ���༭��", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL,
			30, 30, 200, 100, hWnd, (HMENU)111, pcs->hInstance, NULL);

		//��༭����ѡ���ַ�������Ϣ
		SendMessage(hEdit, EM_SETSEL, 2, 6);

		//���иո�ѡ�������
		//SendMessage(hEdit, WM_CUT, 0, 0); 

		//����
		//SendMessage(hEdit, EM_UNDO, 0, 0);

		return 0;
	}

	case   WM_COMMAND:
	{

		WORD  id = LOWORD(wParam);//�ؼ�ID
		WORD  code = HIWORD(wParam);//��Ϣ����
		HWND   hCtrl = (HWND)lParam;//���ھ��

									//�����ڽ��յ��ӿؼ�������Ϣ
		if (id == 111 && code == EN_CHANGE)
		{
			//MessageBox(NULL, L"�༭����ı����ı䣡", L"��ʾ", MB_OK);

			TCHAR  buf[64] = { 0 };
			GetWindowText(hCtrl, buf, sizeof(buf));
			MessageBox(NULL, buf, L"��ʾ", MB_OK);
		}

	}break;

	case  WM_CTLCOLOREDIT:
	{
		HDC  hdc = (HDC)wParam;
		HWND   hCtrl = (HWND)lParam;
		//��ȡ�༭��ؼ���ID
		UINT  CtrlID = GetWindowLong(hCtrl, GWL_ID);
		if (CtrlID == 111)
		{
			SetTextColor(hdc, RGB(255, 0, 0));//������ɫ
			SetBkMode(hdc,  TRANSPARENT);//���ֱ���ɫ͸��
		}  
		HBRUSH   hbr = CreateSolidBrush(RGB(255, 255, 0));
		return   (LRESULT)hbr;//�ؼ��ı���ɫ
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