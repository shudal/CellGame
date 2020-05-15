//
// Created by perci on 2020/5/15.
//

#include "GameWidget.h"
#include "../../../include/Config.h"
#include <thread>
#include <chrono>
#include <src/utility/CellGameCore.h>
#include <QMetaType>


GameWidget::GameWidget() {
    commonInit();
}
GameWidget::GameWidget(std::vector<std::vector<int>> ns) {
    cells_status_ = ns;
    commonInit();
}

void GameWidget::commonInit() {
    setupVar();
    setupUi();
    setupTimer();
    qRegisterMetaType<std::vector<std::vector<int>>>("std::vector<std::vector<int>>");
    connect(this, SIGNAL(changeStateSignal(std::vector<std::vector<int>>)), this, SLOT(changeStateSlot(std::vector<std::vector<int>>)));
}

// setupUi在setupVar后
void GameWidget::setupUi() {
    this->resize(Config::GetConfig()->WINDOW_WIDTH, Config::GetConfig()->WINDOW_HEIGHT);
    this->cell_grid_layout_ = std::make_unique<QGridLayout>(this);
    this->setLayout(this->cell_grid_layout_.get());
    for (auto i=1; i<=Config::GetConfig()->ROWS_COUNT; i++) {
        std::vector<std::unique_ptr<QLabel>> vs;
        cells_.push_back(std::move(vs));
        for (auto k=1; k<=Config::GetConfig()->COLS_COUNT; k++) {
            std::unique_ptr<QLabel> q (new QLabel());
            cells_[i-1].push_back(std::move(q));
            cells_[i-1][k-1]->resize(cell_width_, cell_height_);

            QPixmap pix;
            if (i < cells_status_.size() && k < cells_status_[i].size()) {
                if (cells_status_[i][k] == Config::GetConfig()->STATUS_HAP) {
                    pix = hap_pix_map_;
                } else {
                    pix = sad_pix_map_;
                }
            } else {
                pix = sad_pix_map_;
            }
            cells_[i-1][k-1]->setPixmap(pix.scaled(cells_[i-1][k-1]->size(), Qt::KeepAspectRatio));
            cells_[i-1][k-1]->setParent(this);
            this->cell_grid_layout_->addWidget(cells_[i-1][k-1].get(), i, k);
        }
    }
}

void GameWidget::setupVar() {
    cell_width_  = static_cast<int>(Config::GetConfig()->WINDOW_WIDTH * Config::GetConfig()->GAME_WINDOW_SIZE_RATE / Config::GetConfig()->COLS_COUNT);
    cell_height_ = static_cast<int>(Config::GetConfig()->WINDOW_HEIGHT * Config::GetConfig()->GAME_WINDOW_SIZE_RATE / Config::GetConfig()->ROWS_COUNT);

    sad_img_ = QImage(Config::GetConfig()->SAD_SRC.c_str());
    hap_img_ = QImage(Config::GetConfig()->HAP_SRC.c_str());
    sad_pix_map_ = QPixmap::fromImage(sad_img_);
    hap_pix_map_ = QPixmap::fromImage(hap_img_);
}

void GameWidget::setupTimer() {
    std::thread thread1(evolve, 2, this);
    thread1.detach();
}

void GameWidget::evolve(int circle_seconds, GameWidget * gw) {
    static CellGameCore core;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(circle_seconds));
        gw->changeStateSignal(core.process(gw->cells_status_));
        qDebug("tick");
    }
}

void GameWidget::changeStateSlot(std::vector<std::vector<int>> vs) {
    qDebug("change state slots");
    cells_status_ = vs;
    for (auto i=0; i<cells_.size(); i++) {
        for (auto k=0; k<cells_[i].size(); k++) {
            bool hap = true;
            if (i < cells_status_.size() && k < cells_status_[i].size()) {
                if (cells_status_[i][k] == Config::GetConfig()->STATUS_SAD) {
                    hap = false;
                }
            } else {
                hap = false;
            }

            QPixmap pix;
            if (hap) {
                pix = hap_pix_map_;
            } else {
                pix = sad_pix_map_;
            }

            cells_[i][k]->resize(cell_width_, cell_height_);
            cells_[i][k]->setPixmap(pix.scaled(cells_[i][k]->size(), Qt::KeepAspectRatio));
        }
    }
}

