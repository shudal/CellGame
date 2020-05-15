//
// Created by perci on 2020/5/15.
//

#ifndef CELLGAME_CELLGAMECORE_H
#define CELLGAME_CELLGAMECORE_H

#include <vector>
class CellGameCore {
public:
    /*
     * @param vs 。 矩形数组。
     *  元素值为0或1，0代表忧伤，1代表兴奋
     * @return 经过一次演化后的矩形数组
     */
    std::vector<std::vector<int>> process(std::vector<std::vector<int>> vs);
};


#endif //CELLGAME_CELLGAMECORE_H
