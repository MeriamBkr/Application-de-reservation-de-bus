#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
typedef struct BinarySearchTree BST;
struct BinarySearchTree
{
  int PassnNo;
  char name[10];
  struct BinarySearchTree *left;
  struct BinarySearchTree *right;
};
BST *root = NULL;
int coutTicket(BST *r);              // Permet de calculer les coûts
void status();                 // Permet d'afficher le statut des bus et des sièges
void ListeDesBus();               // Permet d'afficher le statut des bus avec les détails nécessaires tel que la ville de départ, l'horaire
void DisplaySeat(int bus[33]); 
void annulation(int x);            //Permet d'annuler une réservation
BST *reservationInfo(BST *, int, int *); // Permet d'afficher les informations d'une réservation
BST *insert(BST **r, int custID);

int busSeat[32][9] = {0};

void redColor()
{
  printf("\033[1;31m");
}

void resetColor()
{
  printf("\033[0m");
}

BST *reservationInfo(BST *r, int s, int *custIDmatched)
{
  if (r == NULL)
    return NULL;
  BST *presentnode = r;
  while (presentnode)
  {

    if (presentnode->PassnNo == s)
    {
      *custIDmatched = 1;
      printf("\n-----------------------------------------------------------------");
      printf("\n||              NOM: %10s                               ", (presentnode->name));
      printf("\n||              IDENTIFIENT CLIENT: %d                              ", presentnode->PassnNo);
      printf("\n||              NUMERO DE BUS: %d                                  ", (presentnode->PassnNo) / 1000);
      printf("\n||              NUMERO DE SIEGE: %d                                 ", (presentnode->PassnNo) % 100);
      printf("\n||              PRIX DU TICKET: %d                             ", coutTicket(presentnode));
      printf("\n-----------------------------------------------------------------");
      getch();
      return r;
    }
    else if (presentnode->PassnNo > s)
      presentnode = presentnode->left;
    else
      presentnode = presentnode->right;
  }

  return NULL;
}

BST *insert(BST **r, int custId)
{
  if (*r == NULL)
  {

    *r = (BST *)malloc(sizeof(BST));
    (*r)->PassnNo = custId;
    if (*r == NULL)
    {
      printf("No memory…");
      return NULL;
    }
    else
    {
      (*r)->left = (*r)->right = NULL;
      printf("\n   DONNER LE NOM DU CLIENT: ");
      scanf("%s", &((*r)->name));
    }
  }
  else
  {
    if ((*r)->PassnNo > custId)
    {
      (*r)->left = insert(&((*r)->left), custId);
    }
    else if ((*r)->PassnNo < custId)
    {
      (*r)->right = insert(&((*r)->right), custId);
    }
  }
  return *r;
}

void DisplaySeat(int bus[33])
{
	    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  for (int i = 1; i <= 32; i++)
  {
    if (i < 10 && i > 0)
    {
      printf("0%d ", i);
    }
    else
    {
      printf("%d ", i);
    }

    {
      if (bus[i] == 0){
	    // Changer la couleur du texte en vert
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf(":LIBRE");
        // Rétablir la couleur par défaut
    	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);}
      else{
	  	// Changer la couleur du texte en rouge
      	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf(":RESERVE");
        // Rétablir la couleur par défaut
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);}
    }
    printf("         ");
    if (i % 4 == 0)
      printf("\n");
  }
}

