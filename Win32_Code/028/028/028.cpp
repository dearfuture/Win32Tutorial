#include<windows.h>
#include<stdio.h> 
#include<Richedit.h>//���ı��༭�ؼ���ͷ�ļ�
 
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
		HWND  hCtrl = (HWND)lParam;
		if (CtrlID == 111)
		{
			WORD  code= HIWORD(wParam);
			if (code == EN_CHANGE)
			{
				TCHAR buf[64];
				GetWindowText(hCtrl, buf, 64);
				MessageBox(NULL, buf,L"��ʾ",MB_OK);
			}
		}


	}break;

	case  WM_NOTIFY:
	{
		//�ȿ�����ͷ��
		NMHDR *pHDR = (NMHDR *)lParam;
		if (pHDR->code == EN_SELCHANGE)
		{
			SELCHANGE  * pSC= (SELCHANGE *)lParam;
			TCHAR   buf[64];
			wsprintf(buf, L"ѡ���ı�����%d - %d\n", pSC->chrg.cpMin, pSC->chrg.cpMax);
			OutputDebugString(buf);
		} 

	}break;

	case WM_CREATE:
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		
		//������ض�̬��
		LoadLibrary(L"Msftedit.dll");

		HWND  hRichEdit=CreateWindow(MSFTEDIT_CLASS, L"����һ�����ı��༭�ؼ�������",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE|ES_AUTOVSCROLL, 30, 30, 200, 200, hWnd, (HMENU)111, pcs->hInstance, NULL);

		//ѡ������2-7���ı�
		SendMessage(hRichEdit, EM_SETSEL, 2, 7);
		//��ʾѡ�񱳾�ɫ
		SendMessage(hRichEdit, EM_HIDESELECTION,0 , 0);

		//�Ȼ�ȡĬ�ϵ��ַ���ʽ
		CHARFORMAT   cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT));
		cf.cbSize = sizeof(CHARFORMAT);
		SendMessage(hRichEdit, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM) &cf);

		//��ѡ������ּӴ�
		cf.dwMask |= CFM_BOLD;
		cf.dwEffects |= CFE_BOLD;

		//�����»���
		cf.dwMask |= CFM_UNDERLINE;
		cf.dwEffects |= CFE_UNDERLINE;

		//���������С
		cf.dwMask |= CFM_SIZE;
		cf.yHeight =20*20;

		//��������
		cf.dwMask |= CFM_FACE;
		wcscpy(cf.szFaceName ,  L"����");

		//����������ɫ
		cf.dwMask |= CFM_COLOR;
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		cf.crTextColor = RGB(255, 0, 0);

		//����ѡ���ַ��ĸ�ʽ
		SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

		//ȡ��ѡ��
		SendMessage(hRichEdit, EM_SETSEL, -1, -1);

		//���ø��ı��༭��ı���ɫ
		SendMessage(hRichEdit, EM_SETBKGNDCOLOR, 0, (LPARAM)  RGB(0,255,0));

		//���Ϳؼ����ݸı��¼���ѡ��ı��¼�����
		SendMessage(hRichEdit, EM_SETEVENTMASK, 0, (LPARAM)ENM_CHANGE|  ENM_SELCHANGE);


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