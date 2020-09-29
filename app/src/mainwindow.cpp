#include <QFileDialog>
#include "mainwindow.h"
#include "sound_tags.h"
#include "ui_mainwindow.h"

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

using std::cout;
using std::endl;

char *toChar(QString str)
{
    char *test = str.toUtf8().data();
    //    std::cout << "run function toChar " << str.toStdString().data() << "|" << test << std::endl;
    //    QByteArray ba = str.toUtf8();
    //    return ba.data();

    //    QByteArray array = str.toLocal8Bit();
    //    char* buffer = array.data();
    return test;
}

void MainWindow::outputCurrentInfo(const QVector<QString> &current, const QModelIndex &index)
{
    m_tableViewer->setNewItems(current, index);
}

MainWindow::MainWindow(QString sPath, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_path(sPath)
{
    ui->setupUi(this);

    m_player = new soundPlayer(ui);
    m_tableViewer = new TableViewer(ui->tableInfoSong);
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath(m_path);
    ui->fileBrowser->setModel(m_dirmodel);
    ui->fileBrowser->setRootIndex(m_dirmodel->index(m_path));
//    m_log = new Logger();

    for (int i = 1; i < m_dirmodel->columnCount(); ++i)
    {
        ui->fileBrowser->hideColumn(i);
    }
    ui->fileBrowser->setRootIndex(m_dirmodel->index(m_path));
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

    if (!current_directory.exists())
    {
        std::cout << "dir not opend" << std::endl;
    };

    current_directory.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    current_directory.setNameFilters(QStringList() << "*.mp3"
                                                   << "*.flac"
                                                   << "*.wav"
                                                   << "*.ogg"
                                                   << "*.m4a"
                                                   << "*.aif");
    //    current_directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    //    current_directory.setSorting(QDir::Size | QDir::Reversed);

    delete m_tableModel;
    m_tableModel = new MusicTableModel(ui->mainMusicTable);

    QFileInfoList list = current_directory.entryInfoList();

    m_music_list.clear();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QVector<QString> tmp;
        try
        {
            Sound_tags current;
            //            current.read_tags(fileInfo.fileName(), fileInfo.filePath());
            //            tmp = current.get_vector();
            tmp = read_tags(toChar(QString(fileInfo.fileName())),
                            toChar(QString(fileInfo.filePath())));
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
        if (!tmp.empty())
            m_music_list.push_back(tmp);
    }

    m_tableModel->music_list_add(m_music_list);
    ui->mainMusicTable->setModel(m_tableModel);
}

void MainWindow::on_mainMusicTable_clicked(const QModelIndex &index)
{
    QVector<QString> current = m_music_list[index.row()];
    std::string fileName = m_music_list[index.row()][0].toStdString().data();
    std::string fileType = fileName.substr(fileName.size() - 3);
    QImage coverQImg;

    if (fileType == "mp3") {
        coverQImg = load_cover_image_mpeg(m_music_list[index.row()][8].toStdString().data());
        ui->statusbar->showMessage(tr( " loaded"), 200);
    }
    else if (fileType == "m4a") {
        coverQImg = load_cover_image_m4a(m_music_list[index.row()][8].toStdString().data());
        ui->statusbar->showMessage(tr( " loaded"), 200);
    }
    else {
        ui->statusbar->showMessage(tr(" cover is unsupported." ), 200);
        coverQImg = QImage("../../app/logo1.png");
    }

    QGraphicsScene *scene = new QGraphicsScene();
    ui->imageSong->setScene(scene);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(coverQImg));
    scene->addItem(item);
    ui->imageSong->show();

    //    QImage coverQImg = load_cover_image(m_music_list[index.row()][8].toStdString().data());
    //    ui->statusbar->showMessage(tr("image loaded"), 200);
    //    QGraphicsScene *scene = new QGraphicsScene();
    //    ui->imageSong->setScene(scene);
    //    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(coverQImg));
    //    scene->addItem(item);
    //    ui->imageSong->show();
    outputCurrentInfo(current, index);
}

