# Тестовое задание
## Запуск программы
Склонировать репозиторий

```
git clone https://github.com/ankolesn/YADRO_test
```

Скомпилировать файлы

```
g++ main.cpp Info_Club.cpp Processing_Event.cpp Time_Table.cpp Event.cpp
```

Запуск

```
.\a file
```

## Тестовые файлы и результаты работы программы

`file` - Тестовый файл из задания


![Image alt](https://github.com/ankolesn/YADRO_test/blob/main/img/1.png)

`file2` - Случай, когда клиент поменял стол

Таблица, для наглядного изменения работы компьютерного клуба:

Время | 1 стол | 2 стол | 3 стол | Выручка | Время работы стола
--- | --- | --- | --- | --- | ---
09:54 | client1 |  | 
10:25 | client1 | client2 | 
10:58 |  | client2 | client1 | (20, 0, 0) | (1:04, 0, 0)
12:33 |  | client2 | client3 | (20, 0, 20) | (1:04, 0, 1:15)
12:43 |  | client4 | client3 | (20, 30, 20) | (1:04, 2:18, 1:15)
15:52 |  |  | client3 | (20, 70, 20) | (1:04, 5:27, 1:15)
19:00 |  |  | |(20, 70, 90) | (1:04, 5:27, 8:02)

![Image alt](https://github.com/ankolesn/YADRO_test/blob/main/img/2.png)

`file3` - Случай, когда клиент попытался сесть за стол, который занимает

![Image alt](https://github.com/ankolesn/YADRO_test/blob/main/img/3.png)

`file4` - Проверка входных данных

![Image alt](https://github.com/ankolesn/YADRO_test/blob/main/img/4.png)

`file5` - Случаи, когда:

- клиент уже есть в клубе и пытается зайти снова;

- в очереди ожидания клиентов больше, чем общее число столов;

- клиент не находится в компьютерном клубе, но пытается занять стол.

Таблица, для наглядного изменения работы компьютерного клуба:

Время | 1 стол | 2 стол | 3 стол | Выручка | Время работы стола
--- | --- | --- | --- | --- | ---
09:54 | client1 |  | 
10:25 | client1 | client2 | 
10:59 | client1 | client2 | client3 | 
12:33 | client4 | client2 | client3 | (30, 0, 0) | (2:39, 0, 0)
12:43 | client4 | client5 | client3 | (30, 30, 0) | (2:39, 2:18, 0)
15:52 | client6 | client5 | client3 | (70, 30, 0) | (5:58, 2:18, 0)
19:00 | client6 | client5 | client3 | (110, 100, 90) | (9:06, 08:35, 8:01)

![Image alt](https://github.com/ankolesn/YADRO_test/blob/main/img/6.png)
