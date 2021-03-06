//
// Created by perci on 2020/5/15.
//

#include "GameWidget.h"
#include "../../../include/Config.h"
#include <thread>
#include <chrono>
#include <src/utility/CellGameCore.h>
#include <QMetaType>
#include <QIcon>

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

    this->setWindowTitle(Config::GetConfig()->MAIN_TITLE.c_str());

    QPixmap bkgnd(Config::GetConfig()->MAIN_BG_SRC.c_str());
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    this->setWindowIcon(QIcon(Config::GetConfig()->MAIN_ICON_SRC.c_str()));

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
    p_thread_quit = false;
    int circle_seconds = 2;
    GameWidget *gw = this;
    std::reference_wrapper<bool> p_quit = std::ref(p_thread_quit);
    // 这里必须要是 copy，而不能是 reference,
    // 因为thread2用的是setupTimer()函数内局部变量
    // 若reference, 这些局部变量会在setupTimer()结束时销毁，从而导致thread2里出现悬垂指针现象。
    std::thread thread2([=]{
        static CellGameCore core;
        while (true) {
            if (p_quit) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(circle_seconds));
            gw->changeStateSignal(core.process(gw->cells_status_));
            qDebug("tick");
        }
        qDebug("tick thread exit.");
    });
    thread2.detach();
}

void GameWidget::changeStateSlot(std::vector<std::vector<int>> vs) {
    qDebug("change state slots");
    cells_status_ = vs;
    setCellStatus();
}

void GameWidget::closeEvent(QCloseEvent *e) {
    p_thread_quit = true;
    qDebug("game widget close");
}

void GameWidget::setCellStatus() {
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

