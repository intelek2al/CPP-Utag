#include <iomanip>
#include <iostream>
#include <string>

#include "src/tag_functions.h"
#include "src/mainwindow.h"

#include <sys/stat.h>
#include <dirent.h>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
//#include <QMediaMetaData>
#include <QDir>
using std::cout;
using std::endl;

#include <QApplication>
int main(int argc, char **argv)
{
//        modify_tag(argv[1]);
//        load_lyrics(argv[1]);
//        read_tags(argv[1]);

    QApplication app(argc, argv);
    MainWindow window((QString(argv[1])));
    window.show();

//    QCoreApplication app(argc, argv);


    return app.exec();
}

t 
//    if ((dp = opendir(argv[1])) == NULL) {
//        std::cerr << "error open folder" << endl;
//    }
//    while((dirp = readdir(dp)) != NULL) {

//    modify_tag(argv[1]);
//    cout << "-- LYRICS --" << endl;
//    load_lyrics(argv[1]);
//    cout << "-- COVER --" << endl;
//    load_cover(argv[1]);

/*
if (lstat(argv[1], &buf) < 0) {
std::cerr << "ошибка вызова функции lstat" << endl;
}

if (S_ISDIR(buf.st_mode)) {
std::cerr << " argv not a folder" << endl;
return 1;
}

 */


/*
 *     QDir dir("/Users/snikolayen/___test_media/");

    if(!dir.exists()) {
        std::cout << "dir not opend" << std::endl;
    };

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setNameFilters(QStringList() << "*.mp3"
                                                   << "*.flac"
                                                   << "*.wav"
                                                   << "*.ogg"
                                                   << "*.aif");


//    QDir dir;
//    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    std::cout << "     Bytes Filename" << std::endl;
    for (int i = 0; i < list.size(); ++i) {

        QFileInfo fileInfo = list.at(i);
        cout << "============== \"" << fileInfo.fileName().toStdString() << "\" =======================" << endl;
//        std::cout << qPrintable(QString("%1 %2 %").arg(fileInfo.size(), 10)
//                                        .arg(fileInfo.fileName()));
        TagLib::FileRef f (toChar(QString(fileInfo.fileName())));
        QVector<QString> data;

        if (!f.isNull() && f.tag()) {

            TagLib::Tag *tag = f.tag();

            cout << "-- TAG (basic) --" << endl;
            cout << "Artist  - \"" << tag->artist() << "\"" << endl;
            cout << "Title   - \"" << tag->title() << "\"" << endl;
            cout << "Album   - \"" << tag->album() << "\"" << endl;
            cout << "Genre   - \"" << tag->genre() << "\"" << endl;
            cout << "year    - \"" << tag->year() << "\"" << endl;
            cout << "comment - \"" << tag->comment() << "\"" << endl;
            cout << "track   - \"" << tag->track() << "\"" << endl;


            TagLib::PropertyMap tags = f.file()->properties();

            unsigned int longest = 0;
            for (TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                if (i->first.size() > longest) {
                    longest = i->first.size();
                }
            }

            cout << "-- TAG (properties) --" << endl;
            for (TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                for (TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
                    cout << std::left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
                }
            }
        }

        if (!f.isNull() && f.audioProperties()) {

            TagLib::AudioProperties *properties = f.audioProperties();

            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

//        data.push_back(QString::fromStdString(std::to_string(minutes) +
//                                                      ":" + std::to_string(seconds)));
            data.push_back("");// time
            cout << "-- AUDIO --" << endl;
            cout << "bitrate     - " << properties->bitrate() << endl;
            cout << "sample rate - " << properties->sampleRate() << endl;
            cout << "channels    - " << properties->channels() << endl;
            cout << "length      - " << minutes << ":" << std::setfill('0')
                 << std::setw(2) << seconds << endl;
        }


        std::cout << std::endl;
    }
    cout << "============== end =======================" << endl;

 */