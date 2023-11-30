#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main() 
{

        int fd = open ("/dev/LM_module",O_RDWR  );
        if (fd < 0) 
				{
                perror ("Unable to open device");
        }

        unsigned int arg;
        long r =  ioctl(fd, 0x01 , &arg);

        if (r < 0) 
				{
                perror ("Unable to open device");
        }

        int buf;
        r = read (fd, &buf, sizeof(int));

        write (fd, &buf, sizeof(int));  

        close(fd);

}
