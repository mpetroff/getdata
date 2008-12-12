/* Attempt to delete a field */
#include "../src/getdata.h"


#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* format_data = "data RAW UINT8 8\n"
    "META data e STRING 1\n"
    "META data q STRING 2\n"
    "META data a STRING 3\n"
    "META data b STRING 4\n"
    "META data z STRING 5\n"
    "META data l STRING 6\n"
    "s STRING e\n";
  int fd;

  mkdir(filedir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  DIRFILE* D = dirfile_open(filedir, GD_RDWR);
  int ret = dirfile_delete(D, "data", GD_DEL_META);
  int error = get_error(D);
  int nf = get_nfields(D);
  dirfile_close(D);

  unlink(format);
  rmdir(filedir);

  if (error != GD_E_OK) {
    fprintf(stderr, "2=%i\n", error);
    return 1;
  }
  if (nf != 2) {
    fprintf(stderr, "3=%i\n", nf);
    return 1;
  }
  if (ret != 0) {
    fprintf(stderr, "4=%i\n", ret);
    return 1;
  }

  return 0;
}