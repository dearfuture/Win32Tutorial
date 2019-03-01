#include<windows.h>
#include<CommCtrl.h> //公共控件的头文件
 

//自定义的窗口过程
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0    
		return 0;  

	 case WM_CREATE: 
	 {   
		 //创建动画控件
		HWND  hAnimate= CreateWindow(ANIMATE_CLASS, L"XXX", WS_CHILD | WS_VISIBLE | ACS_CENTER,
			10, 10, 350, 350, hWnd, (HMENU)111, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		//打开一个AVI剪辑动画
		SendMessage(hAnimate, ACM_OPEN, NULL, (LPARAM)L"C:\\Users\\35497\\Desktop\\code\\030\\Debug\\clock.avi");

		//播放剪辑动画（wparam播放次数，-1循环播放，  lparam 低字节开始，高字节结束  ）
		SendMessage(hAnimate, ACM_PLAY, -1 ,  MAKELPARAM(0,-1));


	 }break; 
	  
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
	wnd.hCursor= LoadCursor(NULL, IDC_ARROW);//光标
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标
	//wnd.lpfnWndProc = DefWindowProc;//默认窗口过程函数，用于处理消息
	wnd.lpfnWndProc =MyWindowProc;//自定义的窗口过程函数
	wnd.lpszClassName = L"MrHuang";//窗口类名
	wnd.lpszMenuName = NULL;//菜单资源名称
	wnd.style = CS_HREDRAW| CS_DBLCLKS;//窗口类、样式
	wnd.hInstance = hInstance;//实例句柄
	RegisterClass(&wnd);

	//创建窗口(返回之前发送WM_CREATE)
	HWND    hWnd = CreateWindow(L"MrHuang",L"第一个窗口程序",
		WS_OVERLAPPEDWINDOW,100,100,400 ,400,NULL,NULL, hInstance,NULL );
	 

	//显示窗口
	ShowWindow(hWnd, nShowCmd); 
	//更新窗口(发送WM_PAINT)
	UpdateWindow(hWnd);
	 

	 //消息循环（收到WM_QUIT消息退出）
	MSG  msg; 
	while ( GetMessage(&msg, NULL, 0,0 ) )
	{  
		TranslateMessage(&msg);//翻译消息
		DispatchMessage(&msg);//分发消息到窗口过程
	}
}