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

    return app.exec();
}





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