/**
 * Практическое занятие №1. Базовые типы данных, операторы языка, простой
 * ввод-вывод.
 *
 * В результате выполнения данной работы слушатель получает много мелких, но
 * необходимых для дальнейшей работы навыков, поэтому задание построено как
 * последовательность закомментированных блоков, которые требуется
 * последовательно раскомментировать, отвечая при этом на поставленные вопросы.
 *
 * Необходимое программное обеспечение:
 *
 * - Unix-совместимая командная строка (для Windows необходимо установить WSL);
 * - компилятор g++, отладчик gdb (для установки в командной строке: 
 *   `apt update; apt install gcc g++ gdb`)
 * - любимый текстовый редактор.
 *
 * Примерная последовательность действий при отладке проекта:
 * 1. наберите (исправьте, раскомментируйте нужный фрагмент) исходный текст
 *    программы;
 * 2. скомпилируйте программу (в командной строке: `g++ -g lab1.cpp`);
 * 3. запустите отладчик (в командной строке `gdb ./a.out`);
 * 4. в отладчике установите точку останова на нужной строке (например, 
 *    `break 55` для 55 строки или `b 55` - так короче) и начните выполнение 
 *    программы (`run` или `r`).
 * 5. выведите значение интересующей переменной (`print cByte` или `p cByte`)
 *    или добавьте переменную для постоянного отслеживания (`watch cByte`).
 * 6. Переходите к следующей точке останова (`c`) или к следующей строке (`n`).
 */

#include  <iostream>

int nTwin = 1;
namespace TwinSpace { int nTwin1 = 2; }

