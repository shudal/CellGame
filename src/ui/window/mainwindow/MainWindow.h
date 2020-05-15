#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <src/ui/widget/game/GameWidget.h>
#include <src/utility/Rand_int.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::unique_ptr<Ui::MainWindow> ui_;
    std::unique_ptr<GameWidget> gw_;
private:
    std::string main_title_;
    void setRandomGameWidget();
public slots:
    void startGame();
};

#endif // MAINWINDOW_H
