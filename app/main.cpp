#include <iomanip>
#include <iostream>
#include <string>

#include "tag_functions.h"
#include "src/mainwindow.h"

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

#include <iomanip>
#include <string>
#include <iostream>
#include <dirent.h>

#include "src/mainwindow.h"

#include <QApplication>
int main( int argc, char **argv ) {
//    modify_tag(argv[1]);
//    load_lyrics(argv[1]);
//    read_tags(argv[1]);
//
    QApplication app( argc, argv );
    MainWindow window((QString(argv[1])));
    window.show();


//    QApplication app(argc, argv);
//    QWidget *window = new QWidget;
//
//    QLabel *nameLabel = new QLabel("Open Happiness");
//    QLineEdit *firstNameLineEdit= new QLineEdit;
//    QLineEdit *lastNameLineEdit= new QLineEdit;
//    QSpinBox *ageSpinBox = new QSpinBox;
//    ageSpinBox->setRange(1, 100);
//    QComboBox *employmentStatusComboBox= new QComboBox;
//    QStringList employmentStatus = {"Unemployed", "Employed", "NA"};
//    employmentStatusComboBox->addItems(employmentStatus);
//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(nameLabel, 0, 0);
//    layout->addWidget(firstNameLineEdit, 0, 1);
//    layout->addWidget(lastNameLineEdit, 0, 2);
//    layout->addWidget(ageSpinBox, 1, 0);
//    layout->addWidget(employmentStatusComboBox, 1, 1,1,2);
//    window->setLayout(layout);
//    window->show();
//    DIR *dp;
//    struct dirent *dirp;
//    if (argc != 2) {
//        return 1;
//    }



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