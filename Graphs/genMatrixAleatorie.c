#include <stdio.h>  
#include <stdlib.h>
#include <time.h>


struct Node
{
	int valeur;
	struct Node* next;
};

void afficheTab(int tab[], int taille);
void afficheValeurTab(int *tab, int taille);
void afficheMatrix(int **matrix, int taille);
void plusPetit(int **matrix, int taille,int sD, int *distance, int *pred);
int* getVoisin(int **tab, int taille, int sommet);
void enfiler(int valeur, struct Node **debut, struct Node **fin);
int defiler(struct Node **debut);

void main(){
	int taille = 8;
	int **matrix = NULL;
	matrix = (int **) malloc(taille*sizeof(int**));
	for (int i = 1; i < taille+1; i++) 
		matrix[i] = (int *)malloc(taille*sizeof(int));



	srand(time(NULL));   // should only be called once
	int r = rand()%20;  
	printf("%d r = \n", r);
	int tabs[4] = {0, 0, 0, r};
	
	int randomnumber = rand()%3;
	printf("%d randomnumber = \n", randomnumber);
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			{
				matrix[i][j] = r;
			}
	}

	printf("MATRIC NEW GEN\n");
	afficheMatrix(matrix, taille);
	
	
}
void plusPetit(int **matrix, int taille, int sD, int *distance, int *pred){


	distance[sD] = 0;
	struct Node *debut = NULL;
	struct Node *fin = NULL;
	enfiler(sD, &debut, &fin);
	while(debut != NULL){
		int s = defiler(&debut);
		for (int v = 1; v < taille+1; v++){
			// Si c'est un voisin avec une ponderation
			if(matrix[s][v] > 0 ) {
				if(distance[v] > distance[s] + matrix[s][v]){
					distance[v] = distance[s] + matrix[s][v];
					enfiler(v, &debut,&fin);
					pred[v] = s;

				}	
			}		
		}
	}

/*printf(" TABLEAU DES PREDECESSEURS : \n");
afficheValeurTab(pred, taille);
afficheValeurTab(&pred, taille);*/

}
/* Affiche une matrice */
void afficheMatrix(int **matrix, int taille){
	for (int i = 0; i <taille; i++){
		for (int j = 0; j < taille; j++){
			printf("%d\t",matrix[i][j] );
		}
		printf("\n");
	}
}
/*	Affiche un tableau avec ses valeurs en %u */
void afficheTab(int tab[], int taille){
    for (int i = 0; i < taille; i++)
    {
        printf("%u | ", tab[i]);
    }
    printf("\n");
}
/* Affiche un tableau avec ses valeurs en %d */
void afficheValeurTab(int *tab, int taille){

    for (int i = 1; i < taille+1; i++)
    {
        printf("%d =>  %d \n", i, tab[i]);
    }
}
/* Affiche un tableau avec la liste des voisins du sommet */
int* getVoisin(int **tab, int taille, int sommet){
	int *result = (int *) malloc(taille*sizeof(int));
	for (int i = 0; i < taille; i++)
		if(tab[sommet][i]>0) result[i] = tab[sommet][i];
	return result;
}

int defiler(struct Node **debut){
	if(*debut == NULL)
		return -1;
	else {
		int result = (*debut)->valeur;
		struct Node *next = (*debut)->next;		
		free(*debut); // Je vire la tete
		*debut= next;
		return result;
	}
}

void enfiler(int valeur, struct Node **debut, struct Node **fin){
	struct Node *new;
	new = (struct Node *)malloc(sizeof(struct Node));
	new->valeur = valeur;

	if(*debut==NULL){
		new->next = NULL;
		*debut = new;
		*fin = new;
	}else{
		new->next = NULL;
		(*fin)->next = new;
		*fin = new;
	}
}
