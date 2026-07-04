#include "process.h"
#include <string>
#include <unistd.h>
#include <cstdio>
using namespace std;

#define SUM 20000
#define V 100

void Process_v1()
{
    string arr(100, ' ');
    string con = "-/|\\";
    for(int i = 0; i <= 100; ++i)
    {
        printf("\r[%s][%d%%][%c]", arr.c_str(), i, con[i%4]);
        fflush(stdout);
        usleep(20000);
        arr[i] = '#';
    }
    printf("\n");
}

void Process_v2()
{
    string arr(100, ' ');
    string con = "-/|\\";
    int sum = 0;
    int tmp = 0;

    while(sum <= 100)
  {
    int _sum = sum;
    tmp += V;
    sum = tmp * 100 / SUM;

    for (int i = _sum; i < sum && i <= 100; ++i)
    {
        arr[i] = '#';
        printf("\r[%s][%d%%][%c]", arr.c_str(), i, con[i % 4]);
        fflush(stdout);
    }

    usleep(20000);
  }

    printf("\n");
}
