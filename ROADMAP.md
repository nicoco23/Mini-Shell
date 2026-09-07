# Roadmap Minishell v2 — état réel après le Parsing (Personne A)

> Ce document remplace la vision *prévisionnelle* de `ROADMAP.md` par une vision
> *à jour* : la Phase 2 (Parsing, Personne A) est essentiellement terminée et le
> code existant fige déjà l'interface. Ce fichier décrit **ce qui existe vraiment**,
> **ce qui manque encore côté Phase 1**, et **précisément** ce que la Personne B doit
> construire par-dessus, sans deviner les structures.

---

## 1. Ce qui est fait (Personne A — Parsing)

Fichiers livrés : `src/parsing/lexer.c`, `lexer_utils.c`, `expand.c`, `cmd_builder.c`,
`cmd_redir.c`, `syntax_check.c`, `parsing_free.c`.

- **Lexer** : découpe une ligne en `t_token` (mots, `|`, `<`, `>`, `<<`, `>>`),
  gère les quotes simples/doubles avec état, et appelle l'expansion `$` en cours
  de lecture d'un mot.
- **Expansion** : `$VAR` (vide si non trouvée), `$?` (lit `shell->last_exit`),
  pas d'expansion en quotes simples, expansion en quotes doubles.
- **Syntax check** (`check_syntax`) : rejette pipe en tête/fin/double, et
  redirection non suivie d'un mot. Erreur affichée : `mouliswag: syntax error
  near unexpected token '...'`.
- **Construction des commandes** (`build_cmds`) : découpe par pipe, remplit
  `args` (tableau `char **` NULL-terminé, compatible `execve`) et `redirs`
  (liste chaînée dans l'ordre d'apparition).
- **Libération mémoire** : `free_tokens` et `free_cmds` couvrent tokens,
  commandes, args et redirections.

### Interface figée (`include/minishell.h`)

```c
typedef struct s_redir
{
    t_token_type    type;   // TOKEN_REDIR_IN / OUT / APPEND / HEREDOC
    char            *target; // fichier, ou délimiteur pour le heredoc
    struct s_redir  *next;
} t_redir;

typedef struct s_cmd
{
    char            **args;  // args[0] = nom commande, NULL-terminé
    t_redir         *redirs; // dans l'ordre d'apparition sur la ligne
    struct s_cmd    *next;   // commande suivante du pipeline, NULL si dernière
} t_cmd;

