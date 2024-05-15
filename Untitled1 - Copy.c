#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Tableau.h"

char Nom[10];
int ID_TXT = 0;

void WriteID() {
	FILE *f;
	f=fopen("Id.txt","wt");
	if(f) {
		ID_TXT++;
		fprintf(f,"%d",ID_TXT);
		fclose(f);
	}
} 

void ReadID() {
	FILE *f;
	f=fopen("Id.txt","rt");
	if(f) {
		fscanf(f,"%d",&ID_TXT);
		fclose(f);
	}
}

 void Inserer(Voiture *t,int i) {
	int d;
	printf("Entrer La Marque : ");
	rewind(stdin);
	scanf("%s",t[i].Marque);
	printf("Entrer Le Modele : ");
	rewind(stdin);
	scanf("%s",t[i].modele);
	do{
		printf("Entrer Le Type DE Carburent (1->essence ou 2->diesel): ");
		rewind(stdin);
		scanf("%d",&d);
	}while(d<1||d>2);
		if(d==1) strcpy(t[i].type_C,"Essence");
		if(d==2) strcpy(t[i].type_C,"Diesel");
	printf("Entrer Le Nombre de place : ");
	rewind(stdin);
	scanf("%d",&t[i].nbr_Place);
	rewind(stdin);
	do{
		printf("Entrer Le Type de transmission (1->automatique ou 2->manuelle): ");
		rewind(stdin);
		scanf("%d",&d);
	}while(d<1||d>2);
		if(d==1) strcpy(t[i].type_T,"Automatique");
		if(d==2) strcpy(t[i].type_T,"Manuelle");
	printf("Entrer Le prix : ");
	rewind(stdin);
	scanf("%f",&t[i].prix);
	do{
		printf("Entrer La Disponibiliter (1->Oui ou 2->Non): ");
		rewind(stdin);
		scanf("%d",&d);
	}while(d<1||d>2);
		if(d==1) strcpy(t[i].Dis,"Oui");
		if(d==2) strcpy(t[i].Dis,"Non");
	ReadID();
	t[i].Id = ID_TXT;
	WriteID();
	strcpy(t[i].nom,Nom);
}

int countLines() {
    FILE *f;
    int n = 0;
    char c;
    f = fopen("Data.csv", "r");
    if (f) {
        while ((c = fgetc(f)) != EOF) {
            if (c == '\n') {
                n++;
            }
        }
        fclose(f);
    }
    return n;
}

Voiture *Ajout(Voiture *t,int *n) {
	(*n)++;
	if(t==NULL){
		t = (Voiture*)malloc(*n*sizeof(Voiture));
	} else {
		t = (Voiture*)realloc(t,*n*sizeof(Voiture));
	}
	Inserer(t,*n-1);
	return t;
}

int Menu_M() {
	int choix;
	printf("************MENU************\n");
	printf("1) la marque\n");
	printf("2) le nom\n");
	printf("3) le modele\n");
	printf("4) le type de carburant\n");
	printf("5) le nombre de place\n");
	printf("6) le type de transsmition\n");
	printf("7) le prix\n");
	printf("8) la disponibilite\n");
	printf("9) return to main menu\n");
	printf("****************************\n\n");
	do{
		printf("saisir votre choix :");
		rewind (stdin);
		scanf("%d",&choix);
	}while(choix>9||choix<1);
	return choix;
}

