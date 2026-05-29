# Roadmap Minishell — 2 personnes

## Vue d'ensemble de la séparation des rôles

| Personne A | Personne B |
|---|---|
| Parsing / Lexer | Exécution / Builtins |

---

## Phase 1 — Infrastructure commune (1-2 jours)

*À faire ensemble ou en parallèle avant de se séparer.*

- [ ] Structure du projet : dossiers `src/`, `include/`, `libft/`
- [ ] `Makefile` avec les règles obligatoires (`NAME`, `all`, `clean`, `fclean`, `re`)
- [ ] Structures de données partagées (`t_token`, `t_cmd`, `t_env`) — **à aligner ensemble**
- [ ] Boucle principale : `readline` + `add_history` + boucle REPL
- [ ] Variable globale unique pour les signaux (`g_signal`)

---

## Phase 2 — Parsing (Personne A)

### Étape 2.1 — Lexer / Tokenizer
- [ ] Découpage de la ligne en tokens (mots, opérateurs, redirections, pipes)
- [ ] Gestion des quotes : `'...'` (tout littéral) et `"..."` (expansion `$` uniquement)
- [ ] Détection des quotes non fermées → message d'erreur sans crash

### Étape 2.2 — Expansion
- [ ] Expansion des variables d'environnement : `$VAR`
- [ ] Expansion de `$?` (exit status du dernier process)

### Étape 2.3 — Parser / AST
- [ ] Construction d'une liste de commandes avec leurs arguments
- [ ] Association des redirections à chaque commande (`<`, `>`, `<<`, `>>`)
- [ ] Gestion des pipes (séparation en commandes chainées)

---

## Phase 3 — Exécution (Personne B)

### Étape 3.1 — Exécution simple
- [ ] Recherche de l'exécutable dans `PATH` (`access` + `execve`)
- [ ] Gestion des chemins relatifs et absolus
- [ ] `fork` + `waitpid`, récupération du code de retour

### Étape 3.2 — Builtins *(pas de `fork` pour ces commandes)*
- [ ] `echo` avec option `-n`
- [ ] `pwd` sans options
- [ ] `env` sans options
- [ ] `cd` chemin relatif/absolu
- [ ] `export` sans options (ajouter/modifier une variable)
- [ ] `unset` sans options
- [ ] `exit` sans options

### Étape 3.3 — Redirections
- [ ] `<` redirection entrée
- [ ] `>` redirection sortie (écrasement)
- [ ] `>>` redirection sortie (append)
- [ ] `<<` heredoc (lire jusqu'au délimiteur, pas dans l'historique)

### Étape 3.4 — Pipes
- [ ] Création des pipes (`pipe()`)
- [ ] Chainage des `dup2` entre processus
- [ ] Gestion correcte des fds (pas de fuite de fds)

---

## Phase 4 — Intégration (2-3 jours ensemble)

- [ ] Connecter le parser à l'executor
- [ ] Signaux : `ctrl-C` (nouveau prompt), `ctrl-D` (quitte), `ctrl-\` (rien)
- [ ] Comportement correct des signaux dans les processus enfants
- [ ] Vérification mémoire : `valgrind` sur tous les cas (pas de leak sur votre code)
- [ ] Tests croisés : chacun teste le travail de l'autre
- [ ] README.md obligatoire (description, compilation, ressources, usage de l'IA)

---

## Phase 5 — Bonus *(seulement si le mandatory est parfait)*

- [ ] Opérateurs `&&` et `||` avec priorité
- [ ] Parenthèses pour les priorités
- [ ] Wildcards `*` dans le répertoire courant

---

## Points d'attention critiques

- **Une seule variable globale** : uniquement le numéro du signal — rien d'autre en global
- **Pas de `\` ni `;`** à interpréter
- **Fuites mémoire** : les leaks de `readline` sont tolérés, les vôtres non
- **La norme 42** s'applique aux fichiers bonus aussi
- Référence en cas de doute : **comportement de bash**

---

## Ordre suggéré

```
Semaine 1 : Phase 1 ensemble → Phase 2 + 3 en parallèle
Semaine 2 : Fin Phase 2 + 3 → début Phase 4
Semaine 3 : Phase 4 complète + tests → bonus si le temps le permet
```

> La partie la plus délicate sera l'intégration parser/executor et la gestion des signaux dans les pipes — prévoir du temps pour ça.
