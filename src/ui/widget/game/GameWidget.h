//
// Created by perci on 2020/5/15.
//

#ifndef CELLGAME_GAMEWIDGET_H
#define CELLGAME_GAMEWIDGET_H

#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <memory>
#include <QtWidgets/QLabel>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget();
    GameWidget(std::vector<std::vector<int>>);

    private slots :
    void changeStateSlot(std::vector<std::vector<int>>);
private:
    void commonInit();
    void setupUi();
    void setupVar();
    void setupTimer();
    static void evolve(int, GameWidget*);

    std::unique_ptr<QGridLayout> cell_grid_layout_;
    double cell_width_;
    double cell_height_;
    std::vector<std::vector<std::unique_ptr<QLabel>>> cells_;
    std::vector<std::vector<int>> cells_status_;

    QPixmap sad_pix_map_;
    QPixmap hap_pix_map_;
    QImage sad_img_;
    QImage hap_img_;
signals :
    void changeStateSignal(std::vector<std::vector<int>>);
};


#endif //CELLGAME_GAMEWIDGET_H
