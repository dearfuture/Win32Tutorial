#include<windows.h>
#include<CommCtrl.h>  
//ʹ��Unicode�汾�������manifestǿ����Ӧ�ó������common Control 6.0
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
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
	case  WM_COMMAND:
	{
		WORD  CtrlID = LOWORD(wParam);
		WORD   code = HIWORD(wParam);
	}break;

	case  WM_NOTIFY:
	{
		NMHDR  * pHDR = (NMHDR  *)lParam;
		if (pHDR->code == UDN_DELTAPOS)
		{
		     LPNMUPDOWN   pNM = (LPNMUPDOWN)lParam;
			 TCHAR  buf[64] = {0};
			 wsprintf(buf, L"iDelta: %d   iPos:%d", pNM->iDelta, pNM->iPos);
			 MessageBox(hWnd, buf, L"��ʾ", MB_OK);

			 pNM->iDelta = -pNM->iDelta;//�������ӣ����¼���

			 //return 1;//���ط�0��ֹ�ؼ��ı�
		}
	}break;

	case WM_CREATE:
	{
	 //�������ؼ�
		HWND  hEdit = CreateWindow(WC_EDIT, L"0", WS_CHILD | WS_VISIBLE | ES_NUMBER,
			30, 30, 100, 50, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);

		//�������¿ؼ�
		HWND  hUpDown= CreateWindow(UPDOWN_CLASS , NULL, WS_CHILD | WS_VISIBLE | UDS_AUTOBUDDY| UDS_WRAP /*ѭ��*/|UDS_ALIGNRIGHT|UDS_SETBUDDYINT,
			0, 0, 0, 0, hWnd, (HMENU)222, GetModuleHandle(NULL), NULL);

		//���ÿؼ���Χ
		SendMessage(hUpDown, UDM_SETRANGE, 0, MAKELPARAM(1, 10));

		//���õ�ǰ��ֵ
		SendMessage(hUpDown, UDM_SETPOS, 0, 6);

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