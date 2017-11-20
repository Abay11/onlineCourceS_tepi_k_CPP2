/*
//
// Created by adygha on 11/20/17.
//


Какие из следующих реализаций класса ElementN будут работать корректно, т.е. объекты такого класса можно будет неоднократно использовать для удаления элементов последовательности при помощи алгоритма remove_if.

// 1
struct ElementN
{
    explicit ElementN(size_t n)
            : n(n), i(0)
    {}

    template<class T>
    bool operator()(T const& t) { return (i++ == n); }

    size_t n;
    size_t i;
};

//2
struct ElementN
{
    explicit ElementN(size_t n)
            : n(n)
    {}

    template<class T>
    bool operator()(T const& t) { return (i++ == n); }

    size_t n;
    static size_t i;
};

size_t ElementN::i = 0;

// 3
struct ElementN
{
    explicit ElementN(size_t n)
            : n(n), pi(new size_t(0))
    {}

    template<class T>
    bool operator()(T const& t) { return ((*pi)++ == n); }

    ~ElementN() { delete pi; }

    size_t n;
    size_t * pi;
};

// 4
struct ElementN
{
    explicit ElementN(size_t n)
            : n(n), pi(new size_t(0))
    {}

    template<class T>
    bool operator()(T const& t) { return ((*pi)++ == n); }

    size_t n;
    std::shared_ptr<size_t> pi;
};

// 5
struct ElementN
{
    explicit ElementN(size_t n)
            : n(n), pi(new size_t(0))
    {}

    template<class T>
    bool operator()(T const& t) { return ((*pi)++ == n); }

    size_t n;
    std::unique_ptr<size_t> pi;
};

// 6
struct ElementN
{
    explicit ElementN(size_t n)
            : n(n)
    {}

    template<class T>
    bool operator()(T const& t)
    {
        static size_t i = 0;
        return (i++ == n);
    }

    size_t n;
};

См. объяснение к предыдущему тесту.
Переменная i общая для всех объектов и не обнуляется. Такой объект можно использовать только однажды.
Приводит к двойному удалению при копировании, т.к. не переопределён конструктор копирования.
+Работает корректно, т.к. shared_ptr можно копировать и это обеспечивает общий счётчик для всех копий исходного объекта.
Не копируется, а только перемещается. При перемещении указатель забирается, а значит в коде из предыдущего теста мы бы получили обращение по нулевому указателю.
Аналогично п.2.
*/
