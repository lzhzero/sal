#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <emscripten.h>
#define min(x,y)  ( x<y?x:y )

int fs_prepare(){
  EM_ASM(
    FS.mkdir('/working');
    FS.mount(NODEFS, { root: '/mnt/mem' }, '/working');
  );
  return 0;
}


int zero_file(char *filename) {
  FILE *file;
  int res;
  char str[100];
  strcpy(str, "/working/");
  strcat(str, filename);
  int fd; 
//  char buf[4096];
  char buf[32786];
  struct stat st;
  off_t pos;
  ssize_t written;
  memset(buf, 0, 32786);   
  fd = open(str, O_WRONLY);
  fstat(fd, &st);
  
  for(pos=0; pos < st.st_size; pos+=written)
    if ((written = write(fd, buf, min(st.st_size - pos, 4096))) <= 0)
      break;

  fsync(fd);
  close(fd);
  return 0;
}

int run(char *message) {
  char* filename;
  strncpy(filename, message+3, 20);
  //  memcpy(filename, &message[3], strlen(message)-3);
  zero_file(filename);
//  printf("%s\n", message);
//  printf("%d\n", strlen(message)); 
//  printf("%s\n", filename);
//  free(filename); 
  return 0;
}
