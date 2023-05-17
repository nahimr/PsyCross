#ifndef PSYX_FS_H
#define PSYX_FS_H

#include <stdio.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern FILE *PsyX_FS_OpenFile(const char *path, const char *mode);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif
