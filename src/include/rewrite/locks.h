/*-------------------------------------------------------------------------
 *
 * locks.h
 *
 *
 *
 * Copyright (c) 1994, Regents of the University of California
 *
 * $Id$
 *
 *-------------------------------------------------------------------------
 */
#ifndef LOCKS_H
#define LOCKS_H

#include "nodes/parsenodes.h"
#include "rewrite/prs2lock.h"

extern List *matchLocks(CmdType event, RuleLock *rulelocks, int varno,
		   Query *parsetree);
extern void checkLockPerms(List *locks, Query *parsetree, int rt_index);

#endif	 /* LOCKS_H */
