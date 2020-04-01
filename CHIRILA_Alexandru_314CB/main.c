/* CHIRILA Alexandru - 314CB */

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functia 'bara' afiseaza o bara de 30 de caractere '-' si un spatiu.
void bara()
{
	int i;
	for(i = 1; i <= 30; ++i)
	{
		printf("-");
	}
	printf(" ");
}

// Functia comanda verifica daca un sir de caractere este o comanda
int comanda(char *name)
{
	if(name == NULL)return 0;
	if(!strcmp(name, "DELETE_DB") | !strcmp(name, "DELETE"))return 1;
	if(!strcmp(name, "INIT_DB") || !strcmp(name, "PRINT_DB"))return 1;
	if(!strcmp(name, "PRINT_DB") || !strcmp(name, "SEARCH"))return 1;
	if(!strcmp(name, "CREATE") || !strcmp(name, "PRINT"))return 1;
	if(!strcmp(name, "CLEAR") || !strcmp(name, "ADD"))return 1;
	return 0;
}

// Functia 'fel' primeste un sir de caractere si returneaza tipul t_cellType
// corespunzator.
t_cellType fel(char *tip_def)
{
	if(!strcmp(tip_def, "INT"))return INT;
	if(!strcmp(tip_def, "FLOAT"))return FLOAT;
	if(!strcmp(tip_def, "STRING"))return STRING;
	return -1;
}

// Functia recursiva 'free_cells' elibereaza memoria alocata unei liste
// de celule.
void free_cells(t_cell *celula, t_cellType tip)
{
	// Daca nu este sfarsitul listei, atunci:
	if(celula != NULL)
	{
		// Se elibereaza urmatoarele celule din lista
		free_cells(celula->next, tip);
		// Se elibereaza celula curenta
		if(tip == INT)
		{
			int *val;
			val = (int*)(celula->val);
			free(val);
		}
		else if(tip == FLOAT)
		{
			float *val;
			val = (float*)(celula->val);
			free(val);
		}
		else if(tip == STRING)
		{
			char *val;
			val = (char*)(celula->val);
			free(val);
		}
		if(celula != NULL)free(celula);
		celula = NULL;
	}
}

// Functia 'free_line' elibereaza memoria alocata unei linii.
void free_line(t_line *linie, t_cellType tip)
{
	if(linie != NULL)
	{
		// Se elibereaza memoria alocata listei de celule.
		free_cells(linie->cells, tip);
		// Se elibereaza memoria alocata liniei.
		free(linie);
		linie = NULL;
	}
}

// Functia recursiva 'free_lines' elibereaza o lista de linii.
void free_lines(t_line *linie, t_cellType tip)
{
	if(linie != NULL)
	{
		// Se elibereaza urmatoarele linii
		free_lines(linie->next, tip);
		// Se elibereaza linie curenta
		free_line(linie, tip);
	}
}

