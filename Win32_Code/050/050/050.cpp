#include<windows.h>
#include<CommCtrl.h>  
//ʹ��Unicode�汾�������manifestǿ����Ӧ�ó������common Control 6.0
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
//#pragma comment(lib,"Comctl32.lib")


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;
		 
	case  WM_LBUTTONDOWN:
		{
			//��ȡ��ǰ��Ĵ���
			HWND  hActive = GetActiveWindow();
			TCHAR buf[64] = { 0 };
			GetWindowText(hActive, buf, 64);
			MessageBox(NULL, buf, L"��ʾ", MB_OK);

		}break;


	case WM_CREATE:
	{

		HWND hEdit1 = CreateWindow(WC_EDIT,
			L"�༭�ؼ�",
			WS_CHILD | WS_VISIBLE ,
			30, 30,
			100, 30,
			hWnd,
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		HWND hEdit2 = CreateWindow(WC_EDIT,
			L"123",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			30, 100,
			200, 30,
			hWnd,
			(HMENU)222,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		//���ݴ��ھ�����û����ô���
		EnableWindow(hEdit1,false);
		EnableWindow(hEdit1, true);
		//EnableWindow(hWnd, false);//���ø�����


		//���ݴ������������ڱ�����Ҷ��㴰��(������)
		HWND   h1 = FindWindow(L"MrHuang", NULL);
		bool  b1 = (h1 == hWnd);
		HWND   h2 = FindWindow(NULL, L"��һ�����ڳ���");
		bool  b2 = (h2 == hWnd);
		HWND   h3 = FindWindow(L"Mr", L"��һ�����ڳ���");
		bool  b3 = (h3 == hWnd);
		HWND   h4 = FindWindow(WC_EDIT,  NULL);//���������Ӵ�����ؼ�
		bool  b4 = (h4 == hEdit2);
	 
		HWND   hTxt= FindWindow(NULL, L"�½��ı��ĵ�.txt - ���±�");//���Ҽ��±�
		SendMessage(hTxt, WM_SETTEXT, 0,(LPARAM)L"�۸���ı���");

		//���ݴ��ھ�����ô��ڱ���
		//SetWindowText(hWnd, L"�ĵ�����");
		//SetWindowText(hEdit1, L"�ĵ�����");

		//���ݴ��ھ����ȡ���ڱ���
		TCHAR buf[64] = {0};
		GetWindowText(hEdit2, buf, 64);
		OutputDebugString(buf);

		//��ȡ���ڵľ�������
		RECT  r;
		GetWindowRect(hWnd, &r);
		 
		//��ȡ���ڵĿͻ�����
		RECT  r2;
		GetClientRect(hWnd, &r2);

      //���ÿؼ����н���
		SetFocus(hEdit1);

		//���ݴ��ھ���ƶ�����
		//MoveWindow(hWnd, 0, 0, 600, 600, true);//�ƶ�������
		//MoveWindow(hEdit2, 300, 300, 100, 100, true);//�ƶ��ؼ�

		//��ȡ��ǰ��Ĵ���
		HWND  hActive = GetActiveWindow();
		bool  b8 = (hActive == hWnd);
		 

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


	//��������(����֮ǰ����WM_CREATE)
	HWND    hWnd2 = CreateWindow(L"MrHuang", L"�ڶ������ڳ���",
		WS_OVERLAPPEDWINDOW, 500, 100, 400, 400, NULL, NULL, hInstance, NULL);

	//��ʾ����
	ShowWindow(hWnd2, nShowCmd);
	//���´���(����WM_PAINT)
	UpdateWindow(hWnd2);



	//��Ϣѭ�����յ�WM_QUIT��Ϣ�˳���
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//������Ϣ
		DispatchMessage(&msg);//�ַ���Ϣ�����ڹ���
	}
}