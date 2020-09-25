#ifndef UTAG_SOUNDPLAYER_H
#define UTAG_SOUNDPLAYER_H
#include <QWidget>
#include <QMediaPlayer>
#include "ui_mainwindow.h"

class SoundPlayer {
public:
    SoundPlayer(Ui::MainWindow *child);
    ~SoundPlayer();

    void setSound(QString path);

public slots:
    void setPlay();
    void setPause();
    void setStop();
    void setVolume();
    void setPosition();

private:
    QMediaPlayer *m_player;
    Ui::MainWindow *m_child;
};


#endif //UTAG_SOUNDPLAYER_H