// Functia 'line' citeste o linie noua pentru un tabel.
void line(t_table *tabel, t_line **linie)
{
	// Se retine tipul tabelului.
	t_cellType tip = tabel->type;
	// Se retine lista de coloane a tabelului.
	t_column *coloana;
	coloana = tabel->columns;
	// Se retine adresa listei de celule.
	t_cell **celula;
	celula = &((*linie)->cells);
	// Cat timp nu s-au citit valori pentru
	// toate coloanele.
	while(coloana != NULL)
	{
		// Se aloca celula.
		*celula = calloc(1, sizeof(t_cell));
		
		// In cazul alocarii esuate:
		if(*celula == NULL)
		{
			// Se afiseaza mesajul de eroare.
			printf("Eroare alocare memorie pentru celula.");
			// Se elibereaza linia cu tot cu celule.
			free_line(*linie, tip);
			// Se elibereaza celula alocata.
			return;
		}
		if(tip == INT)
		{
			// Se retine adresa la care se afla valoarea celulei.
			int **val;
			val = (int**)(&((*celula)->val));
			// Se aloca celula
			(*val) = calloc(1, sizeof(int));
			// In cazul alocarii esuate:
			if(*val == NULL)
			{
				// Se afiseaza mesajul de eroare.
				printf("Eroare alocare memorie pentru ");
				printf("celula.\n");
				//free_cells((*linie)->cells);
				// Se elibereaza linia cu tot cu celule.
				free_line(*linie, tip);
				// Se elibereaza celula alocata.
				free(celula);
				// Se opreste executia functiei
				return;
			}
			// Se citeste valoarea efectiva a celulei.
			scanf("%d", *val);
		}
		else if(tip == FLOAT)
		{
			// Se retine adresa la care se afla valoarea celulei.
			float **val;
			val = (float**)(&((*celula)->val));
			// Se aloca celula
			(*val) = calloc(1, sizeof(float));
			// In cazul alocarii esuate:
			if(*val == NULL)
			{
				// Se afiseaza mesajul de eroare.
				printf("Eroare alocare memorie pentru ");
				printf("celula.\n");
				//free_cells((*linie)->cells);
				// Se elibereaza linia cu tot cu celule.
				free_line(*linie, tip);
				// Se elibereaza celula alocata.
				free(celula);
				// Se opreste executia functiei
				return;
			}
			// Se citeste valoarea efectiva a celulei.
			scanf("%f", *val);
		}
		else if(tip == STRING)
		{
			// Se retine adresa la care se afla valoarea celulei.
			char **val, *s;
			val = (char**)(&((*celula)->val));
			// Se aloca celula
			s = calloc(MAX_CMD_LEN, sizeof(char));
			// In cazul alocarii esuate:
			if(s == NULL)
			{
				// Se afiseaza mesajul de eroare.
				printf("Eroare alocare memorie pentru ");
				printf("celula.\n");
				//free_cells((*linie)->cells);
				// Se elibereaza linia cu tot cu celule.
				free_line(*linie, tip);
				// Se elibereaza celula alocata.
				free(celula);
				// Se opreste executia functiei
				return;
			}
			// Se citeste valoarea efectiva a celulei in pointerul
			// auxiliar.
			scanf("%s", s);
			*val = calloc(strlen(s) + 1, sizeof(char));
			if(*val == NULL)
			{
				// Se afiseaza mesajul de eroare.
				printf("Eroare alocare memorie pentru ");
				printf("celula.\n");
				//free_cells((*linie)->cells);
				// Se elibereaza linia cu tot cu celule.
				free_line(*linie, tip);
				// Se elibereaza celula alocata.
				free(celula);
				// Se elibereaza memoria alocata pointerului
				// auxiliar.
				free(s);
				// Se opreste executia functiei
				return;
			}
			// Se retine sirul citit in celula.
			strcpy(*val, s);
			// Se elibereaza memoria alocata pointerului auxiliar.
			free(s);
			// Se trece la urmatoarea celula si la urmatoarea
			// coloana.
		}
		//Se trece la urmatoarea celula.
		celula = &((*celula)->next);
		// Se trece la urmatoarea coloana.
		coloana = coloana->next;
	}
}

// Functia 'ADD' adauga o linie noua in tabelul cu numele identic cu cel
// memorat la pointerul 'nume' sau afiseaza codul de eroare respectiv
// daca tabelul specificat nu exista.
void ADD(char *nume, t_db *baza)
{
	t_table *tabel;
	tabel = baza->tables;
	// Se cauta tabelul specificat pana este gasit sau se ajunge la
	// sfarsitul listei de tabele.
	if(tabel != NULL)
	while(!strcmp(tabel->name, nume) == 0)
	{
		tabel = tabel->next;
		if(tabel == NULL)break;
	}
	// Daca nu a fost gasit tabelul se afiseaza mesajul de eroare, se
	// citeste restul liniei si se citeste urmatoarea comanda si
	// se opreste executia functiei.
	if(tabel == NULL)
	{

		printf("Table \"%s\" not found in database.\n", nume);
		fgets(nume, MAX_CMD_LEN, stdin);
		scanf("%s", nume);
		return;
	}
	// Daca nu s-a ajuns la sfarsitul listei de tabele, atunci
	// s-a gasit abelul specificat.
	t_line **linie;
	linie = &(tabel->lines);
	// Se cauta sfarsitul listei de linii din tabel.
	while((*linie) != NULL)
	{
		linie = &((*linie)->next);
	}
	// Se aloca noua linie.
	(*linie) = calloc(1, sizeof(t_line));
	// In caz de esec se afiseaza mesajul de eroare, se
	// citeste restul liniei, se citeste urmatoarea comanda
	// si se opreste executia functiei.
	if(*linie == NULL)
	{
		printf("Eroare alocare memorie pentru linie.\n");
		fgets(nume, MAX_CMD_LEN, stdin);
		scanf("%s", nume);
		return;
	}
	// Se aloca si se completeaza noua linie in tabel.
	line(tabel, linie);
	// Se citeste urmatoarea comanda.
	scanf("%s", nume);
}


