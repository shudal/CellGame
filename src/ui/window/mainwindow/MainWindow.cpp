#include <src/include/Config.h>
#include "MainWindow.h"
#include <QScreen>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    main_title_ = Config::GetConfig()->MAIN_TITLE;
    ui_->setupUi(this);
    ui_->centralwidget->setLayout(ui_->mainLayout);

    ui_->startBtn->setMinimumSize(410, 66);
    ui_->startBtn->setStyleSheet("QPushButton {background-color: rgb(58,64,85); color:white; font-size:28px; border-radius:5px;} QPushButton:hover { background-color: rgb(82,89,111);}");

    this->setWindowTitle(QString(main_title_.c_str()));

    QPixmap bkgnd(Config::GetConfig()->MAIN_BG_SRC.c_str());

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        bkgnd = screen->grabWindow(0);
    }
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    this->setWindowIcon(QIcon(Config::GetConfig()->MAIN_ICON_SRC.c_str()));

    connect(ui_->startBtn, SIGNAL(released()), this, SLOT(startGame()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::startGame() {
    qDebug("hi");

    setRandomGameWidget();
    gw_->show();
}

void MainWindow::setRandomGameWidget() {
    static Rand_int rand_int {0,1};
    std::vector<std::vector<int>> vs;
    for (int i=0; i<Config::GetConfig()->ROWS_COUNT; i++) {
        std::vector<int> vs2;
        vs.push_back(vs2);
        for (int k=0; k<Config::GetConfig()->COLS_COUNT; k++) {
            vs[i].push_back(rand_int());
        }
    }
    gw_ = std::make_unique<GameWidget>(vs);
}
