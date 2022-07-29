#include <iostream>
#include <set>
#include <map>

int main()
{
    std::set<int> odds{ 1, 7, 5, 3, 9 };
    std::set<int, std::greater<>> evens{ 2, 4, 6, 8 };
    evens.insert(10);
    evens.insert(2);

    if (evens.find(4) != evens.end())
    {
        std::cout << "4 is found!" << std::endl;
    }
    else
    {
        std::cout << "4 is not found!" << std::endl;
    }

    for (auto& n : odds)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    for (auto& n : evens)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    using psi = std::pair<std::string, int>;
    std::set<psi> managers{ {"Amelia", 29}, {"Noah", 25}, {"Olivia", 31}, {"Sophia", 40} };
    managers.insert({ "George", 35 });

    psi person1 = { "Noah", 25 };

    if (managers.find(person1) != managers.end())
    {
        std::cout << person1.first << " is a manager!" << std::endl;
    }
    else
    {
        std::cout << person1.first << " is not a manager!" << std::endl;
    }

    managers.erase({ "Sophia", 40 });
    managers.erase({ "Noah", 40 });

    for (auto& m : managers)
    {
        std::cout << m.first << "(" << m.second << ")" << std::endl;
    }

    std::map<std::string, int> fruits;
    fruits.insert({ "apple", 1000 });
    fruits.insert({ "banana", 1500 });
    fruits["orange"] = 3000;
    fruits["grape"] = 4000;
    fruits["lemon"] = 5000;

    fruits["apple"] = 2000;
    fruits.erase("grape");

    std::cout << fruits["apple"] << std::endl;

    for (auto& p : fruits)
    {
        std::cout << p.first << " is " << p.second << " won." << std::endl;
    }

    return 0;
}