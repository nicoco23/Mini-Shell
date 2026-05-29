# Roadmap Minishell — 2 personnes

## Vue d'ensemble de la séparation des rôles

| Personne A | Personne B |
|---|---|
| Parsing / Lexer / Expansion | Exécution / Builtins / Redirections / Pipes |

La séparation se fait autour d'une **interface commune** : le parser produit une structure
de données que l'executor consomme. Cette interface doit être définie ensemble en Phase 1
avant que chacun parte de son côté.

---

## Phase 1 — Infrastructure commune (1-2 jours)

*À faire ensemble avant de se séparer. Tout le reste dépend de cette phase.*

### 1.1 — Structure du projet
Organiser les dossiers dès le départ pour éviter de tout réorganiser plus tard.
Un découpage raisonnable : un dossier par grande responsabilité (parsing, execution,
builtins, utils), un dossier `include/` pour tous les headers, `libft/` pour la librairie.

### 1.2 — Makefile
Écrire le Makefile complet dès le début avec toutes les règles obligatoires.
Penser à compiler la libft depuis son propre Makefile avant de compiler le projet.
Vérifier que le Makefile ne relink pas inutilement (règle basée sur les `.o`).

### 1.3 — Structures de données partagées

C'est **la décision la plus importante de la Phase 1**. Les deux personnes doivent
se mettre d'accord sur exactement ce que contient chaque structure avant de coder quoi
que ce soit. Un désaccord ici coûte cher plus tard.

Ce qu'il faut modéliser :

- **Le token** : unité minimale produite par le lexer. Il doit savoir quel type il est
  (mot, pipe, redirection, etc.) et stocker sa valeur brute.

- **La redirection** : associée à une commande, elle doit savoir son type (`<`, `>`,
  `<<`, `>>`) et sa cible (fichier ou délimiteur pour le heredoc).

- **La commande** : unité d'exécution. Elle contient le nom de la commande, la liste
  de ses arguments, et la liste de ses redirections.

- **La liste chaînée de commandes** : une commande par segment de pipe. Chaque commande
  pointe vers la suivante dans le pipeline.

- **L'environnement** : copie de `envp` stockée en interne sous forme de liste ou tableau
  de chaînes. Jamais accéder directement à `envp` après initialisation — travailler
  toujours sur la copie.

### 1.4 — Boucle principale (REPL)

Le coeur du shell : afficher le prompt, lire une ligne, la traiter, recommencer.
`readline` gère l'affichage du prompt et la saisie. `add_history` ajoute chaque ligne
valide à l'historique (pas les lignes vides). La boucle tourne jusqu'à `ctrl-D` ou
la commande `exit`.

### 1.5 — Variable globale pour les signaux

Une seule variable globale est autorisée dans tout le projet, et elle ne sert qu'à
stocker le numéro du dernier signal reçu. Aucune structure, aucun pointeur en global.
La définir ici et ne plus y toucher structurellement.

---

## Phase 2 — Parsing (Personne A)

L'objectif est de transformer une chaîne de caractères brute en une structure de données
propre, prête à être exécutée. Le parser ne sait rien de l'exécution — il produit,
l'executor consomme.

### Étape 2.1 — Lexer / Tokenizer

Le lexer lit la ligne caractère par caractère et produit une liste de tokens.

**Ce qu'il doit reconnaître :**
- Les mots (suite de caractères sans signification spéciale)
- Le pipe `|`
- Les redirections `<`, `>`, `<<`, `>>`
- Les quotes simples et doubles (voir ci-dessous)
- Les espaces comme séparateurs (mais pas dans les quotes)

**Gestion des quotes :**

Les quotes changent complètement l'interprétation de ce qui suit. Le lexer doit
maintenir un état pour savoir s'il est à l'intérieur d'une quote simple, double, ou
aucune.

- **Quote simple `'...'`** : tout ce qui est entre les guillemets est traité comme du
  texte littéral. Aucun caractère n'a de signification spéciale, même pas `$`.
- **Quote double `"..."`** : presque tout est littéral, sauf `$` qui déclenche
  l'expansion de variable.
- **Quote non fermée** : si la ligne se termine sans fermer une quote ouverte, c'est une
  erreur de syntaxe. Afficher un message et ne pas exécuter la commande.

