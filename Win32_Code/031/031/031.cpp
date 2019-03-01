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

	case WM_CREATE:
	{  
		//�����̶����ؼ�
		HWND   hTackbar = CreateWindow(TRACKBAR_CLASS, L"XXX",
			WS_CHILD | WS_VISIBLE|  TBS_TOP|TBS_AUTOTICKS|TBS_ENABLESELRANGE, 30, 30, 200, 70, hWnd, (HMENU)111,
			GetModuleHandle(NULL), NULL);

		//���ò������ķ�Χ
		SendMessage(hTackbar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10));

		//���ò������Ļ���λ��
		SendMessage(hTackbar, TBM_SETPOS, TRUE,  5 );
		 
		//���û����ѡ������
		SendMessage(hTackbar, TBM_SETSEL, TRUE,   MAKELPARAM(1,3));


	}break;

	case  WM_HSCROLL:
	{
		WORD  code = LOWORD(wParam);//ָʾ�û��Ĺ�����Ϊ
		WORD  value = HIWORD(wParam);//����code��TB_THUMBPOSITION��TB_THUMBTRACK ��HIWORD(wParam)ָ���ڹ�����ĵ�ǰλ�ã�������ԣ�
		HWND   hCtrl =(HWND) lParam;//�ؼ����
  
/*  code��ֵ��
#define TB_LINEUP               0
#define TB_LINEDOWN             1
#define TB_PAGEUP               2
#define TB_PAGEDOWN             3
#define TB_THUMBPOSITION        4
#define TB_THUMBTRACK           5
#define TB_TOP                  6
#define TB_BOTTOM               7
#define TB_ENDTRACK             8
		*/

		UINT  v = SendMessage(hCtrl, TBM_GETPOS, 0, 0);

		TCHAR  buf[64] = {0};
		wsprintf(buf, L"��ǰλ��: %d   LOWORD: %d   HIWORD: %d\n" ,  v, code ,value);
		OutputDebugString(buf);

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