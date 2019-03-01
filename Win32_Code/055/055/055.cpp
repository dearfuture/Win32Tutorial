#include<windows.h> 


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
		//获取设备上下文句柄
		HDC   hdc = BeginPaint(hWnd, &ps);
 
		//创建画笔
		HPEN  hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
		//将笔选入到设备上下文(使用这支笔)
		SelectObject(hdc, hPen);

		//1.画直线(两个点)
		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 200, 100);

		//创建画刷
		HBRUSH hBsh = CreateSolidBrush(RGB(0, 255, 0));
		//将画刷选入到设备上下文(使用这支画刷)
		SelectObject(hdc, hBsh);
		 
		//2.画矩形(正方形)
		Rectangle(hdc, 200, 200, 400, 400);


		//获取透明画刷
		HGDIOBJ hBsh2  =GetStockObject(NULL_BRUSH);
		SelectObject(hdc, hBsh2);
		Rectangle(hdc,  100, 100, 200, 150);

		//3.画椭圆（圆形）
		Ellipse(hdc, 200, 200, 400, 400);
		Ellipse(hdc, 100, 100, 200, 150);


		//4.画饼图 
/*			
        //饼图产生的步骤分解
        Ellipse(hdc, 500, 100, 800, 400); 
		 //从圆心到第一个点的连线
		 MoveToEx(hdc, 650, 250, NULL);
		 LineTo(hdc,1000, 300);  
		 //从圆心到第二个点的连线
		 MoveToEx(hdc, 650, 250, NULL);
		 LineTo(hdc, 400, 400);
 */		
		 Pie(hdc, 500, 100, 800, 400, 1000, 300,400, 400);


		//删除GDI对象
		DeleteObject(hPen);
		DeleteObject(hBsh);

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
		WS_OVERLAPPEDWINDOW, 100, 100, 1000, 700, NULL, NULL, hInstance, NULL);

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