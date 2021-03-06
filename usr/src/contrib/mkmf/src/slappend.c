/*
 * Copyright (c) 1983, 1985, 1991 Peter J. Nicklin.
 * Copyright (c) 1991 Version Technology.
 * All Rights Reserved.
 *
 * $License: VT.1.1 $
 * Redistribution and use in source and binary forms,  with or without
 * modification,  are permitted provided that the following conditions
 * are met:  (1) Redistributions of source code must retain the  above
 * copyright  notice,  this  list  of  conditions  and  the  following
 * disclaimer.  (2) Redistributions in binary form must reproduce  the
 * above  copyright notice,  this list of conditions and the following
 * disclaimer in the  documentation  and/or other  materials  provided
 * with  the  distribution.  (3) All advertising materials  mentioning
 * features or  use  of  this  software  must  display  the  following
 * acknowledgement:  ``This  product  includes  software  developed by
 * Version Technology.''  Neither the name of Version  Technology  nor
 * the  name  of  Peter J. Nicklin  may  be used to endorse or promote
 * products derived from this software without specific prior  written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY VERSION TECHNOLOGY ``AS IS''  AND  ANY
 * EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT LIMITED TO, THE
 * IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL  VERSION  TECHNOLOGY  BE
 * LIABLE  FOR ANY DIRECT,  INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR  CONSEQUENTIAL DAMAGES   (INCLUDING,   BUT   NOT   LIMITED   TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT LIABILITY,  OR  TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING  IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE,  EVEN  IF  ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * Report problems and direct questions to nicklin@netcom.com
 *
 * $Header: slappend.c,v 4.3 91/11/25 19:44:59 nicklin Exp $
 *
 * Author: Peter J. Nicklin
 */

/*
 * slappend() saves a null-terminated key string somewhere and inserts a
 * pointer to the key at the tail of list slist. Returns a pointer to
 * the somewhere, or a null pointer if out of memory.
 */
#include <stdio.h>
#include "macro.h"
#include "null.h"
#include "slist.h"
#include "stringx.h"

char *
slappend(key, slist)
	char *key;			/* key string */
	SLIST *slist;			/* pointer to list head block */
{
	char *malloc();			/* memory allocator */
	SLBLK *slbptr;			/* pointer to list block */
	unsigned int klen;		/* key length */

	if (slist == NULL)
		return(NULL);
	klen = strlen(key);
	slist->maxkey = MAX(slist->maxkey, klen);
	if ((slbptr = (SLBLK *) malloc(sizeof(SLBLK))) == NULL ||
	    (slbptr->key = malloc(klen+1)) == NULL)
		{
		nocore();
		return(NULL);
		}
	strcpy(slbptr->key, key);
	slbptr->next = NULL;
	if (slist->tail == NULL)
		slist->head = slist->tail = slbptr;
	else
		slist->tail = slist->tail->next = slbptr;
	slist->nk++;
	return(slbptr->key);
}
