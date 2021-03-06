/*-------------------------------------------------------------------------
 *
 * attoptcache.h
 *	  Attribute options cache.
 *
 * Portions Copyright (c) 1996-2010, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $PostgreSQL$
 *
 *-------------------------------------------------------------------------
 */
#ifndef SPCCACHE_H
#define SPCCACHE_H

/*
 * Attribute options.
 */
typedef struct AttributeOpts
{
	int32		vl_len_;		/* varlena header (do not touch directly!) */
	float8		n_distinct;
	float8		n_distinct_inherited;
} AttributeOpts;

AttributeOpts *get_attribute_options(Oid spcid, int attnum);

#endif   /* SPCCACHE_H */
