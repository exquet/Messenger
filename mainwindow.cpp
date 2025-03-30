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
        if (ui->usersList->currentItem()) {
            ui->msgText->clear();

            //html форматирование
            QString formattedMessage = QString("<div style='text-align: right; margin: 5px;'>"
                                               "<span style='background-color: #E0E0E0; "
                                               "border-radius: 10px; padding: 8px; "
                                               "display: inline-block; max-width: 80%;'>"
                                               "%1</span></div>").arg(str); // %1 - placeholder

            text->insertHtml(formattedMessage); //вставка html отфарматированного текста

            text->append("");
            text->verticalScrollBar()->setValue(text->verticalScrollBar()->maximum());
        }
        else {
            ui->msgText->clear();
        }
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

    //cancel
    connect(buttonBox, &QDialogButtonBox::rejected, [=]() {
        qd->reject();
    });

    //ok
    connect(buttonBox, &QDialogButtonBox::accepted, [=]() {
        QString userName = lineText->text().trimmed(); // removing spaces
        QListWidget *users = ui->usersList;
        users->addItem(userName);
        qd->reject();
    });


    qd->exec();
    qd->deleteLater();
}

