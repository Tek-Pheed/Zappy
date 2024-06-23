# {E} - Zappy

## Description

Le Zappy est un projet Epitech consistant au développement d'un jeu en réseau.
Plusieurs équipes doivent s'affronter sur un terrain contenant des ressources.
L'équipe gagnante est celle avec au moins 6 joueurs qui ont atteint le niveau maximal.
Ce sont des I.A qui composent les équipes et incarnent les joueurs.

-   Le serveur a entièrement été développé en C avec les librairies du système Linux.
-   Les I.A ont été développées avec Python 3.
-   Le client graphique a été créé en CPP avec la librairie RayLib permettant d'effectuer de la 3D.

## Utilisation

### Compilation

```bash
make
```

### Lancements des programmes

#### Serveur

```bash
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq [-v verbose true|false]
```

#### IA

```bash
./zappy_ia -p port -n teamname -h host --verbose
```

#### GUI

```bash
./zappy_gui -p port -h host
```

## Documentation

Vous pouvez trouver la documentation du projet [ici](https://github.com/Tek-Pheed/Zappy/blob/master/documentation/Zappy%20-%20Documentation.pdf)
