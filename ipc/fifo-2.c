// C program to implement one side of FIFO 
// This side reads first, then writes 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>
 
int main() 
{ 
    int fd1; 
    
    // FIFO file path 
    char *myfifo = "/tmp/myfifo"; 
    
    // Creating the named file(FIFO) 
    // Check if it already exists
    if (mkfifo(myfifo, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }
    
    char str1[80], str2[80]; 
    
    while (1) 
    { 
        // First open in read only and read 
        fd1 = open(myfifo, O_RDONLY); 
        if (fd1 == -1) {
            perror("open for read");
            return 1;
        }
        
        ssize_t bytes_read = read(fd1, str1, sizeof(str1)); 
        if (bytes_read == -1) {
            perror("read");
            close(fd1);
            return 1;
        }
        
        // Ensure null termination
        str1[bytes_read < 80 ? bytes_read : 79] = '\0';
        
        // Print the read string and close 
        printf("User1: %s", str1); 
        close(fd1); 
        
        // Now open in write mode and write 
        // string taken from user. 
        printf("You: ");
        fflush(stdout);
        
        if (fgets(str2, 80, stdin) == NULL) {
            break;
        }
        
        fd1 = open(myfifo, O_WRONLY); 
        if (fd1 == -1) {
            perror("open for write");
            return 1;
        }
        
        if (write(fd1, str2, strlen(str2) + 1) == -1) {
            perror("write");
            close(fd1);
            return 1;
        }
        close(fd1); 
    } 
    
    return 0; 
}