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
    ui->settings_b->setIcon(QIcon("://icons/settings.png"));
    ui->addAcc_b->setIcon(QIcon("://icons/add.png"));
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

void MainWindow::on_send_b_clicked()
{
    QString str = ui->msgText->toPlainText();
    QTextBrowser *text = ui->textBrowser;

    if (!str.isEmpty()) {
        ui->msgText->clear();

        text->append(str);
    }
}


void MainWindow::on_addAcc_b_clicked()
{
    QDialog *qd = new QDialog(this);
    qd->setWindowTitle("authorization");

    QVBoxLayout *layout = new QVBoxLayout(qd);
    QLabel *text = new QLabel(qd);
    text->setText("enter the user's username");
    QLineEdit *lineText = new QLineEdit(qd);
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, qd);

    layout->addWidget(text);
    layout->addWidget(lineText);
    layout->addWidget(buttonBox);

    qd->exec();
    qd->deleteLater();
}

