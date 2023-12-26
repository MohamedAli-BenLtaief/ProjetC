#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Date {
    int j,m,a;
};

struct Noms {
    char Nom[50];
    struct Noms* next;
};

struct Transaction {
    char IdCompteT[8],IdCompteR[8],IdTrans[16];
    struct Date DateTrans;
    float Somme;
};

struct Compte {
    char NomClient[50];
    char IdCompte[8];
    char Mdp[20];
    char TypeCompte;
    struct Date DateCreation;
    float Solde;
};

//Enfiler la structure Noms
void Enqueue(struct Noms* h, char Nom[]) {
    struct Noms* temp = (struct Noms*)malloc(sizeof(struct Noms));
    strcpy(temp->Nom, Nom);
    temp->next = NULL;
    if (h->next == NULL) {
        h->next = temp;
        return;
    }
    struct Noms* current = h->next;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
}

// Défiler la structure Noms
void Dequeue(struct Noms* h) {
    if (h->next == NULL) {
        printf("La file est vide.\n");
        return;
    }
    struct Noms* temp = h->next;
    printf("%s\n", temp->Nom);
    h->next = temp->next;
    free(temp);
}

//Cryptage et Décryptage des Mots de passes avec une opération XOR
void Crypt(char Mdp[20]) {
    char cle = 'X';
    int len = strlen(Mdp);
    for (int i = 0; i < len; i++) {
        Mdp[i] = Mdp[i] ^ cle;
    }
}

//Créer un nouveau compte.
void Append(struct Compte C) {
    FILE *fp = fopen("AccountData.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Nom du Client: %.50s\n", C.NomClient);
        fprintf(fp, "Identifiant du Compte: %.8s\n", C.IdCompte);
        fprintf(fp, "Mot de passe: %.20s\n", C.Mdp);
        fprintf(fp, "Type de Compte(Epargne/Courant): %c\n", C.TypeCompte);
        fprintf(fp, "Date de Creation: %d-%d-%d\n", C.DateCreation.j, C.DateCreation.m, C.DateCreation.a);
        fprintf(fp, "Solde: %.2f\n\n", C.Solde);
        fclose(fp);
        printf("Compte ajoute avec succes.\n");
    }
    else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Ajouter une nouvelle transaction.
void AppendTrans(struct Transaction T) {
    FILE *fp = fopen("TransactionData.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Identifiant de Transaction: %s\n", T.IdTrans);
        fprintf(fp, "Identifiant d'expediteur: %s\n", T.IdCompteT);
        fprintf(fp, "Identifiant de destinataire: %s\n", T.IdCompteR);
        fprintf(fp, "Date de Transaction: %d-%d-%d\n", T.DateTrans.j, T.DateTrans.m, T.DateTrans.a);
        fprintf(fp, "Somme: %.2f\n\n", T.Somme);
        fclose(fp);
        printf("Transaction effectue avec succes.\n");
    }
    else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Mise à jour des informations d’un compte existant.
