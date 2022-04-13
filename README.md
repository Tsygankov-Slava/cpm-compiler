# Compiler
# Описание проекта
Программа принимает на вход файл языка программирования C+-, компилирует под C++ и выдаёт файл .cpp
<hr>

# Описание C+-
<h3>Имеет:</h3><br>
<ul>
  <li>Переменные и константы (var/val)</li>
  <li>Литералы (12 / 234.4 / "Hello")</li>
  <li>Операторы (+ / - / =)</li>
  <li>Вывод (print)</li>
  <li>Ввод (input)</li>
</ul>
<hr>
<ul>
  <li>Переменные типа int</li>
  <li>Переменные типа float</li>
  <li>Переменные типа string</li>
</ul>
<hr>
<ul>
  <h4>Правила для операторов</h4>
  <li>String + Int/Float -> String</li>
  <li>String - Int/Float -> Int/Float (Строка преобразуется в числовой тип, если такое невозможно, то она 0)</li>
  <li>Int/Float + Int/Float -> Int/Float</li>
</ul>
<hr>

# Настройка
1. Загружаем к себе на компьютер архив проекта Compiler.zip
2. Разархивируем его
3. Зайдём в командную строку, там перейдём в директорию с проектом ../Compiler/cmake-build-debug/
4. Запустим команду "./Compiler ../file.cpm" (при этом подготовив файл с кодом заранее [в данном примере файл с кодом находится в папке Compiler/ , поэтому путь задаётся следующим образом])<br><img width="821" alt="Снимок экрана 2022-04-13 в 22 05 10" src="https://user-images.githubusercontent.com/88239778/163252051-d713c0b8-22aa-4125-a862-d74ecfb41636.png">
6. После выполненя команды у нас появится файл .cpp в том же каталоге, что и изначальный файл<br><img width="241" alt="Снимок экрана 2022-04-13 в 22 06 44" src="https://user-images.githubusercontent.com/88239778/163252447-6cfac1b4-19c9-4fac-a5b8-2f68ed339594.png">
<hr>

# Описание работы программы
1. Получаем от пользователя путь к файлу с кодом на "C+-".
2. Разбиваем код на лексемы.
3. Парсим его, получаем абстрактное синтаксическое дерево (AST) для кода на "C+-".
4. Проверяем, что переменные/константы объявлены(правильно) и константы не перезаписываются.
5. По AST кода для "C+-" строим AST для "C++".
6. По AST для "C++" собираем код и записываем его в новый файл с расширением cpp.
<hr>

# Пример работы программы
<h3>Определение переменных</h3>
INPUT:<br><img width="266" alt="Снимок экрана 2022-04-13 в 22 12 17" src="https://user-images.githubusercontent.com/88239778/163253141-0b65c055-148c-4bbc-a445-65030c802a49.png">
OUTPUT:<br><img width="345" alt="Снимок экрана 2022-04-13 в 22 13 11" src="https://user-images.githubusercontent.com/88239778/163253263-3d4c9cbe-4972-40a9-a2f4-1b5d3b647b71.png"><br><br>
<hr>
<h3>Определение констант</h3>
INPUT:<br><img width="151" alt="Снимок экрана 2022-04-13 в 22 28 17" src="https://user-images.githubusercontent.com/88239778/163255608-541e77af-4cd7-4342-bc46-0847ade7b67b.png"><br>
OUTPUT:<br><img width="342" alt="Снимок экрана 2022-04-13 в 22 28 52" src="https://user-images.githubusercontent.com/88239778/163255709-bd7c1876-7df0-4ba2-a783-5f0d08d77eef.png"><br><br>
<hr>
<h3>Вывод</h3>
INPUT:<br><img width="219" alt="Снимок экрана 2022-04-13 в 22 15 18" src="https://user-images.githubusercontent.com/88239778/163253555-f21dc0ce-f39f-4e31-a739-679df0afd351.png"><br>
OUTPUT:<br><img width="276" alt="Снимок экрана 2022-04-13 в 22 15 42" src="https://user-images.githubusercontent.com/88239778/163253607-d8b4394f-92d7-4cc6-a79a-dd18a21a5c37.png"><br><br>
<hr>
<h3>Ввод</h3>
INPUT:<br><img width="257" alt="Снимок экрана 2022-04-13 в 22 20 50" src="https://user-images.githubusercontent.com/88239778/163254435-39fb03e2-9e44-4f52-921d-70c705822440.png">
P.S. После запуска комманды, программа попросит ввести значения<br><img width="828" alt="Снимок экрана 2022-04-13 в 22 22 33" src="https://user-images.githubusercontent.com/88239778/163254709-b65a1909-283f-4b95-80ea-d0ae644abb0d.png"><br>
OUTPUT:<br><img width="347" alt="Снимок экрана 2022-04-13 в 22 23 04" src="https://user-images.githubusercontent.com/88239778/163254796-72d4abc5-1369-4f2f-9088-84a7c1df904c.png"><br><br>
<hr>
<h3>Общий пример</h3>
INPUT:<br><img width="251" alt="Снимок экрана 2022-04-13 в 22 25 57" src="https://user-images.githubusercontent.com/88239778/163255219-d3d8b28f-2831-4735-bbdb-d0f6961b27a5.png"><br>
P.S. После запуска комманды, программа попросит ввести значения<br> <img width="801" alt="Снимок экрана 2022-04-13 в 22 25 27" src="https://user-images.githubusercontent.com/88239778/163255140-c5db930a-e3e6-4726-a9fd-7b5fd6e87194.png"><br>
OUTPUT:<br><img width="371" alt="Снимок экрана 2022-04-13 в 22 26 32" src="https://user-images.githubusercontent.com/88239778/163255306-dae4f0e6-8bfc-42d4-b19e-4b95a8a64876.png"><br>
<hr>

# Обработка ошибок
<h3>Переопределение переменной/константы</h3>
INPUT:<br><img width="166" alt="Снимок экрана 2022-04-13 в 22 39 28" src="https://user-images.githubusercontent.com/88239778/163257262-3fd0c5b3-8e4f-48db-a017-034bf76a711e.png"><br>
OUTPUT:<br><img width="873" alt="Снимок экрана 2022-04-13 в 22 39 59" src="https://user-images.githubusercontent.com/88239778/163257314-08a84b48-1f4e-49c4-8d3b-f46dc0f19248.png"><br><br>
<hr>
<h3>Переменная не инициализирована</h3>
INPUT:<br><img width="106" alt="Снимок экрана 2022-04-13 в 22 43 59" src="https://user-images.githubusercontent.com/88239778/163257921-517813e7-d8bd-4ad9-afa9-416e09457ec4.png"><br>
OUTPUT:<br><img width="865" alt="Снимок экрана 2022-04-13 в 22 44 24" src="https://user-images.githubusercontent.com/88239778/163257979-236eba25-7205-4e31-8958-852b7a853c30.png">
<br><br>
<hr>
<h3>Нераспознанная лексема</h3>
INPUT:<br><img width="139" alt="Снимок экрана 2022-04-13 в 22 46 30" src="https://user-images.githubusercontent.com/88239778/163258300-650d3647-26cb-40b2-bdca-45db8f05fb44.png"><br>
OUTPUT:<br><img width="806" alt="Снимок экрана 2022-04-13 в 22 46 54" src="https://user-images.githubusercontent.com/88239778/163258380-d69f5ed9-efc1-4f75-845e-d3649a1966c2.png">
<br><br>
<hr>
