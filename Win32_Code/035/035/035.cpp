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


	case  WM_NOTIFY:
	{
		//WM_NOTIFY�����Ĺ���ͷ��
		NMHDR  *pHDR = (NMHDR*)lParam; 
		if ((pHDR->code == MCN_SELCHANGE) && (pHDR->idFrom == 111))
		{
			LPNMSELCHANGE   pSelect = (LPNMSELCHANGE)lParam;

			SYSTEMTIME   st0 = pSelect->stSelStart;
			SYSTEMTIME   st1 = pSelect->stSelEnd;

			TCHAR  buf[64] = { 0 };
			wsprintf(buf, L"%04d-%02d-%02d %02d:%02d:%02d �� %04d-%02d-%02d %02d:%02d:%02d",
				st0.wYear, st0.wMonth, st0.wDay, st0.wHour, st0.wMinute, st0.wSecond,
				st1.wYear, st1.wMonth, st1.wDay, st1.wHour, st1.wMinute, st1.wSecond);
		
			MessageBox(hWnd, buf, L"��ʾ", MB_OK);
		}

	}break;

	case WM_CREATE:
	{
       //���������ؼ�
		HWND   hCalendar = CreateWindow(MONTHCAL_CLASS,
			L"XXX", WS_CHILD | WS_VISIBLE , 30, 30, 600, 600,
			hWnd, (HMENU)111, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
	
	//���ÿ�ѡ�����ڵķ�Χ 
		SYSTEMTIME st[2];//0����Сֵ��1�����ֵ
		st[0].wYear = 2018;
		st[0].wMonth = 1;
		st[0].wDay = 1;
		st[1].wYear = 2018;
		st[1].wMonth = 1;
		st[1].wDay = 7;
		SendMessage(hCalendar, MCM_SETRANGE, GDTR_MAX | GDTR_MIN, (LPARAM)st);
	
		//ѡ��ĳ������ֵ20180107
		 SendMessage(hCalendar, MCM_SETCURSEL,  0 , (LPARAM)&st[1]);

	
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