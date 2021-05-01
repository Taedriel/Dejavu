## Checkpoints

1. Voiture en ligne droite.
2. Voiture qui arrive à l'arrivé en local 
( avec des if histoire d'avoir qqch qui marche même si ça perds à coup sur).
3. Voiture qui suit le chemin le plus court en longueur.
4. Voiture qui suit le chemin le plus opti en terme d'accélération max possible.
5. Adaptation du cas précédant avec optimisation du boost.
6. Ajouter un système de gène des adversaires (Très optionnel il me semble)

## What it needs to do checkpoints

1.  [x] Une structure de voiture
    [x] Gestion des sorties (Dire au GDC que notre voiture veut aller à droite)

2.  [x] Une structure map 
    [x] Une enumération dans le but de représenter les différents types de noeud dans la map
    [ ] Trouver un moyen d'économiser le plus possible l'essence

3.  [x] Un algorithme type chemin le plus court
    [x] Adaptation map pour l'algo de plus court chemin (graphe / matrice)
    [ ] Réflechir au moyen de faire ce traitement sans perdre de temps (car traitement possiblement long)

4.  [ ] 
 

## TODO

- [ ] revoir l'asservissement
- [ ] séparer en segments
- [ ] revoir le sable
- [ ] ponderer avec l'acceleration
- [ ] gérer les autres voiture !!!