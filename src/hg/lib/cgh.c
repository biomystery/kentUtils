/* cgh.c was originally generated by the autoSql program, which also 
 * generated cgh.h and cgh.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "jksql.h"
#include "cgh.h"


void cghStaticLoad(char **row, struct cgh *ret)
/* Load a row from cgh table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = atof(row[4]);
ret->type = sqlUnsigned(row[5]);
ret->tissue = row[6];
ret->clone = row[7];
ret->spot = sqlUnsigned(row[8]);
}

struct cgh *cghLoad(char **row)
/* Load a cgh from row fetched with select * from cgh
 * from database.  Dispose of this with cghFree(). */
{
struct cgh *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = atof(row[4]);
ret->type = sqlUnsigned(row[5]);
ret->tissue = cloneString(row[6]);
ret->clone = cloneString(row[7]);
ret->spot = sqlUnsigned(row[8]);
return ret;
}

struct cgh *cghLoadAll(char *fileName) 
/* Load all cgh from a tab-separated file.
 * Dispose of this with cghFreeList(). */
{
struct cgh *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileRow(lf, row))
    {
    el = cghLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct cgh *cghCommaIn(char **pS, struct cgh *ret)
/* Create a cgh out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cgh */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlSignedComma(&s);
ret->type = sqlUnsignedComma(&s);
ret->tissue = sqlStringComma(&s);
ret->clone = sqlStringComma(&s);
ret->spot = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void cghFree(struct cgh **pEl)
/* Free a single dynamically allocated cgh such as created
 * with cghLoad(). */
{
struct cgh *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->tissue);
freeMem(el->clone);
freez(pEl);
}

void cghFreeList(struct cgh **pList)
/* Free a list of dynamically allocated cgh's */
{
struct cgh *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    cghFree(&el);
    }
*pList = NULL;
}

void cghOutput(struct cgh *el, FILE *f, char sep, char lastSep) 
/* Print out cgh.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->score);
fputc(sep,f);
fprintf(f, "%u", el->type);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tissue);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->clone);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->spot);
fputc(lastSep,f);
}

