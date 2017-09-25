/* Takes input m_test_text 'Number of lines to print' 'Number of haracters in each line'
 * Prints the output to stdout
 */

#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int l, c;
    int i, j;
    int count = 1;
    l = atoi(argv[1]);
    c = atoi(argv[2]);
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) 
            printf(1, "%d", count);
        printf(1, "\n");
        count = (count + 1) % 10;
    }
    exit();
}
