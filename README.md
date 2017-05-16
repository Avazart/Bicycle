BICYCLE
=======

Bicycle - набор классов обверток для Windows(WinApi,WinSocks,WinInet) для порождения дочерних процессов, работы с СOM-портом, 
работы с протоколами Tcp,Http,Ftp

Установка и использование
-------------------------

Для скачивания исходников используйте утилиту git набрав в консоли команду:

    git clone https://github.com/Avazart/Bicycle

Или же используя веб интерфейс скачав исходники в zip-архиве.

Исходники должны без проблем работать в MSVC 2010 и С++Builder.
Для использования необходимо включить все файлы(*.cpp и *.h) в ваш проект, а так же указать в проекте зависимости от библиотек Windows
* WinInet.lib 
* Ws2_32.lib
* Shlwapi.lib 
* А так же возможно потребуется указать User32.lib, Setupapi.lib, Advapi32.lib.

В  MSVC 2010 и С++Builder это  можно сделать используя директиву:

    #pragma comment(lib,"имя библиотеки")

Папку Bicycle необходимо добавить в INCLUDEPATH среды разработки.	
	
Папки проекта
-------------

* Bicycle  - исходники самой библиотеки.
* Examples - примеры кода.
* Projects - проекты для сред разработки QtCreator и С++Builder для примеров Examples.

Подпапки Bicycle
----------------

* Algorithm - некоторые алгоритмы со строками позаимствованные из boost/string/algorithm и некоторые алгоритмы из С++11/С++14
* Other - разные заготовки.

* Win/Common - общие файлы, глобальные объявления.
* Win/Process - для порождение дочерних процессов, чтение вывода консольных утилит, изменение переменных среды
* Win/Serial  - для работы с COM портом
* Win/TextStream -класс TextStream для построчного чтения(с буферизацией) из Process, SerialPort идр наследников IODevice

* Win/WinSocks/TcpClient - класс tcp-сокета
* Win/WinInet - ftp и http клиент на основе WinInet

* Win/Console - работа с консолью, перемещение курсора, смена цвета, очистка консоли, смена кодировки.

Ссылки
------

[Мой блог на киберфоруме](http://www.cyberforum.ru/blogs/131347/blog4416.html)