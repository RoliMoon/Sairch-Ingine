SCOTS LEID
# Sairch ingine

Hullo abody. A present mine graduation study project o the C++ developer coorse fae SkillBox online schuil.

## Whit is a project:
It's a sairch ingine. This program wis creatit for performance a tasks relatit wi sairchin o documents in a database bi keywairds.
This is a console application, whit hain the features for settin near json files.

## Stack o uisit trechnologies:
- JSON for modern C++ library bi Niels Lohmann - tae read an scrive JSON-files.
- Google test - C++ framewark for unit tests in a project.

## Hou tae uise:
Tae run the project performs neist steps:
1. Create a faulder for project;
2. Dounlaid an extract ZIP in a prepairit faulder;
3. Compile project, uisin yer IDE, or uisin a command prompt commands;
4. Prepare the text files, bi whit necessary perform a sairch. Important:
   - the presence o files thamsels;
   - placin this in een faulder. Let it's wull a "resoorces" faulder;
   - files main be in "*.txt" format;
5. Scrive the paths tae files in the project configuration (file "config.json"):
   This file main hae neist structur:
   {
      "config": {
         "name": "Yet anither unbekent indexer",
         "version": "1.0.1022",
         "max_responses": 5
      },
      "files": [
         "../resoorces/here_main_be_scrived_the_pathes.txt",
         "../resoorces/file0002.txt"
      ]
   }
   
"config" - a block o common speirins, necessary tae launchin, whit includes:
   "name" - program name;
   "version" - version nummer;
   "max_responses" - the limit o responses per een querie (5 default);
   "files" - files array, whaur need tae scrive paths for tham in the squerr brackets "[" "]".
   
6. Create a file o requests wi name "requests.json" an mak a list o whit ye need tae find: 
   This file main hae neist structur:
   {
      "requests": [
         "some wairds",
         "request nummer twa",
         "nummer three"
         "fover"
      ]
   }
   
"requests" - an array o requests, aa requests are listit ben the squerr brackets "[" "]", separatit bi commas.
"some wairds" - the requests thamsels, whit ye need tae mak yersel, basit on the files contents.

7. Play.

INGLIS LEID
# Search engine

Hello everyone. I present my graduation study project o the C++ developer course from SkillBox online school.

## What is a project:
It's a search engine. This program was created for performance a tasks related with searching of documents in a database by keywords.
This is a console application, whith having the features for setting near json files.

## Stack o uisit trechnologies:
- JSON for modern C++ library by Niels Lohmann - to read and write JSON-files.
- Google test - C++ framework for unit tests in a project.
   
## How to use:
To run the project perform next steps:
1. Create a folder for project;
2. Download and extract ZIP in a prepaed folder;
3. Compile project, using your IDE, or using a command prompt commands;
4. Prepare the text files, by that necessary perform a search. Important:
   - the presence of files themselves;
   - placing this on one folder. Let it's will a "resoorces" folder;
   - files must be in "*.txt" format;
5. Write the paths to files in the project configuration (file "config.json"):
   This file must have next structure:
   {
      "config": {
         "name": "Yet anither unbekent indexer",
         "version": "1.0.1022",
         "max_responses": 5
      },
      "files": [
         "../resoorces/here_main_be_scrived_the_pathes.txt",
         "../resoorces/file0002.txt"
      ]
   }
   
"config" - a block of common information, necessary to launching, that includes:
   "name" - program name;
   "version" - version number;
   "max_responses" - the limit of responses per one query (5 default);
   "files" - files array, where need to write paths for them in the square brackets "[" "]".
   
6. Create a file of requests with name "requests.json" and make a list of that you need to find: 
   This file must have next structure:
   {
      "requests": [
         "some wairds",
         "request nummer twa",
         "nummer three"
         "fover"
      ]
   }
   
"requests" - an array of requests, all requests are listed inside the square brackets "[" "]", separated by commas.
"some wairds" - the requests themselves, that you need to make yourself, based on the files contents.

7. Play.

ROUSHIAN LEID
# Поисковый движок

Всем здравствуйте. Это мой итоговый учебный проект курса C++ разработчика от онлайн школы SkillBox.

## Что это за проект:
Это поисковый движок. Эта программа создана для выполнения задач, связанных с поиском документов в базе данных по ключевым словам.
Представляет собой консольное приложение, имеющее возможность настройки через JSON.

## Стек использованных технологий:
- Библиотека «Json for modern C++» от Нильса Лоуманна – для чтения и записи данных в JSON файлах.
- Google Test – фреймворк C++ для модульного тестирования проекта.

## Как использовать:
Чтобы запустить проект, выполните следующие шаги:
1. Создайте папку под проект;
2. Скачайте и распакуйте ZIP-архив в подготовленную папку;
3. Скомпилируйте проект, используя средства среды разработки, либо при помощи команд в командной строке;
4. Подготовьте текстовые файлы, по которым нужно осуществить поиск. Важно:
   - наличие самих файлов;
   - разместить их в одной папке. Пусть это будет папка "resoorces";
   - файлы должны иметь формат "*.txt";
5. Пропишите пути к файлам в конфигурации проекта (файл "config.json"):
   {
      "config": {
         "name": "Yet anither unbekent indexer",
         "version": "1.0.1022",
         "max_responses": 5
      },
      "files": [
         "../resoorces/here_main_be_scrived_the_pathes.txt",
         "../resoorces/file0002.txt"
      ]
   }
   
"config" - блок общей информации, нужной для запуска, в состав которого входят:
   "name" - имя программы;
   "version" - номер версии;
   "max_responses" - лимит ответов на один запрос (по уолчанию 5);
   "files" - массив файлов, куда и нужно прописать пути к ним внутри квадратных скобок "[" "]".
   
6. Создайте файл запросов с названием "requests.json" и сформируйте список того, что нужно найти: 
   Структура должна быть такой:
   {
      "requests": [
         "some wairds",
         "request nummer twa",
         "nummer three"
         "fover"
      ]
   }
   
"requests" - массив запросов, все запросы перечисляются внутри квадратных скобок "[" "]" через запятую.
"some wairds" - сами запросы, которые нужно сформировать самостоятельно, исходя из содержимого файлов.

7. Играйте.

   
