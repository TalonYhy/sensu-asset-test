#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <sys/statvfs.h>
using namespace std;

// 读取/proc/stat文件
vector<unsigned long long> getCpuInfo();

// 计算cpu使用率（%）
float calCpuUsage(const vector<unsigned long long> &preCpuInfo, const vector<unsigned long long> &curCpuInfo);

// 计算内存使用率（%）
double calMemUsage();

double calDiskUsage(const string &path);