void modifier(Voiture *t,int n) {
	int Id,m,i,test = 0;
		printf("entrer l'Id : ");
		rewind(stdin);
		scanf("%d",&Id);
	do{
		for(i=0; i<n; i++) {
			if(t[i].Id==Id) {
				test = 1;
	  			m = Menu_M();
				switch (m){
					case 1:
						printf("Entrer La Marque : ");
						rewind(stdin);
						scanf("%s",t[i].Marque);
						break;
					case 2:
						printf("Entrer Le Nom : ");
						rewind(stdin);
						scanf("%s",t[i].nom);
						break;
					case 3:
						printf("Entrer Le Modele : ");
						rewind(stdin);
						scanf("%s",t[i].modele);
						break;
					case 4:
						printf("Entrer Le Type DE Carburent : ");
						rewind(stdin);
						scanf("%s",t[i].type_C);
						break;
					case 5:
						printf("Entrer Le Nombre de place : ");
						rewind(stdin);
						scanf("%d",&t[i].nbr_Place);
						break;
					case 6:
						printf("Entrer Le Type de transmission: ");
						rewind(stdin);
						scanf("%s",t[i].type_T);
						break;
					case 7:
						printf("Entrer Le prix : ");
						rewind(stdin);
						scanf("%f",&t[i].prix);
						break;
					case 8:
						printf("Entrer La Disponibilite : ");
						rewind(stdin);
						scanf("%s",t[i].Dis);
						break;
				}
				break;		
			}
		}
		if(test == 0){
			printf("Rien trouver !!!");
			m=9;
		}
	}while(m!=9);
}

Voiture *supression (Voiture *t,int *n){
	int Id ,i,j,test=0;
	if(t!=NULL){
		printf("entrer l Id :");
		rewind(stdin);
		scanf("%d",&Id);
		for (i=0;i<*n;i++){
			if(t[i].Id==Id){
				test=1;
				break;
				
			}
		}
		if(test){
			for(j=i;j<*n;j++){
				t[j]=t[j+1];
			}
			(*n)--;
			t=(Voiture*)realloc(t,*n*sizeof(Voiture));
		}else	printf("Rien trouver !!!");
	}
	return t;
}

void afficher (Voiture *t,int n){
	int i;
	head(t, n);
	for (i=0;i<n;i++){
		aff(t,i,n);
	}
}

void Read_Data(Voiture *tab)
{
    FILE *fp = fopen("Data.csv", "r");
    Voiture x;
    if (!fp) {
        printf("Cant open file.\n");
        return;
    }
    char buffer[1024];
    int row = 0, col = 0;
    while (fgets(buffer, 1024, fp)) {
        col = 0;
        row++;
        char *value = strtok(buffer, ", ");
        while (value) {
            switch (col)
            {
            case 0:
                x.Id = atoi(value);
                break;
            
            case 1:
                strcpy(x.nom, value);
                break;

            case 2:
                strcpy(x.Marque, value);
                break;

            case 3:
            	strcpy(x.modele, value);
                break;
            
            case 4:
                strcpy(x.type_C, value);
                break;

            case 5:
              	x.nbr_Place = atoi(value);
                break;

            case 6:
				strcpy(x.type_T, value);
                break;

            case 7:
				x.prix = atof(value);
                break;
            
            case 8:
       			strcpy(x.Dis, value);
                x.Dis[3]='\0';
				break;
            }
            value = strtok(NULL, ", ");
            col++;
        }
        tab[row - 1] = x;
    }
    fclose(fp);
}

void write_Data(Voiture *t,int n){
	int i;
	FILE *f;
	f=fopen("Data.csv","wt");
	if(f){
		for(i=0;i<n;i++){
			fprintf(f,"%d, %s, %s, %s, %s, %d, %s, %f, %s\n",t[i].Id,t[i].nom,t[i].Marque,t[i].modele,t[i].type_C,t[i].nbr_Place,t[i].type_T,t[i].prix,t[i].Dis);
		}
		fclose(f);	
	}
}

void Recherche_Marque(Voiture *t,int  n){
	int i,test=0;
	char Marque[10];
	printf("entrer la Marque :");
	rewind(stdin);
	scanf("%s",Marque);
	for(i=0;i<n;i++){
		if(strcmp(Marque,t[i].Marque)==0){
			test=1;
			break;
		} 
	}
	if(test){
		head(t, n);
		for(i=0;i<n;i++){
			if(strcmp(Marque,t[i].Marque)==0){
				aff(t,i,n);	
			}
		}
	}else printf("Rien trouver !!!");
}

