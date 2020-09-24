//
// Created by snikolayen on 24.09.2020.
//

#ifndef UTAG_SOUNDPLAYER_H
#define UTAG_SOUNDPLAYER_H
#include <QWidget>
#include <QMediaPlayer>



class SoundPlayer : public QWidget {

protected:
    QMediaPlayer* m_player;

};


#endif //UTAG_SOUNDPLAYER_H
