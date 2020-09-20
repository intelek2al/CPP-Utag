//
// Created by Serhiy Nikolayenko on 9/18/20.
//

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
                std::cout << frames.front()->toString() << std::endl;
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
    } else {
        std::cout << "id3v2 not present";
    }
}

