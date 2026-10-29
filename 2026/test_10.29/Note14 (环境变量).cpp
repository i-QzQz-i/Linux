#define _CRT_SECURE_NO_WARNINGS 

// 
// 1.是什么环境变量
// 
// 1.1命令行参数
// main函数的参数：
// int main(int argc, char* argv[], char* )
// argc：命令行参数的个数
// argv[]：命令行参数列表（支持选项功能）
// 
// 结论：main的命令行参数，是实现程序不同子功能的方法（也就是指令选项的原理）
// 
// 2.一个环境变量 + 一个例子 
// PATH
// 例子：环境变量PATH支持我们不带路径运行系统指令（程序）
// 
// 
// 3.更多的环境变量（用指令env查询，格式：名称=内容）
// 环境变量生命周期：内存、文件
// 
// HOME    家目录
// SHELL   哪个版本的
// USER    
// LOGNAME 
//    su -
// HSITSIZE
// HOSTNAME
// PWD
// OLDPWD
// 
// 
// 4.获取环境变量的办法（环境变量相关命令）
// env
// echo $XXX
// export XXX=
// unset XXX
// set
// 
// 
// 