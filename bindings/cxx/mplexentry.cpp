// Copyright (C) 2012 D. V. Wiebe
//
///////////////////////////////////////////////////////////////////////////
//
// This file is part of the GetData project.
//
// GetData is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// GetData is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with GetData; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
#include "internal.h"

MplexEntry::MplexEntry(const char* field_code, const char* in_field,
    const char* count, gd_count_t count_val, gd_count_t count_max,
    int fragment_index) : Entry()
{
  dtrace("\"%s\", \"%s\", \"%s\", %i, %i, %i", field_code,
      in_field, count, count_val, count_max, fragment_index);

  E.field = strdup(field_code);
  E.field_type = GD_MPLEX_ENTRY;
  E.in_fields[0] = strdup(in_field);
  E.in_fields[1] = strdup(count);
  E.scalar[0] = E.scalar[1] = 0;
  E.u.mplex.count_val = count_val;
  E.u.mplex.count_max = count_max;
  E.fragment_index = fragment_index;

  dreturnvoid();
}

int MplexEntry::SetInput(const char* field, int index)
{
  if (index < 0 || index > 1)
    return -1;

  char* ptr = strdup(field);

  if (ptr == NULL)
    return -1;

  free(E.in_fields[index]);
  E.in_fields[index] = ptr;

  if (D != NULL)
    return gd_alter_entry(D->D, E.field, &E, 0);
  
  return 0;
}

int MplexEntry::SetCountVal(gd_count_t count_val)
{
  int ret = 0;

  dtrace("%u", count_val);

  E.u.mplex.count_val = count_val;

  if (D != NULL)
    ret = gd_alter_entry(D->D, E.field, &E, 0);
  
  dreturn("%i", ret);
  return ret;
}

int MplexEntry::SetCountMax(gd_count_t count_max)
{
  int ret = 0;

  dtrace("%u", count_max);

  E.u.mplex.count_max = count_max;

  if (D != NULL)
    ret = gd_alter_entry(D->D, E.field, &E, 0);
  
  dreturn("%i", ret);
  return ret;
}

int MplexEntry::SetCountVal(const char *count_val)
{
  int r = 0;

  dtrace("\"%s\"", count_val);

  SetScalar(0, count_val);

  if (D != NULL) {
    r = gd_alter_entry(D->D, E.field, &E, 0);

    if (!r)
      r = gd_get_constant(D->D, count_val, GD_UINT16, &E.u.mplex.count_val);
  }
  
  dreturn("%i", r);
  return r;
}

int MplexEntry::SetCountMax(const char *count_max)
{
  int r = 0;

  dtrace("\"%s\"", count_max);

  SetScalar(1, count_max);

  if (D != NULL) {
    r = gd_alter_entry(D->D, E.field, &E, 0);

    if (!r)
      r = gd_get_constant(D->D, count_max, GD_UINT16, &E.u.mplex.count_max);
  }
  
  dreturn("%i", r);
  return r;
}