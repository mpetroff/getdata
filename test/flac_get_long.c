/* Copyright (C) 2016 D. V. Wiebe
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

#define N 65536
int main(void)
{
#if ! (defined TEST_FLAC && defined USE_FLAC)
  return 77;
#else
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *data = "dirfile/data";
  const char *flacdata = "dirfile/data.flac";
  const char *format_data = "data RAW UINT16 8\n";
  char command[4096];
  uint16_t *dataw, *datar;
  int i, fd, n, error, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0777);

  dataw = malloc(N * sizeof(*dataw));
  datar = malloc(N * sizeof(*datar));

  for (i = 0; i < N; ++i)
    dataw[i] = i;

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  fd = open(data, O_CREAT | O_EXCL | O_WRONLY | O_BINARY, 0666);
  write(fd, dataw, N * sizeof(*dataw));
  close(fd);

  snprintf(command, 4096,
      "%s --endian=little --silent --sample-rate=1 --channels=1 --bps=16 "
      "--sign=signed --delete-input-file %s > /dev/null", FLAC, data);
  if (gd_system(command))
    return 1;

  D = gd_open(filedir, GD_RDONLY);
  n = gd_getdata(D, "data", 0, 0, 0, N, GD_UINT16, datar);
  CHECKI(n, N);

  error = gd_error(D);
  CHECKI(error, 0);

  gd_discard(D);

  for (i = 0; i < N; ++i)
    CHECKIi(i, datar[i], dataw[i]);

  unlink(flacdata);
  unlink(format);
  rmdir(filedir);
  free(dataw);
  free(datar);

  return r;
#endif
}
