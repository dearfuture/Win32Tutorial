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
		if (pHDR->code == TTN_SHOW)
		{ 
			//MessageBox(hWnd, L"��ʾ��Ҫ������", L"��ʾ" ,MB_OK);
			OutputDebugString(L"��ʾ��Ҫ������\n");
		}
		 
	}break;

	case WM_CREATE:
	{
		//������ʾ�ؼ�
		HWND  hTip = CreateWindow(TOOLTIPS_CLASS, NULL,
			WS_POPUP|TTS_BALLOON, 0, 0, 0, 0, hWnd, NULL/*����NULL*/, GetModuleHandle(NULL), NULL);
		
		//����ʾ�ؼ�ע��  ����
		TOOLINFO  ti;
		ti.cbSize = sizeof(TOOLINFO);
		ti.hinst = GetModuleHandle(NULL);
		ti.hwnd = hWnd;  //ָ�����ĸ���������ʾtip
		ti.lpszText = L"����һ����ʾ�ؼ��������������ȥ֮������û�һЩ��Ϣ��";
		GetClientRect(hWnd, &ti.rect/*����Ƶ��ĸ����� */); 
		ti.uFlags = TTF_SUBCLASS;
		ti.uId = (UINT_PTR)hTip; //tip�Ĵ��ھ��

		//ע����Ҫtip�Ĵ���
		SendMessage(hTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

		//����tip���ڵĿ��
		SendMessage(hTip, TTM_SETMAXTIPWIDTH, 0, (LPARAM)100);

		//����tip����ʾʱ��(����)
		SendMessage(hTip, TTM_SETDELAYTIME, TTDT_AUTOPOP,  MAKELPARAM( 10*1000, 0 ));

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