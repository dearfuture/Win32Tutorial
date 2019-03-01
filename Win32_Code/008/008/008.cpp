#include<stdio.h>
#include<string.h>
#include <Locale.h>
#include<windows.h>

int  main()
{
	char  *str1 = "A中";
	printf("%s     %d\n", str1, strlen(str1)); //计算字符个数3，遇到\0结束


	_wsetlocale(LC_ALL, L"chs");
	wchar_t *str2= L"A中"; //必须加L表示字符串是unicode
	wprintf(L"%s     %d\n", str2, wcslen(str2)); //计算字符个数2，遇到\0结束
	 

	//MessageBox();

	return 0;
}