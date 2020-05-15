//
// Created by perci on 2020/5/15.
//

#include "CellGameCore.h"

CellGameCore::CellGameCore() {
    this->flag = 1;
}

std::vector<std::vector<int>> CellGameCore::process(std::vector<std::vector<int>> vs) {
    setFlag();
    int next_x[8] = {-1,-1,0,1,1,1,0,-1};
    int next_y[8] = {0,1,1,1,0,-1,-1,-1};
    int len_x = vs.size();
    int len_y = vs[0].size();
    std::vector<std::vector<int>> re(len_x,std::vector<int>(len_y,0));
    for(int i=0;i<len_x;++i){
        for(int j=0;j<len_y;++j){
            //计算周围活细胞数量
            int count = 0;
            for(int k=0;k<8;++k){
                int dx = i+next_x[k];
                int dy = j+next_y[k];
                if(dx<0 || dx>=len_x || dy<0 || dy>=len_y){
                    continue;
                }
                if(vs[dx][dy]==1){
                    ++count;
                }
            }
            if(count==3){
                re[i][j] = 1;
            }else if(count!=2){
                re[i][j] = 0;
            }else{
                re[i][j] = vs[i][j];
            }
            if(re[i][j]!=vs[i][j]){
                flag = 1;
            }
        }
    }
    //return std::vector<std::vector<int>>();
    return re;
}

void CellGameCore::setFlag() {
    this->flag = 0;
}

int CellGameCore::getFlag() {
    return flag;
}