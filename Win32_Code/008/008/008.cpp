#include<stdio.h>
#include<string.h>
#include <Locale.h>
#include<windows.h>

int  main()
{
	char  *str1 = "A��";
	printf("%s     %d\n", str1, strlen(str1)); //�����ַ�����3������\0����


	_wsetlocale(LC_ALL, L"chs");
	wchar_t *str2= L"A��"; //�����L��ʾ�ַ�����unicode
	wprintf(L"%s     %d\n", str2, wcslen(str2)); //�����ַ�����2������\0����
	 

	//MessageBox();

	return 0;
}