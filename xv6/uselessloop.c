#include "types.h"
#include "stat.h"
#include "user.h"


int test_cpu_limit(int limit, int ticks) {
    volatile int i = 0;
    int starting_time = uptime();

    set_limit(limit);

    while (i < ticks) {
        i++;
    }

    return uptime() - starting_time;
}

int main(int argc, char *argv[]) {
    int starting_time = uptime();

    int test_ticks = atoi(argv[1]);

    int current_cpu_limit = 100;

    int initial_cpu_ticks = test_cpu_limit(current_cpu_limit, test_ticks);
    printf(1, "Initial CPU ticks: %d\n", initial_cpu_ticks);

    while (current_cpu_limit - 10 > 0) {
        int new_cpu_limit = current_cpu_limit - 10;
        int new_cpu_ticks = test_cpu_limit(new_cpu_limit, test_ticks);
        printf(1, "CPU limit: %d, CPU ticks: %d, Compared to initial: %d%%\n", new_cpu_limit, new_cpu_ticks, (new_cpu_ticks * 100) / initial_cpu_ticks);
        current_cpu_limit = new_cpu_limit;
    }

    exit();
}