**Ce que le lexer ne fait pas :**
Il ne fait pas d'expansion — il marque seulement les tokens. L'expansion vient après.

### Étape 2.2 — Expansion

L'expansion se fait sur les tokens après le lexing, avant la construction des commandes.

**Expansion de variables `$VAR` :**
- Chercher dans l'environnement interne la variable dont le nom suit le `$`.
- Si la variable n'existe pas, remplacer par une chaîne vide.
- Ne pas expanser à l'intérieur des quotes simples.
- Expanser à l'intérieur des quotes doubles.
- Bien délimiter la fin du nom de variable (s'arrêter au premier caractère non
  alphanumérique ou `_`).

**Expansion de `$?` :**
- Cas spécial : `$?` se remplace par le code de retour de la dernière commande exécutée.
- Cette valeur est maintenue par l'executor et doit être accessible au parser au moment
  de l'expansion. Prévoir comment les deux parties se la transmettent.

**Ordre important :** l'expansion se fait après le lexing mais avant que les commandes
soient construites, pour que les arguments finaux soient déjà expansés.

### Étape 2.3 — Construction des commandes

Une fois les tokens expansés, construire la liste de commandes.

**Séparation par les pipes :**
Chaque `|` délimite deux commandes. Parcourir la liste de tokens et créer une nouvelle
commande à chaque fois qu'un pipe est rencontré.

**Arguments :**
Tous les tokens de type "mot" qui ne sont pas des cibles de redirection deviennent des
arguments de la commande courante. Le premier est le nom de la commande.

**Redirections :**
Un token de redirection (`<`, `>`, etc.) est toujours immédiatement suivi d'un token
"mot" qui est sa cible. Les associer à la commande courante, pas à ses arguments.

**Validation syntaxique :**
Détecter et signaler les erreurs : pipe en début ou fin de ligne, redirection sans
cible, etc.

---

## Phase 3 — Exécution (Personne B)

L'executor reçoit la liste de commandes construite par le parser et les exécute.
Il ne sait rien du parsing.

### Étape 3.1 — Exécution d'une commande simple

Avant d'attaquer les pipes, maîtriser l'exécution d'une seule commande.

**Recherche de l'exécutable :**
- Si le nom contient un `/`, c'est un chemin direct (relatif ou absolu). Vérifier son
  existence et ses permissions avec `access`, puis l'exécuter.
- Sinon, parcourir chaque répertoire listé dans la variable `PATH` et chercher un
  fichier exécutable du bon nom. Prendre le premier trouvé.
- Si rien n'est trouvé : afficher une erreur `command not found`.

**Fork et exec :**
- Créer un processus enfant avec `fork`.
- Dans l'enfant : remplacer le processus par l'exécutable avec `execve`. Si `execve`
  échoue, afficher une erreur et quitter l'enfant.
- Dans le parent : attendre la fin de l'enfant avec `waitpid` et récupérer son code
  de retour pour mettre à jour `$?`.

