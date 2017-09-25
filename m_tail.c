#include "types.h"
#include "stat.h"
#include "user.h"

char buf[8192];
char tmp_buf[512];
uint count = 0;

void reader (int fd) {
    
    int n;
    short i;
    while ((n = read(fd, tmp_buf, sizeof(tmp_buf))) > 0) {
            
        for (i = 0; i < n; i++) {
            buf[count++] = tmp_buf[i];
        }
    }
    buf[count] = '\0';
    if ((tmp_buf[n-1] == '\n') && (tmp_buf[n-1] != '\0')) {
        // Read is not completed, halted on new line
        reader(0);
    }
        
    if (n < 0) {
        printf(1, "Read Unsuccessful\n");
        exit();
    }
}


int main (int argc, char *argv[]) {

    short i, j, nfile;
    int fd, nline = 10;
    count = 0;

    if (argc == 1) {
        fd = 0;
        reader(fd);
        // INSERT CODE TO PRINT NLINE FROM BUF
    }

    else if (argc >= 2) { // Evidently, if the above 'if' statement fails, this should work, ie. this could have been an 'else' statement and not an 'else if' statemnt.
        
        if (argv[1][0] == '-') { // Number of lines is specified

            nline = atoi(argv[1] + 1);
            if (argc == 2) {
                // Print nline lines from standard input
                fd = 0;
                reader(fd);
                // INSERT CODE PRINT NLINE FROM BUF
                exit(); // necessary to avoid redundancy about to happen.
            }
            else {
                nfile = argc - 2;
                j = 2;
            }
        }

        else {
            // Number of lines unspecified, nlines(default) = 10
            nfile = argc - 1;
            j = 1;
        }

        for (i = 0; i < nfile; i++) {
            if ((fd = open(argv[i+j], 0)) < 0) {
                // File not opened
                printf(1, "tail: cannot open %s.\n", argv[i+j]);
                exit();
            }
            printf(1, "--------\nFile: %s\n--------\n", argv[i+j]);
            reader(fd);
            // INSERT CODE PRINT NLNE FROM BUF
        }
    }

    {// REMOVE BLOCK
        printf(1, "\n\n\nnumlines = %d\n\n\n", nline);
    }

    exit();
}
