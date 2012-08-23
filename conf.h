#ifndef __CONF
#define __CONF
#include <nmea/nmea.h>
#include <wx/wx.h>

typedef enum nvSpeed	{nvKn, nvkmh, nvms, nvmph, nvfts, NVSPEED_COUNT = 5};
typedef enum nvLon		{nvdegree, NVLON_COUNT = 1};
typedef enum nvDate		{nvYYMMHH, nvMMDDYY, NVDATE_COUNT = 2};




#define COMMENT
#define PI 3.1415926535897932384626433832795

#ifdef _WIN32
	#define DIR_SEPARATOR "\\"
#endif

#if defined(_LINUX32) || (_LINUX64)
	#define DIR_SEPARATOR "/"
#endif

#define POS_IN_BUF( ptr1, ptr_Buffer ) ( ((size_t)ptr_Buffer)-((size_t)ptr1) )
#define BUFFER_LENGTH 1024

#define PRODUCT_NAME		"GPS Plugin"
#define PRODUCT_VERSION		"0.1"
#define PRODUCT_COPYRIGHT	"Copyright 2010/2011 by NavSim. All rights reserved"
#define PLUGIN_CONFIG_FILE	"gps.conf"

#define KEY_PORT			"port"
#define KEY_BAUD			"baud"
#define KEY_PORT_INDEX		"pindex"
#define KEY_BAUD_INDEX		"bindex"
#define KEY_AUTO			"auto"
#define KEY_CHECK_LOG		"log"
#define KEY_CHECK_HINT		"hint"
#define KEY_AREA_SIZE		"size"

#define MIN_RECT_HEIGHT 100		// minimalna wysokoœc zaznaczenia
#define MIN_RECT_WIDTH 100		// minimalna szerokoœæ zaznaczenia
#define HINT_WIDTH	20			// szerokoœæ hinta

#define GPS_OUT_OF_COORDS 256
#define NUMBER_OF_INVALID_TRIES 10
#define DEFAULT_SELECTION_SIZE 200 // mil morskich
#define DEFAULT_AREA_SIZE 1.2	  // w stopniach

#define X_VALUE		0
#define Y_VALUE		1
#define Z_VALUE		2
#define X_ANGLE		3
#define Y_ANGLE		4
#define Z_ANGLE		5
#define AREA_MINX	6
#define AREA_MINY	7
#define AREA_MAXX	8
#define AREA_MAXY	9

//#define BUILD_GPS_POINTS_VECTOR			// czy ma budowaæ listê punktów

// messages
#define MSG_0 "Not valid GPS signal"
#define MSG_1 "Searching on Port: %s BaudRate: %d \n"
#define MSG_2 "Found GPS signal on Port: %d BaudRate: %d"
#define MSG_3 "Searching mode"
#define MSG_4 "Gps Fix: %d"
#define MSG_5 "\nChecking system ports\n"

#define nvPI 3.1415926535897932384626433832795
#define ID_MENU_BEGIN 1000
#define ID_MENU_END 1100
#define DEFAULT_PRECISION 2
#define DEFAULT_FORMAT 0
#define DEFAULT_CONTROL_TYPE 1000
#define SATTELITE_RADIUS 8
#define DIR_WORKDIR "workdir"

#define KEY_CONTROL_PRECISION "precision"
#define KEY_CONTROL_TYPE "control_type"
#define KEY_FORMAT_TYPE	"format_type"

#define SPEED_KNOT 0
#define SPEED_KMH 1
#define SPEED_MS 2
#define SPEED_MPH 3
#define SPEED_FTS 4

#define LON_NORMAL 0
#define LAT_NORMAL 0

#define DATE_YYMMDD 0
#define DATE_MMDDYY 1

#define MS 0.514444444
#define KMH 1.852
#define MPH	1.150779
#define FTS 1.687810

#define GPS_FIX_NA 1
#define GPS_FIX_2D 2
#define GPS_FIX_3D 3

#define GPS_QUALITY_INVALID 0
#define GPS_QUALITY_FIX 1
#define GPS_QUALITY_DIFFERENTIAL 2
#define GPS_QUALITY_SENSITIVE 3

#define FONT_DIRECTION_SIZE 14
#define BACKGROUND_BRUSH_COLOR 255,255,255
#define BACKGROUND_TEXT_COLOR 94,133,172
#define OUTER_CIRCLE_COLOR 94,133,172
#define LINE_COLOR 255,255,255
#define ARROW_COLOR 255,255,255


#define TRACK_FILE_EXTENSION "track"

#define NOT_AVAILABLE "N/A"

#define SIGNAL_SET_NMEA_INFO 		0x00001



typedef struct
{
	double x;
	double y;

} SPoint;

typedef struct
{
	double x;
	double y;
	nmeaINFO nmea_info;

} SPointInfo;

typedef struct
{
	int version;
	wchar_t track_name[128];
	bool visible;
	int colorR;
	int colorG;
	int colorB;
	

} STrackHeader;


// globalne identyfikatory eventów
enum
{
    ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,

};
#endif
