#include "types.h"
#include "stat.h"
#include "user.h"

struct sentence {
    ushort index;
    char *string;
};

char buffer[512];

// potential problem if returning an initialized pointer ?
char* strsplicer(const char input_string[], int RL, int LL) {
    uint i, size = sizeof(char) * (RL - LL + 2);
    char *temp = (char *)malloc(size);

    memset(temp, 0, size);

    for(i = 0; i < (RL - LL + 1); i++) {
        temp[i] = input_string[i + LL];
    }
    return temp;
}

//// todo Make the lines array storage circular and also, handling a small buffer when a sentance gets mid cut off
//// Note: Read does not insert a null byte into the buffer. But it seems like xv6 / qemu initializes the entire memory space to null before hand
void tail(int fd, int numlines) {
    struct sentence lines[numlines], temp;
    int n = 0, i = 0, last_new_line = 0, j = 0;
    ushort index = 0;

    for (i = 0 ; i < numlines ; i++)
        lines[i].string = (char *)malloc(sizeof(char));

    while((n = read(fd, buffer, sizeof(buffer))) > 0) {

        for (i = 0, last_new_line = 0 ; i < n + 1 ; i++) {
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                free(lines[index % numlines].string);
                lines[index % numlines].string = strsplicer(buffer, i, last_new_line);
                lines[index % numlines].index = index;
                last_new_line = i + 1;
                index++;
            }
        }
    }

    for (i = 1; i < numlines; i++) {
        for (j = i; j > 0 && lines[j - 1].index > lines[j].index ; j--) {
            temp = lines[j];
            lines[j] = lines[j -1];
            lines[j - 1] = temp;
        }
    }

    for (i = 0 ; i < numlines ; i++)
        printf(1, "%s", lines[i].string);
}

int main (int argc, char *argv[]) {
    int fd, i, numfiles = 1, numlines = 10;

    if (argc <= 1) {
        //printf(1, "Usage: %s filename\n", argv[0]);
        tail(0, numlines);
	exit();
    }

    if (argc > 2) {
        numfiles = 2;
        numlines = atoi(argv[1] + 1); // make idiot proof
    }

    for (i = numfiles; i < argc; i++) {
        if ((fd = open(argv[i], 0)) < 0) {
            printf(1, "tail: cannot open %s.\n", argv[i]);
            exit();
        }
        tail(fd, numlines);
        close(fd);
    }
    exit();
}
