#include<windows.h> 
#include"resource.h"

HBRUSH  bsh=NULL;

//�Զ���ĶԻ������
INT_PTR  CALLBACK    MyDlgProc(HWND hDlg, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case  WM_INITDIALOG://�ڶԻ�����ʾ֮ǰ��������
	{

		HWND hEdit = CreateWindow(L"EdiT",
			L"����һ���༭��ؼ�������",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_NOHIDESEL,
			30, 100, 200, 100, hDlg, (HMENU)1111,
			GetModuleHandle(NULL), NULL);

		return  TRUE;//��������Ϣ
	}

	case  WM_CTLCOLORDLG :  //����ǰ��ѧϰ��WM_CTLCOLORBTN
	{
		//������ˢ
	    bsh=  CreateSolidBrush(RGB(255, 0, 0));
		return  (INT_PTR)bsh;
	}


	case  WM_COMMAND://�˵��������ť�������Ϣ
	{
		switch ( LOWORD(wParam))
		{
		case IDOK:
			//���ٶԻ���
			EndDialog(hDlg, 666 ); //�����666����ΪDialogBox�ķ���ֵ
			DeleteObject(bsh);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 999);
			DeleteObject(bsh);
			break;
		}

		return  TRUE;
	}
	 
	}
		
	return FALSE;//û�������Ϣ
}


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;
		 
	case WM_LBUTTONDOWN:
	{
		//���ݶԻ�����Դ����ģ̬�Ի��� 
		int ret= DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDlgProc);
		ret = ret; 
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