// Functia 'free_columns' elibereaza coloana primita prin parametru si pe
// urmatoarele din aceeasi lista deoarece se autoapeleaza pentru urmatoarea
// coloana.
void free_columns(t_column *coloana)
{
	if(coloana != NULL)
	{
		// Eliberarea urmatoarelor coloane prin autoapel.
		free_columns(coloana->next);
		// Eliberarea coloanei curente.
		free(coloana);
	}
}

// Functia 'free_table' sterge tabelul primit prin parametru.
void free_table(t_table *tabel)
{
	// Se elibereaza coloanele tabelului.
	free_columns(tabel->columns);
	// Se elibereaza liniile tabelului.
	free_lines(tabel->lines, tabel->type);
	// Se elibereaza restul memoriei alocata tabelului.
	free(tabel);
}

// Functia recursiva 'free_tables' elibereaza memoria alocata unui tabel
// si urmatoarelor tabele.
void free_tables(t_table *tabel)
{
	if(tabel != NULL)
	{
		// Se elibereaza memoria urmatorului tabel daca acesta exista.
		free_tables(tabel->next);
		// Se elibereaza memoria alocata tabelului curent.
		//free_columns(tabel->columns);
		///free_columns(tabel->columns);
		free_table(tabel);
	}
}

// Functia CLEAR elimina toate liniile dintr-un tabel.
void CLEAR(t_db *baza, char *nume)
{
	t_table *tabel;
	tabel = baza->tables;
	// Cat timp nu am ajuns la capatul listei de tabele caut tabelul
	// cu numele memorat la pointerul 'nume'.
	while(tabel != NULL)
	{
		// Daca am gasit tabelul cautat ma opresc.
		if(strcmp(tabel->name, nume) == 0)break;
		// Altfel trec la urmatorul.
		tabel = tabel->next;
	}
	// Daca nu s-a gasit tabelul cautat, atunci se afiseaza codul de
	// eroare si se opreste executia functiei.
	if(tabel == NULL)
	{
		printf("Table \"%s\" not found in database.\n", nume);
		return;
	}
	// Altfel se elibereaza liniile tabelului.
	free_lines(tabel->lines, tabel->type);
	tabel->lines = NULL;
}

// Functia 'CREATE' initializeaza un tabel cu coloanele ale caror nume le
// citeste de la tastatura. In caz ca exista deja un tabel cu numele specificat
// sau tipul de date este necunoscu, atunci nu va fi adaugat vreu tabel nou in
// baza de date.
// La sfarsitul functiei sirul de caractere catre care va indica pointerul
// 'nume' va fi urmatoarea comanda.
void CREATE(t_db *baza, char *nume, char *tip_def)
{
	// Variabila tip memoreaza tipul corespunzator de celule
	t_cellType tip = fel(tip_def);
	// Daca tipul nu este unul dintre cele valide, atunci
	// se opreste executia functiei.
	if(tip == -1)
	{
		printf("Unknown data type: \"%s\".\n", tip_def);
		scanf("%s", nume);
		while(!comanda(nume))scanf("%s", nume);
		return;
	}
	t_table **tabel;
	tabel = &(baza->tables);
	// Se cauta sfarsitul listei de tabele.
	while((*tabel) != NULL)
	{
		// Daca s-a gasit un tabel cu numele specificat se opreste
		// executia functiei.
		if(!strcmp(nume, (*tabel)->name))
		{
			printf("Table \"%s\" already exists.\n", nume);
			scanf("%s", nume);
			while(!comanda(nume))scanf("%s", nume);
			return;
		}
		tabel = &((*tabel)->next);
	}
	// Se aloca noul tabel.
	(*tabel) = calloc(1, sizeof(t_table));
	// Daca nu s-a putut aloca memorie pentru tabel, atunci se
	// afiseaza mesajul de eroare si se opreste exectutia functiei.
	if(!(*tabel))
	{
		printf("Nu s-a putut aloca memorie pentru ");
		printf("tabelul %s.\n", nume);
	}
	// Se denumeste noul tabel.
	strcpy((*tabel)->name, nume);
	// Se memoreaza tipul noului tabel.
	(*tabel)->type = tip;
	// Se citeste numele primei coloane.
	scanf("%s", nume);
	t_column **coloana;
	coloana = &((*tabel)->columns);
	while(!comanda(nume))
	{
		// Se aloca memorie pentru coloane.
		(*coloana) = calloc(1, sizeof(t_column));
		if(!(*coloana))
		{
			// Se dezaloca memoria alocata coloanelor precedente.
			free_columns((*tabel)->columns);
			// Se dezaloca memoria alocata pentru tabel.
			free((*tabel));
			// Se afiseaza mesajul de eroare.
			printf("Nu s-a putut aloca memorie pentru o ");
			printf("coloana %s.\n", nume);
			// Se opreste executia functiei
			return;
		}
		// Se da nume coloanei.
		strcpy((*coloana)->name, nume);
		// Se trece la urmatoarea coloana.
		coloana = &((*coloana)->next);
		// Se citeste urmatorul cuvant.
		scanf("%s", nume);
	}
}

