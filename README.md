# xv6 OS w/ slight modifications

This repository contains my experimentation with the xv6 OS.

The following syscalls have been added to the operating system:

```c
int set_cpu_limit(int limit); // Set cpu usage limit
int set_mem_limit(int limit); // Set process memory limit
int get_mem_limit(void); // Get current process memory limit
int increase_mem_limit(int limit); // Increase current process's memory limit by 'limit' (limit can be negative)
int increase_mem_usage(int usage); // Increase current process's memory usage
int get_mem_usage(void); // Get current process memory usage
int set_limit(int cpu_limit, int mem_limit); // Set memory and CPU limit for the current process
```

## Disclaimer

This project was originally meant for a course project.
