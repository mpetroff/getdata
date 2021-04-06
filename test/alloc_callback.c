/* Copyright (C) 2016, 2017 D.V. Wiebe
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

void *cb_ptr = NULL;
int good_ptr = 0;

void free_function(void *ptr)
{
  if (ptr == cb_ptr)
    good_ptr = 1;
}

int callback(gd_parser_data_t *pdata, void *extra gd_unused_)
{
  pdata->line = cb_ptr = strdup("/VERSION 10\n");

  return GD_SYNTAX_RESCAN;
}

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  int e1, r = 0;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0700);

  gd_alloc_funcs(NULL, free_function);

  MAKEFORMATFILE(format, "Syntax error\n");

  D = gd_cbopen(filedir, GD_RDONLY, callback, NULL);
  e1 = gd_error(D);
  CHECKI(e1, 0);

  if (good_ptr)
    free(cb_ptr);
  else
    CHECKI(good_ptr, 1);

  gd_discard(D);

  unlink(format);
  rmdir(filedir);

  return r;
}
