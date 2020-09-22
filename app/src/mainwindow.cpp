#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "musictablemodel.h"

MainWindow::MainWindow(QString sPath, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);

    ui->fileBrowser->setModel(dirmodel);
    ui->fileBrowser->setRootIndex(dirmodel->index(sPath));

    for (int i = 1; i < dirmodel->columnCount(); ++i)
    {
        ui->fileBrowser->hideColumn(i);
    }

    MusicTableModel *tableModel = new MusicTableModel;
    filemodel = new QFileSystemModel(this);
    filemodel->setRootPath(sPath);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setNameFilters(QStringList() << "*.mp3"
                                            << "*.flac"
                                            << "*.waw"
                                            << "*.ogg"
                                            << "*.aif");
    filemodel->setNameFilterDisables(false);

    ui->mainMusicTable->setModel(/*filemodel */ tableModel);
    ui->fileBrowser->setRootIndex(dirmodel->index(sPath));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileBrowser_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    // ui->mainMusicTable->setRootIndex(filemodel->setRootPath(sPath));
}
