#include <stdio.h>
#include <unistd.h>

int main() {
    char current_directory[256];

    // Obtenir le répertoire de travail actuel
    getcwd(current_directory, sizeof(current_directory));
    printf("Avant chdir: Current Directory: %s\n", current_directory);

    // Changer le répertoire de travail vers le répertoire parent
    if (chdir("..") == 0) {
        // Obtenez le répertoire de travail mis à jour
        getcwd(current_directory, sizeof(current_directory));
        printf("Après chdir: Current Directory: %s\n", current_directory);
    } else {
        perror("chdir");
        return 1;  // La fonction chdir a échoué
    }

    return 0;
}

