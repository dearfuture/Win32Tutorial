#include<windows.h>
#include<CommCtrl.h>  
//#include"resource.h"
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
		if (code == 0)
		{

		}

	}break;

	case  WM_NOTIFY:
	{
		NMHDR  * pHDR = (NMHDR  *)lParam;
		if (pHDR->code == RBN_CHILDSIZE)
		{
			LPNMREBARCHILDSIZE  pNM = (LPNMREBARCHILDSIZE)lParam;
			RECT  rcBand= pNM->rcBand;
			RECT  rcChild = pNM->rcChild; 
			TCHAR  buf[64] = { 0 };
			wsprintf(buf, L" %drcBand  %d ,%d,%d ,%d\n", pNM->wID,rcBand.left, rcBand.top, rcBand.right, rcBand.bottom);
			OutputDebugString(buf);


		}

	}break;

	case WM_CREATE:
	{
		//����Rebar�ؼ�
		HWND  hRebar = CreateWindow(REBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | RBS_VARHEIGHT,
			0, 0, 0, 0, hWnd, NULL, GetModuleHandle(NULL), NULL);


		//�ӿؼ�
		HWND hBtn = CreateWindow(WC_BUTTON,
			L"��ť�ؼ�",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0,
			0, 0,
			hRebar, //��������Rebar
			(HMENU)111,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);


		HWND hEdit = CreateWindow(WC_EDIT,
			L"�༭�ؼ�",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			0, 0,
			0, 0,
			hRebar, //��������Rebar
			(HMENU)222,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		//��������
		REBARBANDINFO  rb;
		rb.cbSize = sizeof(REBARBANDINFO);
		rb.lpText = L"�ؼ���1";
		rb.fMask = RBBIM_ID |RBBIM_TEXT|RBBIM_STYLE |RBBIM_CHILDSIZE| RBBIM_CHILD;
		rb.fStyle = RBBS_GRIPPERALWAYS;
		rb.cxMinChild = 100;
		rb.cyMinChild = 30;
		rb.hwndChild = hBtn; 
		rb.wID = 1000;
		SendMessage(hRebar, RB_INSERTBAND, 0, (LPARAM)&rb);


		//��������2
		REBARBANDINFO  rb2;
		rb2.cbSize = sizeof(REBARBANDINFO);
		rb2.lpText = L"�ؼ���2";
		rb2.fMask = RBBIM_ID | RBBIM_TEXT | RBBIM_STYLE | RBBIM_CHILDSIZE | RBBIM_CHILD;
		rb2.fStyle = RBBS_GRIPPERALWAYS;
		rb2.cxMinChild = 100;
		rb2.cyMinChild =30;
		rb2.hwndChild = hEdit;
		rb2.wID = 2000;
		SendMessage(hRebar, RB_INSERTBAND, -1, (LPARAM)&rb2);


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