#include <iomanip>
#include <iostream>
#include <string>

#include "tag_functions.h"
#include "dialog.h"

#include "../../taglib/taglib/tag.h"
#include <../taglib/fileref.h>
#include <../taglib/mpeg/id3v2/id3v2tag.h>
#include <../taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h>
#include <../taglib/mpeg/id3v2/id3v2frame.h>
#include <../taglib/mpeg/id3v2/frames/attachedpictureframe.h>
#include <../taglib/mpeg/mpegfile.h>
#include <toolkit/tpropertymap.h>


#include <sys/stat.h>
#include <dirent.h>

#include <QtGui>
#include <QtCore>
#include <QFile>
#include <QDialog>
#include <QApplication>
#include <QLabel>
#include <zconf.h>
//#include <QMediaMetaData>

using std::cout;
using std::endl;



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QLabel label("Hello world !");
    label.setStyleSheet("QLabel:hover { color: rgb(60, 179, 113)}");
//    Dialog ()
    label.show();

//    DIR *dp;
//    struct dirent *dirp;

//    if (argc != 2) {
//        return 1;
//    }

//    Qfile file;
//    struct stat buf;

/*
    if ((dp = opendir(argv[1])) == NULL) {
        std::cerr << "error open folder" << endl;
    }
//    while((dirp = readdir(dp)) != NULL) {

    modify_tag(argv[1]);

        cout << "******************** \"" << argv[1] << "\" ********************" << endl;
        TagLib::FileRef f(argv[1]);

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

            cout << "-- AUDIO --" << endl;
            cout << "bitrate     - " << properties->bitrate() << endl;
            cout << "sample rate - " << properties->sampleRate() << endl;
            cout << "channels    - " << properties->channels() << endl;
            cout << "length      - " << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << endl;
        }
*/

    cout << "-- LYRICS --" << endl;
    load_lyrics(argv[1]);

//    cout << "-- COVER --" << endl;
//    load_cover(argv[1]);
        cout << "========================== end ===========================" << endl;
//    }



    return app.exec();
}

/*
if (lstat(argv[1], &buf) < 0) {
std::cerr << "ошибка вызова функции lstat" << endl;
}

if (S_ISDIR(buf.st_mode)) {
std::cerr << " argv not a folder" << endl;
return 1;
}

 */