int main()
{

    /**
     * Задание 1. Работа с отладчиком. Базовые типы данных. Литералы.
     *
     * Выполняя программу по шагам, следите за значениями переменных и
     * интерпретируйте результат (помните, что количество байт, отводимых под
     * int, системо-зависимо).
     *
     * Обратите внимание на разную интерпретацию отладчиком signed и unsigned
     * целых типов данных, а также на внутреннее представление отрицательных
     * целых чисел.
     */
    
    char cByte = 'A';
    cByte = 0x42;
    cByte = 66;
    cByte = -1;

    unsigned char ucByte = 0x41; 
    ucByte = 'B';
    ucByte = -1;

    int iInt = 0xffffffff; 

    unsigned int uiInt = 0xffffffff; 

    float fFloat = 1.f;  
    double dDouble = 1.; 

    /**
     * Выполните фрагмент, приведенный далее. В комментариях отразите, что
     * реально заносится в переменную. Объясните разницу между этим значением и
     * инициализатором.
     */

    double d = 0.1234567890123456789123456789;  //0.12345678901234568 52бит под мантиссу
    float  f = 0.1234567890123456789123456789; //0.123456791 23бит под мантиссу ` 

    d = 1.; // 1
    d = 0.999999999999999999999999999999999; // 1

    /**
     * В комментариях напишите результат, возвращаемый оператором sizeof для
     * переменной типа wchar_t (ее размер)
     */

    wchar_t cw = L'Ф'; 
    size_t n = sizeof(cw); //4

    /**
     * Задание 2a. Неявное приведение типов данных. 
     *
     * Объясните разницу результата при выполнении (1) и (2): Покажите явно
     * (напишите в коде) преобразования, которые неявно выполняет компилятор
     */

    iInt = 1;
    double dDouble1 = iInt / 3;     // (1) dDouble1 = 0, т.к. int 1/int 3 = int 0 который записывается в double
    double dDouble2 = iInt / 3.;    // (2) dDouble2 = 0.33333333333333331 т.к. int 1 / double 3 = double 0.33

    /**
     * Ассоциативность операторов.
     *
     * Синтаксис языка C допускает "цепочечное" присваивание (как в строках (1)
     * и (2)). Посмотрев результаты выполнения строк (1) и (2) (значения
     * переменных dDouble, fFloat, nInt, sShort, cByte), определите порядок
     * выполнения присваиваний при цепочечной записи и объясните результат.
     *
     * Расставьте скобки, явно определяющие порядок выполнения, как это сделал
     * бы компилятор. Объясните (в комментариях) предупреждения (warnings)
     * компилятора.
     */

    short sShort;
    dDouble = (fFloat = (iInt = (sShort = (cByte = 3.3 / 3)))); // (1)
    
    cByte = (sShort = (iInt = (fFloat = (dDouble = (3.3 / 3))))); // (2) dDouble = 1.0999999999999999    fFloat=1.10000002

    /**
     * Ниже Вам дан пример "небрежного" использования неявного приведения
     * типов, что может привести к нежелательным результатам - объясните (в
     * комментариях), к каким?
     *
     * Напишите явно преобразования, которые неявно выполняет компилятор.
     */

    iInt = 257;
    cByte = iInt; // 257 = 0000 0000 0000 0000 0000 0001 0000 0001 в 32бит int, при присвоении этого значения 8бит char старшие 24 бита отбросятся и останется только 0000 0001 = 1

    unsigned char cN1 = 255, cN2 = 2, cSum;
    cSum = cN1 + cN2; // 255+2=1111 1111 + 0000 0010 = 1 0000 0001 но сhar 8бит, поэтому старший бит отбрасывается и остается 1

    /**
     * Сравните предыдущую строчку с приведенной ниже. 
     *
     * Объясните (в комментариях), почему в следующей строке не происходит
     * выход за разрядную сетку
     *
     * Напишите явно преобразования, которые неявно выполняет компилятор
     */

    int iSum = cN1 + cN2; //255+2=1111 1111 + 0000 0010 = 1 0000 0001 (можно записать в 32бит int)

    /**
     * Напишите, почему при сложении одинаковых значений (одинаковых в двоичной
     * системе) в строках (1) и (2) получаются разные результаты.
     *
     * Напишите явно преобразования, которые неявно выполняет компилятор и
     * объясните, что при этом происходит.
     */

    char c1 = 0xff, c2 = 2;
    unsigned char uc1 = 0xff, uc2 = 2;
    int iSum1 = c1 + c2;   //(1) c1 = 1111 1111, но из-за знака в дес системе это будет -1; -1+2=1
    int iSum2 = uc1 + uc2; //(2) c1 = 1111 1111, которое будет равно 255; 255+2=257

    
    /**
     * Задание 2b. Явное приведение типов данных.
     *
     * Проинтерпретируйте результат (значения переменной dDouble) в строке (3).
     *
     * Напишите явно преобразования, которые неявно выполняет компилятор.
     */

    int nTmp = 100, nn = 3;
    dDouble = 3.3 + nTmp / nn; // (3)расчеты производятся в порядке мат. операций 1) деление, но int(100) / int(3) = int(33) 2)сложение int(33)+double(3.3) = double(36.3)

    /**
     * Получите результат без потери точности с помощью оператора явного
     * приведения типа.
     */

     double dDouble3 = 3.3 + static_cast<double>(nTmp) / nn;    // (4)



    /**
     * Задание 3. Область действия, область видимости и время существования
     * переменных.
     *
     * В этом фрагменте фигурируют четыре переменных с одним и тем же именем
     * nTwin - одна глобальная, вторая определена в своем пространстве имен,
     * (определены выше в начале модуля) третья - локальная внутри функции
     * main(), четвертая - вложенная локальная внутри блока. 
     *
     * В данном задании требуется в выделенных местах фрагмента определить, к
     * какой из четырех переменных идет обращение, а также факт существования и
     * видимости для всех четырех, заполнив приведенные в задании таблицы.
     *
     * Для выведения информации в отладчике можно воспользоваться командой 
     * `info locals`, которая выведет локальные переменные в функции main(),
     * и командой `watch nTwin` или `wacth ::nTwin` для отслеживания значений
     * переменных.
     */

    nTwin = 100; //глобальная 1 -> 100
    TwinSpace::nTwin1 = 300; //в пространстве имен 2 -> 300
    nTwin++; //глобальная 100+1 -> 101

    int nTwin; // локальная внутри функции main()
    nTwin = 200;  // локальная внутри функции main() 0 -> 200
    ::nTwin++;  //глобальная 101+1 -> 102
    {
        int nTwin;
        nTwin = -1; // вложенная локальная внутри блока -1
        ::nTwin++; //глобальная 102+1 -> 103
        TwinSpace::nTwin1++; //в пространстве имен 300+1 -> 301
    }

    nTwin--; // локальная внутри функции main() 200 -1 -> 199
    TwinSpace::nTwin1++;

    /**
     * Задание 4. Спецификатор класса памяти - static.
     *
     * 1. Для каждой итерации цикла напишите значения пременных nLocal# и
     *    nStatic#.
     * 2. Напишите, когда выполняется инициализация обеих переменных.
     * 3. Поясните (в комментарии) разницу между способом инициализации
     *    переменных nStatic1 и nStatic2 и поясните побочный эффект, влияющий 
     *    на переменную nLocal2.
        nStatic1 nStatic2 nLocal1 nLocal2
        101      401       101      201
        102      402       101      200
        103      403       101      200
        инициалицация переменных nStatic производится лишь единожды, эти переменные записываются в статическую память.
        инициалицация переменных nLocal производится каждую итерацию цикла, эти переменные записываются в автоматическую память
        nStatic1 просто = 100, а nStatic2 = (nLocal2=200)*2=400, но в первую итерацию цикла также увеличивается на 1 значение nLocal2 из-за постфиксного инкремента
     */ 

    for (int i = 0; i < 3; i++)
    {
        static int nStatic1 = 100;
        int nLocal1 = 100;
        int nLocal2 = 200;
        static int nStatic2 = nLocal2++ * 2;
        nStatic1++;
        nStatic2++;
        nLocal1++;
    }

    /**
     * Напишите:
     * 1. как изменилось поведение пременной nStatic1?
     * 2. как эта переменная _инициализирована_?
     nStatic1 все еще единожды инициализирлована и записана в статическую память, но каждую итерацию цикла ей присваивается значение 100
     */

    for (int i = 0; i < 3; i++)
    {
        static int nStatic1;
        nStatic1 = 100;
        int nLocal1 = 100;
        nStatic1++;
        nLocal1++;
    }

    /**
     * Задание 5. Перечисления - enum.
     *
     * Обратите внимание на явную и неявную инициализацию констант. 
     *
     * Выполняя задание по шагам, следите за значениями, которые принимает
     * переменная myColors.
     */

    enum eColors
    {
        BLACK, 
        BLUE, 
        GREEN, 
        RED=5, 
        YELLOW, 
        WHITE=RED+4 
    };
    
    eColors myColors; //объявление переменной типа eColors 
    myColors = BLACK; //0
    myColors = BLUE; //1
    myColors = GREEN; //2
    myColors = RED; //5 
    myColors = YELLOW; //6
    myColors = WHITE; //9

    int nnn = BLACK; //любой целочисленной переменной можно присвоить
                     //значение из списка инициализирующих значений

    //Именованные константы можно использовать в выражениях:
    nnn = BLUE | YELLOW; //7

    /**
     * Раскомментируйте следующую строку и обратите внимание на ошибку при
     * компиляции.
     *
     * Модифицируйте выражение таким образом, чтобы компилятор не выдывал
     * ошибки.
     */

    myColors = static_cast<eColors>(1); 

    /**
     * Выполните следующее присваивание НЕ меняя перечисление и тип переменной
     * myColors.
     */

    myColors = static_cast<eColors>(123);


    /**
     * Задание 6.1 Логический тип bool.
     *
     * Выполняя задание по шагам, следите за значениями переменной b и
     * интерпретируйте результат. 
     *
     * Напишите эти значения в комментариях.
     */

    int nNumber = 1;
    bool b = (nNumber != 0); //true
    b = (nNumber == 0); //false
    b = (nNumber > 0); //true
    b = (nNumber > 1); //false
    b = 5; //true

    /**
     * Вы всегда можете преобразовать логическое значение к целому явно или
     * компилятор может это сделать самостоятельно (неявно).
     *
     * Обратите внимание: как интерпретирует значения логических переменных
     * компилятор?
     */

    int tmp =  b + 1; // b+1 = 1 + 1 = 2

    /**
     * Задание 6.2.
     *
     * В Григорианском календаре (которым мы все пользуемся) високосный год
     * определяется по следующему алгоритму: високосным является каждый
     * четвертый год, но каждый сотый високосным не является, при этом каждый
     * 400-й год все таки високосный. Т.е. 1823 - не високосный, 1824 -
     * високосный, 1900 - не високосный, 2000 - високосный.
     *
     * Напишите фрагмент кода, такой что логическая переменная isLeapYear
     * принимает значение true, если год, заданный переменной year -
     * високосный. Проверьте значение в отладчике.
     *
     * Указание: в этом задании нельзя использовать операторы if-else, switch и
     * тернарный оператор; необходимо написать логическое выражение в одну
     * строку.
     */

    {
        //int year = 1823;
        //int year = 1824;
        //int year = 1900;
        int year = 2000;

        bool isLeapYear = (year%400==0) || ((year%4==0)&&(year%100!=0));
        //year = 2;
    }

    /**
     * Задание 7. Модификатор const и переменные.
     *
     * Раскомментируйте следующие две строчки и объясните (в комментариях)
     * ошибки при компиляции.
     */

    {
        //  const int nN; // при инициализации переменных с ключевым const всегда необходимо указывать их значение
        //  nN = 1; // при попытке изменить значение переменных с ключевым const возникает ошибка
    }

    /**
     * Задание 8. Потоки ввода и вывода C++.
     *
     * Напишите фрагмент кода, который бы с помощью объектов потока std::cin и
     * std::cout делал бы следующее:
     *
     * 1. Выводил бы на экран номер задания.
     * 2. Считывал целое число.
     * 3. Считывал символ.
     * 4. Выводил пользователю введенный им символ.
     * 5. Выводил пользователю введенное им целое число.
     *
     * При этом добавьте в места, где от пользователя ожидается ввод,
     * соответствующие приглашения ко вводу (например, `Введите целое число: `). 
     */

    {
        //std::cout << "Задание 8" << std::endl;
        int inputInt;
        char inputChar;
        //std::cout << "Введите целое число: ";
        //std::cin >> inputInt;
        //std::cout << std::endl << "Введите символ: ";
        //std::cin >> inputChar;
        //std::cout << std::endl << inputInt << std::endl;
        //std::cout << inputChar << std::endl;
    }

    /**
     * Задание 9. Логические условные операторы и операторы отношения.
     */

    /**
     * Задание 9.1. 
     *
     * Напишите фрагмент кода, который переводит код символа, хранящийся в
     * переменной ch в противоположный регистр.
     *
     * Требуется предусмотреть проверку ситуации, когда пользователь ввел цифру
     * или нажал другую клавишу, которой символ не соответствует.
     *
     * Подсказка: работаем только с символами английского алфавита, для
     * которого в таблице кодов ASCII код каждой буквы нижнего регистра на 0x20
     * больше кода соответствующей буквы верхнего регистра.
     */

    {
        char ch;
        /** Тут сформируйте значение переменной ch с помощью потока ввода. */     //Проверка на ввод
        std::cout<< std::endl;
        std::cin >> ch;
        /** Тут измените регистр. */
        if ((isalpha(ch)) && (std::cin.peek() == '\n')){
            if (65 <= ch && ch <= 90){ 
                ch += 0x20;
                std::cout<< ch;
            }
            else if (97 <= ch && ch <= 122){
                ch -= 0x20;
                std::cout<< ch;
            }
        }
        else{
                std::cout << "Некорректный ввод";
            }
    }

    /**
     * Задание 9.2. 
     *
     * Напишите фрагмент кода, который реализует с помощью if (if/else)
     * следующую логику: если x меньше или равен 0, y=0, если x больше 0 но
     * меньше 1, то y=x, если x больше или равен 1, то y=1.
     *
     * Подумайте: какого типа должны или могут быть x и y?
     */
    
    {
        float x=2, y=0;     //убрать &&
        if (x<=0){y=0;}
        else if (x>=1){y=1;} 
        else{y=x;} 
    }

    /**
     * Задание 9.3 
     *
     * Напишите фрагмент кода, который реализует с помощью switch следующую
     * логику: в переменной cInput типа char дано значение символа, введенного
     * любым способом.
     *
     * Если введен символ 'y' (т.е. yes) в любом регистре, то присвоить
     * переменной у значение переменной x.
     *
     * Если введен символ 'n' (т.е. no) в любом регистре, то присвоить
     * переменной у значение (x * 2).
     *
     * Если любой другой симол, то вывести сообщение об ошибке.
     */

    {
        char ch, cInput;
        int x=2, y=0;
        //std::cin >> cInput;    //case Для N и Y
        switch(cInput){
            case 'y': 
            case 'Y': 
                y = x;
                break;
            case 'n': 
            case 'N': 
                x*=2;
                break;
            default: std::cout<< "Error";

        }

    }

    /**
     * Задание 10. Циклы.
     */

    /**
     * Задание 10.1.
     *
     * Напишите фрагмент кода, который реализует с помощью for следующую
     * логику: найти сумму заданного диапазона целых чисел.
     *
     * Введите границы с помощью потока ввода или с помощью средств отладки. 
     *
     * Предусмотрите защиту от ввода нижней границы больше, чем верхней.
     */

    {
        /** сформироыать границы диапазона */
        int diap1, diap2, summ;
        //std::cin >> diap1 >> diap2;
        /** проверить корректность значений */
        if(diap1<diap2){                              //else с тем что неправильный диапазон
        /** вычислить сумму */
            for(diap1; diap1<=diap2; diap1++){
                summ+=diap1;
            }
        }
        else{std::cout<<"Неверно заданы границы диапазона";}
        /** проверить в отладчике значение */
        //std::cout << summ;
    }

    /**
     * Задание 10.2. 
     *
     * Напишите фрагмент кода, который реализует с помощью do-while следующую
     * логику: на каждой итерации цикла ввести с консоли целое значение и
     * покинуть цикл, если значение удовлетворяет условию: значение больше или
     * равно 10 и четное.
     */

    {
        int zn;
        do{
            std::cin>>zn;
        }
        while (not(zn>=10 && zn%2==0));   //рассказать разницу not и ! -> никакой, not ввели для повышения читабельности кода
        
    }

    /**
     * Задание 10.3. 
     *
     * Напишите фрагмент кода, который реализует с помощью while следующую логику: 
     *
     * 1. исходно int x = 0; 
     * 2. на каждой итерации x = x + 1, sum = sum + 1 / x;
     * 3. необходимо найти значение x, при котором sum > 1.7.
     */

    {
        int x = 0;
        float sum = 0;
        while (sum < 1.7){
            x = x + 1;
            sum = sum + 1 / static_cast<float>(x);
        }
        //std::cout<<x;
    }

    /**
     * Задание 10.4.
     *
     * Раскомментируйте следующий блок кода, который считает сумму 10
     * последовательных натуральных чисел, начиная со 120. 
     *
     * Объясните логические ошибки в нем и исправьте их.
     */

    {
        int start = 120, sum = 0;
        for (int n = start; n < start + 10; ++n) {
            sum += n;
        }
    }
    
    return 0; /** код завершения приложения */
}
