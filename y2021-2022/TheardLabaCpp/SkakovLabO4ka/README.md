# Дз 3. Сортировка
Техническое задание: [КТ_2022_3.pdf](КТ_2022_3.pdf)

+ Проверка `int`
+ Проверка `float`
+ Проверка `phonebook`
+ Проверка с рандомными кейсами
+ Проверка на ошибки
+ Проверка .clang-fomat

Аргументы для отключения режимов:
+ `-nf` Отключение провекрки float
+ `-nfp` Отключение проверки phonebook
+ `-ner` Отключение проверки на ошибки
+ `-fm` Включение проверки .clang-format. Выводится log от clang-format.

Пример: `python .\SkakovLabO4ka\ lab3.exe -nf -nfp`

## Работа с тестами
Требование: `python3.7+`

### Загрузка
`git clone https://github.com/vanerk03/SkakovLabO4ka`

### Запуск
Тесты больше не компилируют программу. Тестируется уже скомпилированная вами программа.
1. Командная строка Windows: `python .\SkakovLabO4ka\ lab3.exe`
2. Командная строка Ubuntu\MacOS: `python3 .\SkakovLabO4ka\ lab3`


### 
Скрипт делает автоматический `git pull`, для поддержания актуальной версии тестов.

Обратите внимание, на то что вскоре на 
ветке `master` будут лежать тесты для hw4, hw5. В этом случае тесты для hw3 будут лежать на ветке `hw3`
