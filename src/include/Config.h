//
// Created by perci on 2020/5/15.
//

#ifndef CELLGAME_CONFIG_H
#define CELLGAME_CONFIG_H

#include <string>
class Config {
public:
    static Config* GetConfig() {
        static Config c;
        return &c;
    }
    const int WINDOW_WIDTH = 1440;
    const int WINDOW_HEIGHT = 900;
    const int ROWS_COUNT = 10;
    const int COLS_COUNT = 10;
    // 游戏画面 是 游戏窗口的0.8大
    const double GAME_WINDOW_SIZE_RATE = 0.8;
    const std::string SAD_SRC = "sad.png";
    const std::string HAP_SRC = "hap.png";
    const int STATUS_HAP = 1;
    const int STATUS_SAD = 0;
    const std::string MAIN_TITLE = "生命游戏";
};
#endif //CELLGAME_CONFIG_H
