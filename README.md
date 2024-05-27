# Text_editor
**What is structural programming paradigm?**
         <p>Структуроване програмування — це парадигма програмування , спрямована на підвищення чіткості, якості та часу розробки комп’ютерної програми шляхом широкого використання конструкцій структурованого потоку керування вибору ( if/then/else ) і повторення ( while і for ), блокових структур і підпрограми. </p>
 **What is procedural programming paradigm?** 
 <p>Процедурна парадигма програмування - це підхід до розробки програм, у якому програма складається з набору процедур або функцій, які виконують конкретні завдання. Основна ідея полягає в тому, щоб розбити велику задачу на більш маленькі, добре визначені процедури, які можна легко керувати та перевикористовувати. </p>

<p>Основні характеристики процедурного програмування:

 - Процедури або функції: Програма складається з набору процедур або функцій, які виконують конкретні завдання. Ці функції можуть приймати аргументи, обробляти їх та повертати результати.

 - Змінні: Змінні використовуються для зберігання та обробки даних у програмі. Вони можуть бути глобальними або локальними для конкретних процедур.

 - Керування потоком: У процедурному програмуванні використовуються структури управління потоком, такі як умовні оператори (if-else), цикли (for, while) та складні конструкції (switch-case), для керування виконанням програми.

 - Декомпозиція: Великі задачі розбиваються на менші підзадачі, які реалізуються в окремих процедурах. Це дозволяє спростити розробку, зробити код більш структурованим та легшим для розуміння.

 - Підтримка підпрограм: Процедурна парадигма підтримує концепцію підпрограм, яка дозволяє використовувати та перевикористовувати фрагменти коду в різних частинах програми.
   </p>
**Which primitive data types do you know? Key differences between them?**
<p>Існує кілька примітивних типів даних у багатьох мовах програмування, таких як цілі числа, дійсні числа, символи і булеві значення. Ось кілька основних примітивних типів даних та їх ключові відмінності:

- Цілі числа (Integer):

Це цілі числа без десяткової частини.
Зазвичай використовуються для представлення кількості об'єктів або позицій у пам'яті.
Приклади: int (ціле число зі знаком), unsigned int (ціле число без знаку), short, long тощо.
- Дійсні числа (Floating Point):

Це числа з десятковою частинею, яка може бути дробовою.
Використовується для представлення значень з десятковою точністю.
Приклади: float (одинарна точність), double (подвійна точність), long double (розширена точність).
- Символи (Character):

Представляють один символ, такий як літера, цифра або спеціальний символ.
Використовується для роботи зі знаками в текстових рядках.
Приклади: char.
- Булеві значення (Boolean):

Мають два можливих значення: true (істина) або false (хиба).
Використовується для умовних виразів та логічних операцій.
Приклади: bool.</p>
**Which segments does the process memory have?**
<p>Пам'ять процесу має кілька сегментів, включаючи:

- Segment for Code (Segment коду): Цей сегмент містить виконуваний код програми. Це може бути інструкційний код, написаний у мові програмування, такий як С, C++, Java тощо.

- Data Segment (Сегмент даних): У цьому сегменті зберігаються глобальні змінні та статичні змінні, а також змінні, які ініціалізуються до значень в програмі.

- Stack Segment (Стековий сегмент): Стек використовується для зберігання локальних змінних, аргументів функцій, адрес повернення та іншої інформації виклику функцій.

- Heap Segment (Сегмент купи): Це область пам'яті, яка використовується для динамічного виділення пам'яті за допомогою функцій, таких як malloc() чи new. В цьому сегменті можуть бути виділені об'єкти та дані під час виконання програми.

Крім цих основних сегментів, є також інші, такі як сегменти для різноманітних системних ресурсів, які можуть бути присутні в залежності від операційної системи та конкретної реалізації процесу.</p>
**What is the virtual memory space?**
<p>Простір віртуальної пам'яті - це абстрактне поняття, що використовується операційними системами для управління доступом до фізичної пам'яті комп'ютера. Кожен процес в операційній системі має свій власний віртуальний адресний простір, який починається з нуля і може бути розділений на декілька сегментів, таких як код, дані та стек.

Віртуальна пам'ять дозволяє кожному процесу відчувати, що він має доступ до власного простору адрес, незалежно від того, як фактично використовується фізична пам'ять. Операційна система відповідає за те, щоб відображати віртуальний адресний простір кожного процесу на фізичну пам'ять або файлову систему за необхідності. Це дозволяє керувати обсягом пам'яті, яка використовується кожним процесом, і забезпечує ізоляцію між різними процесами.</p>
**How to allocate the memory in each segment?**
         <p>Для виділення пам'яті у кожному сегменті можна використовувати функції виділення пам'яті, такі як malloc(), calloc() або realloc(). Ці функції дозволяють виділяти блоки пам'яті потрібного розміру. Наприклад:
                  <p> - int *segment1 = (int *)malloc(sizeof(int) * segment1_size);</p>
                  <p> - char *segment2 = (char *)calloc(segment2_size, sizeof(char));</p>
**How to reallocate the memory in case we don’t have enough space?**
         <p>Якщо нам не вистачає простору, то для перерозподілу пам'яті ми можемо використовувати функцію realloc(). Вона дозволяє змінити розмір блоку пам'яті, який був виділений раніше за допомогою malloc(), calloc() або realloc(). Якщо вільна пам'ять поряд з блоком, який ми хочемо розширити, не вистачає, realloc() може виділити новий блок пам'яті, скопіювати дані зі старого блоку та вивести старий блок з експлуатації.</p>
**What is a runtime stack?**
          <p>Стек часу виконання (runtime stack) - це структура даних, що використовується в комп'ютерних програмах для зберігання контексту виконання кожного окремого потоку виконання програми під час її виконання. Цей стек зазвичай зберігає інформацію про виклик функцій, змінні, параметри, адреси повернення та інші важливі дані, необхідні для керування виконанням програми.  
          Основними аспектами стеку є те,що коден виклик функції породжує новий стековий кадр, який містить дані, що відносяться до цього виклику функції. Ці кадри утворюють ланцюг викликів, який може розгортатися та згортатися під час виконання програми. Коли функція завершує свою роботу, її стековий кадр вилучається зі стеку, і керування повертається до попереднього виклику функції. Стек також використовується для зберігання локальних змінних, параметрів функцій та інших даних, що стосуються кожного окремого виклику функції. Стек часу виконання дозволяє реалізувати рекурсивні виклики функцій, де функція може викликати сама себе. А також, надмірна рекурсія або велика кількість вкладених викликів функцій може призвести до переповнення стеку, коли стекові кадри вичерпують доступний обсяг пам'яті.</p>
