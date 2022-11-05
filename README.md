# Библитека ParserOptions

## Парсер опций
Библиотека предназначена для считывания опций с консоли
и записи значений в структуру Options

## Конфиг
Настройка считывания опций происходит в файле config.txt 
в следующем формате:

```
<название_опции>: <тип_данных> <флаг_обязательности> <опция_1 опция_2...>
```
* `<название_опции>` - по этому названию можно будет получать
значение опции в коде
* `<тип_данных>` - тип данных, в котором будет храниться значение
опции. Доступные опции:
  + <kbd>string</kbd> - std::string
  + <kbd>int</kbd> - int
  + <kbd>short</kbd> - short
  + <kbd>uint64_t</kbd> - unsigned long long (uint64_t)
  + <kbd>bool</kbd> - bool (true - при введенной опции)
  + <kbd>stringList</kbd> - std::vector< std::string >
* `<флаг_обязательности>` - символ восклицательного знака <kbd>!</kbd>,
если указан, то опция является обязательной для ввода
* `<опция_1 опция_2...>` - сами опции, которое надо прочитать с консоли.
Перечисляются через пробел, их может быть сколько угодно

### Пример конфига
```bash
# опция example1 с тип данных std::vector<std::string>, имеет 3 опции
example1: stringList --option1 -o -1
# опция example2 с тип данных int, имеет 2 опции, является обязательной
example2: int --option2 -p
```

## Код

### Инициализация
Необходимо импортировать библиотеку parser.h, создать переменную
с типом данных Options и передать в нее размер массива ввода с
консоли и сам массив

```cpp
#include "parser.h"

int main(int argc, const char** argv) {

    // переменная хранит все введенные с консоли опции
    Options options(argc, argv);
    
    return 0;
}
```

### Получения значение
Необходимо вызвать метод `getТипДанных(<имя_опции>)`.
* Стоит заметить, что опция <kbd>other</kbd> существует по умолчанию,
в ней хранятся свободные переменные (для которых не была указана опция)
с типом данных `std::vector< std::string >`

```cpp
std::string opt1 = options.getString("optionString");
int opt2 = options.getInt("optionInt");
short opt3 = options.getShort("optionShort");
uint64_t opt4 = options.getUint64_t("optionUint64_t");
bool opt5 = options.getBool("optionBool");
std::vector<std::string> opt6 = options.getInt("optionStringList");

std::vector<std::string> other = options.getStringList("other");
```

### Изменение значение
При необходимости можно изменить значение опции с помощью метода
`set(<имя_опции>, <новое_значение>)`

```cpp
options.set("optionString", "new string");
options.set("optionInt", 666);
options.set("optionBool", false);
options.set("optionStringList", {"new string1", "new string2"});
```
