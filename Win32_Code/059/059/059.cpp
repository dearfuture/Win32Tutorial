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

	case  WM_CREATE:
	{
		//��������˵�
		HMENU  hTop = CreateMenu();//�ղ˵�
		AppendMenu(hTop, MF_STRING, 100, L"�ļ�"); //��ӵ�һ��
		InsertMenu(hTop, 0, MF_STRING | MF_BYPOSITION, 200, L"����"); //��ӵڶ���

																	//���������˵�(�Ӳ˵�)
		HMENU  hPopUp = CreatePopupMenu();//�ղ˵� 
		AppendMenu(hPopUp, MF_SEPARATOR, NULL, NULL);//�ָ���
		AppendMenu(hPopUp, MF_STRING, 301, L"��");
		InsertMenu(hPopUp, 0, MF_STRING | MF_BYPOSITION, 302, L"�½�");

		//��ӵ�����
		AppendMenu(hTop, MF_POPUP, (UINT_PTR)hPopUp, L"��2");
	
		 //���ô��ڲ˵�
		SetMenu(hWnd, hTop);

		//�ͷŲ˵���Դ
		DestroyMenu(hTop);
		DestroyMenu(hPopUp);


	
	}break;

	case WM_COMMAND:
	{ 
		//�˵�ID
		WORD  menuId = LOWORD(wParam);
		switch (menuId)
		{
		case 100:
			MessageBox(hWnd, L"�ļ��˵����", L"��ʾ", MB_OK);
			break;
		case 200:
			MessageBox(hWnd, L"���߲˵����", L"��ʾ", MB_OK);
			break;
		case 301:
			MessageBox(hWnd, L"�򿪲˵����", L"��ʾ", MB_OK);
			break;
		case 302:
			MessageBox(hWnd, L"�½��˵����", L"��ʾ", MB_OK);
			break;
		} 

	}  break;

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