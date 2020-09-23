
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
    unsigned long Size;

    FILE *jpegFile;
    jpegFile = fopen("FromId3.jpg", "wb");

    if (id3v2tag) {
        // picture frame
        Frame = id3v2tag->frameListMap()[IdPicture];
        if (!Frame.isEmpty()) {
            for (TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it) {
                PicFrame = (TagLib::ID3v2::AttachedPictureFrame * )(*it);
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

void modify_tag(char *file_name)
{
    TagLib::FileRef f(file_name);

    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        tag->setArtist("MOBY_2");
        // "Tiesto feat. GALXARA"
    }
    f.save();
}




QVector<QString> read_tags(char *file_name, char *file_path) {

    std::string file_n= file_name;
    cout << "============== \"" << file_n << "\" =======================" << endl;
    TagLib::FileRef f(file_path);
    QVector<QString> data;

//    {"Title", "Artist", "Gener", "Album", "Year", "Track"};
    if (!f.isNull() && f.tag()) {

        TagLib::Tag *tag = f.tag();


        data.push_back(QString(file_n.data()));
        data.push_back( tag->title() != TagLib::String::null ? tag->title().toCString(): "");
        data.push_back(tag->artist() != TagLib::String::null ? tag->artist().toCString(): "");
        data.push_back(tag->genre() != TagLib::String::null ? tag->genre().toCString(): "");
        data.push_back(tag->album() != TagLib::String::null ? tag->album().toCString(): "");
//        std::string year = std::to_string(tag->year());
//        data.push_back(QString::fromStdString(std::to_string(tag->year())));
//        data.push_back(QString::fromStdString(std::to_string(tag->track())));
        data.push_back("");
        data.push_back("");

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

//        data.push_back(QString::fromStdString(std::to_string(minutes) +
//                                                      ":" + std::to_string(seconds)));
        data.push_back("");// time
        cout << "-- AUDIO --" << endl;
        cout << "bitrate     - " << properties->bitrate() << endl;
        cout << "sample rate - " << properties->sampleRate() << endl;
        cout << "channels    - " << properties->channels() << endl;
        cout << "length      - " << minutes << ":" << std::setfill('0')
                                 << std::setw(2) << seconds << endl;
    }

    std::cout << " print vector\n {" << std::endl;
    for (auto& item : data) {
        std::cout << item.toStdString() << "\t";
    }
    std::cout << "}" << std::endl;
    cout << "==============  end  =======================" << endl;
//    data.pop_back();

    return data;
}