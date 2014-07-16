/* bed12wSeq.h was originally generated by the autoSql program, which also 
 * generated bed12wSeq.c and bed12wSeq.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef BED12WSEQ_H
#define BED12WSEQ_H

#include "jksql.h"
#define BED12WSEQ_NUM_COLS 14

struct bed12wSeq
/* Browser extensible data (12 fields) plus two sequences */
    {
    struct bed12wSeq *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome (or contig, scaffold, etc.) */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    unsigned thickStart;	/* Start of where display should be thick (start codon) */
    unsigned thickEnd;	/* End of where display should be thick (stop codon) */
    unsigned reserved;	/* Used as itemRgb as of 2004-11-22 */
    int blockCount;	/* Number of blocks */
    int *blockSizes;	/* Comma separated list of block sizes */
    int *chromStarts;	/* Start positions relative to chromStart */
    char *seq1;	/* sequence 1, normally left paired end */
    char *seq2;	/* sequence 2, normally right paired end */
    };

struct bed12wSeq *bed12wSeqLoad(char **row);
/* Load a bed12wSeq from row fetched with select * from bed12wSeq
 * from database.  Dispose of this with bed12wSeqFree(). */

struct bed12wSeq *bed12wSeqLoadAll(char *fileName);
/* Load all bed12wSeq from whitespace-separated file.
 * Dispose of this with bed12wSeqFreeList(). */

struct bed12wSeq *bed12wSeqLoadAllByChar(char *fileName, char chopper);
/* Load all bed12wSeq from chopper separated file.
 * Dispose of this with bed12wSeqFreeList(). */

#define bed12wSeqLoadAllByTab(a) bed12wSeqLoadAllByChar(a, '\t');
/* Load all bed12wSeq from tab separated file.
 * Dispose of this with bed12wSeqFreeList(). */

struct bed12wSeq *bed12wSeqLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all bed12wSeq from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with bed12wSeqFreeList(). */

void bed12wSeqSaveToDb(struct sqlConnection *conn, struct bed12wSeq *el, char *tableName, int updateSize);
/* Save bed12wSeq as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct bed12wSeq *bed12wSeqCommaIn(char **pS, struct bed12wSeq *ret);
/* Create a bed12wSeq out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new bed12wSeq */

void bed12wSeqFree(struct bed12wSeq **pEl);
/* Free a single dynamically allocated bed12wSeq such as created
 * with bed12wSeqLoad(). */

void bed12wSeqFreeList(struct bed12wSeq **pList);
/* Free a list of dynamically allocated bed12wSeq's */

void bed12wSeqOutput(struct bed12wSeq *el, FILE *f, char sep, char lastSep);
/* Print out bed12wSeq.  Separate fields with sep. Follow last field with lastSep. */

#define bed12wSeqTabOut(el,f) bed12wSeqOutput(el,f,'\t','\n');
/* Print out bed12wSeq as a line in a tab-separated file. */

#define bed12wSeqCommaOut(el,f) bed12wSeqOutput(el,f,',',',');
/* Print out bed12wSeq as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* BED12WSEQ_H */

