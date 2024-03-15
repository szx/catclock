//
// Created by sszczyrb on 15.03.24.
//

#ifndef CATCLOCK_LOCK_H
#define CATCLOCK_LOCK_H

#include "u.h"

typedef struct {
    int val;
} Lock;

#ifdef __cplusplus
extern "C" {
#endif

extern void lock(Lock *);
extern void unlock(Lock *);
extern int canlock(Lock *);
extern int tas(int *);

#ifdef __cplusplus
}
#endif

#endif //CATCLOCK_LOCK_H
