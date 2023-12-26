E-BANK - Système de Gestion Bancaire Ce programme, E-BANK, est un
système simple de gestion bancaire implémenté en C. Il permet aux
utilisateurs d\'effectuer diverses opérations telles que la création de
comptes, la gestion des transactions, la mise à jour des informations
des comptes, etc.

Fonctionnalités

\-\--Gestion des Comptes

Créer un Compte : Ajouter de nouveaux comptes avec les détails du
client, l'identifiant du compte, le mot de passe, le type de compte, la
date de création et le solde initial.

Afficher les Détails d'un Compte : Consulter les détails d'un compte
spécifique en fournissant l'identifiant du compte.

Mettre à Jour les Informations du Compte : Modifier les détails d'un
compte existant tels que le nom du client, l'identifiant, le mot de
passe, le type de compte, la date de création ou le solde.

Supprimer un Compte : Supprimer un compte existant en fournissant
l'identifiant du compte.

Liste des Clients : Afficher une liste de tous les noms de clients.

\-\--Gestion des Transactions

Effectuer des Transactions : Transférer des fonds entre les comptes en
spécifiant les identifiants de l'expéditeur et du destinataire,
l'identifiant de la transaction, la date de la transaction et le
montant.

Afficher les Transactions : Visualiser toutes les transactions
enregistrées.

Historique des Transactions Client : Afficher l'historique des
transactions pour un identifiant de compte spécifique.

Structure des Fichiers

ebank.c : Contient le code source du système de gestion bancaire.

AccountData.txt : Stocke les informations relatives aux comptes.

TransactionData.txt : Stocke les informations relatives aux
transactions.

temp.txt : Fichier temporaire utilisé pour les opérations sur les
fichiers.

Comment Utiliser

Compilation : Compiler le fichier ebank.c en utilisant un
compilateur C.

Exécution : Lancer le fichier compilé.

Interaction : Suivre les instructions fournies dans le terminal pour
naviguer dans le menu du programme et effectuer les opérations
souhaitées.
