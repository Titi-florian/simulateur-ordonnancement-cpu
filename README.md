# Simulateur d'Ordonnancement de CPU en C

Ce projet consiste à développer un simulateur en langage C permettant d'évaluer et de comparer différents algorithmes d'ordonnancement de processus sur un système type Ubuntu / Code::Blocks.

## Algorithmes Implémentés
1. **FIFO** (*First-In, First-Out*) : Ordonnancement non préemptif basé sur l'ordre d'arrivée.
2. **SGF** (*Shortest Job First*) : Ordonnancement non préemptif privilégiant le processus ayant la plus courte durée d'exécution.
3. **SRP** (*Shortest Remaining Time First*) : Version préemptive du SGF.
4. **Round Robin** : Ordonnancement préemptif basé sur un quantum de temps global.

## Prérequis
* Un compilateur GCC
* Code::Blocks ou tout autre environnement de développement C sous Linux (Ubuntu)

## Compilation et Exécution
1. Cloner le dépôt :
   ```bash
   git clone [https://github.com/Titi-florian/simulateur-ordonnancement-cpu.git](https://github.com/Titi-florian/simulateur-ordonnancement-cpu.git)
