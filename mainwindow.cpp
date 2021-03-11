#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);




    ui->dataPath->hide();
    ui->btnOk->hide();
    ui->exportPath->hide();
    ui->btnOkEport->hide();
}

MainWindow::~MainWindow()
{
    delete ui;



}


void MainWindow::on_btnSubmit_clicked()
{

    QSqlQuery query = QSqlQuery(db);
            if(!query.exec("select* from table_person")){
                    qDebug() << query.lastError().databaseText();
                     qDebug() << query.lastError().driverText();
                     return;
}
            while(query.next()) {




                qDebug() << query.record();
            }
}

void MainWindow::on_btnSelectTable_clicked()
{
    model->select();
}

void MainWindow::on_btnAdd_clicked()
{
    qDebug() << "insert row" << model->insertRow(model->rowCount());
}

void MainWindow::on_btndelete_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0 ) {
        qDebug() << "deleting row" << model->removeRow(selectedRow);
 model->select();
    } else {
        qDebug() << "no row";
    }
}



void MainWindow::on_btnOk_clicked()
{
    data_path = ui->dataPath->text();
    ui->label->setText("DATABASE IMPORTED FROM SQLITE " + data_path);


    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(data_path);

    if (!db.open()) {

    qDebug() << db.lastError().text();
    return;
    }
    else {
          qDebug() << "АЛlАРМ ALL RIGHT!";

    }

    model = new QSqlTableModel(this, db);
    model -> setTable("table_person");
    model->select();
    ui->tableView->setModel(model);

    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(1);



    ui->dataPath->hide();
    ui->btnOk->hide();
}

void MainWindow::on_btnData_clicked()
{
    ui->dataPath->show();
    ui->btnOk->show();
}

void MainWindow::on_btnExport_clicked()
{
    ui->exportPath->show();
    ui->btnOkEport->show();
}

void MainWindow::on_btnOkEport_clicked()
{
    ui->exportPath->hide();
    ui->btnOkEport->hide();
    data_export = ui->exportPath->text();
    ui->label->setText("DATABASE WAS EXPORTED TO CSV " + data_export);
}
