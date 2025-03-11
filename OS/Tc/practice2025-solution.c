#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> 
#include <string.h>

//compile with: gcc -Wall -g practice2025-solution.c -o exe
//run with: valgrind ./exe

int main() {
    char* s[3];
    int i, j, fd,offset;

    for(i=0; i<3; i++) {
        s[i] = (char*)malloc(128*sizeof(char)); /////////////
        if(fgets(s[i], 128, stdin) == NULL) {
            perror("Error reading the sentence");
            return 1;
        }
    }

    offset = 'a' - 'A';
    for(i=0; i<3; i++) {
        for(j=0; j<strlen(s[i]); j++) {
            if(s[i][j] >= 'a' && s[i][j] <= 'z') {
                s[i][j] -= offset;
            }
            else if(s[i][j] >= 'A' && s[i][j] <= 'Z') {
                s[i][j] += offset;
            }
        }
    }

    fd = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if(fd < 0) {
        perror("Failed to create the output file");
        return 1;
    }
    for(i=0; i<3; i++) {
        write(fd, s[i], strlen(s[i]));
        free(s[i]);
    }
    close(fd);

    return 0;
}