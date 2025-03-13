#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define FIFO_NAME "/tmp/myfifo"

int syslogf(){

    int fd = open("/var/log/syslog", O_RDONLY); // Open a system log file
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead); // Print to stdout
    }
    close(fd);
    return 0;
}


int cpu(){

    FILE *file = fopen("/proc/cpuinfo", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;

}

int memusage(){

    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
        perror("Failed to open /proc/meminfo");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}

int temp(){

    FILE *file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!file) {
        perror("Failed to open temp file");
        return 1;
    }

    int temp;
    fscanf(file, "%d", &temp);
    fclose(file);

    printf("CPU Temperature: %.2f°C\n", temp / 1000.0);
    return 0;


}
/*
int inter_process_com(){

    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO");
        return 1;
    }

    char buffer[256];
    while (read(fd, buffer, sizeof(buffer)) > 0) {
        printf("Received: %s\n", buffer);
    }

    close(fd);
    return 0;



}


*/


#define SHELLSCRIPT "clear"
int main() {

    syslogf();
    
    printf("##################################################################################\n");
    cpu();
    printf("##################################################################################\n");
    memusage();
    printf("##################################################################################\n");
    temp();
    printf("##################################################################################\n");
    system(">> out.txt");

}




