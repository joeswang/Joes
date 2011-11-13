#ifndef _SWFLIB_H_
#define _SWFLIB_H_

#include "types.h"

typedef signed SCOORD;

typedef struct _SRECT
{
  SCOORD	xmin;
  SCOORD	ymin;
  SCOORD	xmax;
  SCOORD	ymax;
} SRECT;

typedef struct _TAG
{
   U16		id;
   U8*		data;
   U32		memsize;

   U32		len;
   U32		pos;
   struct _TAG * next;
   struct _TAG * prev;

   U8		readBit;
   U8		writeBit;
} TAG;


typedef struct _SWF
{
  U8		fileVersion;
  U8		compressed;	/* SWF or SWC */
  U32		fileSize;
  SRECT		movieSize;
  U16		frameRate;
  U16		frameCount;
  TAG*		firstTag;
  U32		fileAttributes;
} SWF;


#define swf_ResetReadBits(tag)	if(tag->readBit) { tag->pos++; tag->readBit = 0; }

// Basic Functions
int  swf_ReadSWF(int handle,SWF* swf);
int swf_FreeTags(SWF* swf);

U32 swf_GetU32(TAG* t);

// Tag IDs (adopted from J. C. Kessels' Form2Flash)
#define ST_END                  0
#define ST_SHOWFRAME            1
#define ST_DEFINESHAPE          2
#define ST_FREECHARACTER        3
#define ST_PLACEOBJECT          4
#define ST_REMOVEOBJECT         5
#define ST_DEFINEBITS           6
#define ST_DEFINEBITSJPEG       6
#define ST_DEFINEBUTTON         7
#define ST_JPEGTABLES           8
#define ST_SETBACKGROUNDCOLOR   9
#define ST_DEFINEFONT           10
#define ST_DEFINETEXT           11
#define ST_DOACTION             12
#define ST_DEFINEFONTINFO       13
#define ST_DEFINESOUND          14 /* Event sound tags. */
#define ST_STARTSOUND           15
#define ST_DEFINEBUTTONSOUND    17
#define ST_SOUNDSTREAMHEAD      18
#define ST_SOUNDSTREAMBLOCK     19
#define ST_DEFINEBITSLOSSLESS   20 /* A bitmap using lossless zlib compression. */
#define ST_DEFINEBITSJPEG2      21 /* A bitmap using an internal JPEG compression table. */
#define ST_DEFINESHAPE2         22
#define ST_DEFINEBUTTONCXFORM   23
#define ST_PROTECT              24 /* This file should not be importable for editing. */
#define ST_PLACEOBJECT2         26 /* The new style place w/ alpha color transform and name. */
#define ST_REMOVEOBJECT2        28 /* A more compact remove object that omits the character tag (just depth). */
#define ST_FREEALL              31 /* ? */
#define ST_DEFINESHAPE3         32 /* A shape V3 includes alpha values. */
#define ST_DEFINETEXT2          33 /* A text V2 includes alpha values. */
#define ST_DEFINEBUTTON2        34 /* A button V2 includes color transform, alpha and multiple actions */
#define ST_DEFINEBITSJPEG3      35 /* A JPEG bitmap with alpha info. */
#define ST_DEFINEBITSLOSSLESS2  36 /* A lossless bitmap with alpha info. */
#define ST_DEFINEEDITTEXT       37
#define ST_DEFINEMOVIE          38
#define ST_DEFINESPRITE         39 /* Define a sequence of tags that describe the behavior of a sprite. */
#define ST_NAMECHARACTER        40 /* Name a character definition, character id and a string, (used for buttons, bitmaps, sprites and sounds). */
#define ST_SERIALNUMBER         41
#define ST_GENERATORTEXT        42 /* contains an id */
#define ST_FRAMELABEL           43 /* A string label for the current frame. */
#define ST_SOUNDSTREAMHEAD2     45 /* For lossless streaming sound, should not have needed this... */
#define ST_DEFINEMORPHSHAPE     46 /* A morph shape definition */
#define ST_DEFINEFONT2          48
#define ST_TEMPLATECOMMAND      49
#define ST_GENERATOR3           51
#define ST_EXTERNALFONT         52
#define ST_EXPORTASSETS		56
#define ST_IMPORTASSETS		57
#define ST_ENABLEDEBUGGER	58
#define ST_DOINITACTION         59
#define ST_DEFINEVIDEOSTREAM    60
#define ST_VIDEOFRAME           61
#define ST_DEFINEFONTINFO2	62
#define ST_MX4			63 /*(?) */
#define ST_ENABLEDEBUGGER2      64 /* version 8 */
#define ST_SCRIPTLIMITS		65 /* version 7- u16 maxrecursedepth, u16 scripttimeoutseconds */
#define ST_SETTABINDEX		66 /* version 7- u16 depth(!), u16 tab order value */
#define ST_FILEATTRIBUTES	69 /* version 8 (required)- */
#define ST_PLACEOBJECT3		70 /* version 8 */
#define ST_IMPORTASSETS2	71 /* version 8 */
#define ST_RAWABC               72 /* version 9, used by flex */
#define ST_DEFINEFONTALIGNZONES 73 /* version 8 */
#define ST_CSMTEXTSETTINGS	74 /* version 8 */
#define ST_DEFINEFONT3		75 /* version 8 */
#define ST_SYMBOLCLASS		76 /* version 9 */
#define ST_METADATA		77 /* version 8 */
#define ST_DEFINESCALINGGRID    78 /* version 8 */
#define ST_DOABC		82 /* version 9 */
#define ST_DEFINESHAPE4		83 /* version 8 */
#define ST_DEFINEMORPHSHAPE2    84 /* version 8 */
#define ST_SCENEDESCRIPTION	86 /* version 9 */
#define ST_DEFINEBINARY		87 /* version 9 */
#define ST_DEFINEFONTNAME	88 /* version 9 */

/* custom tags- only valid for swftools */
#define ST_REFLEX              777 /* to identify generator software */
#define ST_GLYPHNAMES          778

#endif //  _SWFLIB_H_
