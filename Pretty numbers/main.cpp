#include <string>
#include <iostream>
#include <vector>
#include <numeric>

/// <summary>
/// The program is used for calculating the amount of all possible "pretty" numbers in BaseN number system (up to Base16 system)
/// amount of "pretty" numbers -- the sum of all digits in left number part is equal to its right counterpart, i.e. 59186, 77123695501, 2446550...
/// </summary>
/// <param name="baseN"></param>
/// <returns></returns>


std::string toBase(int number, int base)
{
    std::string bases = "0123456789ABCDEF"; // can handle up to Base16 system
    std::string result = "";

    while (number > 0)
    {
        result = bases[number % base] + result;
        number /= base;
    }
    return result;
}

std::vector<std::string> ToBaseVec(std::vector<int> vInts, int base)
{
    std::vector<std::string> ddd;
    for (auto const& v : vInts)
        ddd.push_back(toBase(v, base));
    return ddd;
}


std::vector<int> CreateNewMagnituteVector(std::vector<int> MagVector, int increm, int inceptionLevel) // input -- Base10, output -- Base10; increm -- used in formalizing (for Base10 -- 9, for Base13 -- 12)
                                                                                                      // inceptionLevel -- amount of recursions of the function. 0 recursions is allowed
{
    std::vector<int> formalizer(increm, 0); // Used for additing zeroes to both beginning and ending
    std::vector<int> newVector;
    newVector.reserve(MagVector.capacity() + increm); // capacity of a new vector is BaseSystem-1 greater

    MagVector.insert(MagVector.begin(), formalizer.begin(), formalizer.end()); // adding zeroes, so that accumulator will always have a certain range
    MagVector.insert(MagVector.end(), formalizer.begin(), formalizer.end());
    int j = 0; // нижн€€ граница суммы, элемент управлени€
    int k = increm + 1; // верхн€€ граница суммы, элемент управлени€
    for (size_t i = 0; i < newVector.capacity(); i++) // создаЄм новый вектор индексов
    {
        newVector.push_back(std::accumulate(MagVector.begin() + j, MagVector.begin() + k, 0));
        j++;
        k++;
    }
    if (inceptionLevel == 0)
        return newVector;
    else
    {
        inceptionLevel--;
        return CreateNewMagnituteVector(newVector, increm, inceptionLevel);
    }
}


int main()
{
    int BaseSystem = 0;
    int inceptionLevel = 0; // used as a recursion factor. It defines the magnitute of formalized numbers, i.e. 1: 00000-99999; 2: 000000-999999; 3: 0000000-9999999 (all the examples are for Base10)
    std::cout << "input base system number" << std::endl;
    std::cin >> BaseSystem;
    std::cout << "input inception level" << std::endl;
    std::cin >> inceptionLevel;
    std::cout << std::endl;

    std::vector<int> M1Vector(BaseSystem, 1); // provided we have a fixed second digit, every number in magnitute 3 numbers will have only 1 its counterpart, i.e. 212, 919, 818

    std::vector<int> MNVector10 = CreateNewMagnituteVector(M1Vector, BaseSystem - 1, inceptionLevel); // 12 дл€ base13, 9 дл€ base10; 4 -- количество рекурсий дл€ получени€ индексов 13 значных чисел

    std::vector<std::string> M1VectorAnother = ToBaseVec(MNVector10, BaseSystem);
    for (auto const& v : M1VectorAnother)
        std::cout << v << std::endl;

    long long int answer = 0; // amount of "pretty" numbers in any base system
    std::vector<long long int> Squared; // вектор дл€ квадратов индексов
    for (auto const& vi : MNVector10)
    {
        Squared.push_back(pow(vi, 2));
    }

    answer = std::accumulate(std::begin(Squared), std::end(Squared), 0LL);

    answer *= BaseSystem; // takes in account every "fixed digit" number, not some random from base system
    std::cout << answer << std::endl;

    return 0;
}