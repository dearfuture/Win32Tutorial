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

	 case WM_CREATE:
	  {  

		  HWND hBtn = CreateWindow(WC_BUTTON,
			  L"��ť�ؼ�",
			  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			  30, 30,
			  100, 30,
			  hWnd,
			  (HMENU)111,
			  ((LPCREATESTRUCT)lParam)->hInstance,
			  NULL); 

		  HWND hEdit = CreateWindow(WC_EDIT,
			  L"123",
			  WS_CHILD | WS_VISIBLE | WS_BORDER,
			  30, 100,
			  200, 30,
			  hWnd,
			  (HMENU)222,
			  ((LPCREATESTRUCT)lParam)->hInstance,
			  NULL);

		  //ͨ���ؼ�ID��ȡ���
		  HWND   h1= GetDlgItem(hWnd, 111);
		  bool  b = (h1 == hBtn);
		  HWND   h2 = GetDlgItem(hWnd, 222);
		  bool  b2 = (h2 == hEdit);

		  //��ȡ�ؼ����ı������
		  TCHAR  buf[64] = {0};
		  GetDlgItemText(hWnd, 111, buf, 64);
		  GetDlgItemText(hWnd, 222, buf, 64);
		  OutputDebugString(buf);

		  //��ȡ�ؼ��ı���ת��Ϊ����
		  BOOL  bSuccess = FALSE;
		  int  v1=GetDlgItemInt(hWnd, 111, &bSuccess, true);
		  bSuccess = FALSE;
		  int  v2 = GetDlgItemInt(hWnd, 222, &bSuccess, true);
		   
		  //���ݿؼ������ȡID
		  UINT  id1= GetDlgCtrlID(hBtn);
		  UINT  id2 = GetDlgCtrlID(hEdit);
		  UINT  id3 = GetDlgCtrlID(hWnd); //���㴰��û��ID������0
		  id3 = id3;

		  //����ID���ÿؼ����ı����߱���
		  SetDlgItemText(hWnd, 111, L"��ð���");
		  SetDlgItemText(hWnd, 222, L"456");

		  //����ID���������ÿؼ����ı����߱���
		  SetDlgItemInt(hWnd, 111, 666, true);
		  SetDlgItemInt(hWnd, 222, -888, true);

		  //���ݿؼ�ID��ؼ�����ָ������Ϣ
		  SendDlgItemMessage(hWnd, 222, WM_SETTEXT, 0,(LPARAM) L"������Ϣ��");
		   

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