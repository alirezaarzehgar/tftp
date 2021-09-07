#include <unistd.h>
#include <stdlib.h>

#if !defined(DMALLOC3D_H)
#define DMALLOC3D_H

void **malloc3d (size_t nitem, size_t itemSize);

#endif // DMALLOC3D_H
