//
// Created by Serhiy Nikolayenko on 9/18/20.
//

#ifndef UTAG_TAG_FUNCTIONS_H
#define UTAG_TAG_FUNCTIONS_H

#include "../../taglib/taglib/tag.h"
#include <../taglib/fileref.h>
#include <../taglib/mpeg/id3v2/id3v2tag.h>
#include <../taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h>
#include <../taglib/mpeg/id3v2/id3v2frame.h>
#include <../taglib/mpeg/id3v2/frames/attachedpictureframe.h>
#include <../taglib/mpeg/mpegfile.h>


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


void load_lyrics(char *file_name);

void load_cover(char * file_name);

void modify_tag(char *file_name) {
    TagLib::FileRef f(file_name);

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        tag->setArtist("MOBY_2");
        // "Tiesto feat. GALXARA"
    }
    f.save();
}

#endif //UTAG_TAG_FUNCTIONS_H