// Functia INIT_DB initializaeza baza de date.
t_db *INIT_DB(char *nume)
{
	t_db *baza;
	// Se aloca baza de date.
	baza = calloc(1, sizeof(t_db));
	// Baza de date primeste numele primit de functie prin parametru.
	strcpy(baza->name, nume);
	// Se returneaza pointerul la baza de date initializata.
	return baza;
}

// Functia free_db elibereaza memoria alocata pentru toata baza de date.
void free_db(t_db *baza)
{
	t_table *tabel;
	tabel = baza->tables;
	free_tables(tabel);
	free(baza);
}

// Functia 'PRINT' afiseaza toate datele stocate intr-un tabel al carui
// nume este primit prin parametru daca acesta exista in baza de date.
void PRINT(t_db *baza, char *nume)
{
	t_table *tabel;
	tabel = baza->tables;
	// Cat timp nu am ajuns la capatul listei de tabele caut tabelul
	// cu numele memorat la pointerul 'nume'.
	while(tabel != NULL)
	{
		// Daca am gasit tabelul cautat ma opresc.
		if(strcmp(tabel->name, nume) == 0)break;
		// Altfel trec la urmatorul.
		tabel = tabel->next;
	}
	// Daca nu s-a gasit tabelul cautat, atunci se afiseaza codul de
	// eroare si se opreste executia functiei.
	if(tabel == NULL)
	{
		printf("Table \"%s\" not found in database.\n", nume);
		return;
	}
	// Daca s-a gasit tabelul, atunci se afiseaza numele acestuia,
	printf("TABLE: %s\n", tabel->name);
	t_column *coloana;
	coloana = tabel->columns;
	// se afiseaza numele coloanelor (capul tabelului),
	while(coloana != NULL)
	{
		// Specificarea '%-31s' va afisa sirul de caractere si
		// apoi atatea spatii cate sunt necesare pentru afisarea
		// unui total de 31 de caractere (functioneaza pentru orice
		// tip de date, iar daca afisarea respectiva depaseste numarul
		// specificat de caractere, atunci se va afisa in mod normal).
		printf("%-31s", coloana->name);
		coloana = coloana->next;
	}
	printf("\n");
	coloana = tabel->columns;
	// se afiseaza bara de caractere '-' care separa capul tabelului de
	// restul liniiilor,
	while(coloana != NULL)
	{
		bara();
		coloana = coloana->next;
	}
	printf("\n");
	t_line *linie;
	linie = tabel->lines;
	// se retine tipul tabelului,
	t_cellType tip = tabel->type;
	// si pentru fiecare linie din tabel
	while(linie != NULL)
	{
		t_cell *celula;
		celula = linie->cells;
		// se afiseaza valorile din celule.
		while(celula != NULL)
		{
			if(tip == INT)
			{
				printf("%-31d", *((int*)(celula->val)) );
			}
			else if(tip == FLOAT)
			{
				printf("%-31f", *((float*)(celula->val)) );
			}
			else if(tip == STRING)
			{
				printf("%-31s", (char*)(celula->val) );
			}
			celula = celula->next;
		}
		printf("\n");
		linie = linie->next;
	}
	// Afisare linie in plus dupa afisarea tabelului.
	printf("\n");
}

// Functia 'DEL_tabel' elibereaza memoria alocata tabelului cu
// numele primit prin pointerul nume.
void DEL_tabel(t_db *baza, char* nume)
{
	t_table *tabel, *ant;
	ant = NULL;
	tabel = baza->tables;
	// Se cauta tabelul specificat in lista de tabele.
	// Pentru cazul in care tabelul exista, pointerul
	// 'ant' va memora adresa tabelului precedent sau
	// 'NULL' daca tabelul cautat este primul din lista.
	while(tabel != NULL)
	{
		if(strcmp(tabel->name, nume) == 0)break;
		ant = tabel;
		tabel = tabel->next;
	}
	// Daca tabelul nu a fost gasit se afiseaza mesajul de eroare
	// si se opreste executia functiei.
	if(tabel == NULL)
	{
		printf("Table \"%s\" not found in database.\n", nume);
		return;
	}
	// Se scoate tabelul gasit din lista de tabele astfe:
	// Daca tabelul gasit nu este primul din lista, atunci
	if(ant != NULL)
	{
		// Tabelul 'tabel' este exclus din lista
		ant->next = tabel->next;
	}
	// Altfel, daca este primul, atunci:
	else if(ant == NULL)
	{
		// Capul listei de tabele din baza de date se muta la
		// urmatorul tabel.
		baza->tables = tabel->next;
	}
	// Se elibereaza tabelul specificat.
	free_table(tabel);
}