void login()
{
  char login[20] = "meriam";
  char motDePasse[10] = "meriam123";
  char memeLogin[10];
  char memeMotDePasse[10];
  int resultat;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
  printf("\n\n#########################################################################################\n");
  printf("\n\t\t\tBIENVENUE A LA RESERVATION EN LIGNE DE BUS");
  printf("\n\n#########################################################################################\n\n");
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
login:
{
  printf("\n\n   NOM UTILISATEUR: ");
  gets(memeLogin);

  printf("\n   MOT DE PASSE: ");
  gets(memeMotDePasse);
}

  resultat = strcmp(motDePasse, memeMotDePasse); /// Permet de comparer le mot de passe prédéfini avec celui introduit
  if (resultat != 0)
  {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("\n   DETAILS INVALIDES, VEUILLEZ REESSAYER!\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    goto login;
  }
  else
  {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("\n   VOUS ETES CONNECTE AVEC SUCCEES!\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  }
}

int coutTicket(BST *r)
{
  int cost, prixBus;
  prixBus = (r->PassnNo) / 1000;
  switch (prixBus % 3)
  {
  case 1:
    return 20;
    break;
  case 2:
    return 15;
    break;
  case 0:
    return 10;
    break;
  default:
    return 0;
    break;
  }
}

void status()
{
  int NumeroBus;
  ListeDesBus();
  busInput:
  printf("\n\n   DONNEZ LE NUMERO DU BUS: ");
  scanf("%d", &NumeroBus);
  if (NumeroBus <= 0 || NumeroBus >= 10)
  {
    redColor();
    printf("\n  SVP ENTREZ UN NUMERO DE BUS CORRECT!\n");
    resetColor();
    goto busInput;
  }
  printf("\n");
  DisplaySeat(busSeat[NumeroBus]);
  getch();
}

void ListeDesBus()
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  printf("--------------------------------------------------------------------------------------------------");
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
  printf("\nNUMERO DU BUS\tNOM DU BUS\t\t\tDESTINATION  \t\tPRIX  \t\tHORAIRE\n");
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  printf("--------------------------------------------------------------------------------------------------");
  printf("\n1\t\tTravel To Do        \t\tMater to Zaghouane      20 DT   \t08:10  AM");
  printf("\n2\t\tGO Voyage    \t\t\tTunis To Kaserine       15 DT    \t03:45  PM");
  printf("\n3\t\tTunis All Transport   \t\tMonastir-> Sousse\t10 DT    \t06:00  PM");
  printf("\n4\t\tHappy Bus        \t\tZaghouane -> Jendouba   20 DT    \t03:15  AM");
  printf("\n5\t\tTunisie Bus Minute    \t\tTunis -> Monastir \t15 DT    \t11:10  AM");
  printf("\n6\t\tBooking Bus     \t\tSousse -> Bizerte    \t10 DT    \t07:45  AM");
  printf("\n7\t\tYes To Travel       \t\tNefza -> Tabarka        20 DT   \t12:20  PM");
  printf("\n8\t\tBeautiful Bus      \t\tKairaouane -> Beja     \t15 DT    \t10:20  AM");
  printf("\n9\t\tBus In Bizerte       \t\tBizerte -> Tunis       \t10 DT    \t07:15  PM");
  printf("\n");
  printf("\n   CLIQUEZ SUR 'ENTER' POUR CONTINUER ");
  getch();
}

void annulation(int randomNum)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  int numReservation;
  int numSiege;
  int monChoix;
  char x;
  int SiegeAnnule;

aa:
{
  printf("\n   DONNEZ LE NUMERO DE VOTRE RESERVATION : ");
  scanf("%d", &numReservation);
  if (numReservation == randomNum)
  {
    printf("\n   EST CE QUE CE NUMERO DE RESERVATION EST CORRECT? %d \n   VEUILLEZ CHOISIR (O/N) : ", numReservation);
    scanf("%s", &x);
    if (x == 'o' || x == 'O')
    {
      printf("\n\n============================================\n\n");
      printf("   DONNEZ LE NUMERO DU BUS: ");
      scanf("%d", &monChoix);

      printf("\n   COMBIEN DE SIEGES VOULEZ VOUS ANNULER: ");
      scanf("%d", &SiegeAnnule);
      for (int i = 0; i < SiegeAnnule; i++)
      {
        printf("\n   DONNEZ LE NUMERO DU SIEGE: ");
        scanf("%d", &numSiege);
        busSeat[monChoix][numSiege] = 0;
      }
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
      printf("\n\n   VOTRE RESERVATION A ETE ANNULEE AVEC SUCCEES!\n\n");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
      printf("\n  CLIQUEZ SUR 'ENTER' POUR CONTINUER \n");
      getch();
      DisplaySeat(busSeat[monChoix]);
    }

    else if (x == 'n' || x == 'N')
    {
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
      printf("\n   ANNULATION DE VOTRE RESERVATION REFUSEE!\n");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
  }
  else
  {
  	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("\n   NUMERO NON TROUVE, VEUILLEZ SAISIR UN NUMERO DE RESERVATION CORRECT!\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    goto aa;
  }
}
}

void saveNodeToFile(BST *node, FILE *file) {
    if (node != NULL) {
        fprintf(file, "%d %s\n", node->PassnNo, node->name);
        saveNodeToFile(node->left, file);
        saveNodeToFile(node->right, file);
    }
}
void saveReservationsToFile(BST *r, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }
    saveNodeToFile(r, file);

    fclose(file);
}


int main()
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  srand(time(0));
  int randomNum = rand();
  int numero, i, custID, reservationNo;
  BST *root1;
  login();
main:
{
  do
  {
  	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("\t\t\tRESERVATION DE BUS\t\t");
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
    printf("\n====================");
    printf("      MENU PRINCIPAL      ");
    printf("=====================\n\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("   [1] VOIR LA LISTE DES BUS \n\n");
    printf("   [2] FAIRE UNE RESERVATION\n\n");
    printf("   [3] ANNULER UNE RESERVATION\n\n");
    printf("   [4] VOIR DETAILS DES SIEGES\n\n");
    printf("   [5] VOIR LES DETAILS DES RESERVATIONS\n\n");
    printf("   [6] QUITTER LE PROGRAMME\n");
    printf("\n=====================================================\n");
    printf("\n   ENTREZ VOTRE CHOIX: ");
    scanf("%d", &numero);
    switch (numero)
    {
    case 1:
      ListeDesBus(); // Permet d'afficher la liste des bus
      break;
    case 2:
      ListeDesBus(); // Permet d'afficher la liste des bus pour pouvoir choisir le bus désiré

      int IdClient, choixBus, nbSieges;

    busChoice:
      printf("\n\n   CHOISISSEZ VOTRE BUS: ");
      scanf("%d", &choixBus);
      if (choixBus <= 0 || choixBus > 9)
      {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n   VEUILLEZ ENTRER UN NUMERO VALIDE !! \n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        getch();
        goto busChoice;
      }
      printf("\n");
      DisplaySeat(busSeat[choixBus]);
    busSeatChoice:
      printf("\n\n   COMBIEN DE SIEGES VOULEZ VOUS RESERVER: ");
      scanf("%d", &nbSieges);
      if (nbSieges <= 0)
      {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n   VEUILLEZ ENTRER UN NOMBRE DE SIEGES VALIDE\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto busSeatChoice;
      }
      else if (nbSieges > 32)
      {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n   LA CAPACITE DES BUS EST 32. VEUILLEZ RESPECTER CETTE LIMITE!\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto busSeatChoice;
      }
      int numSiege;
      for (int i = 1; i <= nbSieges; i++)
      {
        printf("\n\n==================================================================================\n\n");
      seat:
        printf("   DONNEZ LE NUMERO DU SIEGE: ");
        scanf("%d", &numSiege);
        if (numSiege <= 0)
        {
          SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
          printf("\n   VEUILLEZ ENTRER UN NUMERO DE SIEGE VALIDE!\n\n");
          SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          goto seat;
        }
        else if (numSiege > 32)
        {
          SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
          printf("\n   IL Y A QUE 32 SIEGES! VEUILLEZ ENTRER UN NUMERO DE SIEGE QUI RESPECTE CETTE LIMITE!\n\n");
          SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          goto seat;
        }
        IdClient = choixBus * 1000 + numSiege; // Ceci va générer l'identifiant du client
        busSeat[choixBus][numSiege] = 1;
        root = insert(&root, IdClient);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        printf("\n   VOTRE IDENTIFIANT CLIENT EST: %d", IdClient);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n\n==================================================================================\n\n");
      }
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
      printf("\n   VOTRE NUMERO DE RESERVATION EST: ");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
      printf("%d\n", randomNum);
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
      printf("\n   VEUILLEZ CONSERVEZ VOTRE NUMERO DE RESERVATION EN CAS D'ANNULATION DE CETTE DERNIERE!\n");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
      printf("   CLIQUEZ SUR 'ENTER' POUR CONTINUER \n");
      getch();
      
      saveReservationsToFile(root, "reservations.txt");
      break;

    case 3:
      annulation(randomNum);
      break;
    case 4:
      status();
      break;
    case 5:
    takingReservationNo:
      printf("\n   DONNER VOTRE NUMERO DE RESERVATION :");
      scanf("%d", &reservationNo);

      if (randomNum == reservationNo)
      {
      cust:
        printf("\n   VEUILLEZ ENTRER VOTRE IDENTIFIANT CLIENT:");
        scanf("%d", &custID);
        int custIDmatched = 0;
        root1 = reservationInfo(root, custID, &custIDmatched);
        if (custIDmatched == 0)
        {
          SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
          printf("\n   VEUILLEZ ENTRER UN IDENTIFIANT CLIENT VALIDE!\n");
          SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
          goto cust;
        }
      }
      else
      {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n   NUMERO DE RESERVATION INVALIDE! VEUILLEZ RESSAYER!\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto takingReservationNo;
      }
      break;
    default:
    
      break; 
    }
  } while (numero != 6);
  printf("\n\n=====================================================================\n\n");
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
  printf("   MERCI D'AVOIR CHOISI NOTRE APPLICATION POUR RESERVER VOTRE PROCHAIN VOYAGE");
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  printf("\n\n   CLIQUEZ SUR ENTRER POUR QUITTER LE PROGRAMME! \n");
  printf("\n\n");
  getch();
  return 0;
}
}
