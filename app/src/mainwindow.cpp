#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "musictablemodel.h"

//    {"Name", "Time", "Title", "Artist", "Genre", "Album", "Year", "Track", "Path", "Comment" };

//#define T___NAME 0
//#define T___TIME 1
//#define V__TITLE 2
//#define V_ARTIST 3
//#define V__GENRE 4
//#define V__ALBUM 5
//#define T___YEAR 6
//#define T__TRACK 7
//#define T___COMT 8

//#define V___NAME 0
//#define V___TIME 1
//#define V__TITLE 2
//#define V_ARTIST 3
//#define V__GENRE 4
//#define V__ALBUM 5
//#define V___YEAR 6
//#define V__TRACK 7
//#define V___COMT 8

char *toChar(QString str){
    QByteArray ba = str.toUtf8();
    return ba.data();
}

void MainWindow::outputCurrentInfo(const QVector<QString> &current, const QModelIndex &index)
{
    m_tableViewer->setNewItems(current, index);
}

MainWindow::MainWindow(QString sPath, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    m_tableViewer = new TableViewer(ui->tableInfoSong);
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath(sPath);

    ui->fileBrowser->setModel(m_dirmodel);
    ui->fileBrowser->setRootIndex(m_dirmodel->index(sPath));

    for (int i = 1; i < m_dirmodel->columnCount(); ++i)
    {
        ui->fileBrowser->hideColumn(i);
    }

    ui->fileBrowser->setRootIndex(m_dirmodel->index(sPath));
}

MainWindow::~MainWindow()
{
    delete m_tableViewer;
    delete m_dirmodel;
//    deleteLater()
system("leaks -q utag");
    delete ui;
}

void MainWindow::on_fileBrowser_clicked(const QModelIndex &index)
{
    QString sPath = m_dirmodel->fileInfo(index).absoluteFilePath();

    QDir current_directory(sPath);

    if(!current_directory.exists()) {
        std::cout << "dir not opend" << std::endl;
    };

    current_directory.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    current_directory.setNameFilters(QStringList() << "*.mp3"
                                            << "*.flac"
                                            << "*.wav"
                                            << "*.ogg"
                                            << "*.aif");
//    current_directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//    current_directory.setSorting(QDir::Size | QDir::Reversed);

    MusicTableModel *tableModel = new MusicTableModel(ui->mainMusicTable);

    QFileInfoList list = current_directory.entryInfoList();

//    std::cout << "==========================\n";
//    for(auto& elem : list) {
//        std::cout << elem.fileName().toStdString() << "\n";
//    }
//    std::cout << "==========================\n\n";

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

//        std::cout << "MainWindow::on_fileBrowser_clicked line 70 fileInfo = " << fileInfo.fileName().toStdString() << std::endl;
        QVector<QString> tmp;
        try {
            tmp = read_tags(toChar(QString(fileInfo.fileName())),
                            toChar(QString(fileInfo.filePath())));
        }
        catch (std::exception& e) {
           std::cerr << e.what() << std::endl;
        }
        if (!tmp.empty())
                m_music_list.push_back(tmp);
    }
    std::cout << "======================  end read dir \n\n";

    // /////////////////////////////////////////////////////

    tableModel->music_list_add(m_music_list);
//    for (int i = 0; i < m_music_list.size(); i++) {
//        std::cout << "---\nsize: " << m_music_list[i].size() << "\n";
//        for (int j = 0; j < m_music_list[i].size(); j++) {
//            std::cout << "|" << m_music_list[i][j].toStdString() << "|\t";
//        }
//        std::cout << "\n---\n\n";
//    }
    ui->mainMusicTable->setModel(tableModel);

    // ui->mainMusicTable->setRootIndex(filemodel->setRootPath(sPath));
}



void MainWindow::on_mainMusicTable_clicked(const QModelIndex &index)
{
    QVector<QString> current = m_music_list[index.row()];
    QImage image("/Users/msavytskyi/Desktop/CPP-Utag/app/Filesaveas.png");
//    QByteArray ba = load_cover_array(m_music_list[index.row()][8].toStdString().data());
//    image.loadFromData(ba);
    QGraphicsScene* scene = new QGraphicsScene();
    ui->imageSong->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);
    ui->imageSong->show();
//    buffer.open(QIODevice::ReadWrite);
    outputCurrentInfo(current, index);
}

void MainWindow::on_pushButton_clicked()
{
    auto newSongTag = m_tableViewer->getResult();
    //  change filetags
    m_music_list[m_tableViewer->getIndex().row()] = std::move(newSongTag);

}