// Functia 'cmp_INT_FLOAT' verifica daca valoarea memorata la pointerul 'a'
// respecta conditia 'cond' in raport cu valoarea memorata la pointerul 'val'.
// In caz afirmativ se se returneaza 1. Altfel se returneaza 0.
int cmp(void *a, void *val, char *cond, t_cellType tip)
{
	if(tip == INT)
	{
		// Se retin valorile de tip INT in variabile adecvate acestui
		// tip.
		int x = *((int*)(a)), y = *((int*)(val));
		if(!strcmp(cond, "==") && x == y)return 1;
		else if(!strcmp(cond, "!=") && x != y)return 1;
		else if(!strcmp(cond, ">") && x > y)return 1;
		else if(!strcmp(cond, "<") && x < y)return 1;
		else if(!strcmp(cond, ">=") && x >= y)return 1;
		else if(!strcmp(cond, "<=") && x <= y)return 1;
	}
	else if(tip == FLOAT)
	{
		// Se retin valorile de tip FLOAT in variabile adecvate acestui
		// tip.
		float x = *((float*)(a)), y = *((float*)(val));
		if(!strcmp(cond, "==") && x == y)return 1;
		else if(!strcmp(cond, "!=") && x != y)return 1;
		else if(!strcmp(cond, ">") && x > y)return 1;
		else if(!strcmp(cond, "<") && x < y)return 1;
		else if(!strcmp(cond, ">=") && x >= y)return 1;
		else if(!strcmp(cond, "<=") && x <= y)return 1;
	}
	else if(tip == STRING)
	{
		// Se retin valorile de tip STRING (char*) in variabile
		// adecvate acestui tip.
		char *x = (char*)(a), *y = (char*)(val);
		if(!strcmp(cond, "==") && strcmp(x, y) == 0)return 1;
		else if(!strcmp(cond, "!=") && strcmp(x, y) != 0)return 1;
		else if(!strcmp(cond, ">") && strcmp(x, y) > 0)return 1;
		else if(!strcmp(cond, "<") && strcmp(x, y) < 0)return 1;
		else if(!strcmp(cond, ">=") && strcmp(x, y) >= 0)return 1;
		else if(!strcmp(cond, "<=") && strcmp(x, y) <= 0)return 1;
	}
	// In caz ca valoarea memorata la pointerul 'a' nu respecta condia
	// 'cond' in raport valoarea memorata la pointerul 'val' se
	// returneaza 0.
	return 0;
}
																				
// Functia 'conditie' verifica daca valoarea de tipul 'tip' din celula de pe
// pozitia 'poz' de pe linia 'linie' respecta conditia 'cond' in raport cu
// valoarea 'val'.
int conditie(t_line *linie, int poz, char *cond, void *val, t_cellType tip)
{
	t_cell *celula;
	celula = linie->cells;
	int i = 0;
	// Se cauta celula de pe pozitia 'poz' in lista de celule.
	while(i < poz)
	{
		celula = celula->next;
		++ i;
	}
	// Se verifica daca valoarea din celula respecta conditia
	return cmp(celula->val, val, cond, tip);
}

// Se sterg liniile din tabelul cu numele similar cu cel memorat la pointerul
// 'nume' (daca acest tabel exista) care respecta conditia ce se va citi de la
// stdin (de la tastatura sau prin redirectare exterioara dintr-un
// fisier text).

