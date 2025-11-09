#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <errno.h>
 
int main() 
{ 
    int fd; 
    
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
    
    char arr1[80], arr2[80]; 
    
    while (1) 
    { 
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
        if (fd == -1) {
            perror("open for write");
            return 1;
        }
        
        // Take an input string from user. 
        printf("You: ");
        fflush(stdout);
        if (fgets(arr2, 80, stdin) == NULL) {
            break;
        }
        
        // Write the input string on FIFO and close it 
        if (write(fd, arr2, strlen(arr2) + 1) == -1) {
            perror("write");
            close(fd);
            return 1;
        }
        close(fd); 
        
        // Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY); 
        if (fd == -1) {
            perror("open for read");
            return 1;
        }
        
        // Read from FIFO 
        ssize_t bytes_read = read(fd, arr1, sizeof(arr1)); 
        if (bytes_read == -1) {
            perror("read");
            close(fd);
            return 1;
        }
        
        // Print the read message 
        printf("User2: %s\n", arr1); 
        close(fd); 
    }
    
    return 0; 
}