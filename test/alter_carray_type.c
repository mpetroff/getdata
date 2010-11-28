/* Test field modifying */
#include "test.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* format_data = "carray CARRAY FLOAT32 8.3 7.2 6.1 5.0 3.9 2.8 1.7\n";
  int fd, i, ret, error, n, r = 0;
  size_t z;
  DIRFILE *D;
  double d[7];

  mkdir(filedir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY | O_BINARY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  D = gd_open(filedir, GD_RDWR | GD_VERBOSE);
  ret = gd_alter_carray(D, "carray", GD_UINT8, 0);
  error = gd_error(D);
  z = gd_carray_len(D, "carray");
  n = gd_get_carray(D, "carray", GD_FLOAT64, &d);

  gd_close(D);

  unlink(format);
  rmdir(filedir);

  CHECKI(error, 0);
  CHECKI(n, 0);
  CHECKI(ret, 0);
  CHECKU(z, 7);
  for (i = 0; i < 7; ++i)
    CHECKFi(i, d[i], ((i > 3) ? 7. : 8.) - i);

  return r;
}
