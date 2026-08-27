#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

extern struct proc proc[];

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0; // not reached
}

uint64
sys_sqNumber(void){
  int n;
  argint(0, &n);
  return n*n;
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

extern struct spinlock wait_lock;
uint64
sys_getppid(void)
{
  int parentId;
  acquire(&wait_lock);
  struct proc *p = myproc()->parent;
  parentId = p->pid;
  release(&wait_lock);
  return parentId;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_nfork(void)
{
  int n;
  uint64 child_pid;
  argint(0, &n);
  argaddr(1, &child_pid);

  struct proc *p = myproc();
  for (int i = 0; i < n; i++) {
    int childId = kfork();
    if (childId == 0) return 0;
    // if it failed to create child then that child id is stored as negetive only
    kwait(0);
    if (copyout(p->pagetable, p->sz, child_pid, (char *)&childId, sizeof(int)) < 0) {
      return -1; // Handle error if user pointer is invalid
    }
    child_pid = child_pid + sizeof(int);
  }
  return n;
}

uint64 
sys_print_syscalls(void){
  struct proc *p = myproc();
  int n = sizeof(p->sysCallCount)/(sizeof(int));
  int *arr = p->sysCallCount;
  printk("syscall_number     invocation\n");
  for(int i=0; i< n; i++){
    printk("%d        %d \n", i+1, arr[i]);
  }

  return 1;
}

uint64 
sys_print_process_syscalls(void){

  int pid;
  argint(0, &pid);
  struct proc *p;
  int processFound = 0;
  for(p = proc; p < &proc[NPROC]; p++){
    if(p->state != UNUSED && p->pid == pid){
      //we got our proc structure
      processFound = 1;
      break;
    }
  }
  if(!processFound){
    printk("Process not found! \n");
    return -1;
  }
  int n = sizeof(p->sysCallCount)/(sizeof(int));
  int *arr = p->sysCallCount;
  printk("syscall_number     invocation\n");
  for(int i=0; i< n; i++){
    printk("%d        %d \n", i+1, arr[i]);
  }
  return 1;
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_get_child_count(void)
{
  return myproc()->childCount;
}

uint64
sys_get_process_child_count(void)
{
  int pid;
  int childCount = -1;
  argint(0, &pid);
  struct proc * p;
  for(p = proc; p < &proc[NPROC]; p++){
    if(p->state != UNUSED && p->pid == pid){
      //we got our proc structure
      acquire(&p->lock);
      childCount = p->childCount;
      release(&p->lock);
      return childCount;
    }
  }
  return -1;
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if (t == SBRK_EAGER || n < 0) {
    if (growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if (addr + n < addr)
      return -1;
    if (addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (killed(myproc())) {
      release(&tickslock);
      return -1;
    }
    sleep_prepare(&ticks);
    release(&tickslock);
    sleep();
    acquire(&tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
