#include <regex>
#include <QImage>
#include "tag_functions.h"

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
    TagLib::MPEG::File f1(file_name);

    if (f1.ID3v2Tag()) {
        TagLib::ID3v2::FrameList frames = f1.ID3v2Tag()->frameListMap()["USLT"];

        if (!frames.isEmpty()) {
            TagLib::ID3v2::UnsynchronizedLyricsFrame *frame =
                    dynamic_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame *>(frames.front());
            // There could be multiple frames here; you may want to look at language
            // and/or description, instead of just picking the first.
            if (frame)
                std::cout << frames.front()->toString() << " here" << std::endl;
        }
    }
}

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

void load_cover(char *file_name) {
    static const char *IdPicture = "APIC";  //  APIC    [#sec4.15 Attached picture]

    TagLib::MPEG::File mpegFile(file_name);
    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame;
    TagLib::ID3v2::AttachedPictureFrame *PicFrame;

    void *SrcImage;
    unsigned long Size = 0;

    FILE *jpegFile;
    jpegFile = fopen("FromId3.jpg", "wb");

    if (id3v2tag) {
        // picture frame
        Frame = id3v2tag->frameListMap()[IdPicture];
        if (!Frame.isEmpty()) {
            for (TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it) {
                PicFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame * >(*it);
                {
                    if (PicFrame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)

                        // extract image (in it’s compressed form)
                        Size = PicFrame->picture().size();
                    SrcImage = malloc(Size);
                    if (SrcImage) {
                        memcpy(SrcImage, PicFrame->picture().data(), Size);
                        fwrite(SrcImage, Size, 1, jpegFile);
                        fclose(jpegFile);
                        free(SrcImage);
                    }
                }
            }
        }
    }
    else {
        std::cout << "id3v2 not present";
    }
}


QImage load_cover_image(char *file_path) {
//    QImage coverQImg("app/logo1.png");
    QImage coverQImg("../../app/logo1.png");

    static const char *IdPicture = "APIC";  //  APIC    [#sec4.15 Attached picture]
    TagLib::MPEG::File mpegFile(file_path);
    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame;
    TagLib::ID3v2::AttachedPictureFrame *PicFrame;

    if (id3v2tag) {
        Frame = id3v2tag->frameListMap()[IdPicture];
        if (!Frame.isEmpty()) {
            for (TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it) {
//                std::cout << "for "<< *it << std::endl;
                PicFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame * >(*it);
                {
//                    if (PicFrame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
                    if (PicFrame)
                    {
                        coverQImg.loadFromData((const uchar *) PicFrame->picture().data(), PicFrame->picture().size());
                        coverQImg = coverQImg.scaled(190, 190);
                    }
                }
            }
        }
    }
    return coverQImg;
}


static QImage load_cover_image_mpeg(char *file_path)
{
    static const char *IdPicture = "APIC";  //  APIC    [#sec4.15 Attached picture]
    TagLib::MPEG::File mpegFile(file_path);
    TagLib::ID3v2::Tag *tag = mpegFile.ID3v2Tag();
    TagLib::ID3v2::FrameList l = tag->frameList("APIC");

    QImage image;

    if(l.isEmpty())
        return QImage("../../app/logo1.png");

    TagLib::ID3v2::AttachedPictureFrame *f =
            static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());

    image.loadFromData((const uchar *) f->picture().data(), f->picture().size());
    return image;
}


unsigned int str_to_uint(const char* new_value) {
    unsigned int res = 0;

    std::regex regular(R"lit(\s*[0-9]\s*)lit");
    std::cmatch result;
    std::string line = new_value;

    if (std::regex_match(line.c_str(), result, regular)) {
        res = std::stoul(result[0]);

    } else {
        throw std::invalid_argument("invalid argument\n");
    }
    return res;
}


