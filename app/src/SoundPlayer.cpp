#include "SoundPlayer.h"
#include "ui_mainwindow.h"


SoundPlayer::SoundPlayer(Ui::MainWindow *child)
{
    m_player = new QMediaPlayer();
    ui = child;
}

SoundPlayer::~SoundPlayer()
{
    delete m_player;
}

#include <QMediaMetaData>

void SoundPlayer::setSound(QString path)
{
    m_player->setMedia(QUrl::fromLocalFile(path));
    if (m_player->isMetaDataAvailable())
        ui->statusbar->showMessage("Audio Avalib ", 2000);
    else {
        while (!m_player->isMetaDataAvailable()) {
            QCoreApplication::processEvents();
        }
    }
    QStringList list = m_player->availableMetaData();
    if (m_player->isMetaDataAvailable())
    ui->statusbar->showMessage("Audio Not Avalib " + m_player->metaData(QStringLiteral("Title")).toString(), 2000);

//    m_player->isMetaDataAvailable();
    m_player->play();
    ui->playButton->click();
}

void SoundPlayer::setPlay()
{
    m_player->play();
}

void SoundPlayer::setPause()
{
    m_player->pause();
}

void SoundPlayer::setStop()
{
    m_player->stop();
}

void SoundPlayer::setVolume(int position)
{
    m_player->setVolume(position);
}

void SoundPlayer::setPosition(int position)
{
    if (ui->statusPlay->maximum() != m_player->duration())
       ui->statusPlay->setMaximum(static_cast<int>(m_player->duration()));
    ui->statusPlay->setValue(position);

    int sececonds = (position / 1000) % 60;
    int minute = (position / 60000) % 60;
    int hours = (position / 3600000) % 24;
    QTime time{hours, minute, sececonds};
}

void SoundPlayer::setMovedPosition(int position)
{
    m_player->setPosition(position);
}
