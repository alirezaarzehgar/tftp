/**
 * @file malloc3d.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "malloc3d.h"

void **
malloc3d (size_t nitem, size_t itemSize)
{
  void **v3d = (void **)malloc (nitem * itemSize);

  for (size_t i = 0; i < nitem; i++)
    v3d[i] = (void *)malloc (itemSize);

	return v3d;
}