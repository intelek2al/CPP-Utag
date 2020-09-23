#include "mainwindow.h"
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

char *toChar(QString str)
{
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

    if (!current_directory.exists())
    {
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

    m_tableModel = new MusicTableModel(ui->mainMusicTable);

    QFileInfoList list = current_directory.entryInfoList();

    m_music_list.clear();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QVector<QString> tmp;
        try
        {
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
//    QImage coverQImg;
/*
    ///===============
    TagLib::MPEG::File mpegFile(m_music_list[index.row()][8].toStdString().data());
    TagLib::ID3v2::Tag *m_tag = mpegFile.ID3v2Tag(true);
    TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

    if(frameList.isEmpty()) {
        QImage coverQImg("../../app/logo1.png");
//        return QImage();
    } else {

        TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());


        coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
    }
    //=======
    */
///===================================== try load image =====================================
/*
    static const char *IdPicture = "APIC";  //  APIC    [#sec4.15 Attached picture]

    TagLib::MPEG::File mpegFile(m_music_list[index.row()][8].toStdString().data());
    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame;
    TagLib::ID3v2::AttachedPictureFrame *PicFrame;

    void *SrcImage;
    unsigned long Size = 0;

    if (id3v2tag) {
        Frame = id3v2tag->frameListMap()[IdPicture];
        if (!Frame.isEmpty()) {
            for (TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it) {
                PicFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame * >(*it);
                {
                    if (PicFrame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
                        // extract image (in it’s compressed form)
                        Size = PicFrame->picture().size();
                    SrcImage = malloc(Size);
                    if (SrcImage) {
                        memcpy(SrcImage, PicFrame->picture().data(), Size);
                    }
                }
            }
        coverQImg.loadFromData((const uchar *) PicFrame->picture().data(), PicFrame->picture().size());
        free(SrcImage);
        }
    }
    else {
        QImage coverQImg("../../app/logo1.png");
//        std::cout << "id3v2 not present";
    }
    ///==========================================================================
*/
    QImage coverQImg("../../app/logo1.png");  // default image


    QGraphicsScene *scene = new QGraphicsScene();
    ui->imageSong->setScene(scene);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(coverQImg));
    scene->addItem(item);

    std::cout << " element path =" << m_music_list[index.row()][8].toStdString().data() << std::endl;
    ui->imageSong->show();
    outputCurrentInfo(current, index);
}

void MainWindow::on_pushButton_clicked()
{
    auto newSongTag = m_tableViewer->getResult();
    //  change filetags
    m_music_list[m_tableViewer->getIndex().row()] = std::move(newSongTag);
    m_tableModel->music_list_add(m_music_list);
    ui->mainMusicTable->setModel(m_tableModel);
}
