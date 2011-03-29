/* Test include */
#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
  const char *filedir = __TEST__ "dirfile";
  const char *subdir = __TEST__ "dirfile/sub";
  const char *format = __TEST__ "dirfile/format";
  const char *format1 = __TEST__ "dirfile/sub/format1";
  const char *format2 = __TEST__ "dirfile/sub/format2";
  const char *format_data = "INCLUDE sub/format1\n";
  const char *format1_data = "INCLUDE format2\n";
  const char *format2_data = "data RAW UINT8 11\n";
  int fd, r = 0;
  DIRFILE *D;
  gd_spf_t spf;

  mkdir(filedir, 0777);
  mkdirsub(subdir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  fd = open(format1, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format1_data, strlen(format1_data));
  close(fd);

  fd = open(format2, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format2_data, strlen(format2_data));
  close(fd);

  D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  spf = gd_spf(D, "data");
  gd_close(D);

  unlink(format2);
  unlink(format1);
  unlink(format);
  rmdir(subdir);
  rmdir(filedir);

  CHECKU(spf, 11);
  return r;
}