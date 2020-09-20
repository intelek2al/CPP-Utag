#ifndef UTAG_DIALOG_H
#define UTAG_DIALOG_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QAbstractItemView>

namespace Ui {
    class FileBrowser;
}

class FileBrowser : public QMainWindow
{
Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = 0);
    ~FileBrowser();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::FileBrowser *ui;
    QFileSystemModel *file_model;
    QFileSystemModel *dir_model;
};


FileBrowser::FileBrowser(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::FileBrowser)
{
    ui->setupUi(this);
    file_model = new QFileSystemModel(this);
    file_model->setFilter(QDir::NoDotAndDotDot|QDir::Files);
    file_model->setRootPath("/home");
    ui->listView->setModel(file_model);

    dir_model = new QFileSystemModel(this);
    dir_model->setFilter(QDir::NoDotAndDotDot|QDir::Dirs);
    dir_model->setRootPath("/home");
    ui->treeView->setModel(dir_model);
    connect(ui->treeView,&QTreeView::clicked,this,&FileBrowser::on_treeView_clicked);
}

FileBrowser::~FileBrowser()
{
    delete ui;
}

void FileBrowser::on_treeView_clicked(const QModelIndex &index)
{
    qDebug()<<"Qtree view is clicked "<<index.data(Qt::DisplayRole)<<" : "<<index.row()<<index.column()<<index.parent();
    QString path = dir_model->fileInfo(index).absoluteFilePath();
    qDebug()<<path;
    ui->listView->setRootIndex(file_model->setRootPath(path));
}

void FileBrowser::on_listView_clicked(const QModelIndex &index)
{



/*
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
*/

#endif //UTAG_DIALOG_H
