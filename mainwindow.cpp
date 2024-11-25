#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connectToDatabase();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_saveButton_clicked() {
    QString name = ui->nameEdit->text();
    int age = ui->ageSpinBox->value();
    QString diagnosis = ui->diagnosisEdit->text();
    QString sex = ui->sexEdit->text();

    QSqlQuery query;
    query.prepare("INSERT INTO patients (name, age, diagnosis, sex) VALUES (:name, :age, :diagnosis, :sex)");
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":diagnosis", diagnosis);
    query.bindValue(":sex", sex);

    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
    } else {
        qDebug() << "Patient data saved successfully";
    }
}

void MainWindow::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("medical_db");
    db.setUserName("zhuk17");
    db.setPassword("12345");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }
}
