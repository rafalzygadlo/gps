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
#define KEY_CHECK_LOG		"log"
#define KEY_RUNNING			"running"
#define KEY_BOAT_TYPE		"boatType"

#define MIN_RECT_HEIGHT 100		// minimalna wysoko�c zaznaczenia
#define MIN_RECT_WIDTH 100		// minimalna szeroko�� zaznaczenia
#define HINT_WIDTH	20			// szeroko�� hinta

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

#define BUILD_GPS_POINTS_VECTOR			// czy ma budowa� list� punkt�w

// messages
#define MSG_CONNECT					0
#define MSG_DISCONNECT				1
#define MSG_PORT_INFO				2
#define MSG_SCAN					3
#define MSG_CLOSE					4
#define MSG_SHOW_LOG				5
#define MSG_SCANNING_PORTS			6
#define MSG_GPS_CONFIG_NOT_EXISTS	7
#define MSG_PORT					8
#define MSG_BAUD					9
#define MSG_SIGNALS_INFO			10
#define MSG_FONT_NOT_EXISTS			11
#define MSG_DISTANCE_UNITS			12
#define MSG_OK						13
#define MSG_CANCEL					14
#define MSG_ALARM_CONFIG			15
#define MSG_BOAT_CONFIG				16
#define MSG_GPS						17
#define MSG_SETTINGS				18
#define MSG_DISTANCE_UNIT_CONFIG	19
#define MSG_SHIP1					20
#define MSG_SHIP2					21
#define MSG_BOAT1					22
#define MSG_BOAT2					23
#define MSG_TRIANGLE				24
#define MSG_BAD_CRC					25
#define MSG_STATUS					26
#define MSG_CONNECTED				27
#define MSG_NMEA_LINES				28
#define MSG_SIGNAL_QUALITY			29
#define MSG_NEW_TRACK_RECORD		30



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
#define KEY_DISTANCE_UNIT "distance_unit"

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


#define NV_PI 3.1415926535897932384626433
enum nvDistanceUnits { nvNauticMiles, nvKilometer, nvMeter, nvDistanceSize = 3 };

#define TITLE_FONT_SIZE 8

struct SPoint
{
	double x;
	double y;
};
 
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


// globalne identyfikatory event�w
enum
{
    ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,

};
#endif
