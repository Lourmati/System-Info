#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv) {
  
int booleen=0;//Le int, que je vais utiliser pour faire ma boucle globale
int choice;
char hostname[100];//Le hostname, je lui ai donne 100 caractere pour la taille

//Bienvenue au hostname
printf("\n");
//J'utilise la fonction gethosname et hostname
gethostname(hostname, sizeof(hostname));
printf("Bonjour, vous êtes présentement sur l'ordinateur %s\n",hostname);
printf("\n");

//Boucle (do...while) pour revenir au menu, tant que l'utilisateur n'a pas selectionne 4.Quitter
do{
  
//Affichage du menu
printf("Veuillez choisir parmi les options suivantes:\n");
printf("1.Afficher les informations sur la mémoire \n");
printf("2.Afficher les informations sur la configuration IP \n");
printf("3.Afficher les informations sur les périphériques \n");
printf("4.Quitter ce magnifique logiciel\n");

//Saisie du choix de l'utilisateur
printf("Veuillez choisir entre 1 et 4:");
scanf ("%d", &choice);

//Boucle, si l'utilisateur fait un choix invalide (inferieur a 1, ou superieur a 4)
while(choice<1 || choice>4){
  vider_buffer(); //On vide le buffer avant la prochaine lecture
  printf("Entrez une valeur entre 1 et 4 inclusivement \n");//Message d'erreur
  printf("Veuillez choisir entre 1 et 4:");
  scanf ("%d", &choice); 
}

//J'utilise le switch, pour afficher selon le choix
switch (choice) {
 case 1:
   //Affichage des informations sur la mémoire
   printf("\n");
   afficherMem();
   printf("\n");
   break;
        
 case 2:
   //Affichage de l'adresse IP
   afficherIP();
   break;

 case 3:
   printf("\n");
   //Cette méthode fonctionne comme le afficherMem()
   //En utilisant, le strstr, et en affichant la ligne
   afficherPeri();//Afficher infos sur le peripherique
   printf("\n");
   break;

 case 4:
   booleen=1; //Je met le booleen a 1, pour quitter la boucle, car 4.Quitter
   break;
}
}while(booleen==0);//Tant que mon int booleen est a 0, le menu va reboucler
 
 return 0;//Le methode ne retourne rien, 0
}



//Methode vider_buffer() que l'enseignant nous a offert
void vider_buffer() {
 int c;
 do {
 c = getchar();
 } while (c != '\n' && c != EOF);
}



//Methode pour afficher les informations sur la memoire, aucun parametre
void afficherMem(){
system("cat /proc/meminfo > meminfo.txt");

int detruire;//Le int pour detruire le fichier txt a la fin
int compteur=0;
FILE *fichier;
char ligne[512];//char ligne, où j'ai donne 512 pour la taille

        //Ouverture du fichier
	if((fichier = fopen("meminfo.txt", "r")) == NULL) {
	  return(-1);
	}
	
	//On veut chercher "Mem", pour trouver les informations sur la mémoire
	//J'utilise la fonction strstr pour chercher le mot "Mem",
	//si la ligne contient ce mot, je l'affiche.
	//Donc peu importe l'endroit où est la ligne, je peux l'afficher
	while(fgets(ligne, 512, fichier) != NULL) {
		if((strstr(ligne, "Mem")) != NULL) {
			printf("%s", ligne);
			compteur++;
		}
	}

	
	//Si jamais, dans le meminfo.txt, je ne trouve pas des infos sur la mémoire, j'affiche ce message.
	if(compteur == 0) {
		printf("\nDesole, aucune information sur la memoire n'a ete trouve.\n");
	}
	
	//Je ferme le fichier, s'il est toujours ouvert
	if(fichier) {
		fclose(fichier);
	}
	
	//Je detruit le fichier, tel que mentionne dans l'enonce
	detruire = remove("meminfo.txt");
   	return(0);
}



//Méthode pour afficher l'adresse IP, aucun parametre
void afficherIP(){
  
system(" ping -W 2 -c 4 8.8.8.8 > /dev/null 2>&1");
system("hostname -I > ip.txt");
 
int detruire;//int avec lequel je vais supprimer ip.txt a la fin
printf("\n");
printf("Cet ordinateur est connecte a Internet\n");
printf("Son adresse IP est:");
int c;

 
FILE *fichier;
//Ouverture du fichier,afin d'afficher l'adresse IP
fichier = fopen("ip.txt", "r");
if (fichier) {
    while ((c = getc(fichier)) != EOF)
      putchar(c);//J'utilise le putchar, une fonction que j'ai trouve en ligne
      fclose(fichier);//Je ferme le fichier
}

 
//Je supprime le fichier txt
detruire = remove("ip.txt");
printf("\n");
 
 return 0;//La methode ne retourne rien,0
}



//Methode pour afficher les informations sur le peripherique (carte graphique & carte reseau)
void afficherPeri() {
system("lspci > pci.txt");

int detruire;//Variable que j'utilise par la suite pour detruire le pci.txt
int compteur=0;
 
FILE *fichier;
  char ligne[512];//J'ai alloue une taille de 512, pour mon char ligne

  
  //Ouverture du fichier
	if((fichier = fopen("pci.txt", "r")) == NULL) {
	  return(-1);
	}
	
	//On veut chercher "VGA et Ethernet", pour trouver les informations que l'on veut sur le peripherique
	//"VGA" pour l'information sur la carte graphique, et "Ethernet" pour celle sur la carte reseau
	//J'utilise la fonction strstr pour chercher les 2 mots, si la ligne contient le mot, je l'affiche
	//Donc peu importe l'endroit où est la ligne, je peux l'afficher

	
	while(fgets(ligne, 512, fichier) != NULL) {
	  
	  //Je cherche l'information sur la carte graphique
		if((strstr(ligne, "VGA")) != NULL) {
			printf("%s", ligne);
			compteur++;
		}

		
	  //Je cherche l'information sur la carte reseau
		if((strstr(ligne, "Ethernet")) != NULL) {
			printf("%s", ligne);
			compteur++;
		}
		
	}

	
	//Si jamais, dans le pci.txt, je ne trouve pas des infos sur le peripherique, j'affiche ce message.
	if(compteur == 0) {
		printf("\nDesole, les informations sur le peripherique que vous vouliez, n'ont pas ete trouve.\n");
	}

	
	//Je ferme le fichier, s'il est toujours ouvert
	if(fichier) {
		fclose(fichier);
	}

	//Je detruit le fichier, tel que mentionne dans l'enonce
	detruire = remove("pci.txt");
	
   	return(0);//La methode ne retourne rien,0
}
