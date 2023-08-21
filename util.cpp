#include "include/util.h"
// 读取/proc/stat文件
vector<unsigned long long> getCpuInfo()
{
    vector<unsigned long long> cpuInfo;
    ifstream statFile("/proc/stat");
    if (!statFile.is_open())
    {
        cerr << "Failed to open /proc/meminfo" << endl;
    }
    string firstLine;
    getline(statFile, firstLine);
    istringstream iss(firstLine);

    // 第一个字符串是“cpu”，跳过
    string cpuLable;
    iss >> cpuLable;

    unsigned long long value;
    while (iss >> value)
    {
        cpuInfo.push_back(value);
    }
    statFile.close();
    return cpuInfo;
}

// 计算cpu使用率（%）
float calCpuUsage(const vector<unsigned long long> &preCpuInfo, const vector<unsigned long long> &curCpuInfo)
{
    unsigned long long preCpuIdleTime = preCpuInfo[3] + preCpuInfo[4];
    unsigned long long curCpuIdleTime = curCpuInfo[3] + curCpuInfo[4];

    unsigned long long preCpuTotalTime = 0;
    unsigned long long curCpuTotalTime = 0;

    int size = preCpuInfo.size();
    for (int i = 0; i < size; i++)
    {
        preCpuTotalTime += preCpuInfo[i];
        curCpuTotalTime += curCpuInfo[i];
    }

    unsigned long long totalTimeDiff = curCpuTotalTime - preCpuTotalTime;
    unsigned long long idleTimeDiff = curCpuIdleTime - preCpuIdleTime;

    float ret = (totalTimeDiff - idleTimeDiff) / static_cast<float>(totalTimeDiff) * 100.0;
    return ret;
}

// 计算内存使用率
double calMemUsage()
{
    ifstream memInfo("/proc/meminfo");
    if (!memInfo.is_open())
    {
        cerr << "Failed to open /proc/meminfo" << endl;
    }
    long memTotal = 0, memAvailable = 0;
    string line;
    while (getline(memInfo, line))
    {
        if (line.compare(0, 9, "MemTotal:") == 0)
        {
            memTotal = stol(line.substr(9));
        }
        else if (line.compare(0, 13, "MemAvailable:") == 0)
        {
            memAvailable = stol(line.substr(13));
        }
    }
    double memUsage = static_cast<double>(memTotal - memAvailable) / memTotal * 100.0;
    return memUsage;
}

double calDiskUsage(const string &path)
{
    struct statvfs vfs;
    if (statvfs(path.c_str(), &vfs))
    {
        cerr << "Failed to get disk usage for path " << path << endl;
    }
    unsigned long long totalSpace = vfs.f_blocks * vfs.f_frsize ;
    // cout<<"totalSpace = "<<totalSpace<<endl;
    
    unsigned long long availSpace = vfs.f_bavail * vfs.f_frsize;
    // cout<<"availSpace = "<<availSpace<<endl;
    double diskUsage = static_cast<double>(totalSpace - availSpace) / totalSpace * 100;
    return diskUsage;
}
