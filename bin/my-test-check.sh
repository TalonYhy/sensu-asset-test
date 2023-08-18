#!/bin/bash

# # 设置环境变量
export LD_LIBRARY_PATH=../lib




# 检查系统中是否已安装 g++
if ! g++ --version &> /dev/null; then
  echo "g++ 未安装，将下载并安装..."
  if command -v apt-get &> /dev/null; then
      sudo apt-get update
      sudo apt-get install -y g++
  fi
fi

# 显示 g++ 版本信息
echo "g++已安装成功，版本信息为："
g++ --version

# 生成可执行文件
g++ -o test ../main.cpp -L../lib -lmyutil
./test $@
