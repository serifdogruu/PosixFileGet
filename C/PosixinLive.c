#include <stdio.h> 
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <time.h>
#include <stdlib.h>
/*
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 10000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
*/





int main(){
    

    FILE *file = fopen("realtimesave.txt", "w");
    
    if (file == NULL) {
        // If file couldn't be opened, print an error and exit
        perror("Error opening file");
        return 1;
    }
    
    int temp;
    struct sysinfo info ; 
    struct rlimit resinfo ;
    struct sockaddr sockets ;
    int x = 0 ;
    
    while(1){


        if (sysinfo(&info) == 0) {  
            printf("Uptime : %ld seconds \n ", info.uptime);
            
            FILE *filex = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
            fscanf(filex, "%d", &temp);

            printf("CPU Temperature: %.2f°C\n", temp / 1000.0);

            fclose(filex);

            printf("Total Ram : %ld MB/n \n ", info.totalram / 1024 / 1024);
            printf("Free Ram: %ld MB/n \n ", info.freeram / 1024 / 1024) ;
            printf("1, 5, and 15 minute load averages: %ld MB/n \n ", info.loads[3] / 1024 / 1024) ;
            printf("Sockets :  %d  \n" , sockets.sa_family);
            printf("rlimit :  %ld  \n" , resinfo.rlim_max);


            fprintf(file, "Uptime : %ld seconds \n ", info.uptime);
            fprintf(file,"Total Ram : %ld MB/n \n ", info.totalram / 1024 / 1024);
            fprintf(file,"Free Ram: %ld MB/n \n ", info.freeram / 1024 / 1024);
            fprintf(file,"1, 5, and 15 minute load averages: %ld MB/n \n ", info.loads[3] / 1024 / 1024);
            fprintf(file,"Sockets :  %d  \n" , sockets.sa_family);
            fprintf(file,"rlimit :  %ld  \n" , resinfo.rlim_max);

            fprintf(file,"#############################epoch : %d##############################################\n",x);
            fflush(file);

        } else {

            perror("sysinfo");

    }
        printf("#############################%d##############################################\n",x);
        x++;
        
        
        sleep(2);
        
    }
    return 0 ; 


}












