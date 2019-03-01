#include<windows.h>
#include<stdio.h>
#pragma comment( linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")


int   WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE   hPrevInstance,
	LPSTR  lpCmdLind, int  nShowCmd)
{
	//程序实例句柄
	printf("%p    %p   %p\n", hInstance, hPrevInstance, GetModuleHandle(NULL));

	//程序命令行字符串
	printf("%s\n", lpCmdLind);

	//运用程序窗口的初始显示方式
	printf("%d\n", nShowCmd);

	MessageBox(NULL, L"hello", L"提示", MB_OK);
	return 0;
}