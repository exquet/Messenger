#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QPixmap>
#include <QTextBrowser>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_send_b_clicked();

    void on_addAcc_b_clicked();

    void on_settings_b_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

