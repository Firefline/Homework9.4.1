#include "mainwindow.h"
#include "./ui_mainwindow.h"

int pumpValue = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pumpsLabel->setText("Выбор трубы");
    for (int i = 1; i < 11; ++i)
    {
        ui->pumpsBox->addItem("Труба № " + QString::number(i));
    }

    ui->logName->setText("Статус");
    ui->logView->setReadOnly(true);
    ui->logView->setText("Добро пожаловать в систему очистки трубопровода.");
    ui->logView->append("Выбрана " + ui->pumpsBox->currentText());

    ui->value->setTitle("Напор давления");
    ui->value10->setText("10%");
    ui->value20->setText("20%");
    ui->value10->setChecked(true);

    ui->pressureButton->setText("Увеличить давление");
    ui->pressureButton->setCheckable(true);
    ui->pressureProgress->setRange(0, 100);
    ui->pressureProgress->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pressureButton_clicked()
{
    if (ui->value10->isChecked())
    {
        ui->pressureProgress->setValue(pumpValue+10);
        pumpValue += 10;
    }
    else
    {
        ui->pressureProgress->setValue(pumpValue+20);
        pumpValue += 20;
    }
    ui->logView->append("Увеличение давления...");
    if (pumpValue>100)
    {
        ui->pressureProgress->setValue(0);
        pumpValue = 0;
        ui->logView->clear();
        ui->logView->append("Достигнуто максимальное давление. Очистка завершена.");
        ui->logView->append("Сброс давления...");
        ui->logView->append("Давление сброшено успешно.");
        ui->logView->append("Выбрана " + ui->pumpsBox->currentText());
    }
}


void MainWindow::on_pumpsBox_currentIndexChanged(int index)
{
    ui->logView->clear();
    ui->pressureProgress->setValue(0);
    ui->logView->append("Смена контрольной трубы. Сброс давления...");
    ui->logView->append("Давление успешно сброшено.");
    ui->logView->append("Выбрана " + ui->pumpsBox->currentText());
}

