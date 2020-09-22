//
// Created by Serhiy Nikolayenko on 9/18/20.
//

#ifndef UTAG_TAG_FUNCTIONS_H
#define UTAG_TAG_FUNCTIONS_H

#include <iostream>
#include <iomanip>

#include "../../3dparty/taglib/taglib/toolkit/tpropertymap.h"
#include "../../3dparty/taglib/taglib/fileref.h"
#include "../../3dparty/taglib/taglib/tag.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/id3v2frame.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
#include "../../3dparty/taglib/taglib/mpeg/mpegfile.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/id3v2tag.h"
#include "../../3dparty/taglib/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
#include "../../build/3dparty/taglib/taglib_config.h"
#include "../../cmake-build-debug/3dparty/taglib/taglib_config.h"

using std::cout;
using std::endl;

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

void read_tags(char *file_name);

void load_lyrics(char *file_name);

void load_cover(char *file_name);




#endif //UTAG_TAG_FUNCTIONS_H