typedef struct s_shell
{
    char    **env;      // copie interne de envp, format "NOM=valeur", NULL-terminé
    t_cmd   *cmds;       // pipeline courant, produit par parsing(), à consommer puis free_cmds()
    int     last_exit;   // code retour de la dernière commande — lu par $?
} t_shell;
```

**Décisions qui engagent la Personne B :**

- `env` est un **tableau `char **`**, pas une liste chaînée (le `ROADMAP.md`
  original laissait le choix ouvert — c'est tranché). `export`/`unset`/`cd`
  doivent réallouer/modifier ce tableau, format `"NOM=valeur"`.
- `$?` est relu directement dans `shell->last_exit` au moment de l'expansion —
  donc **avant** de rappeler `parsing()` pour la ligne suivante, l'executor doit
  avoir mis `shell->last_exit` à jour avec le code retour réel de la commande
  (ou du dernier processus du pipeline).
- `cmd->args` peut être un tableau **non NULL mais avec `args[0] == NULL`**
  (ligne du type `> fichier` sans commande). Bash ne lance rien dans ce cas,
  mais exécute la redirection (créer/vider le fichier). L'executor doit gérer
  ce cas explicitement, pas juste assumer `args[0]` toujours valide.
- Les redirections d'une commande sont dans l'ordre d'apparition dans
  `cmd->redirs` → appliquer les `dup2` dans cet ordre suffit à obtenir le
  comportement "la dernière du même type gagne".

### Point d'attention identifié : délimiteur de heredoc

Le lexer traite le délimiteur d'un `<<` comme un mot normal : il passe par
`get_word`, qui **retire déjà les quotes et expanse `$`**. Le `target` stocké
dans `t_redir` est donc une chaîne "propre", sans aucune information sur le
fait que le délimiteur était quoté (`<< "EOF"` vs `<< EOF`).

Or en bash, un délimiteur quoté désactive l'expansion des variables **à
l'intérieur du corps du heredoc** — ce n'est pas un bonus, c'est un
comportement standard. Avec l'implémentation actuelle, cette information est
perdue avant d'arriver à l'executor.

→ À trancher ensemble avant que la Personne B implémente le heredoc (3.3) :
soit on ajoute un champ (`int quoted`) à `t_redir` rempli par le lexer, soit on
accepte de ne pas gérer cette nuance pour l'instant. Ne pas laisser la
Personne B découvrir ça seule en pleine implémentation.

---

## 2. Ce qui reste en Phase 1 (à finir avant que B parte à fond)

Contrairement à ce que `ROADMAP.md` supposait ("Phase 1 terminée avant de se
séparer"), une partie de l'infra commune n'est pas encore branchée :

- **`t_shell` n'est jamais instancié.** Aucune fonction n'alloue `t_shell`,
  ne copie `envp` dans `shell->env`, ni n'initialise `last_exit = 0`.
- **`main.c` est actuellement cassé/en cours** : il appelle `parsing()` sans
  argument alors que `parsing(t_shell *shell)` en attend un (`git status`
  montre `main.c` modifié, non commité). Il faut écrire l'init du shell et la
  vraie boucle avant que quiconque puisse tester l'exécution de bout en bout.
- **Le point de branchement existe déjà mais est un no-op** : dans
  `process_line` (`src/parsing/parsing.c`), après `build_cmds`, le code fait
  immédiatement `free_cmds(shell->cmds)`. C'est exactement là que l'appel à
  l'executor doit s'insérer, avant le `free_cmds`.

**Action recommandée (à faire ensemble, avant Phase 3) :**
1. Écrire `init_shell(t_shell *shell, char **envp)` qui alloue et copie
   `envp` dans `shell->env`, met `last_exit = 0`.
2. Réparer `main.c` : instancier `t_shell` une fois, boucler sur `parsing(&shell)`.
3. Dans `process_line`, remplacer le `free_cmds` prématuré par un appel à la
   future fonction d'exécution (ex: `execute_pipeline(shell)`), qui elle-même
   fera le `free_cmds` après usage.
4. Trancher la question du heredoc quoté ci-dessus.

---

## 3. Phase 3 — Exécution (Personne B), détaillée sur l'interface réelle

L'objectif ne change pas ( `ROADMAP.md` §Phase 3 reste valide sur le fond :
fork/execve, builtins, redirections, pipes ), mais voici ce qui est concrètement
disponible en entrée, pour éviter d'avoir à deviner :

### 3.1 — Commande simple
- Point d'entrée : une fonction à créer, appelée depuis `process_line` avec
  `shell->cmds` déjà rempli (liste de `t_cmd`, une par segment de pipe).
- Recherche d'exécutable : `cmd->args[0]` contient le nom (ou chemin). Gérer le
  cas `cmd->args == NULL` ou `cmd->args[0] == NULL` (pas de commande, cf. §1)
  → dans ce cas, appliquer uniquement les redirections (côté effets de bord
  fichiers), ne pas fork.
- Après exécution (simple ou pipeline), écrire le code retour dans
  `shell->last_exit` — c'est la seule façon pour `$?` de fonctionner au tour
  suivant de la boucle.

### 3.2 — Builtins
- Inchangé par rapport à `ROADMAP.md`. Point d'attention supplémentaire :
  `export`, `unset`, `cd` doivent modifier `shell->env` (tableau `char **`) en
  respectant le format `"NOM=valeur"` utilisé par `get_env_value()`
  (`src/parsing/expand.c`) — toute incohérence de format casse l'expansion
  `$VAR` côté parsing.

### 3.3 — Redirections
- `cmd->redirs` est déjà une liste triée dans l'ordre d'apparition : itérer et
  `dup2` dans cet ordre donne directement le comportement "dernière gagne".
- `t_redir.type` réutilise `t_token_type` (`TOKEN_REDIR_IN/OUT/APPEND/HEREDOC`),
  pas un enum séparé.
- Heredoc : voir le point d'attention en §1 avant de commencer — décider
  d'abord si le flag "quoted" doit être ajouté à `t_redir`.

### 3.4 — Pipes
- `t_cmd.next` chaîne les commandes du pipeline dans l'ordre. Nombre de
  commandes = nombre de segments ; créer `N-1` pipes comme prévu.
- Rien de spécifique côté parsing à connaître ici au-delà de la structure
  chaînée déjà en place.

---

## 4. Phase 4 — Intégration : ce qui change concrètement

- **4.1 Connexion parser/executor** : le point de câblage exact est identifié
  (§2, point 3) — ce n'est plus une inconnue architecturale, juste du travail
  d'implémentation.
- **4.2 Signaux** : inchangé, toujours à faire. `g_signal` existe déjà
  (`include/minishell.h`), déclarée et définie dans `main.c`.
- **4.3 Mémoire** : `free_tokens`/`free_cmds` existent déjà côté parsing —
  l'executor doit uniquement veiller à ses propres allocations (fds heredoc,
  éventuelles copies de chemins pour `execve`) et appeler `free_cmds` après
  usage (voir §2).
- **4.4 Tests croisés** : ajouter explicitement un cas de test sur
  `cmd->args[0] == NULL` (ligne avec redirection seule) et sur `<< "EOF"` vs
  `<< EOF`, puisque ce sont les deux zones d'ombre identifiées dans ce document.

---

## 5. Reste inchangé de `ROADMAP.md`

- Phase 5 (bonus), la liste "Points d'attention critiques", et l'ordre suggéré
  restent valides et ne sont pas repris ici pour éviter la duplication —
  se référer à `ROADMAP.md` pour ces sections.


ERREUR ACTUELLES

$$ -> senser return le pid du terminal
$! -> a faire?? a pas faire ??
mimishell dans minishell dans une commande (cat puis ls) fait apparaitre ce qui ressemble a une adresse, a check (./minishell | ./minishell | cat puis ls)

completer export (vide plus avec argument valide)
completer unset (vide plus avec argument valide)