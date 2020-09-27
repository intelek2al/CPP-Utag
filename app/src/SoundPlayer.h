#ifndef UTAG_SOUNDPLAYER_H
#define UTAG_SOUNDPLAYER_H
#include <QWidget>
#include <QMediaPlayer>
#include <QTime>
//#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class SoundPlayer {
public:
    SoundPlayer(Ui::MainWindow *child);
    ~SoundPlayer();

    void setSound(QString path);

public slots:
    void setPlay();
    void setPause();
    void setStop();
    void setVolume(int position);
    void setPosition(int position);
    void setMovedPosition(int position);

private:
    QMediaPlayer *m_player;
    Ui::MainWindow *ui;
};


#endif //UTAG_SOUNDPLAYER_H
