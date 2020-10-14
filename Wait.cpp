#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cstdio>
#include <unistd.h>

int main(void)
{
  pid_t pid;
  if((pid = fork()) == -1)
    perror("fork"),exit(1);

  if(pid == 0){
    sleep(20);
    exit(10);
  }
  else{
    int st;
    int ret = wait(&st);

    if(ret > 0 && (st & 0x7F) == 0){ //正常退出
       printf("child exit code:%d\n",(st>>8)&0xFF);
       // st>>8表示把status的低八位右移出去
       // (status>>8)&0xFF表示把status的低八位右移出去(系统会给status补够32位)
    }else if(ret > 0){
      // 异常退出
      printf("sig code : %d\n",st&0x7F);
    }
  }
}
