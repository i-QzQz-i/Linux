#define _CRT_SECURE_NO_WARNINGS 

//
//		 自动化构建项目make/makefile
// 
//			make/makefile		  //
// 是什么（自动化编译）
// make是一个命令
// makefile/Makefile是一个文件
// 
// makefile基本概念 --- 依赖关系，依赖方法
// 
// code.exe:code.c                         （依赖关系：没有关系谁理你）
//(打一个Tap) gcc -o code code.c           （依赖方法：你要干神魔）
// .PHONY:clean
// clean:
//            rm -rf *.o
// 
// 可执行程序放最前面
// 
// .PHONY:（本质是忽略M时间）（也可以放在开头或结尾）
// 声明伪目标（不是真实的文件），防止与本地文件重名导致"make 命令"不执行
// 也就等通于必须执行.PHONY修饰的命令
// 
// 
// stat --- "ACM"时间
// 文件 == 内容 + 属性
// Access: 最近访问(读取，打开)时间
// Modify: 最近修改文件内容数据的时间
// Change: 修改文件属性(元数据)的时间（特殊：不是时实更新，修改多次更新一次）（因为文件的属性有些宽泛，频繁修改也不好）
// 
// 
//			搭建自己的make/makefile
// 




// 
// stat --- "ACM"时间
// 
// man touch
// touch
// 
// 
//






// 2026.6.27 过去的覆辙，我不想重蹈