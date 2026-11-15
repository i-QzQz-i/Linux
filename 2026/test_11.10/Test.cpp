#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>

#include <iostream>
#include <string>

#define COMMAND_SIZE 1024

// 模拟argv[]与argc
#define COMMANDARG_SIZE 128
char *c_argv[COMMANDARG_SIZE];
int c_argc;

// 记录前一目录与当前目录
#define CWD_SIZE 1024
char prev_cwd[CWD_SIZE];
char cwd[CWD_SIZE];

void InitializeArg()
{
  memset(c_argv, 0, sizeof(c_argv));
  c_argc = 0;
}

void PrintCommandPrompt()
{
#define PRINT_SIZE 256
  char pwd_buf[PRINT_SIZE];
  getcwd(pwd_buf, sizeof(pwd_buf));
  char *DirName = basename(pwd_buf);

  printf("[%s@%s %s]# ",getenv("USER"), getenv("HOSTNAME"), DirName);
}

bool ReadCommand(char *str, int len)
{
    memset(str, 0, len);
    if(!fgets(str, len, stdin))
    {
      return false;
    }
    int c_size = strlen(str);
    if(c_size > 0 && str[c_size - 1] ==  '\n')
    {
      str[c_size - 1] = '\0';
    }

    return true;
}

void CommandParse(char *str)
{
  char *token = strtok(str, " ");
  
  for(c_argc = 1; token != NULL && c_argc < COMMANDARG_SIZE; c_argc++)
  {
    c_argv[c_argc - 1] = token;
    token = strtok(NULL, " ");
  }
  
  c_argv[c_argc] = NULL;
}

bool CheckAndExecBuiltin()
{
  std::string cmd = c_argv[0];
  if(cmd == "cd")
  {
    char tmp[CWD_SIZE];
    if(c_argv[1] == NULL)
    {
      return true;
    }
    else if(*c_argv[1] == '-')
    {
      strcpy(tmp, prev_cwd);
      chdir(prev_cwd);
    }
    else if(*c_argv[1] == '~')
    {
      strcpy(tmp, getenv("HOME"));
      chdir(getenv("HOME"));
    }
    else
    {
      getcwd(tmp, sizeof(tmp));
      chdir(c_argv[1]);
    }
    // 更新prev_cwd与cwd
    strcpy(prev_cwd, cwd);
    strcpy(cwd, tmp);

    return true;
  }
  
  if(cmd == "echo")
  {


    return true;
  }

  //if(cmd == " ")


  return false;
}

void Execute()
{
  pid_t id = fork();

  if(id == 0)
  {
    execvp(c_argv[0], c_argv);
    exit(1);
  }
  
  pid_t rid = waitpid(id, NULL, 0);
  (void)rid;
}

int main()
{

  // 初始化全局目录
  getcwd(cwd, sizeof(cwd));
  strcpy(prev_cwd, cwd);

  while(1)
  {
    // 0.初始化argv[]与argc
    InitializeArg();
    
    // 1.输出命令行提示符
    PrintCommandPrompt();    

    // 2.获取用户命令
    char GetCommand[COMMAND_SIZE];
    if(!ReadCommand(GetCommand, sizeof(GetCommand)))
      continue;

    // 3.命令行分析 （命令 -选项...）
    CommandParse(GetCommand);

    // 4.检测处理内建命令
    if(CheckAndExecBuiltin())
      continue;

    // 5.执行命令
    Execute();

  }


  return 0;
}
