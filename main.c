#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <poll.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define COM_OPEN_ERROR 1

#define FINISH_EXECUTION_READ 1
#define FINISH_EXECUTIONWRITE 2


#define COM_READ_SPEED B9600
#define COM_WRITE_SPEED B9600
#define RECEIVED_BUFFER_SIZE 20
#define SENT_BUFFER_SIZE 20
        
struct termios  
                oldsettings, 
                newsettings;
struct pollfd   
                writeEvent, 
                readEvent;
struct sigaction
                sigint_write_struct,
                sigint_read_struct;
const char     
                *path = "/dev/ttyUSB0";
const int       
                SENT_BUFFER_MAX_SIZE = 21,
                RECEIVED_BUFFER_MAX_SIZE = 20;
char            
                SENT_BUFFER [SENT_BUFFER_SIZE]= {},
                RECEIVED_BUFFER[RECEIVED_BUFFER_SIZE]={},
                RECEIVED_BUFFER [20];
int             
                PID,
                CHILD_RET_VALUE,
                received_buffer_size,
                COM_HENDLER;

char            
                FLAG_MASK_EXECUTION = 0;
ushort          
                received_value;

int     read_com(int, int , int, char *);
int     write_com(int, char *, size_t, int);
ushort  init_com(const char*);
ushort  fin_com(unsigned short int);
void  set_sigstructures();
int     set_str();
void    write_perform();
void    read_perform();
ushort  intepreted_foutput(char*);
void    handler_sigint_write(int);
void    handler_sigint_read(int);

int main(){   
    
    int     counter = 0;
    

    if(init_com(path))
        return 1;
    set_sigstructures();
    if((PID = fork())== 0){
        sigaction(SIGINT,&sigint_write_struct, NULL);
        write_perform();
    }
    else{
        sigaction(SIGINT, &sigint_read_struct, NULL);
        read_perform();
    }
}
int read_com(int fd, int len , int timeout, char * buff){
        int ret = 0;
        
        readEvent.fd=fd;
        readEvent.events = POLLIN;
        poll(&readEvent, 1, timeout);
        if(readEvent.revents & POLLIN) {
                ret = read(fd, buff, len);
                buff[len] = '\0';
        }
        if(ret<0){
                ret = 0;
        }
        return ret;
}
void read_perform(){
    while(received_value!=443){

            received_buffer_size = read_com(COM_HENDLER, RECEIVED_BUFFER_SIZE, 100000, RECEIVED_BUFFER);
            if(received_buffer_size==-1)
                printf("UNFATAL_ERROR: read attampt failure\n");

            printf("value getted[%d]: %d\n",received_buffer_size, (received_value=intepreted_foutput(RECEIVED_BUFFER)));
        }
        printf("read performance funktion finised execution successfuly\n");
        waitpid(PID,&CHILD_RET_VALUE, 0);
        printf("child procces finished with value %d\n", CHILD_RET_VALUE);
        return;
}
void write_perform(){
    int     sent_buffer_size,
            sent_bytes_value;
    char   *trash;
    
    while(1){
            if((sent_buffer_size = set_str())==-1){   
                printf("UNFATAL_ERROR: an overflowe has occured\n");
                continue;
            }
            if((SENT_BUFFER[0]=='q') && (SENT_BUFFER[1]=='\0'))
                break;

            printf("str size: %d\n", sent_buffer_size);
            sent_bytes_value = write_com(COM_HENDLER,SENT_BUFFER, sent_buffer_size, 5);
            if(sent_bytes_value != -1)
                printf("%d bytes were written\n", sent_bytes_value);
            SENT_BUFFER[0]='\0';
        }
        
}
int set_str(){
    int size = 0;
    while(scanf("%c",&SENT_BUFFER[size]),SENT_BUFFER[size] !=10) 
    ++size;
    SENT_BUFFER[size]='\0';
    if(size >= SENT_BUFFER_MAX_SIZE)
        return -1;
    return size;
}
int write_com(int fd, char * buf, size_t size, int timeout){
        int ret = 0;
        writeEvent.fd=fd;
        writeEvent.events = POLLOUT;
        
        poll(&writeEvent, 1, timeout);
        if(writeEvent.revents & POLLOUT){
                ret = write(fd, buf, size);
                if(ret == -1){
                    perror("UNFATAL_ERROR: ");
                    return -1;
                }
                tcdrain(fd); 

        }
        
        return ret;
}
void  set_sigstructures(){
    sigaction(SIGINT, NULL, &sigint_read_struct);
    sigint_write_struct = sigint_read_struct;

    sigint_read_struct.sa_handler=handler_sigint_read;
    sigint_write_struct.sa_handler=handler_sigint_write;

}
unsigned short int init_com(const char* path){
    COM_HENDLER = open(path, O_RDWR | O_NOCTTY);
    if(COM_HENDLER == -1)
    {
        perror("ERROR");
        return COM_OPEN_ERROR;
    }
    tcgetattr(COM_HENDLER, &oldsettings); 
    newsettings = oldsettings;
    cfsetispeed(&newsettings, COM_WRITE_SPEED); 
    cfsetospeed(&newsettings, COM_READ_SPEED);
    newsettings.c_cflag &= ~PARENB;
    newsettings.c_cflag &= ~CSIZE;
    newsettings.c_cflag |=  CS8;
    newsettings.c_cflag &= ~CRTSCTS;
    newsettings.c_cflag |= CREAD | CLOCAL;
    newsettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    newsettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    newsettings.c_oflag &= ~OPOST;
    newsettings.c_cc[VMIN] = 1;
    newsettings.c_cc[VTIME] = 10;
    tcsetattr(COM_HENDLER,TCSANOW,&newsettings);
    printf("port initiation success\n");
    return 0;
}
unsigned short int fin_com(unsigned short int com_hendler){
    tcsetattr(COM_HENDLER,TCSANOW,&oldsettings);
    close(COM_HENDLER);
}

ushort intepreted_foutput(char*buf){
    if(!buf)
        return 0;
    ushort result =0;
    result = *buf;
    result = result & 255;
    ++buf;
    result += *buf<<8;
    return result;
}

void handler_sigint_write(int sig){
    tcdrain(COM_HENDLER); 
    printf("child procces successfuly finished\n");
    exit(0);
}
void handler_sigint_read(int sig){
    if(waitpid(PID, &CHILD_RET_VALUE, 0)!=PID){
        printf("parent: ERROR: in waitpid() execution. ");
        perror("");
    }
    fin_com(COM_HENDLER);
    exit(CHILD_RET_VALUE);
}
/*
int main(){   
    int counter = 20;
    char buffer = 0;
    char wBuffer[10]={'q','w','e','r','t','y','7','8','9','10'}; 
    init_com(path);
    while(counter){
        read_com(COM_HENDLER,1, 10000, &buffer);
        printf("%d\n", buffer);
        --counter;
    }
    fin_com(COM_HENDLER);
    return 0;
    
}*/

/*
   while(received_value!=443){

            received_buffer_size = read_com(COM_HENDLER, RECEIVED_BUFFER_SIZE, 100000, RECEIVED_BUFFER);
            if(received_buffer_size==-1)
                printf("UNFATAL_ERROR: read attampt failure\n");

            printf("value getted[%d]: %d\n",received_buffer_size, (received_value=intepreted_foutput(RECEIVED_BUFFER)));
        }
        printf("read performance funktion finised execution successfuly\n");
        waitpid(PID,&CHILD_RET_VALUE, 0);
        printf("child procces finished with value %d\n", CHILD_RET_VALUE);
        return 0;
    }
    */