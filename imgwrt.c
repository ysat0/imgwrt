#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <doslib.h>
#include <fcntl.h>

static char buf[0x80000];
int main(int argc, char *argv[])
{
  int fd;
  int size;
  int rsize;
  int drv;
  if (argc != 3) {
    printf("Usage imgwrt filename drive\n");
    return 1;
  }
  drv = atoi(argv[2]);
  fd = open(argv[1], O_RDONLY | O_BINARY);
  if (fd == -1) {
    perror(argv[1]);
    return 1;
  }
  size = 0;
  do {
    printf("writing %dbyte\r", size);
    fflush(stdout);
    rsize = read(fd, buf, sizeof(buf));
    if (rsize < 0) {
      perror(argv[1]);
      return 1;
    }
    if (rsize > 0) {
      _dos_diskwrt(buf, drv, size / 0x400, rsize / 0x400);
      size += rsize;
    }
  } while(rsize == sizeof(buf));
  close(fd);
  printf("\ndone\n");
  return 0;
}


