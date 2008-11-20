/* Attempt to write UINT8 */
#include "../src/getdata.h"

#include <inttypes.h>
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
  const char* format_data = "data STRING UINT8\nPROTECT all\n";
  int fd;

  mkdir(filedir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  DIRFILE* D = dirfile_open(filedir, GD_RDWR | GD_UNENCODED);
  int n = put_string(D, "data", "some string");
  int error = get_error(D);

  dirfile_close(D);

  unlink(format);
  rmdir(filedir);

  if (error != GD_E_PROTECTED)
    return 1;
  if (n != 0)
    return 1;

  return 0;
}