//
//  Prim.cpp
//  s3574983-a2
//
//  Created by Tuan Le on 5/1/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "Prim.hpp"

vector<Edge> Prim::generate() {
    int seed = getSeed();
    srand(seed);
    int height = getHeight();
    int width = getWidth();
    //    create an array to monitor visited cells
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }
    //    create vector to store edges
    vector<Edge> edges;
    vector<Coordinator> frontiers;
        
    //    generate a random stating cell
    Coordinator startingCell;
    startingCell.setX(rand() % height);
    startingCell.setY(rand() % width);
    //    flag it as visited
    visitedArray[startingCell.getX()][startingCell.getY()] = true;
    
    if (startingCell.getX() - 1 > -1) {
        if (!visitedArray[startingCell.getX() - 1][startingCell.getY()]) {
            Coordinator topCell;
            topCell.setX(startingCell.getX() - 1);
            topCell.setY(startingCell.getY());
            frontiers.push_back(topCell);
        }
    }
    
    if (startingCell.getY() + 1 < width) {
        if (!visitedArray[startingCell.getX()][startingCell.getY() + 1]) {
            Coordinator rightCell;
            rightCell.setX(startingCell.getX());
            rightCell.setY(startingCell.getY() + 1);
            frontiers.push_back(rightCell);
        }
    }
    
    if (startingCell.getX() + 1 < height) {
        if (!visitedArray[startingCell.getX() + 1][startingCell.getY()]) {
            Coordinator bottomCell;
            bottomCell.setX(startingCell.getX() + 1);
            bottomCell.setY(startingCell.getY());
            frontiers.push_back(bottomCell);
        }
    }
    
    if (startingCell.getY() - 1 > -1) {
        if (!visitedArray[startingCell.getX()][startingCell.getY() - 1]) {
            Coordinator leftCell;
            leftCell.setX(startingCell.getX());
            leftCell.setY(startingCell.getY() - 1);
            frontiers.push_back(leftCell);
        }
    }
    
    while (!frontiers.empty()) {
        int currentRandom = rand() % frontiers.size();
        startingCell = frontiers[currentRandom];
        Edge edge;
        edge.setCoordinator1(startingCell);
        visitedArray[startingCell.getX()][startingCell.getY()] = true;
        frontiers.erase(std::remove_if(frontiers.begin(), frontiers.end(),
                                                 [&startingCell](const Coordinator& coordinator) {
                                                     return coordinator.getX() == startingCell.getX() &&
                                                     coordinator.getY() == startingCell.getY();
                                                 }), frontiers.end());
        vector<Coordinator> visitedNeighbours;
        
        if (startingCell.getX() - 1 > -1) {
            Coordinator topCell;
            topCell.setX(startingCell.getX() - 1);
            topCell.setY(startingCell.getY());
            if (visitedArray[startingCell.getX() - 1][startingCell.getY()]) {
                visitedNeighbours.push_back(topCell);
            } else {
                frontiers.push_back(topCell);
            }
        }
        
        if (startingCell.getY() + 1 < width) {
            Coordinator rightCell;
            rightCell.setX(startingCell.getX());
            rightCell.setY(startingCell.getY() + 1);
            if (visitedArray[startingCell.getX()][startingCell.getY() + 1]) {
                visitedNeighbours.push_back(rightCell);
            } else {
                frontiers.push_back(rightCell);
            }
        }
        
        if (startingCell.getX() + 1 < height) {
            Coordinator bottomCell;
            bottomCell.setX(startingCell.getX() + 1);
            bottomCell.setY(startingCell.getY());
            if (visitedArray[startingCell.getX() + 1][startingCell.getY()]) {
                visitedNeighbours.push_back(bottomCell);
            } else {
                frontiers.push_back(bottomCell);
            }
        }
        
        if (startingCell.getY() - 1 > -1) {
            Coordinator leftCell;
            leftCell.setX(startingCell.getX());
            leftCell.setY(startingCell.getY() - 1);
            if (visitedArray[startingCell.getX()][startingCell.getY() - 1]) {
                visitedNeighbours.push_back(leftCell);
            } else {
                frontiers.push_back(leftCell);
            }
        }
        
        currentRandom = rand() % visitedNeighbours.size();
        startingCell = visitedNeighbours[currentRandom];
        edge.setCoordinator2(startingCell);
        edges.push_back(edge);
    }
    return edges;
}