#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //icons
    setWindowIcon(QIcon("://icons/logo.png"));
    ui->call_b->setIcon(QIcon("://icons/call.png"));
    ui->videoCall_b->setIcon(QIcon("://icons/videoCall.png"));
    ui->myProfile_l->setPixmap(QPixmap("://icons/profile.png"));
    ui->theyProfile_l->setPixmap(QPixmap("://icons/profile.png"));

    QPixmap profilePixmap(":/icons/profile.png");
    ui->theyProfile_l->setPixmap(profilePixmap.scaled(
        ui->theyProfile_l->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        ));
}

MainWindow::~MainWindow()
{
    delete ui;
}
