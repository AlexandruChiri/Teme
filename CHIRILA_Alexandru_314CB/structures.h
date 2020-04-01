/* CHIRILA Alexandru - 314CB */

#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

// int
typedef struct intCell
{
	int    value;
	struct intCell* next;
} t_intCell;

typedef struct intLine
{
	t_intCell*      cells;
	struct intLine* next;
} t_intLine;

// float
typedef struct floatCell
{
	float  value;
	struct floatCell* next;
} t_floatCell;

typedef struct floatLine
{
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell
{
	char*  value;
	struct stringCell* next;
} t_stringCell;

typedef struct stringLine
{
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine;

// cell type
typedef enum
{
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column
{
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column;

// Celula universala ce retine un pointer catre
// valoarea propriuzisa ci unul catre 
// urmatoarea celula.
typedef struct cell
{
	void *val;
	struct cell *next;
} t_cell;

// Linie universala ce nu depinde de tipul tabelului
typedef struct line
{
	t_cell *cells;
	struct line *next;
} t_line;

// table
typedef struct table
{
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	t_line*         lines;
	// t_intLine* | t_floatLine* | t_stringLine* au fost inlocuite de t_line*
	struct table* next;
} t_table;

// database
typedef struct db
{
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;

#endif
