#include<windows.h> 
#include"resource.h"

//�Զ���ĶԻ��򴰿ڹ���
INT_PTR   CALLBACK   MyDlgProc(HWND  hDlg, UINT  Msg, WPARAM  wParam, LPARAM  lParam)
{

	switch (Msg)
	{ 

	case WM_INITDIALOG:
	{
		//���öԻ������
		SetWindowText(hDlg, L"�û���¼");
		//���öԻ���ͼ��
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
			wsprintf(str, L"�û�����%s  ����:%s", name, pwd);
			MessageBox(hDlg, str, L"��ʾ", MB_OK);
		} 
			break;

		case IDCANCEL:
			DestroyWindow(hDlg);//���ٷ�ģ̬�Ի���
			PostQuitMessage(0);//WM_QUIT�˳���Ϣѭ��
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
	//������ģ̬�Ի���
	HWND  hDlg=CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
		GetDesktopWindow(), MyDlgProc);
	//��ʾ�Ի���
	ShowWindow(hDlg, SW_SHOW);


	//��Ϣѭ��
	MSG  msg;
	while (GetMessage(&msg, NULL,  0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return   TRUE;
}