void DEL_linii(t_db *baza, char *nume)
{
	t_table *tabel;
	tabel = baza->tables;
	// Se cauta tabelul specificat in baza de date.
	while(tabel != NULL)
	{
		// Daca a fost gasit, atunci opresc cautarea.
		if(strcmp(tabel->name, nume) == 0)break;
		tabel = tabel->next;
	}
	// Daca tabelul nu a fost gasit se afiseaza mesajul de eroare,
	// se citeste restul liniei si se opreste executia functiei.
	if(tabel == NULL)
	{
		printf("Table \"%s\" not found in database.\n", nume);
		fgets(nume, MAX_CMD_LEN, stdin);
		return;
	}
	// Se citeste numele coloanei.
	scanf("%s", nume);
	t_column *coloana;
	coloana = tabel->columns;
	int n = 0;
	// Se cauta coloana specificata si se retine pozitia acesteia in lista.
	while(coloana != NULL)
	{
		if(strcmp(coloana->name, nume) == 0)break;
		coloana = coloana->next;
		++ n;
	}
	// Daca coloana nu a fost gasita se afiseaza mesajul de eroare,
	// se citeste restul liniei si se opreste executia functiei.
	if(coloana == NULL)
	{
		printf("Table \"%s\" does not contain ", tabel->name);
		printf("column \"%s\".\n", nume);
		fgets(nume, MAX_CMD_LEN, stdin);
		return;
	}
	char *cond;
	cond = calloc(3, sizeof(char));
	// Se citeste conditia
	scanf("%s", cond);
	void *val;
	if(tabel->type == STRING)
	{
		// Se citeste valoarea de tip STRING intr-un sir auxiliar.
		char *aux;
		aux = calloc(MAX_CMD_LEN, sizeof(char)); 
		scanf("%s", aux);
		// Se aloca memoria exacta necesara stocarii sirului citit.
		val = calloc(strlen(aux) + 1, sizeof(char));
		strcpy((char*)(val), aux);
		free(aux);
	}
	else if(tabel->type == INT)
	{
		// Se citeste valoarea de tip INT.
		val = calloc(1, sizeof(int));
		scanf("%d", (int*)(val));
	}
	else if(tabel->type == FLOAT)
	{
		// Se citeste valoarea de tip FLOAT.
		val = calloc(1, sizeof(float));
		scanf("%f", (float*)val);
	}
	t_line *ant, *linie;
	ant = NULL;
	// Se cauta liniile a caror valoare din coloana 'n' respecta conditia.
	// Pointerul 'ant' va retine adresa liniei precedente.
	linie = tabel->lines;
	while(linie != NULL)
	{
		if(conditie(linie, n, cond, val, tabel->type))
		{
			t_line *aux;
			// Daca se elimina alta linie decat prima, atunci:
			if(ant != NULL)
			{
				// Aux retine adresa liniei ce trebuie eliberata.
				aux = linie;
				// Se izoleaza linia cu adresa memorata
				// in 'aux'.
				linie = linie->next;
				aux->next = NULL;
				ant->next = linie;
				// Se elibereaza linia de la adresa memorata in 'aux'.
				free_line(aux, tabel->type);
			}
			// Daca se elimina prima linie, atunci:
			else if(ant == NULL)
			{
				// Se izoleaza prima linie de restul liniilor.
				tabel->lines = tabel->lines->next;
				linie->next = NULL;
				// Se elibereaza prima linie.
				free_line(linie, tabel->type);
				// Se face trecerea la urmatoarea linie.
				linie = tabel->lines;
			}
			// Altfel se trece la linia urmatoare.
			else
			{
				ant = linie;
				linie = linie->next;
			}
		}
		else
		{
			ant = linie;
			linie = linie->next;
		}
	}
	free(val);
	free(cond);
}
																				
