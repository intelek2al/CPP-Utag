#include <iomanip>
#include <iostream>
#include <string>
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

//#include <QtGui>
//#include <QtCore>
//#include <QFile>
//#include <QMediaMetaData>

using std::cout;
using std::endl;

/*
 *
 * <Header for 'Attached picture', ID: "APIC">
 * Text encoding   $xx
 * MIME type       <text string> $00
 * Picture type    $xx
 * Description     <text string according to encoding> $00 (00)
 * Picture data    <binary data>
 *
 * Picture type:
    $00     Other
    $01     32x32 pixels 'file icon' (PNG only)
    $02     Other file icon
    $03     Cover (front)
    $04     Cover (back)
    $05     Leaflet page
    $06     Media (e.g. lable side of CD)
    $07     Lead artist/lead performer/soloist
    $08     Artist/performer
    $09     Conductor
    $0A     Band/Orchestra
    $0B     Composer
    $0C     Lyricist/text writer
    $0D     Recording Location
    $0E     During recording
    $0F     During performance
    $10     Movie/video screen capture
    $11     A bright coloured fish
    $12     Illustration
    $13     Band/artist logotype
    $14     Publisher/Studio logotype
 */

void load_cover(char * file_name) {
    static const char *IdPicture = "APIC";  //  APIC    [#sec4.15 Attached picture]

    TagLib::MPEG::File mpegFile (file_name);
    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame ;
    TagLib::ID3v2::AttachedPictureFrame *PicFrame;

    void  *SrcImage ;
    unsigned long Size ;

    FILE *jpegFile;
    jpegFile = fopen("FromId3.jpg","wb");

    if ( id3v2tag ) {
        // picture frame
        Frame = id3v2tag->frameListMap()[IdPicture];
        if (!Frame.isEmpty() ) {
            for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it) {
                PicFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it); {
                  if ( PicFrame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)

                    // extract image (in it’s compressed form)
                    Size = PicFrame->picture().size();
                    SrcImage = malloc ( Size );
                    if ( SrcImage ) {
                        memcpy ( SrcImage, PicFrame->picture().data(), Size );
                        fwrite(SrcImage,Size,1, jpegFile);
                        fclose(jpegFile);
                        free( SrcImage );
                    }
                }
            }
        }
    }
    else {
        std::cout << "id3v2 not present";
    }
}

/* Unsychronised lyrics/text transcription
 * This frame contains the lyrics of the song or a text transcription of other vocal activities.
 * The head includes an encoding descriptor and a content descriptor. The body consists of the actual text.
 * The 'Content descriptor' is a terminated string. If no descriptor is entered,
 * 'Content descriptor' is $00 (00) only. Newline characters are allowed in the text.
 * There may be more than one 'Unsynchronised lyrics/text transcription' frame in each tag,
 * but only one with the same language and content descriptor.
 *
 * <Header for 'Unsynchronised lyrics/text transcription', ID: "USLT">
    Text encoding       $xx
    Language            $xx xx xx
    Content descriptor  <text string according to encoding> $00 (00)
    Lyrics/text         <full text string according to encoding>
*/


void load_lyrics(char *file_name) {
    TagLib::MPEG::File f1 (file_name);

    if (f1.ID3v2Tag()) {
        TagLib::ID3v2::FrameList frames = f1.ID3v2Tag()->frameListMap()["USLT"];

        if (!frames.isEmpty()) {
            TagLib::ID3v2::UnsynchronizedLyricsFrame *frame =
                    dynamic_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame *>(frames.front());
            // There could be multiple frames here; you may want to look at language
            // and/or description, instead of just picking the first.
            if (frame)
                std ::cout << frames.front()->toString() << std::endl;
        }
    }
}



void modify_tag(char *file_name) {
    TagLib::FileRef f(file_name);

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        tag->setArtist("MOBY_2");
        // "Tiesto feat. GALXARA"
    }
    f.save();
}

int main(int argc, char *argv[]) {
    DIR *dp;
//    struct dirent *dirp;

    if (argc != 2) {
        return 1;
    }

//    Qfile file;
//    struct stat buf;
    if ((dp = opendir(argv[1])) == NULL) {
        std::cerr << "error open folder" << endl;
    }
//    while((dirp = readdir(dp)) != NULL) {

    modify_tag(argv[1]);

        cout << "******************** \"" << argv[1] << "\" ********************" << endl;
        TagLib::FileRef f(argv[1]);

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

    cout << "-- LYRICS --" << endl;
    load_lyrics(argv[1]);

    cout << "-- COVER --" << endl;
    load_cover(argv[1]);
        cout << "========================== end ===========================" << endl;
//    }

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