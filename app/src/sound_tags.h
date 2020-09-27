//
// Created by Serhiy Nikolayenko on 9/25/20.
//

#ifndef UTAG_SOUND_TAGS_H
#define UTAG_SOUND_TAGS_H


#include <QCoreApplication>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <iostream>

class Sound_tags {
public:
    Sound_tags();
    ~Sound_tags();
    void read_tags(QString file, QString file_path);

private:
    QMediaPlayer *sound_file;
    QVector<QString> tags{10};

public:

//    Sound_tags(QMediaPlayer *soundFile);

    QVector <QString> get_vector() const;

    void print_tags() const;

};


#endif //UTAG_SOUND_TAGS_H