// Functia 'SEARCH' afiseaza capul tabelului cu numele primit prin pointerul
// 'nume' si liniile care respecta conditia citita de la tastatura in raport
// cu valoarea citita de la tastatura.
void SEARCH(t_db *baza, char *nume)
{
	t_table *tabel;
	tabel = baza->tables;
	// Se cauta tabelul specificat in baza de date.
	while(tabel != NULL)
	{
		// Daca a fost gasit, atunci opresc cautarea.
		if(strcmp(tabel->name, nume) == 0)break;
		tabel = tabel->next;
	}
	// Daca tabelul nu a fost gasit se afiseaza mesajul de eroare,
	// se citeste restul liniei si se opreste executia functiei.
	if(tabel == NULL)
	{
		printf("Table \"%s\" not found in database.\n", nume);
		fgets(nume, MAX_CMD_LEN, stdin);
		return;
	}
	// Se citeste numele coloanei.
	scanf("%s", nume);
	t_column *coloana;
	coloana = tabel->columns;
	int n = 0;
	// Se cauta coloana specificata si se retine pozitia acesteia in lista.
	while(coloana != NULL)
	{
		if(strcmp(coloana->name, nume) == 0)break;
		coloana = coloana->next;
		++ n;
	}
	// Daca coloana nu a fost gasita se afiseaza mesajul de eroare,
	// se citeste restul liniei si se opreste executia functiei.
	if(coloana == NULL)
	{
		printf("Table \"%s\" does not contain ", tabel->name);
		printf("column \"%s\".\n", nume);
		fgets(nume, MAX_CMD_LEN, stdin);
		return;
	}
	char *cond;
	cond = calloc(3, sizeof(char));
	// Se citeste conditia
	scanf("%s", cond);
	void *val;
	if(tabel->type == STRING)
	{
		// Se citeste valoarea de tip STRING intr-un sir auxiliar.
		char *aux;
		aux = calloc(MAX_CMD_LEN, sizeof(char)); 
		scanf("%s", aux);
		// Se aloca memoria exacta necesara stocarii sirului citit.
		val = calloc(strlen(aux) + 1, sizeof(char));
		// Se retine sirul citit la pointerul 'val'.
		strcpy((char*)(val), aux);
		// Se elibereaza memoria alocata pointerului 'aux'.
		free(aux);
	}
	else if(tabel->type == INT)
	{
		// Se citeste valoarea de tip INT.
		val = calloc(1, sizeof(int));
		scanf("%d", (int*)(val));
	}
	else if(tabel->type == FLOAT)
	{
		// Se citeste valoarea de tip FLOAT.
		val = calloc(1, sizeof(float));
		scanf("%f", (float*)val);
	}

	printf("TABLE: %s\n", tabel->name);
	coloana = tabel->columns;
	// Se afiseaza numele coloanelor (capul tabelului).
	while(coloana != NULL)
	{
		printf("%-31s", coloana->name);
		coloana = coloana->next;
	}
	printf("\n");
	coloana = tabel->columns;
	// Se afiseaza bara de caractere '-' care separa capul tabelului de
	// restul liniiilor,
	while(coloana != NULL)
	{
		bara();
		coloana = coloana->next;
	}
	printf("\n");

	t_line *linie;
	// Se cauta liniile a caror valoare din coloana 'n' respecta conditia.
	linie = tabel->lines;
	while(linie != NULL)
	{
		if(conditie(linie, n, cond, val, tabel->type))
		{
			t_cell *celula;
			celula = linie->cells;
			// Se afiseaza valorile din celule.
			while(celula != NULL)
			{
				if(tabel->type == INT)
				{
					printf("%-31d", *((int*)(celula->val)) );
				}
				else if(tabel->type == FLOAT)
				{
					printf("%-31f", *((float*)(celula->val)) );
				}
				else if(tabel->type == STRING)
				{
					printf("%-31s", (char*)(celula->val) );
				}
				celula = celula->next;
			}
			printf("\n");
		}
		linie = linie->next;
	}
	printf("\n");
	free(val);
	free(cond);
}

// Functia 'PRINT_DB' afiseaza toate datele din baza de date.
void PRINT_DB(t_db *baza)
{
	printf("DATABASE: %s\n\n", baza->name);
	t_table *tabel;
	tabel = baza->tables;
	// Pentru fiecare tabel:
	while(tabel != NULL)
	{
		// Se afiseaza numele tabelului.
		printf("TABLE: %s\n", tabel->name);
		t_column *coloana;
		coloana = tabel->columns;
		// Se afiseaza numele coloanelor (capul tabelului),
		while(coloana != NULL)
		{
			printf("%-31s", coloana->name);
			coloana = coloana->next;
		}
		printf("\n");
		coloana = tabel->columns;
		// se afiseaza bara de caractere '-' care separa capul tabelului de
		// restul liniiilor,
		while(coloana != NULL)
		{
			bara();
			coloana = coloana->next;
		}
		printf("\n");
		t_line *linie;
		linie = tabel->lines;
		// se retine tipul tabelului,
		t_cellType tip = tabel->type;
		// si pentru fiecare linie din tabel
		while(linie != NULL)
		{
			t_cell *celula;
			celula = linie->cells;
			// se afiseaza valorile din celule.
			while(celula != NULL)
			{
				if(tip == INT)
				{
					printf("%-31d", *((int*)(celula->val)) );
				}
				else if(tip == FLOAT)
				{
					printf("%-31f", *((float*)(celula->val)) );
				}
				else if(tip == STRING)
				{
					printf("%-31s", (char*)(celula->val) );
				}
				celula = celula->next;
			}
			printf("\n");
			linie = linie->next;
		}
		// Afisare linie in plus dupa afisarea tabelului.
		printf("\n");
		// Se trece la tabelul urmator.
		tabel = tabel->next;
	}
}

