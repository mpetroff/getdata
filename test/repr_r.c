/* Attempt to read argument representation */
#include "test.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format = __TEST__ "dirfile/format";
  const char* data = __TEST__ "dirfile/data";
  const char* format_data = "data RAW COMPLEX128 1\n";
  double c[8];
#ifdef GD_NO_C99_API
  double data_data[100][2];
#else
  double complex data_data[100];
#endif
  int i, r = 0;

  mkdir(filedir, 0777);

  for (i = 0; i < 100; ++i) {
#ifdef GD_NO_C99_API
    const double v = i * 3.14159265358979323846 / 5.;
    data_data[i][0] = cos(v);
    data_data[i][1] = sin(v);
#else
    data_data[i] = cexp(_Complex_I * i * 3.14159265358979323846 / 5.);
#endif
  }

  i = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(i, format_data, strlen(format_data));
  close(i);

  i = open(data, O_CREAT | O_EXCL | O_WRONLY | O_BINARY, 0666);
  write(i, data_data, 200 * sizeof(double));
  close(i);

  DIRFILE* D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  int n = gd_getdata(D, "data.r", 5, 0, 8, 0, GD_FLOAT64, &c);
  int error = gd_error(D);

  gd_close(D);

  unlink(data);
  unlink(format);
  rmdir(filedir);

  CHECKI(error,0);
  CHECKI(n,8);
  for (i = 0; i < 8; ++i)
    CHECKFi(i,c[i],creal(data_data[5 + i]));

  return r;
}
