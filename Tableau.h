#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int Id;
	char Marque[20];
	char nom[20];
	char modele[20];
	char type_C[20];
	int nbr_Place;
	char type_T[20];
	float prix;
	char Dis[4];
} Voiture;

void max_char(Voiture *t, int n,int *l){
	int i;
	l[0]=3;l[1]=6;l[2]=6;
	for(i=0;i<n;i++){
		if(l[0]<strlen(t[i].nom)){
			l[0]=strlen(t[i].nom);
		}
		if(l[1]<strlen(t[i].Marque)){
			l[1]=strlen(t[i].Marque);
		}
		if(l[2]<strlen(t[i].modele)){
			l[2]=strlen(t[i].modele);
		}
	}
}

int taille_int(int n){
	int cmp=0;
	while(n!=0){
		n/=10;
		cmp++;
	}
	return cmp;
}

void max_int(Voiture *t, int n,int *l){
	int i;
	l[0]=2;l[1]=9;l[2]=4;
	for(i=0;i<n;i++){
		if(taille_int(t[i].Id)>l[0]){
			l[0]=taille_int(t[i].Id);
		}
		if(taille_int(t[i].nbr_Place)>l[1]){
			l[1]=taille_int(t[i].nbr_Place);
		}
		if(taille_int(t[i].prix)>l[2]){
			l[2]=taille_int(t[i].prix);
		}
	}
}

void printf_Tirer(int n){
	int i;
	for(i=0;i<n;i++){
		printf("_");
	}
}

void printf_Space(int n){
	int i;
	for(i=0;i<n;i++){
		printf(" ");
	}
}

void Down(int *ti,int *tc,int n){
	printf_Tirer(taille_int(n));
	printf("|");
	printf_Tirer(ti[0]);
	printf("|");
	printf_Tirer(tc[0]);
	printf("|");
	printf_Tirer(tc[1]);
	printf("|");
	printf_Tirer(tc[2]);
	printf("|");
	printf_Tirer(ti[1]);
	printf("|");
	printf_Tirer(9);
	printf("|");
	printf_Tirer(12);
	printf("|");
	printf_Tirer(13);
	printf("|");
	printf_Tirer(ti[2]+3);
	printf("|\n");
}

void head(Voiture *t, int n){
	int i, j, ti[3], tc[3]; 
	max_int(t,n,ti);
	max_char(t,n,tc);
	printf(" ");
	printf_Tirer(taille_int(n)+ti[0]+ti[1]+ti[2]+tc[0]+tc[1]+tc[2]+46);
	printf("\n|");
	printf_Space(taille_int(n));
	printf("|ID");
	printf_Space(ti[0]-2);
	printf("|Nom");
	printf_Space(tc[0]-3);;
	printf("|Marque");
	printf_Space(tc[1]-6);
	printf("|Modele");
	printf_Space(tc[2]-6);
	printf("|Nbr place");
	printf_Space(ti[1]-9);
	printf("|Carburant|Transmission|Disponibilite");
	printf("|Prix");
	printf_Space(ti[2]+3-4);
	printf("|\n|");
	Down(ti,tc,n);
}

void aff(Voiture *t,int i,int n) {
	int j, A, ti[3], tc[3];
	max_int(t,n,ti);
	max_char(t,n,tc);
	printf("|%d",i+1);
	printf_Space(taille_int(n)-taille_int(i+1));
	printf("|%d",t[i].Id);
	printf_Space(ti[0]-taille_int(t[i].Id));
	printf("|%s",t[i].nom);
	printf_Space(tc[0]-strlen(t[i].nom));
	printf("|%s",t[i].Marque);
	printf_Space(tc[1]-strlen(t[i].Marque));
	printf("|%s",t[i].modele);
	printf_Space(tc[2]-strlen(t[i].modele));
	printf("|%d",t[i].nbr_Place);
	printf_Space(ti[1]-taille_int(t[i].nbr_Place));
	printf("|%s",t[i].type_C);
	printf_Space(9-strlen(t[i].type_C));
	printf("|%s",t[i].type_T);
	printf_Space(12-strlen(t[i].type_T));
	printf("|%s",t[i].Dis);
	printf_Space(10);
	printf("|%.2f",t[i].prix);
	printf_Space(ti[2]-taille_int(t[i].prix));
	printf("|\n|");
	Down(ti,tc,n);
}