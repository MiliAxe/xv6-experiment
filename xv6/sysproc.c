#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_set_limit(void)
{
  int limit;
  struct proc *p = myproc();

  if(argint(0, &limit) < 0)
    return -1;

  // TODO: This might need to be atomic?
  myproc()->cpu_limit = limit;

  cprintf("Limit set to %d\n", limit);
  return 0;
}

int
sys_set_mem_limit(void)
{
  int limit;
  struct proc *p = myproc();

  if(argint(0, &limit) < 0)
    return -1;
  
  p->memory_limit = limit;

  return 0;
}

int
sys_get_mem_limit(void)
{
  struct proc *p = myproc();

  return p->memory_limit;
}

int
sys_increase_mem_limit(void)
{
  int limit;
  struct proc *p = myproc();

  if(argint(0, &limit) < 0)
    return -1;

  p->memory_limit += limit;

  return 0;
}

int
sys_increase_mem_usage(void)
{
  int usage;
  struct proc *p = myproc();

  if(argint(0, &usage) < 0)
    return -1;

  // Don't increase memory usage if the process is sh
  if (memcmp(p->name, "sh", 2) == 0) {
    cprintf("ignored sh shell memory usage increase\n");
    return 0;
  }

  p->memory_used += usage;
  cprintf("Memory usage increased by %d, from process: %s\n", usage, p->name);

  return 0;
}

int
sys_get_mem_usage(void)
{
  struct proc *p = myproc();

  return p->memory_used;
}