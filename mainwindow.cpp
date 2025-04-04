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

    ui->msgText->installEventFilter(this); // key event
    QShortcut *playShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this); // enter
    connect(playShortcut, &QShortcut::activated, this, &MainWindow::on_send_b_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_send_b_clicked()
{
    QString str = ui->msgText->toPlainText();
    QTextBrowser *text = ui->textBrowser;

    if (currentUserName.isEmpty()) {
        str.clear();
    }

    if (!str.isEmpty() && !currentUserName.isEmpty()) {
        ui->msgText->clear();

        //html форматирование | %1 - placeholder
        QString formattedMessage = QString("<div align='right' style='margin: 5px;'>"
                                           "<span style='background-color: #E0E0E0; "
                                           "border-radius: 10px; padding: 8px; "
                                           "display: inline-block; max-width: 80%;'>"
                                           "%1</span></div>").arg(str);

        QString currentHtml = text->toHtml();
        // вставляем новое сообщение перед закрывающим тегом body
        int bodyEndPos = currentHtml.lastIndexOf("</body>");
        if (bodyEndPos != -1) {
            currentHtml.insert(bodyEndPos, formattedMessage);
            text->setHtml(currentHtml);
        } else {
            text->insertHtml(formattedMessage);
        }

        //text->append("");
        text->verticalScrollBar()->setValue(text->verticalScrollBar()->maximum());

        userChat[currentUserName] = text->toHtml();
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


void MainWindow::on_settings_b_clicked()
{
    QDialog *qd = new QDialog(this);
    qd->setWindowTitle("settings");

    QVBoxLayout *layout = new QVBoxLayout(qd);
    QLineEdit *lineText = new QLineEdit(qd);
    QLabel *text = new QLabel(qd);
    text->setText("enter your username");
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Apply | QDialogButtonBox::Cancel, qd);

    layout->addWidget(text);
    layout->addWidget(lineText);
    layout->addWidget(buttonBox);

    //cancel
    connect(buttonBox, &QDialogButtonBox::rejected, [=]() {
        qd->reject();
    });

    //appy
    connect(buttonBox, &QDialogButtonBox::clicked, [=]() {
        QString userName = lineText->text().trimmed(); // removing spaces
        ui->myName_l->setText(userName);
    });

    qd->exec();
    qd->deleteLater();
}


void MainWindow::on_usersList_itemClicked(QListWidgetItem *item)
{
    if (!currentUserName.isEmpty()) {
        userChat[currentUserName] = ui->textBrowser->toHtml(); // возвращает html отформат. текст
    }

    currentUserName = item->text();
    ui->theyName_l->setText(currentUserName);

    if (userChat.contains(currentUserName)) { // проверка содержится ли
        ui->textBrowser->setHtml(userChat[currentUserName]);
    }
    else {
        ui->textBrowser->clear();
    }

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->msgText && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event); // преобразует QEvent* в QKeyEvent*.
        if (keyEvent->key() == Qt::Key_Return) {
            on_send_b_clicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event); // default
}



void MainWindow::on_call_b_clicked()
{
    if (!currentUserName.isEmpty()) {
        QDialog *qd = new QDialog(this);
        qd->setWindowTitle("Call");

        QVBoxLayout *layout = new QVBoxLayout(qd);
        QLabel *name = new QLabel(qd);
        name->setText(currentUserName);

        QPushButton *vidCall_b = new QPushButton(qd);
        vidCall_b->setText("swap to video");
        QPushButton *micMute_b = new QPushButton(qd);
        micMute_b->setText("mic mute");
        QPushButton *callLeave_b = new QPushButton(qd);
        callLeave_b->setText("leave");
        QHBoxLayout *buttonLayout = new QHBoxLayout(qd);
        buttonLayout->addWidget(vidCall_b);
        buttonLayout->addWidget(micMute_b);
        buttonLayout->addWidget(callLeave_b);

        layout->addWidget(name);
        layout->addLayout(buttonLayout);

        qd->exec();
        qd->deleteLater();
    }
}


void MainWindow::on_videoCall_b_clicked()
{
    QDialog *qd = new QDialog(this);
    qd->setWindowTitle("Video call");

    qd->exec();
    qd->deleteLater();
}

