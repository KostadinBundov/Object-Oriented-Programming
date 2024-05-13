#include "Dictionary.h"
#include <iostream>

int main() 
{
    try 
    {
        Dictionary dict;

        dict.add("carrot", "A root vegetable that is orange and crunchy");
        dict.add("banana", "A yellow fruit that is long and soft");
        dict.add("apple", "A fruit that is sweet and crisp");

        dict.print();

        Dictionary copyDict(dict);
        std::cout << "After copying dictionary:" << std::endl;
        copyDict.print();

        Dictionary movedDict(std::move(copyDict));
        std::cout << "After moving dictionary:" << std::endl;
        movedDict.print();

        std::cout << "Description of 'apple': " << dict("apple") << std::endl;

        dict.remove("apple", "A fruit that is sweet and crisp");
        std::cout << "After removing 'apple':" << std::endl;
        dict.print();

        Dictionary newDict;
        newDict.add("dog", "A domestic animal that barks");
        Dictionary combined = dict + newDict;
        std::cout << "Combined Dictionary:" << std::endl;
        combined.print();

    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }
}
