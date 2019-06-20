#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

#include "types.h"
#include "controller.h"
#include "management.h"
#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_load_model_triggered();

    void on_pushButtonTransport_clicked();

    void on_pushButtonScale_clicked();

    void on_pushButtonRotate_clicked();

    void on_action_save_model_triggered();

private:
    Ui::MainWindow *ui;

    char message[MAX_LENGHT_STRING];

    void update(const controller_t &controller, RESPONSE_ACTION action);
};

#endif // MAINWINDOW_H
