# Этап 1: Сборка приложения
FROM gcc:latest AS build-stage

# Устанавливаем рабочую директорию
WORKDIR /app

# Копируем исходный код в контейнер
COPY ./app /app

# Компилируем приложение с флагом для POSIX-расширений
RUN gcc -o my_shell main.c -D_GNU_SOURCE

# Этап 2: Минимальный образ для запуска
FROM ubuntu:22.04

# Устанавливаем необходимые зависимости для запуска и Git
RUN apt-get update && apt-get install -y libc-bin git && apt-get clean

# Копируем скомпилированное приложение из первого этапа
COPY --from=build-stage /app/my_shell /usr/local/bin/my_shell

# Устанавливаем рабочую директорию
WORKDIR /root

# Указываем точку входа
ENTRYPOINT ["my_shell"]