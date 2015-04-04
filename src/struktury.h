/*
 * struktury.h
 *	@brief Pilk zawierający definicje struktur używanych przez program oraz nagłówki funkcji je obsługujących.
 *
 *  Created on: 04-04-2015
 *      Author: zakp2
 */

#ifndef STRUKTURY_H_
#define STRUKTURY_H_

/// Stała określająca maksymalną długość pojedyńczego słowa.
#define MAX_WRD 100
/// Stała określająca maksymalną długość ścierzki dostępu do pliku wraz z jego nazwą.
#define MAX_DN 100

/**
 * @brief Struktura przechowująca numery wystąpień słowa.
 */
typedef struct key_vector_t{
	/// Wskaźnik na wartości wystąpień.
	int*var;
	/// (capacity) Obecna pojemność wektora.
	int cap;
	/// (occupaid) Ilość obecnie zajętych pól w wektorze.
	int oc;
}key_vector;

/**
 * @brief Funkcja tworząca nowy @ref key_vector .
 * @return Wskaźnik do stworzonego wektora.
 */
key_vector *new_key_vector(){
	key_vector *new;
	new=(key_vector*)malloc(sizeof(key_vector));
	new->cap=2;
	new->oc=0;
	new->var=(int*)malloc(new->cap*sizeof(int));
	return new;
}

/**
 * @brief Funkcja usuwająca @ref key_vector .
 * @param *key_p Wskaźnik na wektor do usunięcia.
 */
void del_key_vector(key_vector*key_p){
	free(key_p->var);
	free(key_p);
}

/**
 * @brief Funkcja dodająca wystąpienie do @ref key_vector .
 * @param *key_p Wskaźnik na wektor do którego ma być dodana wartość.
 * @param key Numer wystąpienia.
 */
void add_to_key_vector(key_vector*key_p,int key){
	if(key_p->cap==key_p->oc){
		key_p->var=(int*)realloc(key_p->var,2*key_p->cap*sizeof(int));
		key_p->cap*=2;
	}
	key_p->var[++key_p->oc]=key;
}



/**
 * @brief Struktura węzła drzewa vlc
 * @details Za pomocą tej struktury zostanie stworzone drzewo przechowujące
 * słowa oraz numery ich wystąpień w tekście.
 */
typedef struct noode_t{
	/// Treść słowa.
	char var[MAX_WRD];
	/// Lewy syn.
	struct noode_t * left;
	/// Prawy syn.
	struct noode_t * right;
	/// Ojciec.
	struct noode_t * parent;
	/// Parametr równowagi.
	short bf;
	/// Numery wystąpień słów w tekście.
	key_vector * keys;
}noode;



/**
 * @brief Struktura przechowująca dane uzyskane z plików wejściowych lub(oraz) wcześniej utworzonej bazy.
 * @details
 */
typedef struct container_t{
	/// Wskaźnik na korzeń drzewa zawierającego możliwe słowa oraz numery ich wystąpień.
	noode *root;
	/// Numer wystąpienia ostatniego dodanego słowa;
	int last_key;
	/// Wskaźnik na tablicę przechowującą odwołania do słow z pomocą numeru wystąpinia.
	noode *pointers;
}container;



/**
 * @brief Struktura przechowująca nazwy plików z tekstem będącym podstawą generacji..
 */
typedef struct in_vector_t{
	/// Wskaźnik na nazwy.
	char**var;
	/// (capacity) Obecna pojemność wektora.
	int cap;
	/// (occupaid) Ilość obecnie zajętych pól w wektorze.
	int oc;
}in_vector;

/**
 * @brief Funkcja tworząca nowy @ref in_vector .
 * @return Wskaźnik do stworzonego wektora.
 */
in_vector *new_in_vector(){
	in_vector *new;
	new=(in_vector*)malloc(sizeof(in_vector));
	new->cap=2;
	new->oc=0;
	new->var=(char**)malloc(new->cap*sizeof(char*));
	return new;
}

/**
 * @brief Funkcja usuwająca @ref in_vector .
 * @param *in_p Wskaźnik na wektor do usunięcia.
 */
void del_in_vector(in_vector*in_p){
	int i;
	for(i=0;i<in_p->oc;i++){
		free(in_p->var[i]);
	}
	free(in_p->var);
	free(in_p);
}

/**
 * @brief Funkcja dodająca wystąpienie do @ref in_vector .
 * @param *in_p Wskaźnik na wektor do którego ma być dodana wartość.
 * @param dn (destination) Wystąpienie.
 */
void add_to_in_vector(in_vector*in_p,char *dn){
	if(in_p->cap==in_p->oc){
		in_p->var=(char**)realloc(in_p->var,2*in_p->cap*sizeof(char*));
		in_p->cap*=2;
	}

	in_p->var[++in_p->oc]=(char*)malloc(sizeof(int[MAX_DN]));
	strcpy(in_p->var[in_p->oc],dn);
}




/**
 * @brief Struktura przechowująca imformacje uzyskane za pomocą parametrów uruchomienia programu.
 *  @details Wartości przyjmowane domyślnie opisane są
 */
typedef struct parameters_t{
	/// Czy podano pliki z tekstem będącym podstawą generacji.
	int in;
	/// Wektor przechowujący nazwy plików z tekstem będącym podstawą generacji.
	in_vector*in_v;
	/// Którego stopnia n-gramy mają zostać użyte do generacji.
	int n_gram;
	/// Czy określono miejsce zapisu wygenerowanego tekstu.
	int out;
	/// Miejsce zapisu wygenerowanego tekstu.
	char out_v [MAX_DN];
	/// Czy kożystać z wcześniej utworzonej bazy danych.
	int b_in;
	/// Miejsce zapisu bazy danych która ma być wykorzystana.
	char b_in_v [MAX_DN];
	/// Czy utworzyć bazę danych.
	int b_out;
	/// Miejsce zapisu bazy danych która ma być utworzona.
	char b_out_v [MAX_DN];
	/// Ilość akapitów w generowanym tekście.
	int par;
	/// Ilość słów w akapicie w generowanym tekście.
	int wrd;
}parameters;


/**
 * @brief Funkcja tworząca nowy @ref parameters .
 * @return Wskaźnik do stworzonego pola.
 */
parameters *new_parameters(){
	parameters *new;
	new=(parameters*)malloc(sizeof(parameters));
	new->in=0;
	new->b_in_v=NULL;
	new->b_out=0;
	new->b_out_v="baza.out\0";
	new->in=0;
	new->in_v=NULL;
	new->n_gram=3;
	new->out=0;
	new->out_v="generated.out\0";
	new->par=5;
	new->wrd=50;
	return new;
}

/**
 * @brief Funkcja usuwająca @ref parameters .
 * @param *in_p Wskaźnik na wektor do usunięcia.
 */
void del_parameters(parameters*in_p){
	del_in_vector(in_p->in_v);
	free(in_p);
}

#endif /* STRUKTURY_H_ */
