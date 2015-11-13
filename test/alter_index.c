/* Copyright (C) 2013, 2015 D. V. Wiebe
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

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  int ret, error, r = 0;
  DIRFILE *D;
  gd_entry_t E;

  rmdirfile();

  memset(&E, 0, sizeof(E));

  E.field_type = GD_INDEX_ENTRY;

  D = gd_open(filedir, GD_RDWR | GD_CREAT | GD_EXCL);
  ret = gd_alter_entry(D, "INDEX", &E, 0);
  error = gd_error(D);

  CHECKI(error, GD_E_BAD_FIELD_TYPE);
  CHECKI(ret, GD_E_BAD_FIELD_TYPE);

  gd_discard(D);

  unlink(format);
  rmdir(filedir);

  return r;
}
