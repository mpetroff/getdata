/* Requesting the number of frames from an empty dirfile should fail cleanly */
#include "test.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";

  mkdir(filedir, 0777);
  close(open(format, O_CREAT | O_EXCL | O_WRONLY, 0666));

  DIRFILE* D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  size_t n = gd_get_nframes(D);
  int error = gd_error(D);
  gd_close(D);

  unlink(format);
  rmdir(filedir);

  if (n != 0)
    return 1;

  return (error != GD_E_OK);
}
