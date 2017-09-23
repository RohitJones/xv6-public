#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int i, no = 25;
    if (argc == 2)
        no = atoi(argv[1] + 1);
    for (i = 0; i < no ; i++) {
        printf(1, "\n");
    }
    exit();
}