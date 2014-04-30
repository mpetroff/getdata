/* Copyright (C) 2014 D. V. Wiebe
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *data[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
  int n, error;
  int r = 0;
  gd_entry_t E;
  DIRFILE *D;

  rmdirfile();
  D = gd_open(filedir, GD_RDWR | GD_CREAT | GD_VERBOSE);

  E.field = "data";
  E.field_type = GD_SARRAY_ENTRY;
  E.EN(scalar,array_len) = 6;
  E.fragment_index = 0;
  gd_add(D, &E);
  error = gd_error(D);
  CHECKI(error, GD_E_OK);

  /* check */
  memset(&E, 0, sizeof(E));
  gd_entry(D, "data", &E);
  if (gd_error(D))
    r = 1;
  else {
    CHECKI(E.field_type, GD_SARRAY_ENTRY);
    CHECKI(E.fragment_index, 0);
    gd_free_entry_strings(&E);
  }
  n = (int)gd_sarray_len(D, "data");
  CHECKI(n, 6);

  gd_get_sarray(D, "data", data);
  for (n = 0; n < 6; ++n)
    CHECKSi(n, data[n], "");

  gd_discard(D);

  unlink(format);
  rmdir(filedir);

  return r;
}
