#include<windows.h>
#include<CommCtrl.h> 

//ָ���嵥����������޷�����SysLink�ؼ�
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls'  \
version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")


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
		if ((pHDR->code == NM_CLICK)  && ( pHDR->idFrom = 111))
		{
			PNMLINK  pLink = (PNMLINK)lParam;
			LITEM  & item = pLink->item;

			if (item.iLink == 0)//��һ��<a>��ǩ
			{
				//����վitem.szUrl;
				ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
			}
			else  if (item.iLink == 1)//�ڶ���<a>��ǩ
			{
				ShellExecute(NULL, L"open", L"https://www.baidu.com", NULL, NULL, SW_SHOW);
			}

		}
	 
	}break;

	case WM_CREATE:
	{ 
		//���������ӿؼ�
		HWND  hLink = CreateWindow(WC_LINK,
			L"<A  href=\"https://nmwsoft.taobao.com/\">���ǳ�����</A>�Ұ��й���<A  id=\"he\"  href=\"hello\">���ǵڶ���������</A>", WS_CHILD | WS_VISIBLE,
			30, 30, 200, 30, hWnd, (HMENU)111, GetModuleHandle(NULL), NULL);

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