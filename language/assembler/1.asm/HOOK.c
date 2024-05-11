//内联钩子（Inline Hook）实现
void InlineHook(DWORD dwHookAddr, LPVOID pFunAddr)
{
    BYTE jmpCode[5] = {0xE9};
    //计算偏移
    *(DWORD*)(&jmpCode[1]) = (DWORD)pFunAddr - dwHookAddr - 5;
    // 保存以前的属性用于还原
    DWORD OldProtext = 0;
    DWORD dwWritten;
    // 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
    VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);
    WriteProcessMemory(GetCurrentProcess(), (FARPROC)dwHookAddr, jmpCode, 5, &dwWritten);
    VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}

int main()
{
    //故意让程序暂停
    getchar();
    //执行函数
    InlineHook((DWORD)&demo, &fake_demo);
    demo();
}

