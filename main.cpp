#include <iostream>
#include <list>
#include <string>
#include <stdio.h>

#include "graph.h"


int main()
{

    size_t noV;

    std::cin >> noV;

    Graph graph(noV);

    size_t a,b;

    while(!std::cin.eof())
    {
        std::cin >> a;
        std::cin >> b;

        graph.addPair(a, b);
    }

    graph.findBridgesAndPrint();


    return 0;
}