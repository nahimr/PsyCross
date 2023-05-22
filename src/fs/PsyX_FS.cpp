#include "PsyX_FS.h"
#include "PsyX/PsyX_globals.h"
#include "SDL.h"
#include "../PsyX_main.h"

#include <assert.h>

FILE *PsyX_FS_OpenFile(const char *path, const char *mode) {
#ifdef __ANDROID__
    char buffer[255];
    sprintf(buffer, "%s/%s", SDL_AndroidGetExternalStoragePath(), path);
#ifdef _DEBUG
    eprintinfo("Opening file '%s'\n", buffer);
#endif
    FILE* handle = fopen(buffer, mode);

    if (!handle) {
        eprinterr("Can't open file '%s'\n", buffer);
        assert(0);
    }

    return handle;
#else
    return fopen(path, mode);
#endif
}

