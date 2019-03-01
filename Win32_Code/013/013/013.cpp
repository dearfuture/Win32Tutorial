#include<windows.h>
#include<stdio.h>

  

//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	  case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0; 

	  case WM_ERASEBKGND:
	  {  
		  static  int  j = 0;
	      char str[64];
	      sprintf(str, "第%d次产生WM_ERASEBKGND！\n", ++j);
	      OutputDebugStringA(str);//在输出窗口打印信息
	      return  1; 
	  }

	  case WM_PAINT:
	  {  PAINTSTRUCT  ps;
	  HDC  hdc = BeginPaint(hWnd, &ps);//使无效区域变得有效

	  static  int  i = 0;
	  char str[64];
	  sprintf(str, "第%d次产生WM_PAINT！\n", ++i);
	  OutputDebugStringA(str);//在输出窗口打印信息

	  EndPaint(hWnd, &ps);
	  return 0;
	  }
	  case  WM_LBUTTONDOWN:
		  //InvalidateRect(hWnd, NULL, true);//添加更新区域
		  //UpdateWindow(hWnd);//更新区域不为空，则马上发出WM_PAINT消息
		
		  //不管窗口的任何部分是否无效，都会导致WM_PAINT消息被发布到窗口。
		  RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);
		  break;

	  case  WM_NCPAINT://自定义绘制非客户区
		  HDC  hdc = GetWindowDC(hWnd); 
		  RECT  r;
		  r.left = 0;
		  r.top = 0;
		  r.right = 300;
		  r.bottom = 30;
		  HBRUSH  brh = CreateSolidBrush(RGB(255, 0, 0));
		  FillRect(hdc, &r, brh);
		  SetBkMode(hdc, TRANSPARENT);
		  TextOutA(hdc, 5, 5, "自定义窗口标题", 14);//最后一个参数为字符串长度
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
		//1.注册窗口类
		WNDCLASS  wnd;
		wnd.cbClsExtra = 0;
		wnd.cbWndExtra = 0;
		wnd.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));//背景色
		wnd.hCursor = LoadCursor(NULL, IDC_ARROW);//光标
		wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标
													//wnd.lpfnWndProc = DefWindowProc;//默认窗口过程函数，用于处理消息
		wnd.lpfnWndProc = MyWindowProc;//自定义的窗口过程函数
		wnd.lpszClassName = L"MrHuang";//窗口类名
		wnd.lpszMenuName = NULL;//菜单资源名称
		wnd.style = CS_HREDRAW | CS_DBLCLKS;//窗口类、样式
		wnd.hInstance = hInstance;//实例句柄
		RegisterClass(&wnd);

		//创建窗口(返回之前发送WM_CREATE)
		HWND  hWnd = CreateWindow(L"MrHuang", L"第一个窗口程序",
			WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, hInstance, NULL);

		//显示窗口
		ShowWindow(hWnd, nShowCmd);
		//更新窗口(发送WM_PAINT)
		UpdateWindow(hWnd);


		//消息循环（收到WM_QUIT消息退出）
		MSG  msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);//翻译消息
			DispatchMessage(&msg);//分发消息到窗口过程
		}
	}