#define unix
#ifdef unix
  // http://linux.die.net/man/2/setrlimit
  #include <sys/time.h>
  #include <sys/resource.h>
#endif

// #define WINDOWS
#ifdef WINDOWS
  // https://msdn.microsoft.com/en-us/library/ms686234%28VS.85%29.aspx
  // https://msdn.microsoft.com/en-us/library/ms683179%28v=vs.85%29.aspx
  #include <windows.h>
#endif

// ...

int main() {
#ifdef unix
    struct rlimit rlim;
    // getrlimit(RLIMIT_AS, &rlim);
    // std::cout << "rlim_cur:" << rlim.rlim_cur << "\n";
    // std::cout << "rlim_max:" << rlim.rlim_max << "\n";
    rlim.rlim_cur  = rlim.rlim_max  = 500000000LL;
    setrlimit(RLIMIT_AS, &rlim);
    // getrlimit(RLIMIT_AS, &rlim);
    // std::cout << "rlim_cur:" << rlim.rlim_cur << "\n";
    // std::cout << "rlim_max:" << rlim.rlim_max << "\n";
#endif
#ifdef WINDOWS
    HANDLE hProcess = GetCurrentProcess();
    SIZE_T dwMinimumWorkingSetSize, dwMaximumWorkingSetSize;
    dwMinimumWorkingSetSize = dwMaximumWorkingSetSize = 500000000;
    SetProcessWorkingSetSize(hProcess, dwMinimumWorkingSetSize, dwMaximumWorkingSetSize);
#endif

 // ...

}