QVector<QString> read_tags(char *file_name, char *file_path) {
//      0       1       2           3      4          5       6       7        8       9
//    {"Name", "Time", "Title", "Artist", "Genre", "Album", "Year", "Track", "Path", "Comment" };
//    TagLib_File *file;
    QVector<QString> data;

//    file = taglib_file_new(file_path);
//    if (file == NULL) {
//        return data;
//    }

//    taglib_set_strings_unicode(FALSE);

    std::string file_n= file_name;
    std::string file_p= file_path;
    TagLib::FileRef f(file_path);

    if (!f.isNull() && f.tag()) {
        data.clear();
        data = QVector<QString>(10);
        TagLib::Tag *tag = f.tag();
        data[0] = QString(file_n.data());
        data[2] = tag->title().toCString();
        data[3] =tag->artist().toCString();
        data[4] = tag->genre().toCString();
        data[5] =tag->album().toCString();
        data[6] = (tag->year() != 0 ? QString::fromStdString(std::to_string(tag->year())): "");
        data[7] = (tag->track() != 0 ? QString::fromStdString(std::to_string(tag->track())): "");
        data[8] = QString(file_p.data());
        data[9] =tag->comment().toCString();

        /*
        cout << "-- TAG (basic) --" << endl;
        cout << "Artist  - \"" << tag->artist() << "\"" << endl;
        cout << "Title   - \"" << tag->title() << "\"" << endl;
        cout << "Album   - \"" << tag->album() << "\"" << endl;
        cout << "Genre   - \"" << tag->genre() << "\"" << endl;
        cout << "year    - \"" << tag->year() << "\"" << endl;
        cout << "comment - \"" << tag->comment() << "\"" << endl;
        cout << "track   - \"" << tag->track() << "\"" << endl;
        */

        TagLib::PropertyMap tags = f.file()->properties();

        unsigned int longest = 0;
        for (TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
            if (i->first.size() > longest) {
                longest = i->first.size();
            }
        }

//        cout << "-- TAG (properties) --" << endl;
        for (TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
            for (TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
                cout << std::left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
            }
        }
        if (!f.isNull() && f.audioProperties()) {
            TagLib::AudioProperties *properties = f.audioProperties();
            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

            data[1] =(QString::fromStdString(std::to_string(minutes) +
                                             ":" + std::to_string(seconds)));
            /*
            cout << "-- AUDIO --" << endl;
            cout << "bitrate     - " << properties->bitrate() << endl;
            cout << "sample rate - " << properties->sampleRate() << endl;
            cout << "channels    - " << properties->channels() << endl;
            cout << "length      - " << minutes << ":" << std::setfill('0')
                 << std::setw(2) << seconds << endl;
            */
        }
    }
    return data;
}

void modify_tag_artist(char *file_path, char *new_artist)
{
    TagLib::FileRef f(file_path);

    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setArtist(new_artist);
    }
    f.save();
}


void modify_tag_title(char *file_path, char *new_title) {
    TagLib::FileRef f(file_path);

    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setTitle(new_title);
    }
    f.save();
}

void modify_tag_genre(char *file_path, char *new_genre) {
    TagLib::FileRef f(file_path);

    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setGenre(new_genre);
    }
    f.save();
}

void modify_tag_album(char *file_path, char *new_album) {
    TagLib::FileRef f(file_path);

    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setAlbum(new_album);
    }
    f.save();
}

void modify_tag_comment(char *file_path, char *new_comment) {
    TagLib::FileRef f(file_path);

    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setComment(new_comment);
    }
    f.save();
}

void modify_tag_year(QVector<QString>& changes) {
    TagLib::FileRef f(changes[8].toStdString().data());
    unsigned int n_year;
    try {
        n_year = str_to_uint(changes[6].toStdString().data());
    }
    catch (std::exception& ex) {
        std::cerr << ex.what();
        changes[6] = "";
        return;
    }
    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setYear(n_year);
    }
    f.save();
}

void modify_tag_track(QVector<QString>& changes) {
    TagLib::FileRef f(changes[8].toStdString().data());
    unsigned int n_track;

    try {
        n_track = str_to_uint(changes[7].toStdString().data());
    }
    catch (std::exception& ex) {
        std::cerr << ex.what();
        changes[7] = "";
        return;
    }
    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setTrack(n_track);
    }
    f.save();
}

void modify_tag(char *file_path, char field, char *new_value) {
    TagLib::FileRef f(file_path);
    if (!f.isNull() && f.tag()) {
        unsigned int new_year = 0;
        unsigned int new_track = 0;
        TagLib::Tag *tag = f.tag();
        switch (field) {
            case 't':
                tag->setTitle(new_value);
                break;
            case 'a':
                tag->setArtist(new_value);
                break;
            case 'A':
                tag->setAlbum(new_value);
                break;
            case 'c':
                tag->setComment(new_value);
                break;
            case 'g':
                tag->setGenre(new_value);
                break;
            case 'y':
                try {
                    new_year = str_to_uint(new_value);
                }
                catch (std::exception& ex) {
                    std::cerr << ex.what();
                    break;
                }
                tag->setYear(new_year);
                break;

            case 'T':

            try {
                new_track = str_to_uint(new_value);
            }
            catch (std::exception& ex) {
                std::cerr << ex.what();
                break;
            }
                tag->setTrack(new_track);
        }
    }
}

//{"Name", "Time", "Title", "Artist", "Genre", "Album", "Year", "Track", "Path", "Comment" };

void modify_tags(QVector<QString>& changes) {
    TagLib::FileRef f(changes[8].toStdString().data());
    std::cout << "line 382\n" << std::endl;

    if (!f.isNull() && f.tag())
    {
        std::cout << "line 386\n" << std::endl;

        TagLib::Tag *tag = f.tag();
        tag->setArtist(changes[3].toStdString());
        tag->setTitle(changes[2].toStdString());
        tag->setGenre(changes[4].toStdString());
        tag->setAlbum(changes[5].toStdString());
//        tag->setComment(changes[9].toStdString());
    }
    f.save();
    modify_tag_year(changes);
    modify_tag_track(changes);
}