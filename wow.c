#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(){
    struct dirent **lista = NULL;   // vetor de entradas
    int total = 0;

    DIR *dir = opendir("/home/felipe/");
    if (dir == NULL) {
        perror("Não foi possível abrir o diretório");
        return 1;
    }

    /* ---------- LER TODOS OS ARQUIVOS PARA UM VETOR ----------  */
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        lista = realloc(lista, sizeof(struct dirent*) * (total + 1));
        lista[total] = malloc(sizeof(struct dirent));
        memcpy(lista[total], entry, sizeof(struct dirent));
        total++;
    }
    closedir(dir);
    /* ---------------------------------------------------------- */

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    int ch;
    int selecao = 2;
    int sabido = 2;

    while (1) {
        clear();

        // agora seleciona do vetor
        if (selecao < 1) selecao = 1;
        if (selecao >= total) selecao = total - 1;
        if (sabido < 1) selecao = 1;
        if (sabido >= total) selecao = total - 1;
        if (selecao >= 14) selecao = 14;

        mvprintw(0, 66, "-Vetores comecao em 0!-");
        mvprintw(selecao, 1, "%i %s", sabido, lista[selecao-1]->d_name);

        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                selecao--;
                sabido--;
                break;
            case KEY_DOWN:
                selecao++;
                sabido++;
                break;
        }
    }

    for (int i = 0; i < total; i++) free(lista[i]);
    free(lista);

    return 0;
}
/*
gcc -o wow wow.c -lncurses
./wow
*/
