/* Test include */
#include "../src/getdata.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* format1 = __TEST__ "dirfile/format1";
  int fd;

  mkdir(filedir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  close(fd);

  DIRFILE* D = dirfile_open(filedir, GD_RDWR);
  dirfile_include(D, "format1", 0, GD_CREAT);
  int error = get_error(D);
  dirfile_close(D);

  if (unlink(format1))
    error = 1;
  unlink(format);
  rmdir(filedir);

  return (error != 0);
}