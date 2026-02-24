// 下面这几行为CE的某次结果

//mov eax, [esi + 00005560]
//esi:13057478
//
//mov esi, [edi + 00000768]
//edi : 02ABA330
//
//mov edi, [006A9F38]
//也就是说基址为：006A9F38
//注：除了基址以外的地址都是动态地址，必须通过基址和偏移来计算得到

// 这是整个代码的核心逻辑，注释中是每一步的操作和结果：
// 第1步：从基址得到一级指针
//ReadProcessMemory(hProcess, (LPCVOID)0x006A9F38, &ptr1, sizeof(ptr1), NULL);
// ptr1 = 0x02ABA330
//
// 第2步：从一级指针+偏移得到二级指针
//ReadProcessMemory(hProcess, (LPCVOID)(ptr1 + 0x768), &ptr2, sizeof(ptr2), NULL);
// ptr2 = 0x13057478
//
// 第3步：计算最终地址（注意：这里不是读，是计算）
//sunAddr = ptr2 + 0x5560;  // = 0x1305C9D8
//
// 第4步：读取阳光值
//ReadProcessMemory(hProcess, (LPCVOID)sunAddr, &sunValue, sizeof(sunValue), NULL);
// sunValue = 9999

#include <stdio.h>
#include <windows.h>
int main() {
	// 查找游戏窗口
	HWND hwnd = FindWindow(L"MainWindow", L"植物大战僵尸中文版");
	if (hwnd == NULL) {
		printf("未找到窗口\n");
		return 1;
	}
	printf("已锁定窗口\n");

	// 根据窗口句柄获取进程ID
	DWORD dwPID;
	GetWindowThreadProcessId(hwnd, &dwPID);
	if (dwPID == 0) {
		printf("获取进程ID失败\n");
		return 1;
	}
	printf("进程ID: %lu\n", dwPID);

	// 根据进程ID获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (hProcess == NULL) {
		printf("获取进程句柄失败\n");
		return 1;
	}
	printf("已获取进程句柄\n");
	
	// 根据基地址，找到在进程中的地址
	DWORD_PTR SunshineBaseAddr = 0x6A9F38; // 基地址
	DWORD_PTR SunshineBaseRealAddr; // 进程中的地址
	SIZE_T bytes = 0; // 读取的字节数
	if (!ReadProcessMemory(hProcess, (LPCVOID)SunshineBaseAddr, &SunshineBaseRealAddr, sizeof(SunshineBaseRealAddr), &bytes)) {
		printf("读取地址失败%d\n", GetLastError());
		CloseHandle(hProcess);
		return 1;
	}

	// 找到一级偏移地址
	DWORD_PTR OffSet1 = 0x768;
	DWORD_PTR RealAdd1 = 0;
	if (!ReadProcessMemory(hProcess, (LPCVOID)(SunshineBaseRealAddr + OffSet1), &RealAdd1, sizeof(RealAdd1), &bytes)) {
		printf("读取地址失败%d\n", GetLastError());
		CloseHandle(hProcess);
		return 1;
	}

	// 找到二级偏移地址，也就是我们要修改的地址（阳光数量的地址）
	DWORD_PTR OffSet2 = 0x5560;
	DWORD_PTR RealAdd2 = 0;
	RealAdd2 = RealAdd1 + OffSet2; // 直接计算出阳光数量的地址

	// 修改阳光数量
	DWORD num = 0;
	printf("请输入新的阳光数量：");
	scanf_s("%lu", &num);
	DWORD newSunshine = num; // 新的阳光数量
	if (!WriteProcessMemory(hProcess, (LPVOID)RealAdd2, &newSunshine, sizeof(newSunshine), NULL)) {
		printf("修改阳光数量失败%d\n", GetLastError());
		CloseHandle(hProcess);
		return 1;
	}
	return 0;
}