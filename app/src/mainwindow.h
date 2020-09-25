#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdexcept>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QDir>
#include <QTreeView>
#include <QString>
#include <QStringList>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QMediaMetaData>
#include <QMetaDataReaderControl>

#include <iostream>
#include "tag_functions.h"
#include "tableviewer.h"
#include "musictablemodel.h"
#include "sound_tags.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString path = "~/", QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_fileBrowser_clicked(const QModelIndex &index);

    void on_mainMusicTable_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *m_dirmodel;
    QVector<QVector<QString>> m_music_list;
    TableViewer *m_tableViewer;
    MusicTableModel *m_tableModel;
    QString m_path;
    void outputCurrentInfo(const QVector<QString> &current, const QModelIndex &index);
};

char *toChar(QString str);

#endif // MAINWINDOW_H
