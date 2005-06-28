/*-------------------------------------------------------------------------
 *
 * hba.h
 *	  Interface to hba.c
 *
 *
 * $PostgreSQL$
 *
 *-------------------------------------------------------------------------
 */
#ifndef HBA_H
#define HBA_H

#include "nodes/pg_list.h"


typedef enum UserAuth
{
	uaReject,
	uaKrb5,
	uaTrust,
	uaIdent,
	uaPassword,
	uaCrypt,
	uaMD5
#ifdef USE_PAM
	,uaPAM
#endif   /* USE_PAM */
} UserAuth;

typedef struct Port hbaPort;

extern List **get_role_line(const char *role);
extern void load_hba(void);
extern void load_ident(void);
extern void load_role(void);
extern int	hba_getauthmethod(hbaPort *port);
extern int	authident(hbaPort *port);
extern bool	read_pg_database_line(FILE *fp, char *dbname,
								  Oid *dboid, Oid *dbtablespace);

#endif /* HBA_H */
