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
    
    
    
     QSqlQuery query = QSqlQuery(db);
                if(!query.exec("select* from table_person")){

                         return;
    }
                while(query.next()) {


                export_all = export_all + query.value(0).toString()
                        + ";" + query.value(1).toString() + ";"
                        + query.value(2).toString() + "\n";


                }

               ui->label_export->setText(export_all);

               // write to file

             QString path = "C:\\Qt\\QT\\Step_base-main\\Step_base-main\\export.txt";
               QFile file(path);

               if (file.open(QIODevice::WriteOnly))
               {
                   file.write(export_all.toLocal8Bit());

                   file.close();
               }



               file.close();
    export_all = "";
    
    
}


void MainWindow::on_btn_find_clicked()
{
         QString find =  ui->input_find->text();
        // ui->lineEdit_find->setText(find);
    QSqlQuery query = QSqlQuery(db);
               if(!query.exec("select* from table_person")){
                        return;
   }
               while(query.next()) {

                  if (find == query.value(0) || find == query.value(1) || find == query.value(2) ){

                      QString row_find = query.value(0).toString()
                              + "; " + query.value(1).toString() + "; "
                              + query.value(2).toString() + "\n";
                      //int row_find = ui->tableView->currentIndex().row();
                       // ui->lineEdit_find->setText(row_find);
                       // model->selectRow(row_find);
                      ui->input_find->setText(row_find);
                  }
               }




}




