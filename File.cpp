#include <windows.h>
#include <iostream>

using namespace std;
int main()
{
	HANDLE hFind;
	//HANDLE...ポインタ,ファイル等を識別するための番号
	WIN32_FIND_DATA win32fd;
	//FindFirstFileやFindNextFile関数を格納するための宣言
	hFind = FindFirstFile("/.*.*", &win32fd);
	//&win32fdにファイルを格納

	if (hFind != INVALID_HANDLE_VALUE) { 
					//INVALID_HANDLE_VALUE = true のようなもの
		cout << "Foo" << endl;
		return 1;	//見つからなかった場合エラーを返す
	}
	cout << hFind << endl;
	do {
		if (win32fd.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY) {
			//dwFileAttributesのオフセットは0,FILE_ATTRIBUTE_DIRECTORYはディレクトリ
			//ディレクトリだった場合(FILE_ATTRIBUTE_DIRECTORY = 1)
			printf("%s (DIR)\n", win32fd.cFileName);
		} else {
			//ディレクトリでなかった場合(FILE_ATTRIBUTE_DIRECTORY = 0)
			printf("%s\n", win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);
	//指定された検索ハンドルを閉じる，必須

	return 0;
}
