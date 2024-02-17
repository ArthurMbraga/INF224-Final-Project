# INF224 - Paradigmes de Programmation
## MARTINS BRAGA Arthur

## Comment compiler et exécuter le projet
### Compilation et exécution
Il faut exécuter le serveur avant de lancer le client. Pour cela, il suffit de se placer dans le dossier `cpp` et d'exécuter la commande `make run`:
```bash
cd cpp
make run
```

Ensuite, pour lancer le client, il suffit de se placer dans le dossier `swing` et d'exécuter la commande `make run`:
```bash
cd swing
make run
```
Le client s'ouvre et automatiquement connecté au serveur.

## Comment utiliser le programme
### Interface graphique
L'interface graphique est composée de 4 buttons et 1 zone de texte. Les buttons sont:
- `Find multimedia` pour chercher un objet multimédia dans la base de données
- `Find Group` pour chercher un groupe dans la base de données
- `Play multimedia` pour jouer un objet multimédia dans le serveur
- `Exit` pour quitter le programme

Avant d'utiliser les buttons, il fault écrire le nom de l'objet ou du groupe dans la zone de texte indiquée par `Media/Group name:`.

Le serveur dispose de 4 objets multimédia et 2 groupes. Les objets multimédia sont:
- `Photo1` de type `Photo` 
- `Photo2` de type `Photo` 
- `Video1` de type `Video` 
- `Film1` de type `Film`

Les groupes sont:
- `Group1` contenant `Photo1` et `Photo2`
- `Group2` contenant `Video1` et `Film1`

Attention pour les lettres majuscules et minuscules! Vous devez écrire les noms des objets et des groupes exactement comme ils sont écrits ci-dessus pour ensayer de les trouver.

## Serveur API
Le serveur tourne sur le port 3331 et dispose de 3 commandes pour interagir avec la base de données:
- `find group <group name>` pour chercher un groupe dans la base de données.
- `find multimedia <multimedia name>` pour chercher un objet multimédia dans la base de données.
- `play multimedia <multimedia name>` pour jouer un objet multimédia dans le serveur.

## Questions et réponses
### 4e Etape: Photos et vidéos
- Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?
  - Ce type de méthode est appelé méthode virtuelle. Pour les déclarer, il faut les précéder du mot-clé `virtual` dans la classe de base.

- Si vous avez fait ce qui précède comme demandé, il ne sera plus possible d'instancier des objets de la classe de base. Pourquoi ?
  - Parce que la classe de base contient au moins une méthode virtuelle pure, ce qui la rend abstraite, et on ne peut pas instancier d'objets à partir de classes abstraites.

### 5e Etape: Traitement uniforme (en utilisant le polymorphisme)
- Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?
  - Le polymorphisme permet cela, en utilisant la liaison tardive (ou liaison dynamique).

- Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?
  - Dans le cas du C++, il est nécessaire de déclarer les méthodes virtuelles dans la classe de base et de les redéfinir dans les classes dérivées.

- Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.
  - Le tableau doit contenir des pointeurs vers les objets. Cela permet de gérer efficacement des objets de types différents dans un tableau, contrairement à Java où les tableaux peuvent contenir directement des objets.

### 7e étape. Destruction et copie des objets
- Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ? Modifiez le code de manière à l'éviter.
  - Toutes les classes qui allouent dynamiquement de la mémoire à l'aide de `new` doivent être modifiées pour éviter les fuites mémoire. Il faut s'assurer de libérer la mémoire avec `delete` dans les destructeurs et implémenter correctement le constructeur de copie et l'opérateur d'assignation.

- La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ? Implémentez-en une.
  - Le problème est que la copie par défaut effectue une copie superficielle, ce qui signifie que les pointeurs sont copiés mais pas les données auxquelles ils pointent, ce qui peut entraîner des pointeurs invalides et des fuites mémoire. Une solution consiste à implémenter une copie profonde, où une nouvelle mémoire est allouée pour chaque pointeur et les données sont copiées.

### 8e étape. Gestion des exceptions
- Le groupe ne doit pas détruire les objets quand il est détruit car un objet peut appartenir à plusieurs groupes (on verra ce point à la question suivante). On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.
  - En C++, la liste d'objets doit être une liste de pointeurs d'objets car cela permet de manipuler des objets polymorphiques sans slicing. Contrairement à Java où les tableaux peuvent contenir des objets directement.

### 10e étape. Gestion cohérente des données
- Les méthodes précédentes permettent d'assurer la cohérence de la base de données car quand on crée un objet on l'ajoute à la table adéquate. Par contre, ce ne sera pas le cas si on crée un objet directement avec `new` (il n'appartiendra à aucune table). Comment peut-on l'interdire, afin que seule la classe servant à manipuler les objets puisse en créer de nouveaux ?
  - On peut interdire la création d'objets avec `new` en rendant le constructeur privé et en fournissant une méthode statique dans la classe pour créer de nouveaux objets. Ainsi, seule la classe manipulatrice peut créer de nouveaux objets.


