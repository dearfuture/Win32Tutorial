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
	case  WM_COMMAND:
	{
		WORD  CtrlID = LOWORD(wParam);
		WORD   code = HIWORD(wParam);
	}break;

	case  WM_NOTIFY:
	{
		NMHDR  * pHDR = (NMHDR  *)lParam;
		if (pHDR->code == PGN_CALCSIZE)
		{
			//���ð������ڵĴ�С
			LPNMPGCALCSIZE   pNM = (LPNMPGCALCSIZE)lParam;
			if (pNM->dwFlag == PGF_CALCWIDTH)//ˮƽ���ĵļ����ȣ���ֱ������Ҫ����߶�
			{
				pNM->iWidth = 600;
				pNM->iHeight = 30;
			}
			return 0;
		}
		if (pHDR->code == PGN_SCROLL)
		{
			//֪ͨһ�ι�������
			LPNMPGSCROLL   pNM = (LPNMPGSCROLL)lParam;
			pNM->iScroll = 500;  //�޸Ĺ�������
		}


	}break;

	case WM_CREATE:
	{
		//������ҳ�ؼ�
		HWND   hPage = CreateWindow(WC_PAGESCROLLER, NULL,
			WS_CHILD | WS_VISIBLE | PGS_HORZ, 30, 30, 200, 50, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);
		
		//����һ�����ݱȽϳ��İ�ť 
		HWND hBtn=CreateWindow(WC_BUTTON,  L"��ʼ������һ������ܳ��ܳ��ܳ��ܳ��ܳ��ܳ��ܳ��ܳ��ܳ��ܳ��İ�ť�����ڲŽ�����",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hPage/*�������Ƿ�ҳ�ؼ�*/, (HMENU)222, GetModuleHandle(NULL), NULL);

		//���÷�ҳ�ؼ����Ӵ���
		SendMessage(hPage, PGM_SETCHILD, 0, (LPARAM)hBtn);

		//���ð�ť��ͷ�Ŀ��
		SendMessage(hPage, PGM_SETBUTTONSIZE, 0, (LPARAM) 30);

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