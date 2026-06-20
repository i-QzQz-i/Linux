#define _CRT_SECURE_NO_WARNINGS 

//
//			gcc/g++			//
// gcc与g++操作相同
// 1.预处理（头文件展开、宏替换、去注释、条件编译）
// gcc -E code.c -o code.i（预处理之后就停下来） 
// 
// 2.编译（生成汇编）
// gcc -S code.i -o code.s
// (gcc -S code.c -o code.s 其实也可以,只是会把预处理在做一次)
// 
// 3.汇编（生成机器可识别码）
// gcc -c code.s -o code.o
// 
// 4.链接（生成可执行文件或库文件）
// gcc code.o - code（已经是二进制的文件了）
// 
// -ESc(esc)
// .iso(镜像文件)
//
// 
// 一般先把.c代码都生成.o在一起打包生成
// gcc -c code(123).c
// gcc code1.o code2.o code3.o -o code
// 
// 
// 库：
// 1.动态库：Linux(.so) windows(.dll)
// 
// 2.静态库：Linux(.a) windows(.llb)
// 
// 条件编译：对代码进行动态裁剪
//

// 
// gcc code.c  -> a.out
// gcc code.c -o mycode
//                      ---> mycode
// gcc -o mycode code.c
// 
// gcc -o mycode code.c -DM=100(命令行级别的宏定义)
// 
// ldd + 可执行程序 （查看依赖哪些库）
// 
// 
// 
// 
// 
// 
// 
//
