#include "include/util.h"
#include <unistd.h>
#include <iomanip>
int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            vector<unsigned long long> preCpuInfo = getCpuInfo();
            sleep(3);
            vector<unsigned long long> curCpuInfo = getCpuInfo();
            float cpuUsage = calCpuUsage(preCpuInfo, curCpuInfo);
            cout << setiosflags(ios::fixed) << setprecision(2) << "CPU Usage is " << cpuUsage << " %" << endl;
        }
        else if (strcmp(argv[i], "-m") == 0)
        {
            double memUsage = calMemUsage();
            cout << setiosflags(ios::fixed) << setprecision(2) << "Mem Usage is " << memUsage << " %" << endl;
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            if (i + 1 == argc)
            {
                cerr << "Path is null" << endl;
                continue;
            }
            char *path = argv[i + 1];
            double diskUsage = calDiskUsage(path);
            cout << setiosflags(ios::fixed) << setprecision(2) << "Disk Usage is " << diskUsage << " %" << endl;
        }
    }

    return 0;
}