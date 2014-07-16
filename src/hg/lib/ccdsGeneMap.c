/* ccdsGeneMap.c was originally generated by the autoSql program, which also 
 * generated ccdsGeneMap.h and ccdsGeneMap.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "ccdsGeneMap.h"


void ccdsGeneMapStaticLoad(char **row, struct ccdsGeneMap *ret)
/* Load a row from ccdsGeneMap table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->ccdsId = row[0];
ret->geneId = row[1];
ret->chrom = row[2];
ret->chromStart = sqlUnsigned(row[3]);
ret->chromEnd = sqlUnsigned(row[4]);
ret->cdsSimilarity = atof(row[5]);
}

struct ccdsGeneMap *ccdsGeneMapLoad(char **row)
/* Load a ccdsGeneMap from row fetched with select * from ccdsGeneMap
 * from database.  Dispose of this with ccdsGeneMapFree(). */
{
struct ccdsGeneMap *ret;

AllocVar(ret);
ret->ccdsId = cloneString(row[0]);
ret->geneId = cloneString(row[1]);
ret->chrom = cloneString(row[2]);
ret->chromStart = sqlUnsigned(row[3]);
ret->chromEnd = sqlUnsigned(row[4]);
ret->cdsSimilarity = atof(row[5]);
return ret;
}

struct ccdsGeneMap *ccdsGeneMapLoadAll(char *fileName) 
/* Load all ccdsGeneMap from a whitespace-separated file.
 * Dispose of this with ccdsGeneMapFreeList(). */
{
struct ccdsGeneMap *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = ccdsGeneMapLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct ccdsGeneMap *ccdsGeneMapLoadAllByChar(char *fileName, char chopper) 
/* Load all ccdsGeneMap from a chopper separated file.
 * Dispose of this with ccdsGeneMapFreeList(). */
{
struct ccdsGeneMap *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = ccdsGeneMapLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct ccdsGeneMap *ccdsGeneMapCommaIn(char **pS, struct ccdsGeneMap *ret)
/* Create a ccdsGeneMap out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new ccdsGeneMap */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->ccdsId = sqlStringComma(&s);
ret->geneId = sqlStringComma(&s);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->cdsSimilarity = sqlFloatComma(&s);
*pS = s;
return ret;
}

void ccdsGeneMapFree(struct ccdsGeneMap **pEl)
/* Free a single dynamically allocated ccdsGeneMap such as created
 * with ccdsGeneMapLoad(). */
{
struct ccdsGeneMap *el;

if ((el = *pEl) == NULL) return;
freeMem(el->ccdsId);
freeMem(el->geneId);
freeMem(el->chrom);
freez(pEl);
}

void ccdsGeneMapFreeList(struct ccdsGeneMap **pList)
/* Free a list of dynamically allocated ccdsGeneMap's */
{
struct ccdsGeneMap *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    ccdsGeneMapFree(&el);
    }
*pList = NULL;
}

void ccdsGeneMapOutput(struct ccdsGeneMap *el, FILE *f, char sep, char lastSep) 
/* Print out ccdsGeneMap.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ccdsId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
fprintf(f, "%g", el->cdsSimilarity);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

/* template for SQL to create a ccdsGeneMap table */
static char *createSql =
    "CREATE TABLE %s ("
    "    ccdsId varchar(32) not null,"
    "    geneId varchar(255) not null,"
    "    chrom varchar(255) not null,"
    "    chromStart int unsigned not null,"
    "    chromEnd int unsigned not null,"
    "    cdsSimilarity float not null,"
    "    KEY(ccdsId),"
    "    KEY(geneId)"
    ")";

char *ccdsGeneMapGetCreateSql(char *table)
/* Get SQL command to create ccdsGeneMap table. Result should be freed. */
{
char sql[1024];
sqlSafef(sql, sizeof(sql), createSql, table);
return cloneString(sql);
}

