#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>


int main()
{
  int i = 0;

  pid_t p = fork();

  if(p == 0)
  {
    printf("我是子进程, pid: %d, ppid: %d\n",getpid(),getppid());
    //printf("%d\n",++i);
    printf("开始替换进程\n");

    //execl("/usr/bin/ls", "-l", NULL);

    //execlp("ls", "ls", "-l", NULL);
    
    //execl("/usr/bin/ls", "ls", "-l", NULL);
    
    char* const argv[] = {
      (char*)"ls", 
      (char*)"-l", 
      (char*)"-a",
      NULL
    };

    //execv("/usr/bin/ls", argv);
    
    //execvp(argv[0], argv);
    
    execvp("/usr/bin/ls", argv);

    exit(123);
  }
  else
  {
    printf("我是父进程, pid: %d, ppid: %d\n",getpid(),getppid());
    //printf("%d\n",--i);
  }

  //wait(&i);
  waitpid(p, &i, 0);

  printf("子进程退出码：%d\n",WEXITSTATUS(i));


  return 0;
}
