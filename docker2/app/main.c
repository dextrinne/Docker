#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h> 
#include <stdio.h> 
#include <dirent.h>

#define BUFFER_SIZE 1024 // Максимальный размер буфера

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функция для обработки команды echo
bool handle_echo(char *command, char *output) {
    if (strncmp(command, "echo ", 5) == 0) {
        strcpy(output, command + 5); // Выводим весь текст после "echo"
        return true;
    }
    return false;
}

void handle_sighup(int sig) {
    printf("Configuration reloaded\n");
    exit(0);
}

void mem_dump(DIR* dir, char* path) {
    FILE* res = fopen("12.txt", "w+");
    fclose(res);
    struct dirent* ent;
    char* file_path;
    
    while ((ent = readdir(dir)) != NULL) {
        asprintf(&file_path, "%s/%s", path, ent->d_name);
        FILE *f1 = fopen("12.txt", "a");
        FILE *f2 = fopen(file_path, "r");
        if (!f1 || !f2) {
        printf("Ошибка чтения файла %s\n", file_path);
        return;
    }
    char buf[256];

    while (fgets(buf, 256, f2) != NULL) {
        fputs(buf, f1);
    }
    fclose(f1);
    fclose(f2);
    }
    printf("Готово\n");
}

// Прототипы функций для заданий
int task1();
void task2();
void task3();
void task5();
void task7();
int task8();
int task9();
int task10();
void task12();
void task_unknown();

// Функция для записи истории выбора в файл
void log_choice(int choice);

int main() {
    int choice;

    while (1) {
        printf("\n======== Меню Заданий ========\n");
        printf("1. Задание 1: Ввод/вывод строки\n");
        printf("2. Задание 3: Добавление команд выхода\n");
        printf("3. Задание 5: команда echo и проверка этой команды\n");
        printf("4. Задание 7: команда по выводу переменной окружения (PATH)\n");
        printf("5. Задание 8: выполнение указанного бинарника\n");
        printf("6. Задание 9: по сигналу SIGHUP вывести Configuration reloaded\n");
        printf("7. Задание 10: определить является ли диск загрузочным\n");
        printf("8. Задание 12: По mem <procid> получить дамп памяти процесса\n");
        printf("0. Выход\n");
        printf("Выберите задание: ");
        scanf("%d", &choice);

        log_choice(choice); // Записываем выбор в файл

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task3();
                break;
            case 3:
                task5();
                break;
            case 4:
                task7();
                break;
            case 5:
                task8();
                break;
            case 6:
                task9();
                break;
            case 7:
                task10();
                break;
            case 8:
                task12();
                break;
            case 0:
                printf("Выход из программы.\n");
                return 0;
            default:
                task_unknown();
                break;
        }
    }
    return 0;
}

// Функции для заданий
int task1() {
    clear_input_buffer();
    char buffer[BUFFER_SIZE];
    printf("Введите строку:\n");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        perror("Ошибка чтения строки"); // Вывод сообщения об ошибке
        return 1; // Возвращение кода ошибки
     }
    // Удаление символа новой строки, который fgets() добавляет в конец.
    buffer[strcspn(buffer, "\n")] = 0;
    printf("Вы ввели: %s\n", buffer);
    printf("\n");
}

void task3() {
    clear_input_buffer();
    char input[BUFFER_SIZE];
    printf("Введите команду для закрытия (exit или q)\n");
    fgets(input, BUFFER_SIZE, stdin);
    input[strcspn(input, "\n")] = 0; // Удаляем символ новой строки
    if (strcmp(input, "exit") == 0 || strcmp(input, "\\q") == 0) {
                exit(1); // Прекращение работы task3.c в терминале 
    }
    else {
        printf("Вы ввели несуществующую команду.\n"); // Сообщение об ошибке
    }
}

void task5() {
    clear_input_buffer();

    char buffer[BUFFER_SIZE]; // Ввод команды
    char output[BUFFER_SIZE]; // Вывод строки

    while (1) {
        printf("Введите команду echo и текст после команды (если хотите выйти введите exit):\n");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break; // Выход при Ctrl+D
        }

        buffer[strcspn(buffer, "\n")] = 0; // Удаляем символ новой строки

        if (strcmp(buffer, "exit") == 0) {
            break; // Выход при вводе "exit"
        }

        if (handle_echo(buffer, output)) {
            printf("%s\n", output);
        } 
        
        else {
            printf("Неправильный ввод: %s\n", buffer);
        }
        printf("\n");
    }
    printf("Выход из программы.\n");
}

void task7() {
    clear_input_buffer();
    char *path = getenv("PATH");// Получает значение переменной окружения с именем "PATH".  Она возвращает указатель на строку, содержащую значение, или NULL, если переменная не найдена.
    if (path != NULL) {
        printf("Значение переменной PATH: %s\n", path);
    } else {
        printf("Переменная PATH не найдена.\n");
    }
}

int task8() {
    clear_input_buffer();
    char path[256];
    printf("Введите путь к бинарнику: ");
    scanf("%255s", path);
    int result = system(path);
    return result;
}

int task9() {
    clear_input_buffer();

    signal(SIGHUP, handle_sighup);
    
    while (1) {
        pause(); // Ожидание сигнала
    }
    
    return 0;
}

int task10(int argc, char *argv[]) {
    clear_input_buffer();

    char device_name[15];

    printf("Введите имя устройства (например, sda, sdb): ");
    if (fgets(device_name, sizeof(device_name), stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения с клавиатуры.\n");
        return 1;
    }

    // Удаляем перенос строки, добавленный fgets
    device_name[strcspn(device_name, "\n")] = 0;

    char path[20];
    snprintf(path, sizeof(path), "/dev/%s", device_name);

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Ошибка открытия диска");
        return 1;
    }

    uint8_t buffer[512];
    if (read(fd, buffer, sizeof(buffer)) != sizeof(buffer)) {
        perror("Ошибка чтения первого сектора");
        close(fd);
        return 1;
    }

    close(fd);

    // Проверка сигнатуры загрузочного диска
    if (buffer[510] == 0x55 && buffer[511] == 0xAA) {
        printf("Диск %s является загрузочным.\n", device_name);
    } else {
        printf("Диск %s не является загрузочным.\n", device_name);
    }

    return 0;
}

void task12() {
    clear_input_buffer();

    char input[BUFFER_SIZE];
 
    do {
        printf("Введите функцию: ");
        fflush(stdout);
        bool check=false;

        // input
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            printf("\nЗавершение работы (Ctrl+D)\n");
            break; // выход из цикла при EOF
        }
 
        // \n
        input[strcspn(input, "\n")] = '\0';
 
        // exit
        if (strcmp(input, "exit") == 0) {
            printf("Завершение работы (exit)\n");
            break;
        }
        
        if (strncmp(input, "\\mem ", 5) == 0) {
            char* path;
            asprintf(&path, "/proc/%s/map_files", input+5);

            DIR* dir = opendir(path);
            if (dir) {
                mem_dump(dir, path);
            }
            else {
                printf("Процесс не найден\n");
            }
            check = true;
            continue;
        }

        if(check==false){
        printf("Команда '%s' не найдена\n", input);
        }
       
    }
    while (!feof(stdin));
}

void task_unknown() {
    printf("Неверный выбор задания. Пожалуйста, повторите попытку.\n");
}

void log_choice(int choice) {
    FILE *logfile = fopen("menu_history.txt", "a"); // Открываем файл для дозаписи
    if (logfile == NULL) {
        perror("Ошибка открытия файла для записи истории");
        return;
    }

    fprintf(logfile, "Выполнено задание %d\n", choice);
    fclose(logfile);
}
