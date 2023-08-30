#!/bin/bash
file_path="/tmp/sensu/final_log.txt"
# 读取txt文件的第一行
read -r line < $file_path

# 设置分隔符为“空格”
IFS=' '

# 将第一行分隔为多个字符串
read -ra array <<< "$line"

# 输出结果
pidns_id_in_log=${array[-1]}

# 获取根进程所在的pid ns id
output=$(ls -l /proc/1/ns/pid)

# | 是管道操作符，表示将前一个命令的输出作为后一个命令的输入。
# grep -oP '(?<=pid:\[)\d+(?=\])' 使用了 grep 命令进行字符串匹配和提取数字部分的操作。
# -o 选项表示只输出匹配到的部分。
# -P 选项用于启用 Perl 兼容的正则表达式语法。
# (?<=pid:\[) 是一个正向后顾断言（positive lookbehind assertion），匹配 "pid:["，但不会包含在输出中。
# \d+ 表示匹配一个或多个数字。
# (?=\]) 是一个正向前瞻断言（positive lookahead assertion），匹配 "]"，但不会包含在输出中。
curr_pid_ns_id=$(echo "$output" | grep -oP '(?<=pid:\[)\d+(?=\])')

if [ $pidns_id_in_log == $curr_pid_ns_id ]
then
    cat $file_path
    # 退出码 1 Sensu会warning
    exit 1
else
    rm -rf $file_path
    exit 0
fi
