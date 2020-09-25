//
// Created by Serhiy Nikolayenko on 9/25/20.
//

//    {"Name", "Time", "Title", "Artist", "Genre", "Album", "Year", "Track", "Path", "Comment" };

#include "sound_tags.h"

#include <utility>

Sound_tags::Sound_tags() {
    sound_file = new QMediaPlayer;
}

void Sound_tags::read_tags(QString file, QString file_path) {

    sound_file->setMedia(QUrl::fromLocalFile(file_path));
    while(!sound_file->isMetaDataAvailable()){
        QCoreApplication::processEvents();
    }
    tags[0] = file;
    tags[1] = "00 :01";
    tags[2] = sound_file->metaData(QStringLiteral("Title")).toString();
    tags[3] = sound_file->metaData(QStringLiteral("ContributingArtist")).toString();
    tags[4] = sound_file->metaData(QStringLiteral("Genre")).toString();
    tags[5] = sound_file->metaData(QStringLiteral("AlbumTitle")).toString();
    tags[6] = sound_file->metaData(QStringLiteral("Year")).toString();
    tags[7] = sound_file->metaData(QStringLiteral("TrackNumber")).toString();
    tags[8] = file_path;
    tags[9] = sound_file->metaData(QStringLiteral("Comment")).toString();

    std::cout << "Year" <<
    sound_file->metaData(QStringLiteral("Year")).toString().toStdString() << std::endl;
}

Sound_tags::~Sound_tags() {

    std::cout << "destructor Sound_tags" << std::endl;
    delete sound_file;
}

QVector<QString> Sound_tags::get_vector() const {
    return tags;
}

void Sound_tags::print_tags() const {
    std::cout << "\n vector tags\n";
    std::cout << "file name \t"   << tags[0].toStdString() << std::endl <<
     "Time \t\t =" << tags[1].toStdString() << std::endl <<
     "Title \t\t ="   << tags[2].toStdString() << std::endl <<
    "AlbumArtist \t ="   << tags[3].toStdString() << std::endl <<
     "Genre \t ="   << tags[4].toStdString() << std::endl <<
     "AlbumTitle \t ="   << tags[5].toStdString() << std::endl <<
     "Year \t\t ="   << tags[6].toStdString() << std::endl <<
     "TrackNumber \t ="   << tags[7].toStdString() << std::endl <<
     "file path \t ="   << tags[8].toStdString() << std::endl <<
    "Comment  \t ="   << tags[9].toStdString() << std::endl;


    for (auto& elem  : tags) {
        std::cout << elem.toStdString() << std::endl;
    }

}


