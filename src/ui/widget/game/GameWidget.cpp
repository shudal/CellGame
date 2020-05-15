//
// Created by perci on 2020/5/15.
//

#include "GameWidget.h"
#include "../../../include/Config.h"

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
                    pix = QPixmap::fromImage(hap_img_);
                } else {
                    pix = QPixmap::fromImage(sad_img_);
                }
            } else {
                pix = QPixmap::fromImage(sad_img_);
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

}

