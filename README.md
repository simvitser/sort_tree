# Sort_tree

Реализация бинарного дерева, сортирующего элементы

# Возможности
- Добавление вершины
- inPrint
- prePrint
- postPrint - 3 типа вывода дерева в консоль
- Графический дамп дерева в логи
- Сохранение и чтение из файла

# Структура проекта
- main.c - демо-программа
- tree.h && tree.c - реализация дерева как отдельная библиотека
- common.h &*& common.c	- общие функции
- log.h / log.c	- логи

# Реализована графическая отладка
файл log.htm с картинками сгенерированными программой graphviz

<img width="932" height="806" alt="image" src="https://github.com/user-attachments/assets/acf3a5ce-f806-4c0a-abc4-cea5342a5509" />

# Сборка
```
gcc main.c common.c tree.c log.c
```
