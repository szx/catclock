//
// Created by sszczyrb on 15.03.24.
//

#ifndef CATCLOCK_QLOCK_H
#define CATCLOCK_QLOCK_H

#include "u.h"
#include "lock.h"

typedef struct QLp QLp;
struct QLp {
    int inuse;
    QLp *next;
    char state;
};

typedef
struct QLock {
    Lock lock;
    int locked;
    QLp *head;
    QLp *tail;
} QLock;

#ifdef __cplusplus
extern "C" {
#endif

extern void qlock(QLock *);
extern void qunlock(QLock *);
extern int canqlock(QLock *);

#ifdef __cplusplus
}
#endif

#endif //CATCLOCK_QLOCK_H