void Update(char id[], struct Compte NvC) {
    FILE *fp = fopen("AccountData.txt", "r");
    if (fp != NULL) {
        FILE *tp = fopen("temp.txt", "w");
        if (tp != NULL) {
            struct Compte C;
            int verif = 0;
            while (fscanf(fp, "Nom du Client: %s\n", C.NomClient) == 1) {
                fscanf(fp, "Identifiant du Compte: %s\n", C.IdCompte);
                fscanf(fp, "Mot de passe: %s\n", C.Mdp);
                fscanf(fp, "Type de Compte: %c\n", &C.TypeCompte);
                fscanf(fp, "Date de Creation: %d-%d-%d\n", &C.DateCreation.j, &C.DateCreation.m, &C.DateCreation.a);
                fscanf(fp, "Solde: %f\n\n", &C.Solde);
                if (strcmp(C.IdCompte, id) == 0) {
                    fprintf(tp, "Nom du Client: %s\n", NvC.NomClient);
                    fprintf(tp, "Identifiant du Compte: %s\n", NvC.IdCompte);
                    fprintf(tp, "Mot de passe: %s\n", NvC.Mdp);
                    fprintf(tp, "Type de Compte: %c\n", NvC.TypeCompte);
                    fprintf(tp, "Date de Creation: %d-%d-%d\n", NvC.DateCreation.j, NvC.DateCreation.m, NvC.DateCreation.a);
                    fprintf(tp, "Solde: %.2f\n\n", NvC.Solde);
                    verif = 1;
                }
                else {
                    fprintf(tp, "Nom du Client: %s\n", C.NomClient);
                    fprintf(tp, "Identifiant du Compte: %s\n", C.IdCompte);
                    fprintf(tp, "Mot de passe: %s\n", C.Mdp);
                    fprintf(tp, "Type de Compte: %c\n", C.TypeCompte);
                    fprintf(tp, "Date de Creation: %d-%d-%d\n", C.DateCreation.j, C.DateCreation.m, C.DateCreation.a);
                    fprintf(tp, "Solde: %.2f\n\n", C.Solde);
                }
            }
            fclose(tp);
            fclose(fp);
            remove("AccountData.txt");
            rename("temp.txt", "AccountData.txt");
            if (verif) {
                printf("Compte mis a jour avec succes.\n");
            }
            else {
                printf("Compte non existant.\n");
            }
        }
        else {
            printf("Erreur lors de la creation du fichier temporaire.\n");
            fclose(fp);
        }
    }
    else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Afficher les détails d’un compte existant.
void DisplayClient(char id[]) {
    FILE *fp = fopen("AccountData.txt", "r");
    if (fp != NULL) {
        struct Compte C;
        int verif=0;
        while (fscanf(fp, "Nom du Client: %50s\n", C.NomClient) == 1) {
            fscanf(fp, "Identifiant du Compte: %8s\n", C.IdCompte);
            fscanf(fp, "Mot de passe: %20s\n", C.Mdp);
            fscanf(fp, "Type de Compte: %c\n", &C.TypeCompte);
            fscanf(fp, "Date de Creation: %d-%d-%d\n", &C.DateCreation.j, &C.DateCreation.m, &C.DateCreation.a);
            fscanf(fp, "Solde: %f\n\n", &C.Solde);
            if (strcmp(C.IdCompte, id) == 0) {
                printf("Nom du Client: %50s\n", C.NomClient);
                printf("Identifiant du Compte: %8s\n", C.IdCompte);
                printf("Mot de passe: %8s\n", C.Mdp);
                printf("Type de Compte: %c\n", C.TypeCompte);
                printf("Date de Creation: %d-%d-%d\n", C.DateCreation.j, C.DateCreation.m, C.DateCreation.a);
                printf("Solde: %.2f\n\n", C.Solde);
                verif=1;
                break;
            }
        }
        fclose(fp);
        if (!verif) {
            printf("Compte non existant.\n");
        }
    }
    else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Supprimer un compte existant.
void Delete(char id[]) {
    FILE *fp = fopen("AccountData.txt", "r");
    if (fp != NULL) {
        FILE *tp = fopen("temp.txt", "w");
        if (tp != NULL) {
            struct Compte C;
            int verif = 0;
            while (fscanf(fp, "Nom du Client: %s\n", C.NomClient) == 1) {
                fscanf(fp, "Identifiant du Compte: %s\n", C.IdCompte);
                fscanf(fp, "Mot de passe: %s\n", C.Mdp);
                fscanf(fp, "Type de Compte: %c\n", &C.TypeCompte);
                fscanf(fp, "Date de Creation: %d-%d-%d\n", &C.DateCreation.j, &C.DateCreation.m, &C.DateCreation.a);
                fscanf(fp, "Solde: %f\n\n", &C.Solde);
                if (strcmp(C.IdCompte, id) == 0) {
                    verif = 1;
                    continue;
                }
                fprintf(tp, "Nom du Client: %s\n", C.NomClient);
                fprintf(tp, "Identifiant du Compte: %s\n", C.IdCompte);
                fprintf(tp, "Mot de passe: %s\n", C.Mdp);
                fprintf(tp, "Type de Compte: %c\n", C.TypeCompte);
                fprintf(tp, "Date de Creation: %d-%d-%d\n", C.DateCreation.j, C.DateCreation.m, C.DateCreation.a);
                fprintf(tp, "Solde: %.2f\n\n", C.Solde);
            }
            fclose(tp);
            fclose(fp);
            remove("AccountData.txt");
            rename("temp.txt", "AccountData.txt");
            if (verif) {
                printf("Compte supprimé avec succès.\n");
            }
            else {
                printf("Compte non existant.\n");
            }
        }
        else {
            printf("Erreur lors de la création du fichier temporaire.\n");
            fclose(fp);
        }
    }
    else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Afficher la liste des clients.
void DisplayNames() {
    FILE *fp = fopen("AccountData.txt", "r");
    if (fp != NULL) {
        struct Compte C;
        struct Noms* h = (struct Noms*)malloc(sizeof(struct Noms));
        h->next = NULL;
        while (fscanf(fp, "Nom du Client: %s\n", C.NomClient) == 1) {
            Enqueue(h, C.NomClient);
            fscanf(fp, "Identifiant du Compte: %s\n", C.IdCompte);
            fscanf(fp, "Mot de passe: %s\n", C.Mdp);
            fscanf(fp, "Type de Compte: %c\n", &C.TypeCompte);
            fscanf(fp, "Date de Creation: %d-%d-%d\n", &C.DateCreation.j, &C.DateCreation.m, &C.DateCreation.a);
            fscanf(fp, "Solde: %f\n\n", &C.Solde);
        }
        fclose(fp);
        while (h->next != NULL) {
            Dequeue(h);
        }
        free(h);
    } else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Gérer les transactions bancaires.
void Transfer(struct Transaction T) {
    FILE *fp = fopen("AccountData.txt", "r+");
    if (fp != NULL) {
        struct Compte CT,CR;
        int verif = 0;
        while (fscanf(fp, "Nom du Client: %s\n", CT.NomClient) == 1) {
            fscanf(fp, "Identifiant du Compte: %s\n", CT.IdCompte);
            fscanf(fp, "Mot de passe: %s\n", CT.Mdp);
            fscanf(fp, "Type de Compte: %c\n", &CT.TypeCompte);
            fscanf(fp, "Date de Creation: %d-%d-%d\n", &CT.DateCreation.j, &CT.DateCreation.m, &CT.DateCreation.a);
            fscanf(fp, "Solde: %f\n\n", &CT.Solde);
            if (strcmp(CT.IdCompte, T.IdCompteT) == 0) {
                verif = 1;
                break;
            }
        }
        fclose(fp);
        if (verif) {
            if (CT.Solde >= T.Somme) {
                verif = 0;
                fp = fopen("AccountData.txt", "r+");
                while (fscanf(fp, "Nom du Client: %s\n", CR.NomClient) == 1) {
                    fscanf(fp, "Identifiant du Compte: %s\n", CR.IdCompte);
                    fscanf(fp, "Mot de passe: %s\n", CR.Mdp);
                    fscanf(fp, "Type de Compte: %c\n", &CR.TypeCompte);
                    fscanf(fp, "Date de Creation: %d-%d-%d\n", &CR.DateCreation.j, &CR.DateCreation.m, &CR.DateCreation.a);
                    fscanf(fp, "Solde: %f\n\n", &CR.Solde);
                    if (strcmp(CR.IdCompte, T.IdCompteR) == 0) {
                        verif = 1;
                        break;
                    }
                }
                fclose(fp);
                if (verif){
                    CT.Solde = CT.Solde - T.Somme;
                    CR.Solde = CR.Solde + T.Somme;
                    Update(T.IdCompteT,CT);
                    Update(T.IdCompteR,CR);
                    AppendTrans(T);
                }
            }
            else {
                printf("Transaction invalide.\n");
            }
        }
        else {
            printf("Compte non existant.\n");
        }
    }
    else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Afficher la liste des Transactions
void DisplayTrans() {
    FILE *fp = fopen("TransactionData.txt", "r");
    if (fp != NULL) {
        struct Transaction T;
        while (fscanf(fp, "Identifiant de Transaction: %s\n", T.IdTrans) == 1) {
            fscanf(fp, "Identifiant d'expediteur: %s\n", T.IdCompteT);
            fscanf(fp, "Identifiant de destinataire: %s\n", T.IdCompteR);
            fscanf(fp, "Date de Transaction: %d-%d-%d\n", &T.DateTrans.j, &T.DateTrans.m, &T.DateTrans.a);
            fscanf(fp, "Somme: %f\n\n", &T.Somme);
            printf("Identifiant de Transaction: %s\n", T.IdTrans);
            printf("Identifiant d'expediteur: %s\n", T.IdCompteT);
            printf("Identifiant de destinataire: %s\n", T.IdCompteR);
            printf("Date de Transaction: %d-%d-%d\n", T.DateTrans.j, T.DateTrans.m, T.DateTrans.a);
            printf("Somme: %.2f\n\n", T.Somme);
        }
        fclose(fp);
    } else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}

//Afficher toutes les transactions associées à un compte spécifique
void DisplayClientTrans(char IdCompte[]) {
    FILE *fp = fopen("TransactionData.txt", "r");
    if (fp != NULL) {
        struct Transaction T;
        int verif = 0;
        while (fscanf(fp, "Identifiant de Transaction: %s\n", T.IdTrans) == 1) {
            fscanf(fp, "Identifiant d'expediteur: %s\n", T.IdCompteT);
            fscanf(fp, "Identifiant de destinataire: %s\n", T.IdCompteR);
            fscanf(fp, "Date de Transaction: %d-%d-%d\n", &T.DateTrans.j, &T.DateTrans.m, &T.DateTrans.a);
            fscanf(fp, "Somme: %f\n\n", &T.Somme);
            if (strcmp(T.IdCompteT, IdCompte) == 0 || strcmp(T.IdCompteR, IdCompte) == 0) {
                verif = 1;
                printf("Identifiant de Transaction: %s\n", T.IdTrans);
                printf("Identifiant d'expediteur: %s\n", T.IdCompteT);
                printf("Identifiant de destinataire: %s\n", T.IdCompteR);
                printf("Date de Transaction: %d-%d-%d\n", T.DateTrans.j, T.DateTrans.m, T.DateTrans.a);
                printf("Somme: %.2f\n\n", T.Somme);
            }
        }
        fclose(fp);
        if (!verif) {
            printf("Pas de transactions trouvees pour cette Id : %s.\n", IdCompte);
        }
    } else {
        printf("Erreur d'ouverture du fichier.\n");
    }
}


//Programme Principal
int main() {
    int choix;
    char IdCompte[8];
    struct Compte C;
    struct Transaction T;
    int sortie = 0;
    while (!sortie) {
        printf("**************************************************\n");
        printf("                      E-BANK                      \n");
        printf("**************************************************\n");
        printf("\n1. Creer un compte\n");
        printf("2. Afficher les details d'un compte\n");
        printf("3. Afficher toutes les transactions d'un compte\n");
        printf("4. Mettre a jour les informations du compte\n");
        printf("5. Supprimer un compte\n");
        printf("6. Effectuer une transaction\n");
        printf("7. Voir la liste des clients\n");
        printf("8. Voir la liste des transactions\n");
        printf("9. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf("Entrez le nom du client : ");
                scanf("%s", C.NomClient);
                printf("Entrez l'identifiant du compte : ");
                scanf("%s", C.IdCompte);
                printf("Entrez le mot de passe : ");
                scanf("%s", C.Mdp);
                Crypt(C.Mdp);
                printf("Entrez le type de compte (E pour Epargne, C pour Courant) : ");
                scanf(" %c", &C.TypeCompte);
                printf("Entrez la date de creation (jj mm aaaa) : ");
                scanf("%d %d %d", &C.DateCreation.j, &C.DateCreation.m, &C.DateCreation.a);
                printf("Entrez le solde : ");
                scanf("%f", &C.Solde);
                Append(C);
                break;
            case 2:
                printf("Entrez l'identifiant du compte : ");
                scanf("%8s", IdCompte);
                DisplayClient(IdCompte);
                break;
            case 3:
                printf("Entrez l'identifiant du compte : ");
                scanf("%8s", IdCompte);
                DisplayClientTrans(IdCompte);
                break;
            case 4:
                printf("Entrez l'identifiant du compte a mettre à jour : ");
                scanf("%8s", IdCompte);
                printf("Entrez le nom du client : ");
                scanf("%s", C.NomClient);
                printf("Entrez le identifiant du compte : ");
                scanf("%s", C.IdCompte);
                printf("Entrez le mot de passe : ");
                scanf("%s", C.Mdp);
                Crypt(C.Mdp);
                printf("Entrez le type de compte (E pour Epargne, C pour Courant) : ");
                scanf(" %c", &C.TypeCompte);
                printf("Entrez la date de creation (jj mm aaaa) : ");
                scanf("%d %d %d", &C.DateCreation.j, &C.DateCreation.m, &C.DateCreation.a);
                printf("Entrez le solde : ");
                scanf("%f", &C.Solde);
                Update(IdCompte,C);
                break;
            case 5:
                printf("Entrez l'identifiant du compte à supprimer : ");
                scanf("%8s", IdCompte);
                Delete(IdCompte);
                break;
            case 6:
                printf("Entrez l'identifiant du compte expediteur : ");
                scanf("%8s", T.IdCompteT);
                printf("Entrez l'identifiant du compte destinataire : ");
                scanf("%8s", T.IdCompteR);
                printf("Entrez l'identifiant de la transaction : ");
                scanf("%16s", T.IdTrans);
                printf("Entrez la date de la transaction (jj mm aaaa) : ");
                scanf("%d %d %d", &T.DateTrans.j, &T.DateTrans.m, &T.DateTrans.a);
                printf("Entrez le montant de la transaction : ");
                scanf("%f", &T.Somme);
                Transfer(T);
                break;
            case 7:
                DisplayNames();
                break;
            case 8:
                DisplayTrans();
                break;
            case 9:
                printf("Fermeture...\n");
                sortie = 1;
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
    return 0;
}
