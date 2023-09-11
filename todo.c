/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:26:39 by lmedrano          #+#    #+#             */
/*   Updated: 2023/09/11 18:37:56 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO
//
//Cas particuliers
//1. Commande inexistante : command not found
//2. Fichier inexistant : No such file or directory
//3. Redirection entrée/sortie:
//3a. > pour rediriger la sortie vers un fichier
//3b. < pour lire l'entrée depuis un fichier
//3c. >> pour ajouter à un fichier existant
//4. Pipe : chaîner des commandes en utilisant le pipe (|) pour envoyer la sortie de la première commande comme entrée à la deuxième commande.
//5. Variables d'environnement : Vous pouvez utiliser des variables d'environnement dans vos commandes, comme PATH ou HOME.
//6. Expansion de l'astérisque (*) : Vous pouvez utiliser l'astérisque pour faire correspondre plusieurs fichiers en utilisant des wildcards, par exemple *.txt pour faire correspondre tous les fichiers texte.
//7. Commandes en arrière-plan : En ajoutant un & à la fin d'une commande, vous pouvez la faire s'exécuter en arrière-plan, ce qui signifie que le shell n'attendra pas la fin de la commande avant de vous rendre la main.
//8. Commandes conditionnelles : Vous pouvez utiliser des structures de contrôle telles que if, else, et fi pour créer des commandes conditionnelles.
//9. Commandes en boucle : Vous pouvez utiliser des boucles comme for et while pour répéter des commandes.
//10. Alias : Vous pouvez créer des alias de commande en utilisant alias pour simplifier l'utilisation de commandes longues ou fréquemment utilisées.
//11. Expansion de la commande : Vous pouvez utiliser la touche Tab pour l'auto-complétion des noms de fichiers et de commandes, ainsi que la flèche vers le haut pour parcourir l'historique des commandes.
//12. Variables d'environnement personnalisées : Vous pouvez définir vos propres variables d'environnement pour stocker des valeurs qui sont utilisées dans vos scripts ou dans votre session Bash.
//13. Expressions régulières : Vous pouvez utiliser des expressions régulières pour rechercher et manipuler du texte dans les commandes.
//14. Sous-shell : Vous pouvez lancer un sous-shell en exécutant bash, ce qui crée une nouvelle instance de Bash à l'intérieur de la session actuelle.
//15. Commandes système : Vous pouvez exécuter des commandes système en utilisant system ou en plaçant la commande entre backticks (`).
//16. Commandes interactives : Certaines commandes, comme vi ou nano, vous plongent dans un éditeur de texte interactif où vous pouvez modifier du texte avant de revenir au shell.
//
//
//QUOTES
//
//$ variable="valeur"
//SINGLE
/* $ echo 'Utilisation des single quotes : $variable' */
/* Utilisation des single quotes : $variable */

//DOUBLE
/* $ echo "Utilisation des double quotes : $variable" */
/* Utilisation des double quotes : valeur */
