/* Copyright (C) 2012 D. V. Wiebe
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

int main(void)
{
#if ! defined HAVE_SYMLINK
  return 77;
#else
  const char *filedir = "dirfile/link";
  const char *format = "dirfile/format";
  const char *targ = "../dirfile/";
  int error, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir("dirfile", 0777);
  close(open(format, O_CREAT | O_EXCL | O_WRONLY, 0666));

  /* make a symlink */
  symlink(targ, filedir);

  D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  error = gd_error(D);
  gd_close(D);

  unlink(format);
  rmdir(filedir);

  CHECKI(error, 0);
  return r;
#endif
}