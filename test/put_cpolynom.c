/* Copyright (C) 2013 D. V. Wiebe
 *
 ***************************************************************************
 *
 * This file is part of the GetData project.
 *
 * GetData is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * GetData is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with GetData; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "test.h"

#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *data = "dirfile/data";
  const char *format_data =
    "polynom POLYNOM data 0;1 0.5;0.5\n"
    "data RAW INT8 8\n";
  int8_t d;
  double c[16];
  struct stat buf;
  int fd, i, n, error, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0777);

  for (i = 0; i < 8; ++i) {
    c[2 * i] = 0.5;
    c[2 * i + 1] = 40 + i + 0.5;
  }

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  D = gd_open(filedir, GD_RDWR | GD_UNENCODED | GD_VERBOSE);
  n = gd_putdata(D, "polynom", 5, 0, 1, 0, GD_COMPLEX128, c);
  error = gd_error(D);

  gd_close(D);

  if (stat(data, &buf)) {
    perror("stat");
    r = 1;
  } else {
    CHECKI(buf.st_size, 48 * sizeof(int8_t));

    fd = open(data, O_RDONLY | O_BINARY);
    i = 0;
    while (read(fd, &d, sizeof(int8_t))) {
      if (i < 40 || i > 48) {
        CHECKFi(i,d,0);
      } else
        CHECKFi(i,d,i);
      i++;
    }
    close(fd);
  }

  unlink(data);
  unlink(format);
  rmdir(filedir);

  CHECKI(n,8);
  CHECKI(error, 0);

  return r;
}