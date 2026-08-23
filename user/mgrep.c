#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[1024];
int match(char *, char *);
int matchhere(char *, char *);
int matchstar(int, char *, char *);

void
grep(char *pattern, int fd, int processId)
{
  int n, m;
  char *p, *q;

  m = 0;
  while ((n = read(fd, buf + m, sizeof(buf) - m - 1)) > 0) {
    m += n;
    buf[m] = '\0';
    p = buf;
    while ((q = strchr(p, '\n')) != 0) {
      *q = 0;
      if (match(pattern, p)) {
        *q = '\n';
        printf("(Worker PID: %d)  ",processId);
        write(1, p, q + 1 - p);
      }
      p = q + 1;
    }
    if (m > 0) {
      m -= p - buf;
      memmove(buf, p, m);
    }
  }
}

int
match(char *re, char *text)
{
  if (re[0] == '^')
    return matchhere(re + 1, text);
  do { // must look at empty string
    if (matchhere(re, text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

// matchhere: search for re at beginning of text
int
matchhere(char *re, char *text)
{
  if (re[0] == '\0')
    return 1;
  if (re[1] == '*')
    return matchstar(re[0], re + 2, text);
  if (re[0] == '$' && re[1] == '\0')
    return *text == '\0';
  if (*text != '\0' && (re[0] == '.' || re[0] == *text))
    return matchhere(re + 1, text + 1);
  return 0;
}

// matchstar: search for c*re at beginning of text
int
matchstar(int c, char *re, char *text)
{
  do { // a * matches zero or more instances
    if (matchhere(re, text))
      return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;
}


int main(int argc, char *argv[]){

    if(argc < 3){
        printf("Enter valid number of arguments.\n");
        exit(1);
    }

    for(int i = 2 ; i < argc ; i++){
        int pid = fork();
        // printf("argv : %s \n", argv[i]);
        if(pid < 0){
            printf("Child process creation failed.\n");
            exit(1);
        }
        
        else if (pid == 0){
            // inside child process
            int processId = getpid();
            int fd = open(argv[i],O_RDONLY);
            grep(argv[1], fd, processId);
            close(fd);
            exit(0);
            // char *newArg[] = {"grep", argv[1], argv[i], 0};
            // printf("Worker PID: %d  ", getpid()); 
            // exec("grep", newArg);
            // printf("exec failed\n");
            // exit(1);
        }
        else{
            //inside parent process
            // int status;
            wait(0);
            // int dpid = wait(0);
            // printf("terminated child id: %d\n", dpid);
        }
    }

    exit(0);
}