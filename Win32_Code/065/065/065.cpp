#include<windows.h> 
#include"resource.h"

//自定义的对话框窗口过程
INT_PTR   CALLBACK   MyDlgProc(HWND  hDlg, UINT  Msg, WPARAM  wParam, LPARAM  lParam)
{

	switch (Msg)
	{ 

	case WM_INITDIALOG:
	{
		//设置对话框标题
		SetWindowText(hDlg, L"用户登录");
		//设置对话框图标
		HICON  icon = LoadIcon(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hDlg, WM_SETICON, ICON_SMALL,
			(LPARAM)icon);
		DestroyIcon(icon);


		return  TRUE;
	}

	case    WM_COMMAND:
	{
		UINT  id = LOWORD(wParam);

		switch (id)
		{
		case ID_BTN_LOGIN :
		{
			TCHAR  name[64] = { 0 };
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 64);
			TCHAR  pwd[64] = { 0 };
			GetDlgItemText(hDlg, IDC_EDIT_PWD, pwd, 64);
			TCHAR  str[256] = { 0 };
			wsprintf(str, L"用户名：%s  密码:%s", name, pwd);
			MessageBox(hDlg, str, L"提示", MB_OK);
		} 
			break;

		case IDCANCEL:
			DestroyWindow(hDlg);//销毁非模态对话框
			PostQuitMessage(0);//WM_QUIT退出消息循环
			break;
		}

		return TRUE;
	}

	default:
		break;
	}

	return  FALSE;
}


int  WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE  hPrevInstance,
	LPSTR lpCmdLine, int  nShowCmd)
{
	//创建非模态对话框
	HWND  hDlg=CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
		GetDesktopWindow(), MyDlgProc);
	//显示对话框
	ShowWindow(hDlg, SW_SHOW);


	//消息循环
	MSG  msg;
	while (GetMessage(&msg, NULL,  0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return   TRUE;
}