void MainWindow::on_pushButton_clicked()
{
    auto newSongTag = m_tableViewer->getResult();
    modify_tags(newSongTag);
    m_music_list[m_tableViewer->getIndex().row()] = std::move(newSongTag);
    m_tableModel->music_list_add(m_music_list);
    ui->mainMusicTable->setModel(m_tableModel);
}

void MainWindow::on_mainMusicTable_doubleClicked(const QModelIndex &index)
{
    QVector<QString> current = m_music_list[index.row()];

    //    QImage coverQImg = load_cover_image(m_music_list[index.row()][8].toStdString().data());
    //    ui->statusbar->showMessage(tr("image loaded"), 200);
    //    QGraphicsScene *scene = new QGraphicsScene();
    //    ui->imageSong->setScene(scene);
    //    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(coverQImg));
    //    scene->addItem(item);
    //    ui->imageSong->show();
    outputCurrentInfo(current, index);
    setMusicPlay(current[8]);

    std::string fileName = m_music_list[index.row()][0].toStdString().data();
    std::string fileType = fileName.substr(fileName.size() - 3);
    QImage coverQImg;

    if (fileType == "mp3") {
        coverQImg = load_cover_image_mpeg(m_music_list[index.row()][8].toStdString().data());
        ui->statusbar->showMessage(tr( " loaded"), 200);
    }
    else if (fileType == "m4a") {
        coverQImg = load_cover_image_m4a(m_music_list[index.row()][8].toStdString().data());
        ui->statusbar->showMessage(tr( " loaded"), 200);
    }
    else {
        ui->statusbar->showMessage(tr(" cover is unsupported." ), 200);
        coverQImg = QImage("../../app/logo1.png");
    }

//    coverQImg = coverQImg.scaled(35,35);

/*
    QLabel::setScaledContents(true).

    QGraphicsScene *scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

//    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(coverQImg));
//    scene->addItem(item);

    QPixmap pix = QPixmap::fromImage(coverQImg);
    scene->addPixmap(pix);
    ui->imageSong->show();
*/
//    QLabel::cover_label.set(true).
    QPixmap pix(QPixmap::fromImage(coverQImg));
//    ui->cover_label->setStyleSheet("border-image:url(:/2.png);");
    ui->cover_label->setPixmap(pix);
}

void MainWindow::setMusicPlay(QString soundPath)
{
    m_player->setSound(soundPath);
}

void MainWindow::on_playButton_clicked()
{
    m_player->setPlay();
}

void MainWindow::on_pauseButton_clicked()
{
    m_player->setPause();
}

void MainWindow::on_stopButton_clicked()
{
    m_player->setStop();
}

void MainWindow::on_statusPlay_valueChanged(int value)
{
    m_player->setMovedPosition(value);
}

void MainWindow::on_statusVolume_valueChanged(int value)
{
    m_player->setVolume(value);
}

void MainWindow::on_serarch_line_returnPressed()
{

}

void MainWindow::on_change_cover_button_clicked()
{
    auto currentSongTag = m_tableViewer->getResult();
    std::string current_file = currentSongTag[0].toStdString();
    std::string fileType = current_file.substr(current_file.size() - 3);

    if (fileType == "mp3") {
        QString file_image = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "~/",
                tr("Images (*.png *.jpg)")
        );

        set_image_mpeg(currentSongTag[8].toStdString().data(), file_image.toStdString().data());
        ui->statusbar->showMessage(tr(file_image.toStdString().data()), 2000);
    }
    else {
        ui->statusbar->showMessage(tr("error cover not editible"), 2000);
    }

}

//void MainWindow::on_pushButton_2_clicked()
//{
//    if (ui->fileBrowser->isHidden()) {
//        ui->fileBrowser->show();
//        ui->mainMusicTable->resize();
//    } else {
//        ui->fileBrowser->hide();
//        ui->mainMusicTable->resize();
//    }
//}

void MainWindow::on_actionlog_triggered()
{
    ui->statusbar->showMessage(tr("menu log"), 2000);
}
