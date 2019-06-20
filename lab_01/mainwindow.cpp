#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_load_model_triggered()
{
    controller_t controller = createController();

    QString filePath = QFileDialog::getOpenFileName(this, tr("Загрузка модели"), QDir::currentPath() + "/forms", tr("Text files (*.txt)"));

    ERROR result;
    RESPONSE_ACTION action;

    controller.userInput.file_name = filePath.toLocal8Bit().data();

    result = management(controller, USER_ACTION::LOADMODEL);
    action = handleProcessResult(message, result);
    update(controller, action);

}

void MainWindow::on_pushButtonTransport_clicked()
{
    controller_t controller = createController();

    ERROR result;
    RESPONSE_ACTION action;

    controller.userInput.transportData.dx = ui->lineEditTransdx->text().toDouble();
    controller.userInput.transportData.dy = ui->lineEditTransdy->text().toDouble();
    controller.userInput.transportData.dz = ui->lineEditTransdz->text().toDouble();

    result = management(controller, USER_ACTION::TRANSPORT);
    action = handleProcessResult(message, result);
    update(controller, action);
}

void MainWindow::on_pushButtonScale_clicked()
{
    controller_t controller = createController();

    ERROR result;
    RESPONSE_ACTION action;

    controller.userInput.scaleData.kx = ui->lineEditScaledx->text().toDouble();
    controller.userInput.scaleData.ky = ui->lineEditScaledy->text().toDouble();
    controller.userInput.scaleData.kz = ui->lineEditScaledz->text().toDouble();

    result = management(controller, USER_ACTION::SCALE);
    action = handleProcessResult(message, result);
    update(controller, action);
}

void MainWindow::on_pushButtonRotate_clicked()
{
    controller_t controller = createController();

    ERROR result;
    RESPONSE_ACTION action;

    controller.userInput.rotateData.alphax = ui->lineEditRotatedx->text().toDouble();
    controller.userInput.rotateData.alphay = ui->lineEditRotatedy->text().toDouble();
    controller.userInput.rotateData.alphaz = ui->lineEditRotatedz->text().toDouble();

    result = management(controller, USER_ACTION::ROTATE);
    action = handleProcessResult(message, result);
    update(controller, action);
}

void MainWindow::update(const controller_t &controller, RESPONSE_ACTION action)
{
    if (action == RENDER_ACTION)
    {
        ui->canvas->getPoints(controller.projectedPoints, controller.quantityPoints);
        ui->canvas->repaint();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", message);
    }
}


void MainWindow::on_action_save_model_triggered()
{
    controller_t controller = createController();

    ERROR result;
    RESPONSE_ACTION action;

    QString filePath = QFileDialog::getOpenFileName(this, "Сохранить модель", QDir::currentPath());

    if (filePath.isEmpty())
    {
        filePath = "figure/savedmodel.txt";
    }

    controller.userInput.file_name = filePath.toLocal8Bit().data();

    result = management(controller, USER_ACTION::SAVEMODEL);
    action = handleProcessResult(message, result);
    if (result == OK)
    {
        QMessageBox::information(this, "Сохранить модель", "Модель сохранена в : " + filePath);
    }

    update(controller, action);
}
