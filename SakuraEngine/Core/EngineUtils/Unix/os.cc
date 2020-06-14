/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-09 19:30:30
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-14 15:46:09
 */
#include "Core/EngineUtils/os.h"
#include <unistd.h>
#if defined(__APPLE__) || defined(SAKURA_TARGET_PLATFORM_OSX)
#include <mach-o/dyld.h>
#endif

namespace Sakura::os
{
    Sakura::string env(const char* name)
    {
        char* x = getenv(name);
        return x ? Sakura::string(x) : Sakura::string();
    }

    Sakura::string homedir()
    {
        return os::env("HOME");
    }

    Sakura::string cwd()
    {
        char buf[512];
        char* s = getcwd(buf, 4096);
        return s ? Sakura::string(s) : Sakura::string();
    }

    Sakura::string exename()
    {
        Sakura::string s = os::exepath();
        return s.substr(s.rfind('/') + 1);
    }

    int pid(void)
    {
        return (int)getpid();
    }

    int cpunum(void)
    {
        static int ncpu = (int)sysconf(_SC_NPROCESSORS_ONLN);
        return ncpu;
    }

#if defined(__linux__) || defined(SAKURA_TARGET_PLATFORM_LINUX)
    Sakura::string exepath() {
        char buf[4096] = { 0 };
        int r = (int) readlink("/proc/self/exe", buf, 4096);
        return r > 0 ? Sakura::string(buf, r) : Sakura::string();
    }
#else
    Sakura::string exepath() {
        char buf[4096] = { 0 };
        uint32_t size = sizeof(buf);
        int r = _NSGetExecutablePath(buf, &size);
        return r == 0 ? Sakura::string(buf) : Sakura::string();
    }
#endif
}
