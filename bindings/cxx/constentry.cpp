// Copyright (C) 2008-2011 D. V. Wiebe
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

using namespace GetData;

ConstEntry::ConstEntry(const char* field_code, DataType data_type,
    int fragment_index)
{
  E.field = strdup(field_code);
  E.field_type = GD_CONST_ENTRY;
  E.u.scalar.const_type = (gd_type_t)data_type;
  E.fragment_index = fragment_index;
}

int ConstEntry::SetType(DataType type)
{
  E.u.scalar.const_type = (gd_type_t)type;

  if (D != NULL)
    return gd_alter_entry(D->D, E.field, &E, 0);
  
  return 0;
}
