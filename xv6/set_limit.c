#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    printf(1, "Setting limit to 10\n");
    int result = set_cpu_limit(atoi(argv[1]));
    printf(1, "Result: %d\n", result);
    exit();
}