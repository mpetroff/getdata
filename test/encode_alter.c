/* Test endianness */
#include "../src/getdata.h"


#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* data = __TEST__ "dirfile/data";
  const char* txtdata = __TEST__ "dirfile/data.txt";
  const char* format_data = "data RAW UINT16 8\nENCODING none\n";
  const char* txt_data =
    "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n";
  uint16_t data_data[128];
  uint16_t c[8], d;
  int fd;

  memset(c, 0, 8);
  mkdir(filedir, 0777);

  for (fd = 0; fd < 128; ++fd)
    data_data[fd] = 0x201 * fd;

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  fd = open(txtdata, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, txt_data, strlen(txt_data));
  close(fd);

  fd = open(data, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, data_data, 256);
  close(fd);

  DIRFILE* D = dirfile_open(filedir, GD_RDWR | GD_VERBOSE);
  int ret = dirfile_alter_encoding(D, GD_TEXT_ENCODED, 0, 0);
  int error = get_error(D);
  off_t n = get_nframes(D);

  dirfile_close(D);

  unlink(txtdata);
  unlink(data);
  unlink(format);
  rmdir(filedir);

  if (error) {
    fprintf(stderr, "1=%i\n", error);
    return 1;
  }
  if (ret != 0) {
    fprintf(stderr, "2=%i\n", ret);
    return 1;
  }
  if (n != 2) {
    fprintf(stderr, "3=%lli\n", (long long)n);
    return 1;
  }

  return 0;
}