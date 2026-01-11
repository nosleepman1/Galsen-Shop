# MANGUI DIEGEULOU SHOP - Système de Gestion des Ventes

## 📋 Description

Application de gestion des ventes et du stock pour une boutique d'habillement, développée en C++ avec une architecture modulaire.

## 🏗️ Architecture du Projet

### Structure des Fichiers

```
projet/
├── main.cpp              # Point d'entrée de l'application
├── Utils.hpp/cpp         # Utilitaires généraux (cryptage, validation, timestamps)
├── Category.hpp/cpp      # Gestion des catégories
├── Product.hpp/cpp       # Gestion des produits
├── User.hpp/cpp          # Gestion des utilisateurs
├── Sale.hpp/cpp          # Gestion des ventes
├── Menu.hpp/cpp          # Interface utilisateur et menus
├── Makefile              # Compilation automatique
└── README.md             # Documentation
```

### Fichiers de Données

- **USERS** : Fichier binaire contenant les utilisateurs (mots de passe cryptés)
- **CATEGORIES** : Fichier binaire des catégories
- **PRODUCTS** : Fichier binaire des produits
- **BILLS/** : Dossier contenant les factures au format texte
- **ETAT_AAAAMMDD.txt** : Rapports journaliers des ventes

## 🔧 Compilation et Exécution

### Prérequis
- Compilateur C++ supportant C++11 (g++, clang++)
- Make (optionnel mais recommandé)

### Compilation

**Avec Make :**
```bash
make
```

**Sans Make :**
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o mangui_shop main.cpp Utils.cpp Category.cpp Product.cpp User.cpp Sale.cpp Menu.cpp
```

### Exécution

```bash
./mangui_shop
```

ou

```bash
make run
```

### Commandes Make

- `make` : Compile le projet
- `make clean` : Supprime les fichiers compilés et les données
- `make rebuild` : Recompile tout le projet
- `make run` : Compile et exécute
- `make help` : Affiche l'aide

## 👥 Connexion par Défaut

**Administrateur :**
- Login : `ADMIN`
- Mot de passe : `admin123`

**Nouveaux utilisateurs :**
- Mot de passe par défaut : `passer123`
- Changement obligatoire à la première connexion

## 🎯 Fonctionnalités

### Pour les Administrateurs

1. **Gestion des Utilisateurs**
   - Ajouter un utilisateur
   - Lister les utilisateurs
   - Bloquer/Débloquer un utilisateur

2. **Gestion des Catégories**
   - Ajouter une catégorie
   - Lister les catégories

3. **Gestion des Produits**
   - Ajouter un produit
   - Modifier un produit
   - Supprimer un produit
   - Lister les produits
   - Mettre à jour le stock

4. **Ventes**
   - Effectuer une vente
   - Imprimer l'état journalier

### Pour les Utilisateurs

1. **Ventes**
   - Effectuer une vente
   - Imprimer l'état journalier

2. **Consultation**
   - Liste des produits
   - Liste des catégories

## 📝 Règles de Gestion

### Utilisateurs
- Login : 5 caractères alphabétiques majuscules (ex: ADMIN, USER1)
- Mot de passe : crypté dans le fichier USERS
- Changement de mot de passe obligatoire à la première connexion
- Possibilité de blocage par un administrateur

### Catégories
- ID auto-incrémenté
- Libellé unique

### Produits
- Code : 5 caractères (ex: PR001, SHIRT)
- Doit appartenir à une catégorie existante
- Stock mis à jour automatiquement après chaque vente
- Date d'ajout automatique (date système)

### Ventes
- Numéro au format : AAAAMMDDHHMMSS
- Facture générée automatiquement : `RECU_AAAAMMDDHHMMSS_ID_LOGIN.txt`
- Vérification du stock disponible
- Proposition de prendre le stock restant si quantité insuffisante
- Blocage si produit en rupture de stock

## 🔒 Sécurité

- Cryptage des mots de passe avec algorithme personnalisé
- Authentification requise pour toutes les opérations
- Gestion des droits par rôle (Admin/Utilisateur)
- Blocage de compte possible

## 📊 Format des Fichiers

### Facture (RECU)
```
========================================
   MANGUI DIEGEULOU SHOP
========================================
Date: DD/MM/YYYY HH:MM:SS
Numero: AAAAMMDDHHMMSS
Vendeur: Prénom Nom
========================================

Produit         Qte       P.U.      Total
----------------------------------------
Article1        2         1000      2000
Article2        1         1500      1500
----------------------------------------
TOTAL: 3500 FCFA
========================================
       Merci de votre visite!
========================================
```

### Rapport Journalier (ETAT)
```
========================================
   ETAT DES VENTES DU AAAAMMDD
========================================

Nombre total d'articles vendus: X
Montant total des ventes: XXXX FCFA
========================================
```

## 🛠️ Modules et Extensibilité

Le projet est conçu pour être facilement extensible :

1. **Utils** : Ajouter de nouvelles fonctions utilitaires
2. **Category** : Étendre les fonctionnalités des catégories
3. **Product** : Ajouter des attributs aux produits
4. **User** : Créer de nouveaux rôles
5. **Sale** : Implémenter des méthodes de paiement
6. **Menu** : Ajouter de nouvelles fonctionnalités

## 📌 Conventions de Nommage

- **Classes** : PascalCase (ex: `ProductManager`)
- **Fonctions** : camelCase (ex: `findByCode`)
- **Variables** : camelCase (ex: `currentUser`)
- **Constantes** : UPPER_CASE (ex: `FILENAME`)
- **Fichiers** : PascalCase pour les classes (ex: `Product.hpp`)

## 🐛 Gestion des Erreurs

- Vérification de l'existence des fichiers
- Validation des entrées utilisateur
- Messages d'erreur explicites
- Gestion des cas limites (stock insuffisant, utilisateur bloqué, etc.)

## 📈 Améliorations Possibles

1. Base de données relationnelle (SQLite, MySQL)
2. Interface graphique (Qt, GTK+)
3. Statistiques avancées
4. Gestion des retours/remboursements
5. Système de fidélité client
6. Export Excel/PDF des rapports
7. Backup automatique des données
8. Logs d'activité

## 👨‍💻 Auteur

Projet développé pour MANGUI DIEGEULOU SHOP - ISI DAKAR L1GL

## 📄 Licence

Projet académique - Tous droits réservés