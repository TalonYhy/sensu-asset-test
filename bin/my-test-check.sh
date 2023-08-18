#!/bin/bash

# 获取当前容器状态（这里有点问题，需要容器名，默认情况下主机名就是容器名）
container_name=$(hostname)
lxc-info -n $container_name

# # 设置环境变量
export LD_LIBRARY_PATH=../lib

# 生成可执行文件
g++ -o test ../main.cpp -L../lib -lmyutil
./test $@