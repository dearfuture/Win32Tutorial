#include<windows.h> 


//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0;

	case WM_RBUTTONDOWN:
	{
	    //���������˵�
		HMENU  hPop=CreatePopupMenu();
		AppendMenu(hPop, MF_STRING, 111, L"�½�");
		AppendMenu(hPop, MF_STRING, 222, L"��");

		//ת������
		POINT pt = { LOWORD(lParam)  ,HIWORD(lParam) }; //�Լ����ڵĿͻ���
		ClientToScreen(hWnd,&pt);

		//��ָ��λ�õ����˵�(�����x��y���������Ļ���Ͻǵ�����)
		TrackPopupMenu(hPop, TPM_CENTERALIGN|TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);

		//�ͷŲ˵���Դ
		DestroyMenu(hPop);


	}break;

	case WM_COMMAND:
	{
		//�˵�ID
		WORD  menuId = LOWORD(wParam);
		switch (menuId)
		{
		case 222:
			MessageBox(hWnd, L"�򿪲˵����", L"��ʾ", MB_OK);
			break;
		case 111:
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