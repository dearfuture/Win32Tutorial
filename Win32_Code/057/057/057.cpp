#include<windows.h>
#include<CommCtrl.h> 


//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC   hdc = BeginPaint(hWnd, &ps);
 
		 //1.创建兼容内存DC,此时它的大小时1X1，很小，不能绘制
		HDC  hMemDC=CreateCompatibleDC(hdc);

		//2.创建兼容位图，提供绘画区域
		HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, 100, 100);

		//3.把兼容位图选到兼容内存DC中,此刻DC的大小与位图一致，可以绘制
		SelectObject(hMemDC, hMemBmp);

		//4.在兼容内存DC上进行绘图操作
		SetTextColor(hMemDC, RGB(255, 0, 0));
		TextOut(hMemDC, 0, 0, L"双缓冲技术绘制！", lstrlen(L"双缓冲技术绘制！")); 
		Rectangle(hMemDC, 30, 30, 80, 80);

		//5.把内存DC中的图像一次性画到窗口DC上
		 //不拉伸
		 BitBlt(hdc, 0, 0, 100, 100, hMemDC, 0, 0, SRCCOPY);
		
		 //拉伸(目标矩形大于源矩形)
		 StretchBlt(hdc, 0, 0, 400, 400, hMemDC, 0, 0,100,100, SRCCOPY);
		 //压缩(目标矩形小于源矩形)
		 StretchBlt(hdc, 0, 0, 50, 50, hMemDC, 0, 0, 100, 100, SRCCOPY);


		 //释放资源
		 DeleteDC(hMemDC);
		 DeleteObject(hMemBmp);


		EndPaint(hWnd, &ps);
	}
	break;

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
	HWND    hWnd = CreateWindow(L"MrHuang", L"第一个窗口程序",
		WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);

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