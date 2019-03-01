#include<windows.h>
#include<stdio.h>

  

//�Զ���Ĵ��ڹ���
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	  case WM_DESTROY:
		PostQuitMessage(0);//����ʹGetMessage����0    
		return 0; 

	  case WM_ERASEBKGND:
	  {  
		  static  int  j = 0;
	      char str[64];
	      sprintf(str, "��%d�β���WM_ERASEBKGND��\n", ++j);
	      OutputDebugStringA(str);//��������ڴ�ӡ��Ϣ
	      return  1; 
	  }

	  case WM_PAINT:
	  {  PAINTSTRUCT  ps;
	  HDC  hdc = BeginPaint(hWnd, &ps);//ʹ��Ч��������Ч

	  static  int  i = 0;
	  char str[64];
	  sprintf(str, "��%d�β���WM_PAINT��\n", ++i);
	  OutputDebugStringA(str);//��������ڴ�ӡ��Ϣ

	  EndPaint(hWnd, &ps);
	  return 0;
	  }
	  case  WM_LBUTTONDOWN:
		  //InvalidateRect(hWnd, NULL, true);//��Ӹ�������
		  //UpdateWindow(hWnd);//��������Ϊ�գ������Ϸ���WM_PAINT��Ϣ
		
		  //���ܴ��ڵ��κβ����Ƿ���Ч�����ᵼ��WM_PAINT��Ϣ�����������ڡ�
		  RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
		  break;

	  case  WM_NCPAINT://�Զ�����Ʒǿͻ���
		  HDC  hdc = GetWindowDC(hWnd); 
		  RECT  r;
		  r.left = 0;
		  r.top = 0;
		  r.right = 300;
		  r.bottom = 30;
		  HBRUSH  brh = CreateSolidBrush(RGB(255, 0, 0));
		  FillRect(hdc, &r, brh);
		  SetBkMode(hdc, TRANSPARENT);
		  TextOutA(hdc, 5, 5, "�Զ��崰�ڱ���", 14);//���һ������Ϊ�ַ�������
		  DeleteObject(brh);
		  ReleaseDC(hWnd,  hdc);
		  return  true;
		  //break;
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
		HWND  hWnd = CreateWindow(L"MrHuang", L"��һ�����ڳ���",
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