#include<windows.h>
#include<stdio.h>
#pragma comment( linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")


int   WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE   hPrevInstance,
	LPSTR  lpCmdLind, int  nShowCmd)
{
	//����ʵ�����
	printf("%p    %p   %p\n", hInstance, hPrevInstance, GetModuleHandle(NULL));

	//�����������ַ���
	printf("%s\n", lpCmdLind);

	//���ó��򴰿ڵĳ�ʼ��ʾ��ʽ
	printf("%d\n", nShowCmd);

	MessageBox(NULL, L"hello", L"��ʾ", MB_OK);
	return 0;
}