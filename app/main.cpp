#include <iomanip>
#include <iostream>
//#include "../taglib/tag.h"
#include "../../taglib/taglib/tag.h"
#include <../taglib/fileref.h>
#include <toolkit/tpropertymap.h>
#include <sys/stat.h>
#include <dirent.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        return 1;
    }

//    struct stat buf;
    if ((dp = opendir(argv[1])) == NULL) {
        std::cerr << "error open folder" << endl;
    }
    while((dirp = readdir(dp)) != NULL) {

        cout << "******************** \"" << dirp->d_name << "\" ********************" << endl;

        TagLib::FileRef f(dirp->d_name);

        if (!f.isNull() && f.tag()) {

            TagLib::Tag *tag = f.tag();

            cout << "-- TAG (basic) --" << endl;

            cout << "Artist  - \"" << tag->artist() << "\"" << endl;
            cout << "Title   - \"" << tag->title() << "\"" << endl;
            cout << "Album   - \"" << tag->album() << "\"" << endl;
            cout << "Genre   - \"" << tag->genre() << "\"" << endl;
            cout << "year    - \"" << tag->year() << "\"" << endl;
            cout << "comment - \"" << tag->comment() << "\"" << endl;
            cout << "track   - \"" << tag->track() << "\"" << endl;

            TagLib::PropertyMap tags = f.file()->properties();

            unsigned int longest = 0;
            for (TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                if (i->first.size() > longest) {
                    longest = i->first.size();
                }
            }

            cout << "-- TAG (properties) --" << endl;
            for (TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                for (TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
                    cout << std::left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
                }
            }
        }

        if (!f.isNull() && f.audioProperties()) {

            TagLib::AudioProperties *properties = f.audioProperties();

            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

            cout << "-- AUDIO --" << endl;
            cout << "bitrate     - " << properties->bitrate() << endl;
            cout << "sample rate - " << properties->sampleRate() << endl;
            cout << "channels    - " << properties->channels() << endl;
            cout << "length      - " << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << endl;
        }
        cout << "========================== end ===========================" << endl;
    }

    return 0;
}

/*
if (lstat(argv[1], &buf) < 0) {
std::cerr << "ошибка вызова функции lstat" << endl;
}

if (S_ISDIR(buf.st_mode)) {
std::cerr << " argv not a folder" << endl;
return 1;
}

 */