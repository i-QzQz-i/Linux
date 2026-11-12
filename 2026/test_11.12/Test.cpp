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

// 记录最后一个程序的退出状态
int lastcode;

// 从父进程获取环境变量
#define ENV_SIZE 256
char *c_env[ENV_SIZE];

void InitEnv()
{
  // 获取环境变量
  extern char **environ;
  int size = 0;
  for(;environ[size];size++)
  {
    c_env[size] = (char*)malloc(strlen(environ[size]) + 1);
    strcpy(c_env[size], environ[size]);
  }
  
  c_env[size] = NULL;
  
  // 载入环境变量
  for(int i = 0;i < size;i++)
  {
    putenv(c_env[i]);
  }

  //证明是自己的环境变量表
  setenv("MYENV","---114514---",1);
}

void InitializeShell()
{
  // 初始化家目录与前一目录
  getcwd(cwd, sizeof(cwd));
  strcpy(prev_cwd, cwd);

  // 开辟环境变量表
    
  // 模拟shell启动时，从系统获取环境变量
  InitEnv();
}

void InitializeArg()
{
  memset(c_argv, 0, sizeof(c_argv));
  memset(c_env, 0, sizeof(c_env));
  c_argc = 0;
  lastcode = 0;
}

void PrintCommandPrompt()
{
  // 借助getcwd\basename函数获取DirName
  // 也可以用strtok函数，以'/'为分隔符切出
#define PRINT_SIZE 256
  char pwd_buf[PRINT_SIZE];
  if(getcwd(pwd_buf, sizeof(pwd_buf)))
  {
    setenv("PWD", pwd_buf, 1);
  }
  char *DirName = basename(pwd_buf);

  printf("[%s@%s %s]# ",getenv("USER"), getenv("HOSTNAME"), DirName);
}

bool ReadCommand(char *str, int len)
{
    memset(str, 0, len);
    if(!fgets(str, len, stdin))
    {
      lastcode = 1;
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
  
  for(c_argc = 0; token != NULL && c_argc < COMMANDARG_SIZE; c_argc++)
  {
    c_argv[c_argc] = token;
    token = strtok(NULL, " ");
  }
  
  c_argv[c_argc] = NULL;
}

void Cd()
{
    char tmp[CWD_SIZE];
    if(c_argv[1] == NULL)
    {
      return;
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
}

void Echo()
{
    std::string opt = c_argv[1];

    if(opt == "$?")
    {
      printf("%d\n",lastcode);
    }
    else if(opt[0] == '$')
    {
      char* env_buf = c_argv[1];
      
      printf("%s\n",getenv(env_buf + 1));
    }
    else
    {
      //printf("%s\n",c_argv[1]);

      printf("%s\n",opt.c_str());
    }    
}

bool CheckAndExecBuiltin()
{
  std::string cmd = c_argv[0];
  if(cmd == "cd")
  {
    Cd();
    return true;
  }
  
  if(cmd == "echo")
  {
    if(c_argc == 2)
    {
      Echo();
    }
    else
    {
      printf("echo 输入非法\n");
      lastcode = 1;
    }
    return true;
  }

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
  lastcode = rid;
}

int main()
{

  // 初始化shell(全局目录、环境变量表)
  InitializeShell();

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

    // 测试命令行参数
    //printf("%d\n",c_argc);
    //for(int i = 0; i < c_argc+3; i++)
    //{
    //  printf("%s___", c_argv[i]);
    //}
    //printf("\n");

    // 4.检测处理内建命令
    if(CheckAndExecBuiltin())
      continue;

    // 5.执行命令
    Execute();

  }


  return 0;
}
