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

using std::cout;
using std::endl;

void read_tags(char *file_name);
void load_lyrics(char *file_name);
void load_cover(char *file_name);
void modify_tag(char *file_name);

#endif //UTAG_TAG_FUNCTIONS_H
