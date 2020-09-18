//
// Created by Serhiy Nikolayenko on 9/18/20.
//


#include "dialog.h"


Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new(Dialog)) {
    ui->setupUi(this);

    QString sPath = "~/";

    dir_model = new QFileSystemModel(this);
    dir_model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dir_model->setRootPath(sPath);
    ui->treeView->SetModel(dir_model);

    file_model = new QFileSystemModel(this);
    file_model->SetFilter(QDir::NoDotAndDotDot | QDir::AllFiles);
    file_model->setRootPath(sPath);
    ui->listView->SetModel(file_model);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_treeView_clicked(QModelIndex index) {
    QString sPath = dir_model->fileInfo(index).absolutePath();
    ui->listView->setRootIndex(file_model->setRootPath(sPath));

}