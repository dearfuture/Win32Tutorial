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

		//1.创建内存兼容DC（1px  X  1px）
		HDC  hMemDC = CreateCompatibleDC(hdc);

		//2.加载位图资源
		HBITMAP hBmp= (HBITMAP)LoadImage(NULL, L"bg.bmp", IMAGE_BITMAP, 800, 800, LR_LOADFROMFILE);

		//3.把位图选入到兼容内存DC
		SelectObject(hMemDC, hBmp);

		//添加水印
		TextOut(hMemDC, 100, 100, L"乱涂乱画", lstrlen(L"乱涂乱画"));
		 
		//设置图像拉伸模式
		//SetStretchBltMode(hdc, COLORONCOLOR);//删除多余像素
		SetStretchBltMode(hdc, HALFTONE); 

		//4.将兼容DC中的图像一次性拷贝到窗口DC上
		 //BitBlt(hdc, 0, 0, 800, 800, hMemDC, 0, 0, SRCCOPY);
		//完整显示
		 StretchBlt(hdc, 0, 0, 400, 400, hMemDC, 0, 0, 800,800,SRCCOPY);

		//5.释放DC与位图资源
		DeleteObject(hBmp);
		DeleteDC(hMemDC);
	  
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