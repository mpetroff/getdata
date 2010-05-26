/* Attempt to read UINT8 */
#include "../src/config.h"
#include "test.h"

#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* data = __TEST__ "dirfile/data";
  const char* lzmadata = __TEST__ "dirfile/data.lzma";
  const char* format_data = "data RAW UINT16 8\n";
  uint16_t c[8];
  char command[4096];
  uint16_t data_data[256];
  int fd, r = 0;

  memset(c, 0, 8);
  mkdir(filedir, 0777);

  for (fd = 0; fd < 256; ++fd)
    data_data[fd] = (unsigned char)fd;

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  fd = open(data, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, data_data, 256 * sizeof(uint16_t));
  close(fd);

  /* compress */
  snprintf(command, 4096, "%s -F lzma -f %s > /dev/null", XZ, data);
  if (system(command))
    return 1;

#ifdef USE_LZMA
  DIRFILE* D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
#else
  DIRFILE* D = gd_open(filedir, GD_RDONLY);
#endif
  int n = gd_getdata(D, "data", 5, 0, 1, 0, GD_UINT16, c);
  int error = gd_error(D);

  gd_close(D);

  unlink(lzmadata);
  unlink(format);
  rmdir(filedir);

#ifdef USE_LZMA
  int i;

  CHECKI(error, 0);
  CHECKI(n, 8);
  for (i = 0; i < 8; ++i)
    CHECKUi(i, c[i], 40 + i);
#else
  CHECKI(error, GD_E_UNSUPPORTED);
  CHECKI(n, 0);
#endif

  return r;
}
