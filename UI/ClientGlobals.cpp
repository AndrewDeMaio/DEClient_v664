/*-----------------------------------------------------------------------------

    ClientGlobals.cpp

    Symbols that no other source file provides.
    Most globals/functions that were here have moved back to Client.cpp.

-----------------------------------------------------------------------------*/

#include <windows.h>
#include "NPGameLib.h"

// nProtect.cpp conditionally defines npgl only when __CONTENTS(__NPROTECT)
// is true, which it isn't for dev builds.  Provide it here unconditionally
// so nProtect.obj links.
CNPGameLib      npgl("DarkEden");
