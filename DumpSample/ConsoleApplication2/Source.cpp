#include <windows.h>

#include <Dbghelp.h>
#include<tchar.h>

using namespace std;

 

#pragma auto_inline (off)

#pragma comment( lib, "DbgHelp" )

 

// 为了程序的简洁和集中关注关心的东西，按示例程序的惯例忽略错误检查，实际使用时请注意

LONG WINAPI MyUnhandledExceptionFilter(

struct _EXCEPTION_POINTERS* ExceptionInfo

    )

{

    HANDLE lhDumpFile = CreateFile(_T("DumpFile.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);

 

    MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;

    loExceptionInfo.ExceptionPointers = ExceptionInfo;

    loExceptionInfo.ThreadId = GetCurrentThreadId();

    loExceptionInfo.ClientPointers = TRUE;

    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),lhDumpFile, MiniDumpNormal, &loExceptionInfo, NULL, NULL);

 

    CloseHandle(lhDumpFile);

 

    return EXCEPTION_EXECUTE_HANDLER;

} 

void Fun2()

{

    __try

    {

       static bool b = false;

       

       if(!b)

       {

           b = true;

           int *p = NULL;

           *p = 0;

        }

       else

       {

           MessageBox(NULL, _T("Here"), _T(""), MB_OK);

       }

 

    }

     __except(MyUnhandledExceptionFilter(GetExceptionInformation()))

    {

    }

}

void Fun()

{

    Fun2();

}

int main()

{

    Fun();
    Fun();
    return 1;
}