void Recherche_Dis(Voiture *t,int n){
	int i,d,test=0;
	do{
		printf("Saisir 1 pour afficher les voiture disponible ou 2 pour non disponible :");
		rewind(stdin);
		scanf("%d",&d);
	}while(d<1||d>2);
	for(i=0;i<n;i++){
		if(strcmp("Oui",t[i].Dis)==0&&d==1||strcmp("Non",t[i].Dis)==0&&d==2){
			test = 1;
			break;
		}
	}
	if(test){
		head(t, n);
		for(i=0;i<n;i++){
			if(strcmp("Oui",t[i].Dis)==0&&d==1){
				aff(t,i,n);
			}
			if(strcmp("Non",t[i].Dis)==0&&d==2){
				aff(t,i,n);
			}
		}
	}else printf("Rien trouver !!!");
}

void Trier_Marque(Voiture *t,int n){
	Voiture c;
	int i,j;
	for(i=0;i<n-1;i++){
	    for(j=i+1;j<n;j++){
	        if (strcmp(t[i].Marque,t[j].Marque)>0) {
	            c = t[i];
	            t[i] = t[j];
	            t[j] = c;
	        }
	    }
	}
}

void Trier_Prix(Voiture *t,int n){
	Voiture c;
	int i,j;
	for(i=0;i<n-1;i++){
	    for(j=i+1;j<n;j++){
	        if (t[i].prix>t[j].prix) {
	            c = t[i];
	            t[i] = t[j];
	            t[j] = c;
	        }
	    }
	}
}

void menu1(void) {
	int choix;
	printf("******************************MENU***************************\n");
	printf("1) Afficher La liste des Voitures \n");
	printf("2) cherche Une Voiture\n");
	printf("3) Ajouter Une Voiture\n");
	printf("4) Supprimer Une Voiture\n");
	printf("5) Modifier Une Voiture\n");
	printf("6) Trier La liste des Voitures\n");	
	printf("7) VIP concierge services\n");	
	printf("8) Quitter\n");
	printf("*************************************************************\n\n");
}

int menu2(int a) {
	int choix;
	switch (a)
	{
	case 2:
		printf(" _______________________\n");
		printf("|1) Par Marque          |\n");
		printf("|2) Par Disponibiliter  |\n");
		printf("|3) Retoune o menu 1	|\n");	
		printf("|_______________________|\n\n");
		break;
	case 6:
		printf(" ___________________\n");
		printf("|1) Par Marque      |\n");
		printf("|2) Par Prix        |\n");
		printf("|3) Retoune o menu 1|\n");	
		printf("|___________________|\n\n");
		break;
	}
}

void Space_print(int x){
	int i;
	for(i=0;i<x;i++){
		printf(" ");
	}
}

void Animation(){
	int i;
	for(i=0;i<45;i++){
		Space_print(i);
		printf("           __\n");
		Space_print(i);
		printf("         ~( @\\   \\\n");
		Space_print(i);
		printf("  _________]_[__/_>________\n");
		Space_print(i);
		printf(" /  ____ \\ <>     |  ____  \\\n");
		Space_print(i);
		printf("=\\_/ __ \\_\\_______|_/ __ \\__D\n");
		Space_print(i);
		printf("    (__)             (__)\n");
		if(i==0){
			usleep(1000000);
		}
		usleep(15000);
		if(i!=44){
			system("cls");
		}
	}
	printf("\n\n");
	Space_print(46);
	printf(" ________________________\n");
	Space_print(46);
	printf("/                        \\\n");
	Space_print(45);
	printf("/         Bienvenue        \\\n");
	Space_print(45);
	printf("\\      a notre agence      /\n");
	Space_print(46);
	printf("\\________________________/\n\n");
	
	Space_print(46);
	printf("Veuillez saisir votre nom :");
	scanf("%s",Nom);
}
void displayVoucher(const char* offer, const char* chauffeurName, int chauffeurAge, float pricePerHour) {
    printf("\n=================================================\n");
    printf("||                  VIP Voucher                ||\n");
    printf("=================================================\n");
    printf("||    Offer: %-36s||\n", offer);
    printf("||                                               ||\n");
    printf("||    Chauffeur: %-30s  ||\n", chauffeurName);
    printf("||    Age: %-34d    ||\n", chauffeurAge);
    printf("||                                               ||\n");
    printf("||    Price per Hr: $%-27.2f ||\n", pricePerHour);
    printf("||                                               ||\n");
    printf("||    Tipping is optional. Please consider       ||\n");
    printf("||    tipping your chauffeur for excellent       ||\n");
    printf("||    service.                                   ||\n");
    printf("=================================================\n");
}

