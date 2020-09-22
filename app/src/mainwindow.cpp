#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "musictablemodel.h"

char *toChar(QString str){
    QByteArray ba = str.toUtf8();
    return ba.data();
}

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

    filemodel = new QFileSystemModel(this);
    filemodel->setRootPath(sPath);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setNameFilters(QStringList() << "*.mp3"
                                            << "*.flac"
                                            << "*.waw"
                                            << "*.ogg"
                                            << "*.aif");
    filemodel->setNameFilterDisables(false);

    ui->fileBrowser->setRootIndex(dirmodel->index(sPath));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileBrowser_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();

    QDir current_directory(sPath);

    if(!current_directory.exists()) {
        std::cout << "dir not opend" << std::endl;
    };

    current_directory.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    current_directory.setNameFilters(QStringList() << "*.mp3"
                                            << "*.flac"
                                            << "*.waw"
                                            << "*.ogg"
                                            << "*.aif");
//    current_directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//    current_directory.setSorting(QDir::Size | QDir::Reversed);

    MusicTableModel *tableModel = new MusicTableModel(ui->mainMusicTable);

    QFileInfoList list = current_directory.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        tableModel->music_list_add(read_tags(toChar(QString(fileInfo.fileName())),
                                   toChar(QString(fileInfo.filePath()))));

        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.filePath()));
//        tableModel->music_list_add({"sss", "dcmdckdm"});


    }

    ui->mainMusicTable->setModel(tableModel);

    // ui->mainMusicTable->setRootIndex(filemodel->setRootPath(sPath));
}