int main(void)
{
    t_db *baza;
	char *cmd, *tip_def;
	// Se aloca memorie pointerului cu care se vor citi comenzile.
	cmd = calloc(MAX_CMD_LEN + 1, sizeof(char));
	// Se aloca memorie pointerului in care se va citi tipul tabelului.
	tip_def = calloc(31, sizeof(char));
	scanf("%s", cmd);
	while(1)
	{
		if(!strcmp(cmd, "PRINT_DB"))
		{
			PRINT_DB(baza);
			// Se citeste urmatoarea comanda.
			scanf("%s", cmd);
		}
		else if(!strcmp(cmd, "SEARCH"))
		{
			// Se citeste numele tabelului.
			scanf("%s", cmd);
			// Se executa comanda "SEARCH".
			SEARCH(baza, cmd);
			// Se citeste comanda urmatoare.
			scanf("%s", cmd);
		}
		else if(!strcmp(cmd, "CLEAR"))
		{
			// Se citeste numele tabelului.
			scanf("%s", cmd);
			// Se sterg liniile din tabelul specificat.
			CLEAR(baza, cmd);
			// Se citeste urmatoarea comanda.
			scanf("%s", cmd);
		}
		else if(!strcmp(cmd, "DELETE"))
		{
			// Se citeste numele tabelului
			scanf("%s", cmd);
			char c;
			// Se verifica care dintre comenzile 'DELETE' trebuie indeplinita.
			c = getchar();
			if(c == '\n')
			{
				// Se sterge tabelul cu numele similar cu cel
				// memorat la pointerul 'cmd' daca acest tabel exista
				DEL_tabel(baza, cmd);
			}
			// daca c == ' ' atunci mai urmeaza alti parametri
			else
			{
				// Se sterg liniile din tabelul cu numele similar cu cel
				// memorat la pointerul 'cmd' (daca acest tabel exista)
				// care respecta conditia ce se va citi de la tastatura.
				DEL_linii(baza, cmd);
			}
			// Se citeste urmatoarea comanda.
			scanf("%s", cmd);
		}
		else if(!strcmp(cmd, "PRINT"))
		{
			// Se citeste
			scanf("%s", cmd);
			PRINT(baza, cmd);
			scanf("%s", cmd);
		}
		else if(!strcmp(cmd, "ADD"))
		{
			// Se citeste numele tabelului.
			scanf("%s", cmd);
			ADD(cmd, baza);
		}
		else if(!strcmp(cmd, "INIT_DB"))
		{
			// Se citesc spatiile in plus de dinaintea numelui bazei de date.
			char c;
			scanf("%c", &c);
			while(c == ' ')
			{
				scanf("%c", &c);
			}
			cmd[0] = c;
			// Se citeste numele bazei de date.
			fgets(cmd + 1, MAX_DB_NAME_LEN, stdin);
			// Se elimina posibilul '\n' de la sfarsitul numelui bazei de date.
			if(cmd[strlen(cmd) - 1] == '\n')
			{
				cmd[strlen(cmd) - 1] = '\0';
			}
			// Se initializeaza baza de date.
			baza = INIT_DB(cmd);
			scanf("%s", cmd);
		}
		else if(!strcmp(cmd, "DELETE_DB"))
		{

			// Se elibereaza memoria alocata bazei de date.
			free_db(baza);
			// Se elibereaza memoria alocata variabilei in care sunt citite comenzile.
			free(cmd);
			// Se elibereaza variabila pentru citirea tipului.
			free(tip_def);
			// Se afiseaza o linie si se returneaza 0 pentru oprirea executiei.
			return 0;
		}
		else if(!strcmp(cmd, "CREATE"))
		{
			scanf("%s", cmd);
			scanf("%s", tip_def);
			CREATE(baza, cmd, tip_def);
		}
		// Daca s-a dat o comanda invalida se afiseaza textul
		// corespunzator erorii
		else if(!comanda(cmd))
		{
			// Se afiseaza comanda nerecunoscuta.
			printf("Unknown command: \"%s", cmd);
			// Se citeste si se afiseaza restul liniei.
			fgets(cmd, 300, stdin);
			// Daca s-a citit si un '\n', acesta este inlocuit de
			// terminatorul de sir.
			if(cmd[strlen(cmd) - 1] == '\n')
			{
				cmd[strlen(cmd) - 1] = '\0';
			}
			printf("%s\".\n", cmd);
			// Se citeste urmatoarea comanda.
			scanf("%s", cmd);
		}
	}
}
