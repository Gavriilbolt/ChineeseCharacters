# ChineeseCharacters

Наш проект заключается в создании устройства, способного выводить произвольный текст на китайском языке на дисплей. Устройство оснащено микроконтроллером Arduino и поддерживает вывод иероглифического текста, хранимого на SD-карте, на дисплей разрешением 128×64 пикселей. Мы разработали специальные программные решения, позволяющие отображать и хранить текстовую информацию на устройстве. Наш проект представляет удобный инструмент для работы с китайским языком и может быть использован в различных областях, где требуется вывод китайского текста.

![image](https://github.com/Gavriilbolt/ChineeseCharacters/assets/92447333/a7013aaa-d5a9-4e2a-a979-9fe2c5d03e21)



Полезные ссылки:

***Библиотеки для работы с кнопками

https://github.com/GyverLibs/GyverButton/

https://github.com/GyverLibs/EncButton/


***Работа с дисплеем

https://github.com/olikraus/u8glib

https://github.com/olikraus/u8g2


***Вспомогательне иснструменты

File to hexadecimal converter URL: https://tomeko.net/online_tools/file_to_hex.php

Processing URL: https://processing.org/


Принцип работы устройства:

Работа прошивки построена следующим образом: файл с текстом на китайском языке открывается на чтение, так как дисплей может уместить текст, состоящий только из двадцати четырёх иероглифов за раз, то создаётся массив, содержащий адреса каждого символа (по три байта на символ), затем с этой информацией происходит обращение к файлу со шрифтом, откуда элементы выгружаются на дисплей. При прокрутке текста снова открывается файл, содержащий текст, и в массив адресов записываются новые значения.


