#include<windows.h>
#include<CommCtrl.h> //�����ؼ���ͷ�ļ�
 

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
		 //���������ؼ�
		HWND  hAnimate= CreateWindow(ANIMATE_CLASS, L"XXX", WS_CHILD | WS_VISIBLE | ACS_CENTER,
			10, 10, 350, 350, hWnd, (HMENU)111, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		//��һ��AVI��������
		SendMessage(hAnimate, ACM_OPEN, NULL, (LPARAM)L"C:\\Users\\35497\\Desktop\\code\\030\\Debug\\clock.avi");

		//���ż���������wparam���Ŵ�����-1ѭ�����ţ�  lparam ���ֽڿ�ʼ�����ֽڽ���  ��
		SendMessage(hAnimate, ACM_PLAY, -1 ,  MAKELPARAM(0,-1));


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
	wnd.hCursor= LoadCursor(NULL, IDC_ARROW);//���
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//ͼ��
	//wnd.lpfnWndProc = DefWindowProc;//Ĭ�ϴ��ڹ��̺��������ڴ�����Ϣ
	wnd.lpfnWndProc =MyWindowProc;//�Զ���Ĵ��ڹ��̺���
	wnd.lpszClassName = L"MrHuang";//��������
	wnd.lpszMenuName = NULL;//�˵���Դ����
	wnd.style = CS_HREDRAW| CS_DBLCLKS;//�����ࡢ��ʽ
	wnd.hInstance = hInstance;//ʵ�����
	RegisterClass(&wnd);

	//��������(����֮ǰ����WM_CREATE)
	HWND    hWnd = CreateWindow(L"MrHuang",L"��һ�����ڳ���",
		WS_OVERLAPPEDWINDOW,100,100,400 ,400,NULL,NULL, hInstance,NULL );
	 

	//��ʾ����
	ShowWindow(hWnd, nShowCmd); 
	//���´���(����WM_PAINT)
	UpdateWindow(hWnd);
	 

	 //��Ϣѭ�����յ�WM_QUIT��Ϣ�˳���
	MSG  msg; 
	while ( GetMessage(&msg, NULL, 0,0 ) )
	{  
		TranslateMessage(&msg);//������Ϣ
		DispatchMessage(&msg);//�ַ���Ϣ�����ڹ���
	}
}