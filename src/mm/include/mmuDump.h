/**
 *  Copyright (c) 1999~2017, Altibase Corp. and/or its affiliates. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License, version 3,
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _O_MMU_DUMP_H_
#define _O_MMU_DUMP_H_ 1

#include <idl.h>

class mmuDump
{
public:
    static SInt dump(void *p, vULong len, idBool is_relative_base_address = ID_TRUE);
    static SInt dump(SChar * object_name);
};

#endif
