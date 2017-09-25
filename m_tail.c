/* The whole problem with the program lies in lines 30-48 (while loop)
 * the tmp_buf is being copied into the buf just for the first time
 * the tmp_buf is able to handle \n and is being updated for every line.
 * It's as if buf has been made to constant length after just one time.
 * Otherwise, the input this file can handle is:
 * blah | m_tail
 * blah | m_tail -x
 * m_tail
 * m_tail -x
 * m_tail file 1
 * m_tail -x file 1
 *
 * Should handle :
 * m_tail file file2 ...
 * m_tail -x f1 f2...
 */

#include "types.h"
#include "stat.h"
#include "user.h"

char *buf[8192];
char *tmp_buf[512];
uint count = 0;

void reader (int fd) {
    
    int n;
    short i;
    while ((n = read(fd, tmp_buf, sizeof(tmp_buf))) > 0) {
            
        for (i = 0; i < n; i++) {
            buf[count++] = tmp_buf[i];
                // Tried to make the above line as *buf[count++] = *tmp_buf[i], throws an error, which may be a seg fault.
        }
        count = count - 1;
        *buf[count-2] = '0'; //These are having no effect
        *buf[count-1] = '0';
        *buf[count] = '0';
      /*  if (*buf[n] == '\0') {
                    // I think the problem is here, as if the last char of buf is set to '\0' automatically, but even then, this does not work correctly.
            *buf[n] = '0';
        }
        */
        // REMOVE SUBSEQUENT PRINTF BEFORE SUBMITTING
        printf(1, "Temp buf : %s\n", tmp_buf);
        printf(1, "Buffer after count %d : %s\n", count, buf);
    }
    *buf[count] = '\0';
    if ((*tmp_buf[n-1] == '\n') && (*tmp_buf[n-1] != '\0')) { // or should it be *tmp_buf[n]???
        // Read is not completed, halted on new line
        reader(0);
    }
        
    if (*tmp_buf[n-1] == '\0') {
        // REMOVE SUBSEQUENT PRINTF 
        printf(1, "NULL encountered, read should be completed");
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


    // REMOVE NEXT 2 PRINT LINES BEFORE SUBMITTING!!!
    printf(1, "Printing the buffer : \n%s", buf);
    printf(1, "\nPrinting the temp buffer : %s", tmp_buf);
    exit();
}
