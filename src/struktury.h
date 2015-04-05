/*
 * struktury.h
 *	@brief Pilk zawierający definicje struktur używanych przez program oraz nagłówki funkcji je obsługujących.
 *
 *  Created on: 04-04-2015
 *      Author: zakp2
 */

#ifndef STRUKTURY_H_
#define STRUKTURY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief Struktura węzła drzewa AVL.
 * @details Za pomocą tej struktury zostanie stworzone drzewo przechowujące
 * słowa oraz numery ich wystąpień w tekście.
 * Drzewo AVL jest drzewem poszukiwań binarnych BST, w którym poddrzewa każdego węzła różnią się wysokością (ilością poziomów) co najwyżej o 1.
 * Gwarantuje to zrównoważenie drzewa AVL.
 */
typedef struct node_t{
	/// Treść słowa.
	char var[MAX_WRD];
	/// Lewy syn.
	struct node_t * left;
	/// Prawy syn.
	struct node_t * right;
	/// Ojciec.
	struct node_t * parent;
	/// Parametr równowagi.
	short bf;
	/// Numery wystąpień słów w tekście.
	key_vector * keys;
}node;

/**
 * @brief Struktura przechowująca dane uzyskane z plików wejściowych lub(oraz) wcześniej utworzonej bazy.
 * @details
 */
typedef struct container_t{
	/// Wskaźnik na korzeń drzewa zawierającego możliwe słowa oraz numery ich wystąpień.
	node *root;
	/// Numer wystąpienia ostatniego dodanego słowa;
	int last_key;
	/// Wskaźnik na tablicę przechowującą odwołania do słow z pomocą numeru wystąpinia.
	node *pointers;
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
	/// Czy generować statystyki.
	int stat;
	///Miejsce zapisu statystyk.
	char stat_out_v [MAX_DN];
}parameters;



/**
 * @brief Funkcja tworząca nowy @ref key_vector .
 * @return Wskaźnik do stworzonego wektora.
 */
key_vector *new_key_vector();

/**
 * @brief Funkcja usuwająca @ref key_vector .
 * @param *key_vec_p Wskaźnik na wektor do usunięcia.
 */
void del_key_vector(key_vector*key_vec_p);

/**
 * @brief Funkcja dodająca wystąpienie do @ref key_vector .
 * @param *key_vec_p Wskaźnik na wektor do którego ma być dodana wartość.
 * @param key Numer wystąpienia.
 */
void add_to_key_vector(key_vector*key_vec_p,int key);



/**
 * @brief Funkcja tworząca nowy @ref node .
 * @param key Numer wystąpienia.
 * @param var Treść słowa.
 * @return Wskaźnik do stworzonego węzła.
 */
node* new_node(int key,char var[MAX_WRD]);

/**
 * @brief Funkcja usuwająca @ref in_vector .
 * @param *no_p Wskaźnik na węzeł do usunięcia.
 */
void del_node(node*no_p);

/**
 * @brief Rotacja węzłów połączonych prawymi krawędziami.
 * @details W rotacji uczestniczą węzły A i B.
 *  Węzeł B zajmuje miejsce węzła A, węzeł A staje się lewym dzieckiem węzła B.
 *  Lewe dziecko węzła B (BL) staje się prawym dzieckiem węzła A.
 * @param root Korzeń drzewa.
 * @param A Węzeł, w którym występuje zaburzenie równowagi w prawym poddrzewie.
 * @return Węzeł drzewa, który zastąpił po rotacji węzeł A (prawe dziecko A).
 */
node * AVLrotationRR(node * root, node * A);

/**
 * * @brief Rotacja węzłów połączonych lewymi krawędziami.
 * @param root Korzeń drzewa.
 * @param A Węzeł, w którym występuje zaburzenie równowagi w lewym poddrzewie.
 * @return Węzeł drzewa, który zastąpił po rotacji węzeł A (lewe dziecko A).
 */
node * AVLrotationLL(node * root, node * A);

/**
 * @brief Rotacja RL jest złożeniem rotacji RR i rotacji LL.
 * @param root Korzeń drzewa.
 * @param A Węzeł, w którym występuje zaburzenie równowagi w prawym poddrzewie.
 * @return Węzeł drzewa, który zastąpił po rotacji węzeł A.
 */
node * AVLrotationRL(node * root, node * A);

/**
 * @brief Rotacja LR jest złożeniem rotacji LL i rotacji RR.
 * @param root Korzeń drzewa.
 * @param A Węzeł, w którym występuje zaburzenie równowagi w lewym poddrzewie.
 * @return Węzeł drzewa, który zastąpił po rotacji węzeł A.
 */
node * AVLrotationLR(node * root, node * A);

/**
 * @brief Wstawianie węzła w drzewie AVL
 * @details Operacja wstawiania nowego elementu do drzewa AVL jest dwuetapowa.
 * Pierwszy etap polega na tradycyjnym wstawieniu węzła do drzewa.
 * Nowy węzeł jest zawsze dodawany w liściu drzewa.
 * W drugim etapie idąc od rodzica wstawionego węzła ku korzeniowi drzewa sprawdzamy,
 * czy dodanie węzła nie naruszyło własności AVL. Jeśli tak, to za pomocą odpowiedniej
 * rotacji węzłów przywracamy równowagę w węźle.
 * Po wykonaniu rotacji zrównoważenie drzewa zostaje przywrócone, operacja wstawiania
 * nowego węzła kończy się.
 * @param root Korzeń drzewa.
 * @param key Numer wystąpienia.
 * @param var Wartość słowa.
 */
void AVLinsert(node * root, int key,char var[MAX_WRD]);



/**
 * @brief Funkcja tworząca nowy @ref in_vector .
 * @return Wskaźnik do stworzonego wektora.
 */
in_vector *new_in_vector();

/**
 * @brief Funkcja usuwająca @ref in_vector .
 * @param *in_p Wskaźnik na wektor do usunięcia.
 */
void del_in_vector(in_vector*in_p);

/**
 * @brief Funkcja dodająca wystąpienie do @ref in_vector .
 * @param *in_p Wskaźnik na wektor do którego ma być dodana wartość.
 * @param dn (destination) Wystąpienie.
 */
void add_to_in_vector(in_vector*in_p,char *dn);



/**
 * @brief Funkcja tworząca nowy @ref parameters .
 * @return Wskaźnik do stworzonego pola.
 */
parameters *new_parameters();

/**
 * @brief Funkcja usuwająca @ref parameters .
 * @param *in_p Wskaźnik na wektor do usunięcia.
 */
void del_parameters(parameters*in_p);



#endif /* STRUKTURY_H_ */