struct ccdsGeneMap *ccdsGeneMapSelectByCcds(struct sqlConnection *conn, char *mapTable,
                                            char *ccdsId, char *chrom, float minSimilarity)
/* select ccdsGeneMap records by ccds and minimum CDS similarity from the
 * specified table. Chrom is required since the same CCDS id is mapped twice in the PAR.
 */
{
struct ccdsGeneMap *ccdsGeneList = NULL;
char query[128];
struct sqlResult *sr = NULL;
char **row = NULL;

sqlSafef(query, sizeof(query), "select * from %s where (ccdsId='%s') and (chrom='%s') and (cdsSimilarity >= %f)",
      mapTable, ccdsId, chrom, minSimilarity);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    slSafeAddHead(&ccdsGeneList, ccdsGeneMapLoad(row));
sqlFreeResult(&sr);
return ccdsGeneList;
}

struct ccdsGeneMap *ccdsGeneMapSelectByGene(struct sqlConnection *conn, char *mapTable,
                                            char *geneId, float minSimilarity)
/* select ccdsGeneMap records by gene id and minimum CDS similarity from the
 * specified table. */
{
struct ccdsGeneMap *ccdsGeneList = NULL;
char query[128], simExpr[64];
struct sqlResult *sr = NULL;
char **row = NULL;

simExpr[0] = '\0';
if (minSimilarity > 0.0)
    safef(simExpr, sizeof(simExpr), "and cdsSimilarity >= %f", minSimilarity);

sqlSafef(query, sizeof(query), "select * from %s where geneId='%s' %s",
      mapTable, geneId, simExpr);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    slSafeAddHead(&ccdsGeneList, ccdsGeneMapLoad(row));
sqlFreeResult(&sr);
return ccdsGeneList;
}

struct ccdsGeneMap *ccdsGeneMapSelectByGeneOver(struct sqlConnection *conn, char *mapTable,
                                                char *geneId, char *chrom, unsigned chromStart,
                                                unsigned chromEnd, float minSimilarity)
/* select ccdsGeneMap records by gene id, location overlap, and minimum CDS
 * similarity from the specified table. */
{
struct ccdsGeneMap *ccdsGeneList = ccdsGeneMapSelectByGene(conn, mapTable, geneId, minSimilarity);
struct ccdsGeneMap *overList = NULL, *gene;

while ((gene = slPopHead(&ccdsGeneList)) != NULL)
    {
    if (sameString(gene->chrom, chrom)
        && (positiveRangeIntersection(gene->chromStart, gene->chromEnd,
                                      chromStart, chromEnd) > 0))
        slAddHead(&overList, gene);
    else
        ccdsGeneMapFree(&gene);
    }
return overList;
}

int ccdsGeneMapSimilarityCmp(const void *va, const void *vb)
/* compare based on descending similarity */
{
const struct ccdsGeneMap *a = *((struct ccdsGeneMap **)va);
const struct ccdsGeneMap *b = *((struct ccdsGeneMap **)vb);
if (a->cdsSimilarity > b->cdsSimilarity)
    return -1;
if (a->cdsSimilarity < b->cdsSimilarity)
    return 1;
return 0;
}

int ccdsGeneMapCcdsIdCmp(const void *va, const void *vb)
/* compare based on gene id */
{
const struct ccdsGeneMap *a = *((struct ccdsGeneMap **)va);
const struct ccdsGeneMap *b = *((struct ccdsGeneMap **)vb);
/* convert number past "CCDS" as float */
float aId = sqlFloat(a->ccdsId+4);
float bId = sqlFloat(b->ccdsId+4);

if (aId > bId)
    return -1;
if (aId < bId)
    return 1;
return 0;
}

int ccdsGeneMapGeneIdCmp(const void *va, const void *vb)
/* compare based on gene id */
{
const struct ccdsGeneMap *a = *((struct ccdsGeneMap **)va);
const struct ccdsGeneMap *b = *((struct ccdsGeneMap **)vb);
return strcmp(a->geneId, b->geneId);
}

