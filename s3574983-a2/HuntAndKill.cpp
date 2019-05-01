//
//  HuntAndKill.cpp
//  s3574983-a2
//
//  Created by Tuan Le on 4/30/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "HuntAndKill.hpp"

vector<Edge> HuntAndKill::generate() {
    //    create an array to monitize visited cells
    long seed = getSeed();
    int height = getHeight();
    int width = getWidth();
    bool withSeed = isWithSeed();
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }
    
    //    for (int n = 0; n < height; ++n) {
    //        for (int i = 0; i < width; ++i) {
    //            cout << n << i << " ";
    //        }
    //        cout << endl;
    //    }
    
    
    //    create vector to store edges
    vector<Edge> edges;
    //    check user input seed
    if (!withSeed) {
        seed = time(0);
#warning fix to print out the seed
//        cout << "Your seed is " << seed << endl;
    }
    srand((int) seed);
    
    bool keepHunting = true;
    bool keepKilling = true;
    
    //    generate a random stating cell
    Coordinator startingCell;
    startingCell.setX(rand() % height);
    startingCell.setY(rand() % width);
    //    flag it as visited
    visitedArray[startingCell.getX()][startingCell.getY()] = true;
    //    bool starting = true;
    
    
    //    loop as hunting continuously
    while (keepHunting) {
        //        for(int i=0;i < height;i++) {
        //            for(int j=0;j < width;j++) {
        //                if (!visitedArray[i][j]) {
        //                    keepKilling = true;
        //                    break;
        //                } else {
        //                    keepKilling = false;
        //                }
        //            }
        //        }
        //        check if whe need to killing
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[j][i]) {
                    keepKilling = true;
                    break;
                } else {
                    keepKilling = false;
                }
            }
            if (keepKilling) {
                break;
            }
        }
        //        loop as killing continuously
        while (keepKilling) {
            //            if (starting) {
            //                int numberOfNeighbours = 0;
            
            //                create a vector to store neighbour cell
            vector<Coordinator> neighbours;
            //                neighbours.clear();
            
            //                looking for neighbours
            
            //                bool hasTop = false;
            if (startingCell.getX() - 1 > -1) {
                Coordinator topCell;
                topCell.setX(startingCell.getX() - 1);
                topCell.setY(startingCell.getY());
                neighbours.push_back(topCell);
                //                    hasTop = true;
                //                    numberOfNeighbours++;
            }
            
            //                bool hasRight = false;
            if (startingCell.getY() + 1 < width) {
                Coordinator rightCell;
                rightCell.setX(startingCell.getX());
                rightCell.setY(startingCell.getY() + 1);
                neighbours.push_back(rightCell);
                //                    hasRight = true;
                //                    numberOfNeighbours++;
            }
            
            //                bool hasBottom = false;
            if (startingCell.getX() + 1 < height) {
                Coordinator bottomCell;
                bottomCell.setX(startingCell.getX() + 1);
                bottomCell.setY(startingCell.getY());
                neighbours.push_back(bottomCell);
                //                    hasBottom = true;
                //                    numberOfNeighbours++;
            }
            
            //                bool hasLeft = false;
            if (startingCell.getY() - 1 > -1) {
                Coordinator leftCell;
                leftCell.setX(startingCell.getX());
                leftCell.setY(startingCell.getY() - 1);
                neighbours.push_back(leftCell);
                //                    hasLeft = true;
                //                    numberOfNeighbours++;
            }
            
            //                create vector to store checked neighbours randomly
            vector<int> randomizedNeighbours;
            //                randomizedNeighbours.clear();
            //                coordinator nextCell;
            
            //                loop to check all neighbours randomly to find a not visited neighbour
            bool keepSeeking = true;
            while (keepSeeking) {
                int currentRandom = rand() % neighbours.size();
                bool addingRandom = true;
                //                    check if randomized neighbour is checked or not
                for (int i = 0; i < randomizedNeighbours.size(); ++i) {
                    if (randomizedNeighbours[i] == currentRandom) {
                        addingRandom = false;
                        break;
                    }
                }
                //                    if not checked, add to checked vector
                if (addingRandom) {
                    randomizedNeighbours.push_back(currentRandom);
                    Coordinator neighbour = neighbours[currentRandom];
                    //                        check if not visited
                    if (!visitedArray[neighbour.getX()][neighbour.getY()]) {
                        keepSeeking = false;
                        //                            mark as visited
                        visitedArray[neighbour.getX()][neighbour.getY()] = true;
                        //                            add edge
                        Edge edge1;
                        edge1.setCoordinator1(startingCell);
                        edge1.setCoordinator2(neighbour);
                        edges.push_back(edge1);
                        startingCell.setX(neighbour.getX());
                        startingCell.setY(neighbour.getY());
#warning fix to print notification
//                        printLineWith("killed");
                    }
                } else {
                    //                        else check if the neighbours vector is all checked
                    if (randomizedNeighbours.size() == neighbours.size()) {
                        keepSeeking = false;
                        keepKilling = false;
                    }
                }
            }
            //            }
        }
        
        //        hunting
        bool foundStarting = false;
        //        loop from left to right, top to bottom to find unvisited cell
        for (int k = 0; k < height; ++k) {
            for (int i = 0; i < width; ++i) {
                //                if unvisited step into an check
                if (!visitedArray[k][i]) {
                    //                    assume it has a least one
                    startingCell.setX(k);
                    startingCell.setY(i);
                    
                    //                    create a vector to store neighbour cell
                    vector<Coordinator> neighbours;
                    //                    neighbours.clear();
                    
                    //                bool hasTop = false;
                    if (startingCell.getX() - 1 > -1) {
                        Coordinator topCell;
                        topCell.setX(startingCell.getX() - 1);
                        topCell.setY(startingCell.getY());
                        neighbours.push_back(topCell);
                        //                    hasTop = true;
                        //                    numberOfNeighbours++;
                    }
                    
                    //                bool hasRight = false;
                    if (startingCell.getY() + 1 < width) {
                        Coordinator rightCell;
                        rightCell.setX(startingCell.getX());
                        rightCell.setY(startingCell.getY() + 1);
                        neighbours.push_back(rightCell);
                        //                    hasRight = true;
                        //                    numberOfNeighbours++;
                    }
                    
                    //                bool hasBottom = false;
                    if (startingCell.getX() + 1 < height) {
                        Coordinator bottomCell;
                        bottomCell.setX(startingCell.getX() + 1);
                        bottomCell.setY(startingCell.getY());
                        neighbours.push_back(bottomCell);
                        //                    hasBottom = true;
                        //                    numberOfNeighbours++;
                    }
                    
                    //                bool hasLeft = false;
                    if (startingCell.getY() - 1 > -1) {
                        Coordinator leftCell;
                        leftCell.setX(startingCell.getX());
                        leftCell.setY(startingCell.getY() - 1);
                        neighbours.push_back(leftCell);
                        //                    hasLeft = true;
                        //                    numberOfNeighbours++;
                    }
                    //                    check if any neighbour is visited, if not break to find the next cel
                    for (int j = 0; j < neighbours.size(); ++j) {
                        Coordinator neighbour = neighbours[j];
                        if (visitedArray[neighbour.getX()][neighbour.getY()]) {
                            foundStarting = true;
                            break;
                        }
                    }
                    //                    if any neighbour is visited
                    if (foundStarting) {
                        //                        create a checked neighbours vector
                        vector<int> randomizedNeighbours;
                        //                        randomizedNeighbours.clear();
                        
                        //                        loop to randomized through neighbours vector
                        bool keepSeeking = true;
                        while (keepSeeking) {
                            int currentRandom = rand() % neighbours.size();
                            bool addingRandom = true;
                            //                            check if randomized neighbour is checked or not
                            for (int m = 0; m < randomizedNeighbours.size(); ++m) {
                                if (randomizedNeighbours[m] == currentRandom) {
                                    addingRandom = false;
                                    break;
                                }
                            }
                            //                            if not checked, add to checked vector
                            if (addingRandom) {
                                randomizedNeighbours.push_back(currentRandom);
                                Coordinator neighbour = neighbours[currentRandom];
                                //                                check if visited
                                if (visitedArray[neighbour.getX()][neighbour.getY()]) {
                                    keepSeeking = false;
                                    //                                    mark the starting cell is visisted
                                    visitedArray[startingCell.getX()][startingCell.getY()] = true;
                                    //                                    add edge
                                    Edge edge1;
                                    edge1.setCoordinator1(startingCell);
                                    edge1.setCoordinator2(neighbour);
                                    edges.push_back(edge1);
#warning fix to print out notification
//                                    printLineWith("hunted");
                                }
                            } else {
                                //                                else check if the neighbours vector is all checked
                                if (randomizedNeighbours.size() == neighbours.size()) {
                                    keepSeeking = false;
                                    foundStarting = false;
                                }
                            }
                        }
                    }
                    if (foundStarting) {
                        break;
                    }
                }
            }
            if (foundStarting) {
                break;
            }
        }
        //        check if need hunting
        for (int l = 0; l < height; ++l) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[l][i]) {
                    keepHunting = true;
                    break;
                } else {
                    keepHunting = false;
                }
            }
            if (keepHunting) {
                break;
            }
        }
    }
    
    //    print edges
    for (int n = 0; n < edges.size(); ++n) {
        Edge edge1 = edges[n];
#warning fix to print out the edge
//        cout << edge1.first.first << " " << edge1.first.second << " : " << edge1.second.first << " "
//        << edge1.second.second << endl;
    }
    
    //    mt19937 generator;
    //    if (withSeed) {
    //        generator.seed(time(nullptr) + seed);
    //    } else {
    //        generator.seed(time(nullptr));
    //    }
    //    uniform_int_distribution<u_int32_t> dice(0, width);
    //    dice(generator);
    //    uniform_int_distribution<u_int32_t> dice(0, height);
    //    dice(generator);

    return edges;
}
