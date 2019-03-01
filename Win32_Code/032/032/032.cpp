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

	case WM_NOTIFY:
	{
		NMHDR  *pHDR = (NMHDR  *)lParam;
		if (pHDR->code == DTN_DATETIMECHANGE)
		{
			LPNMDATETIMECHANGE  pDT = (LPNMDATETIMECHANGE)lParam;
			SYSTEMTIME  st = pDT->st;
			TCHAR  buf[64] = {0};
			wsprintf(buf, L"%04d-%02d-%02d %02d:%02d:%02d ",
				st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			MessageBox(hWnd, buf, L"��ʾ", MB_OK);
		}  
	}break;

	case WM_CREATE:
	{
		//����һ������ʱ��ѡ��ؼ�
		HWND   hDatetime = CreateWindow(DATETIMEPICK_CLASS, L"XXX",
			WS_CHILD | WS_VISIBLE| DTS_SHOWNONE, 30, 30, 200, 30, hWnd, (HMENU)111, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		//���ÿؼ�����ʾ��ʽ
		SendMessage(hDatetime, DTM_SETFORMAT, 0, (LPARAM)L"yyyy-MM-dd  hh:mm:ss  tt");

		//���ÿؼ�����ʾʱ��
		SYSTEMTIME  st;
		st.wYear = 1999;
		st.wMonth = 8;
		st.wDay = 7;
		st.wHour = 6;
		st.wMinute = 5;
		st.wSecond = 4;
		st.wMilliseconds = 3;
		SendMessage(hDatetime, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);

		//����ʱ��Ϊ��
		//SendMessage(hDatetime, DTM_SETSYSTEMTIME, GDT_NONE, 0);


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