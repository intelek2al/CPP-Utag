//
// Created by Serhiy Nikolayenko on 9/18/20.
//


#ifndef UTAG_DIALOG_H
#define UTAG_DIALOG_H

#include <QDialog>
#include <QFileSystemModel>


//namespace UIi {
//    class Dialog;
//}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Dialog *ui;
    QFileSystemModel *dir_model;
    QFileSystemModel *file_model;
};


#endif //UTAG_DIALOG_H
