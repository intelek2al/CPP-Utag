#include "SoundPlayer.h"


SoundPlayer::SoundPlayer(Ui::MainWindow *child)
{
    m_player = new QMediaPlayer();
    m_child = child;
}

SoundPlayer::~SoundPlayer()
{
    delete m_player;
}

void SoundPlayer::setSound(QString path)
{

}

void SoundPlayer::setPlay()
{

}

void SoundPlayer::setPause()
{

}

void SoundPlayer::setStop()
{

}
