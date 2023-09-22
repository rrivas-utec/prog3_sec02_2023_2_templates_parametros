#include <iostream>
#include <vector>
#include <list>
const int MAX_SIZE = 100;

/*
int sumar(int a, int b) {
    return a + b;
}
*/

template <int a, int b>
constexpr int sumar() {
    return a + b;       // en tiempo
}

template <int a, int b>
struct Sumar {
    static constexpr int value = a + b;
};

void result1() {
    const int z = 10, w = 40; // instancian al momento de compilar
    auto r2 = sumar<z, w>();
    //auto r3 = Sumar<z, w>::value;

}

void result2() {
    const int z = 10, w = 40; // instancian al momento de compilar
    //auto r2 = sumar<z, w>();
    auto r3 = Sumar<z, w>::value;

}

//----------------------

template<bool condition, typename T1, typename T2>
struct meta_if {
    using type = T1;
};

template<typename T1, typename T2>
struct meta_if<false, T1, T2> {
    using type = T2;
};

void ejemplo_metaprogramacion() {
    using Type = meta_if<(MAX_SIZE > 100), double, float>::type;
    Type x = 10;

}

//----------------------

// Version 17
constexpr int factorial(int n) {
    return n == 0? 1: n * factorial(n-1);
}

template< int n>
struct Factorial {
    static constexpr int value = n * Factorial<n - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

void ejemplo_operaciones_matematicas() {
    std::cout << factorial(5) << std::endl;
    std::cout << Factorial<5>::value << std::endl;
}

//----------------------

template <typename T, size_t sz>
size_t get_size(T (&)[sz]) {
    return sz;
}

void ejemplo_tamano_arreglo_estatico() {
    int arr[] = {1, 3, 4, 5, 6, 7};
    std::cout << get_size(arr) << std::endl;
}

//----------------------
// vector<int>

template <typename Container, typename T = typename Container::value_type>
T maximo(Container contenedor) {
    T result{};
    for (const auto& item: contenedor) {
        if (item > result)
            result = item;
    }
    return result;
}
template <template<typename...> typename TemplateContainer, typename T>
T maximo2(TemplateContainer<T> contenedor) {
    T result{};
    for (const auto& item: contenedor) {
        if (item > result)
            result = item;
    }
    return result;
}
void ejemplo_template_template() {
    std::vector v = {10, 20, 30, 4, 100, 5};
    auto max1 = maximo(v);
    std::list l = {10.5, 20.5, 30.3, 4.2, 100.5, 5.4};
    auto max2 = maximo(l);
    std::vector v2 = {10.5, 20.5};
    auto max3 = maximo2<std::vector>(v);
    auto max4 = maximo2<std::vector>(v2);

}

//----------------------

template <template<typename ...> typename TemplateContainer, typename T>
TemplateContainer<T> make_container(int first, int last, int step) {
    TemplateContainer<T> result;
    for (int i = first; i <= last; i += step) {
        result.push_back(i);
    }
    return result;
}

template <typename Container, typename T = typename Container::value_type>
Container make_container2(int first, int last, int step) {
    Container result;
    for (int i = first; i <= last; i += step) {
        result.push_back(i);
    }
    return result;
}
void ejemplo_crear_container() {
    auto c1 = make_container<std::vector, int>(10, 40, 2);
    auto c2 = make_container2<std::vector<int>>(10, 40, 2);

}


int main() {
//    ejemplo_operaciones_matematicas();
    ejemplo_tamano_arreglo_estatico();
    return 0;
}