void VIP() {
    int choice;

    // Display options with visual elements
    printf("=================================================\n");
    printf("||               VIP Offer Selection            ||\n");
    printf("=================================================\n");
    printf("||   ____                                        ||\n");
    printf("||  |    |                                       ||\n");
    printf("||  |____|                                       ||\n");
    printf("||  |    |_________                              ||\n");
    printf("||  |______________|   CHOOSE YOUR VIP OFFER:    ||\n");
    printf("||  |      %%%%       1. Gold VIP - Personal       ||\n");
    printf("||  |                 concierge for big events   ||\n");
    printf("||  |     %%%%%%%     2. Ultimate VIP - Personal    ||\n");
    printf("||  |                 concierge for big events   ||\n");
    printf("||  |                 including limousines       ||\n");
    printf("||  \\================/                           ||\n");

    // Input validation loop
    do {
        printf("Enter your choice (1 or 2): ");
        // Check if the input is a valid integer
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
        } else if (choice != 1 && choice != 2) { // Check if the input is within the valid range
            printf("Invalid choice. Please select either 1 or 2.\n");
        }
    } while (choice != 1 && choice != 2);

    // Process the user's choice
    switch(choice) {
        case 1:
            printf("\nYou have selected the Gold VIP offer. Enjoy your personal concierge for big events!\n");
            displayVoucher("Gold VIP", "Mehdi Derbez", 35, 50.0); // Example voucher for Gold VIP
            break;
        case 2:
            printf("\nYou have chosen the Ultimate VIP offer. Enjoy your personal concierge with limousines for big events!\n");
            displayVoucher("Ultimate VIP", "Imrane Lakniti", 40, 100.0); // Example voucher for Ultimate VIP
            break;
        default:
            printf("\nInvalid choice. Please select either 1 or 2.\n");
    }
}
int main() {
	Voiture *t=NULL;
	int ch1,ch2;
	int	n=countLines();
	system("color 9");
	if(n!=0){
		t = (Voiture*)malloc(n * sizeof(Voiture));
		Read_Data(t);
	}
	Animation();
	system("cls");
	do{
		menu1();
		do{
			printf("saisir votre choix :");
			rewind (stdin);
			scanf("%d",&ch1);
		}while(ch1>8||ch1<1);
		if(ch1==2||ch1==6){
			menu2(ch1);	
			do{
				printf("saisir votre choix :");
				rewind (stdin);
				scanf("%d",&ch2);
			}while(ch2>3||ch2<1);
		}
		if(t==NULL && ch1!=3){
			printf("Pas de voiture pour le moment");
			ch1=0;
		} 
		switch(ch1){
			case 1:	afficher(t,n);
				break;
			case 2: if(ch2==1) Recherche_Marque(t,n);
					if(ch2==2) Recherche_Dis(t,n);
				break;
			case 3: t = Ajout(t,&n);
				break;
			case 4: t = supression(t,&n);
				break;
			case 5: modifier(t,n);
				break;
			case 6: if(ch2==1) Trier_Marque(t,n);
					if(ch2==2) Trier_Prix(t,n);
				break;
			case 7:
			   VIP();
			   break;	
			case 8: 
				free(t);
				return 0;
		}
		write_Data(t,n);
		printf("\n");
		system("pause");
		system("cls");
	}while(ch1!=7);
}