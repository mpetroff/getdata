/* Parser check */
#include "test.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

static int saw_callback = 0;

int callback(gd_parser_data_t *pdata __attribute__ (( unused )),
    void* extra __attribute__ (( unused )))
{
  saw_callback++;

  return -1;
}

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* format_data =
    "BADDIRECTIVE BADTYPE\n"
    "BADDIRECTIVE BADTYPE\n"
    "BADDIRECTIVE BADTYPE\n";
  int fd, error, r = 0;
  DIRFILE *D;

  mkdir(filedir, 0777);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  D = gd_cbopen(filedir, GD_RDONLY, callback, NULL);
  error = gd_error(D);
  gd_close(D);

  unlink(format);
  rmdir(filedir);

  CHECKI(saw_callback, 1);
  CHECKI(error, GD_E_CALLBACK);

  return r;
}
