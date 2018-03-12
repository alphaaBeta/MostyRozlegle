#pragma once

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

class Graph
{
public:

    //reserves space for array of lists of given size
    explicit Graph(size_t size) : listArray(new std::list<size_t>[size]), vertices(size)//, edges(0)
    {
        
    }


    //Add a connection between a pair of vertices
    void addPair(size_t a, size_t b)
    {
        listArray[a].push_back(b);
        listArray[b].push_back(a);
        
        //++edges;
    }


    bool meetsConditions()
    {

        if(vertices < 3)
            return false;
        

        //bool *wasHere = new bool[vertices];
        bool wasHere[vertices];

        for(size_t i = 0; i < vertices; ++i)
        {
            wasHere[i] = false;
        }

        colourCheck(0, wasHere);

        for(size_t i = 0; i < vertices; ++i)
        {
            if(!wasHere[i])
            {
                return false;
            }
        }

        return true;
    }



    //Take vertices that were removed
    bool isConnectedAdv(size_t a, size_t b)
    {

        //Create an auxiliary array to check if graph is connected
        bool wasHere[vertices];
        
        for(size_t i = 0; i < vertices; ++i)
        {
            wasHere[i] = false;
        }

        //Those vertices don't matter for graph connectivity
        wasHere[a] = true;
        wasHere[b] = true;

        //3 is enough; basically find first vertice that's not disabled
        for(size_t i = 0; i < 3; ++i)
        {
            if(i != a && i != b)//if i is not one of disabled vertices, start colouring from it
            {
                colourCheck(i, wasHere);

                for(size_t j = 0; j < vertices; ++j)
                {
                    if(!wasHere[j])
                    {
                        return false;
                    }
                }

                return true;
            }
        }

        return true;
    }


    //sets the wasHere array, for check. If graph is disconnected, wasHere will have at least one `false`
    //otherwise, it will have only `true`
    void colourCheck(size_t i, bool *wasHere) 
    {
        wasHere[i] = true;
        for(auto it = listArray[i].begin(); it != listArray[i].end(); ++it)
        {
            //invoke itself if the vertice `i` is connected with has not been visited yet
            //`a` and `b` is set as `wasHere`! - this won't enter those vertices
            if( (!(wasHere[*it])) )
            {
                colourCheck(*it, wasHere);
            }
        }
    }



    void findBridgesAndPrint()
    {

        if(!meetsConditions())
            return;


        

        for(size_t i = 0; i < vertices; ++i)
        {

            if(listArray[i].empty())
                continue;
            

            for(auto it = listArray[i].begin(); it != listArray[i].end(); ++it)
            {
                //to avoid checking pairs we've alredy checked:
                if( (*it) < i )
                    continue;

                //a<b
                size_t a,b;
                a = i;
                b = *it;

                // //Now we check connectivity without those vertices
                if(!isConnectedAdv(a, b))
                    std::cout << a << " " << b <<std::endl;
                    
                    
                


                
            }
        }

        
    }

private:

    Graph();
    std::list<size_t> *listArray;
    size_t vertices;//, edges;

};
