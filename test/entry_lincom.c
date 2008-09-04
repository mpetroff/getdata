/* Try to read LINCOM entry */
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
  const char* format_data = "data LINCOM 3 in1 1 2 in2 3 4 in3 5 6\n";
  int fd;

  mkdir(filedir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  DIRFILE* D = dirfile_open(filedir, GD_RDONLY);
  gd_entry_t E;

  int n = get_entry(D, "data", &E);
  int error = D->error;

  dirfile_close(D);
  unlink(format);
  rmdir(filedir);

  if (error != GD_E_OK)
    return 1;
  if (n)
    return 1;
  if (strcmp(E.field, "data"))
    return 1;
  if (E.field_type != GD_LINCOM_ENTRY)
    return 1;
  if (E.n_fields != 3)
    return 1;
  if (strcmp(E.in_fields[0], "in1"))
    return 1;
  if (strcmp(E.in_fields[1], "in2"))
    return 1;
  if (strcmp(E.in_fields[2], "in3"))
    return 1;
  if (fabs(E.m[0] - 1.) > 1e-10)
    return 1;
  if (fabs(E.b[0] - 2.) > 1e-10)
    return 1;
  if (fabs(E.m[1] - 3.) > 1e-10)
    return 1;
  if (fabs(E.b[1] - 4.) > 1e-10)
    return 1;
  if (fabs(E.m[2] - 5.) > 1e-10)
    return 1;
  if (fabs(E.b[2] - 6.) > 1e-10)
    return 1;

  return 0;
}