**Cas des builtins :**
Les builtins ne passent jamais par `fork` + `execve` car ils doivent modifier l'état
du shell lui-même (ex : `cd` change le répertoire courant du shell, pas d'un enfant).
Détecter si la commande est un builtin avant de forker.

### Étape 3.2 — Builtins

Chaque builtin est une fonction C qui reproduit le comportement de la commande bash
correspondante. Les implémenter et les tester un par un, en comparant avec bash.

- **`echo`** : affiche ses arguments séparés par des espaces, suivi d'un saut de ligne.
  Avec `-n`, pas de saut de ligne final.
- **`pwd`** : affiche le répertoire de travail courant. Utiliser `getcwd`.
- **`env`** : affiche toutes les variables d'environnement internes sous la forme
  `NOM=valeur`, une par ligne.
- **`cd`** : change le répertoire courant avec `chdir`. Mettre à jour les variables
  `PWD` et `OLDPWD` dans l'environnement interne. Gérer le cas `cd` sans argument
  (aller dans `HOME`).
- **`export`** : ajoute ou modifie une variable dans l'environnement interne. Sans
  argument, affiche les variables exportées (comportement de bash). Valider le format
  du nom (commence par une lettre ou `_`, suivi de lettres, chiffres, `_`).
- **`unset`** : supprime une variable de l'environnement interne.
- **`exit`** : quitte le shell. Avec un argument numérique, utiliser ce code comme
  code de sortie. Vérifier que l'argument est bien un nombre.

### Étape 3.3 — Redirections

Les redirections modifient les file descriptors d'une commande avant son exécution.
L'idée est de remplacer temporairement `stdin` (fd 0) ou `stdout` (fd 1) par un fichier
ouvert, grâce à `dup2`.

**Ordre d'application :** appliquer les redirections dans l'ordre où elles apparaissent
dans la ligne de commande. En cas de plusieurs redirections du même type, la dernière
gagne (comportement bash).

- **`<`** : ouvrir le fichier en lecture et le brancher sur `stdin`.
- **`>`** : ouvrir/créer le fichier en écriture (troncature) et le brancher sur `stdout`.
- **`>>`** : ouvrir/créer le fichier en écriture (append) et le brancher sur `stdout`.
- **`<<` (heredoc)** : cas particulier. Lire des lignes depuis `stdin` jusqu'à ce que
  le délimiteur soit rencontré. Stocker ce qui a été lu et le brancher sur l'entrée de
  la commande. Le heredoc ne doit pas apparaître dans l'historique de readline.

**Gestion des erreurs :** si un fichier ne peut pas être ouvert, afficher une erreur et
ne pas exécuter la commande (mais continuer le shell).

### Étape 3.4 — Pipes

Les pipes permettent de chaîner des commandes : la sortie de l'une devient l'entrée de
la suivante.

**Principe :**
Pour `N` commandes en pipe, créer `N-1` pipes. Chaque commande est exécutée dans son
propre processus enfant. Les `dup2` redirigent la sortie d'un processus vers l'entrée
du suivant via le pipe.

**Gestion des file descriptors :**
C'est la partie la plus délicate. Après chaque `dup2`, fermer le fd original. Fermer
tous les fds des pipes dans le processus parent après avoir forké tous les enfants.
Un fd oublié ouvert empêche les processus de terminer correctement (le lecteur d'un
pipe attend indéfiniment si l'extrémité d'écriture n'est pas fermée).

**Attente des processus :**
Attendre **tous** les enfants avec `waitpid` après avoir tout lancé. Le code de retour
de `$?` est celui du **dernier** processus du pipeline.

**Builtins dans un pipe :**
Cas particulier : si un builtin se trouve dans un pipeline (ex : `echo foo | cat`), il
doit quand même être forké pour que les redirections de pipe fonctionnent correctement.
Seul un builtin exécuté **seul** (sans pipe) s'exécute dans le processus shell.

---

## Phase 4 — Intégration (2-3 jours ensemble)

La phase la plus délicate du projet. Parser et executor fonctionnent séparément — il
faut maintenant les connecter et gérer tout ce qui touche au cycle de vie du shell.

### 4.1 — Connexion parser / executor

Brancher la sortie du parser sur l'entrée de l'executor dans la boucle principale.
Vérifier que toutes les structures sont correctement remplies dans tous les cas.
Tester méthodiquement : commande simple → redirection → pipe simple → pipe multiple →
combinaisons.

### 4.2 — Gestion des signaux

Les signaux doivent se comporter exactement comme dans bash.

**En mode interactif (pas de commande en cours) :**
- `ctrl-C` (`SIGINT`) : effacer la ligne courante et afficher un nouveau prompt.
- `ctrl-D` : pas un signal mais une fin de fichier détectée par `readline` qui retourne
  NULL. Quitter le shell proprement.
- `ctrl-\` (`SIGQUIT`) : ne rien faire.

**Pendant l'exécution d'une commande :**
- `ctrl-C` : envoyer `SIGINT` au processus enfant, pas au shell. Le shell attend puis
  réaffiche le prompt.
- `ctrl-\` : envoyer `SIGQUIT` au processus enfant (comportement bash standard).
- Les processus enfants doivent avoir leurs propres gestionnaires de signaux — ne pas
  hériter des gestionnaires du parent.

**La variable globale** : le gestionnaire de signal ne fait qu'écrire le numéro du
signal reçu dans la variable globale. Le reste du traitement (mise à jour du prompt,
de `$?`, etc.) se fait dans la boucle principale en lisant cette variable.

### 4.3 — Nettoyage mémoire

Libérer toutes les structures allouées après chaque commande exécutée.
Utiliser `valgrind` avec les options appropriées pour détecter les fuites.
Les fuites internes à `readline` sont acceptées et ignorées — se concentrer sur le code
écrit par vous.

Points souvent oubliés :
- L'environnement interne alloué à l'initialisation
- Les tokens et commandes alloués à chaque iteration de la boucle
- Les fds heredoc ouverts en cas d'erreur avant exécution

### 4.4 — Tests croisés

Chaque personne teste la partie de l'autre avec des cas limites. Se comparer
systématiquement à bash pour chaque comportement. Cas à ne pas oublier :

- Commandes avec chemin absolu, relatif, introuvable
- Variables non définies, vides, avec caractères spéciaux
- Quotes imbriquées et cas limites (`""`, `''`, `"$VAR"`, `'$VAR'`)
- Heredoc avec variable à l'intérieur
- Plusieurs redirections sur la même commande
- Pipes avec builtins
- `exit` dans un pipe
- Signaux pendant un heredoc, pendant un pipe long

### 4.5 — README.md

Obligatoire selon le sujet. Doit inclure :
- Première ligne en italique avec les logins des deux auteurs
- Section "Description" : objectif du projet, vue d'ensemble
- Section "Instructions" : compilation (`make`), lancement (`./minishell`), dépendances
- Section "Resources" : documentation consultée, et **description de l'usage de l'IA**
  (quelles tâches, quelles parties du projet)

---

## Phase 5 — Bonus *(seulement si le mandatory est parfait)*

### 5.1 — Opérateurs `&&` et `||`

- `cmd1 && cmd2` : exécuter `cmd2` seulement si `cmd1` a réussi (code de retour 0).
- `cmd1 || cmd2` : exécuter `cmd2` seulement si `cmd1` a échoué (code de retour non 0).
- Ces opérateurs impliquent de faire évoluer le parser pour gérer un arbre d'expressions
  plutôt qu'une simple liste de commandes.

### 5.2 — Parenthèses

- `(cmd1 && cmd2) || cmd3` : les parenthèses groupent des expressions et définissent
  les priorités.
- Nécessite un parser récursif capable de traiter des sous-expressions.
- Chaque groupe entre parenthèses peut être exécuté dans un sous-shell (processus enfant
  qui exécute le groupe).

### 5.3 — Wildcards `*`

- `*.c` ou `src/*` doit être expansé en la liste des fichiers correspondants dans le
  répertoire courant.
- L'expansion se fait au moment du parsing, avant l'exécution.
- Utiliser `opendir` / `readdir` pour lire le répertoire et filtrer les noms.
- Si aucun fichier ne correspond, laisser le pattern tel quel (comportement bash).
- Le `*` ne matche pas les fichiers cachés (ceux dont le nom commence par `.`).

---

## Points d'attention critiques

- **Une seule variable globale** : uniquement le numéro du signal — aucune structure,
  aucun pointeur, rien d'autre en global. C'est une règle stricte du sujet.
- **Pas de `\` ni `;`** : ne pas les interpréter, mais ne pas crasher non plus si
  ils apparaissent.
- **Fuites mémoire** : les leaks internes à `readline` sont tolérés et documentés.
  Tout autre leak est éliminatoire.
- **La norme 42** s'applique à tous les fichiers, y compris les fichiers bonus.
- **Référence unique en cas de doute** : le comportement de bash. Toujours tester dans
  bash avant d'implémenter.
- **Ne pas sur-implémenter** : le sujet dit explicitement de ne pas aller au-delà de ce
  qui est demandé.

---

## Ordre suggéré

```
Semaine 1 : Phase 1 ensemble → Phase 2 + 3 en parallèle
Semaine 2 : Fin Phase 2 + 3 → début Phase 4
Semaine 3 : Phase 4 complète + tests → bonus si le temps le permet
```

> La partie la plus délicate sera l'intégration parser/executor et la gestion des
> signaux dans les pipes — prévoir du temps pour ça. Ne pas commencer les bonus tant
> que le mandatory n'est pas parfait.
