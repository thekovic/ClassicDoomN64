// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// $Log:$
//
// DESCRIPTION:
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>

#include "doomdef.h"
#include "m_misc.h"
#include "i_video.h"
#include "i_sound.h"

#include "d_net.h"
#include "g_game.h"

#include "i_system.h"

#define TICKS_TO_DOOM_TICKS(val) (((val) / (TICKS_PER_SECOND / TICRATE)))

extern surface_t* _dc;

void DebugOutput_String_For_IError(const char *str, int lineNumber, int good);

// freed up enough space through gc-sections to give 5.5 MB to zone
// this also allowed me to get screen wipe working again
#define MB_FOR_ZONE 5
#define BYTES_PER_MB 1048576
const size_t zone_size = MB_FOR_ZONE * BYTES_PER_MB;
int based_zone = 0;

void I_Tactile(int on, int off, int total)
{
}


ticcmd_t emptycmd;
inline ticcmd_t* I_BaseTiccmd(void)
{
    return &emptycmd;
}


int I_GetHeapSize(void)
{
    if (0 == based_zone)
    {
        return 0;
    }

    return zone_size;
}


byte* I_ZoneBase(int* size)
{
    based_zone = 1;

    *size = zone_size;

    byte *ptr = (byte *)malloc(*size);

    return ptr;
}


//
// I_GetTime
// returns time in increments of 1/35th of a second
//
unsigned long I_GetTime(void)
{
    return TICKS_TO_DOOM_TICKS(get_ticks());
}

//
// I_Init
//
void I_Init(void)
{
    I_InitSound();
    I_InitMusic();

    I_InitGraphics();
}

int return_from_D_DoomMain = 0;

//
// I_Quit
//
void I_Quit(void)
{
    D_QuitNetGame();
    I_ShutdownSound();
    I_ShutdownMusic();
    M_SaveDefaults();
    I_ShutdownGraphics();
    return_from_D_DoomMain = 1;
}

void I_WaitVBL(int count)
{
}

void I_BeginRead(void)
{
}

void I_EndRead(void)
{
}

byte* I_AllocLow(int length)
{
    byte* mem;

    mem = (byte *)malloc(length);

    return mem;
}

extern boolean demorecording;
