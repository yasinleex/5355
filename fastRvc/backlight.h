#define DATA_INFO_LEN     512
#define DATA_FILE_PATH    "/dev/block/mmcblk0"
#define CONFIGS_DATA_A_USER0_SEEK                              (14336 * 512)
#define CONFIGS_DATA_A_USER1_SEEK                              (14337 * 512)
#define CONFIGS_DATA_A_USER2_SEEK                              (14338 * 512)
#define CONFIGS_DATA_A_USER3_SEEK                              (14339 * 512)
#define CONFIGS_DATA_A_CURRENT_SEEK                            (14340 * 512)


#define CONFIGS_DATA_B_USER0_SEEK                              (14341 * 512)
#define CONFIGS_DATA_B_USER1_SEEK                              (14342 * 512)
#define CONFIGS_DATA_B_USER2_SEEK                              (14343 * 512)
#define CONFIGS_DATA_B_USER3_SEEK                              (14344 * 512)
#define CONFIGS_DATA_B_CURRENT_SEEK                            (14345 * 512)

#define CONFIGS_DATA_SIGNATURE                           (0x5aa55aa5)
#define BRIGHTNESS_FILE_PATH    	"/sys/class/backlight/backlight_lcd0/brightness"
#define KEYBRIGHTNESS_FILE_PATH 	"/sys/class/backlight/backlight_key/brightness"
enum {
	INFO_INDEX_SIGA = 0,
	INFO_INDEX_CRCC,
	INFO_INDEX_RBST,    //rgb_brightness_step
	INFO_INDEX_YBST,    //yuv_brightness_step
	INFO_INDEX_RCST,    //rgb_contrast_step
	INFO_INDEX_YCST,    //yuv_contrast_step
	INFO_INDEX_DBGS,

	INFO_INDEX_AVAIL,

	INFO_INDEX_MAX = 64,
};

enum {
	INFO_INDEX_TITA = 0,
	INFO_INDEX_CCRC,
	INFO_INDEX_CUSR,    // CURRENT USER
	INFO_INDEX_GUID,    // CAMERA PICTURE ID
	INFO_INDEX_SECU,

	INFO_INDEX_AVAI,
	INFO_INDEX_ALL = 64,
};


struct eMMC_data {
	int32_t user;
	int32_t rbst;
	int32_t ybst;
	int32_t rcst;
	int32_t ycst;
};


struct  other_data {
	int32_t cusr;
	int32_t guid;
};

const char INFO_ITEM_NAME[7][4] = {
	{'S','I','G','A'},
	{'C','R','C','C'},
	{'R','B','S','T'},
	{'Y','B','S','T'},
	{'R','C','S','T'},
	{'Y','C','S','T'},
	{'D','B','G','S'},
};

const char INFO_ITEM_OTHER[5][4] = {
	{'T','I','T','A'},
	{'C','C','R','C'},
	{'C','U','S','R'},
	{'G','U','I','D'},
	{'S','E','C','U'},
};


struct data_info_item {
	char cName[4];
	int32_t ulValue;
};

enum RETURN_VALUE {
	RETURN_OK = 0,
    RETURN_SIGNATURE,
    RETURN_CRC,
    RETURN_READ_ERROR,
    RETURN_WRITE_ERROR,
};

/*
 * COLOR
 */
#define COLOR_TUNING_INDEX 19
#define PARTIAL_Y_INDEX 10

#define GLOBAL_SAT_SIZE 10
#define CONTRAST_SIZE 34
#define BRIGHTNESS_SIZE 10
#define PARTIAL_Y_SIZE 16
#define PQ_HUE_ADJ_PHASE_CNT 4
#define PQ_SAT_ADJ_PHASE_CNT 4
#define PQ_PARTIALS_CONTROL 5
#define PURP_TONE_SIZE 3
#define SKIN_TONE_SIZE 8 //(-6)
#define GRASS_TONE_SIZE 6 //(-2)
#define SKY_TONE_SIZE 3

typedef struct {
    unsigned int u4SatGain;    // 0 : min , 9 : max.
    unsigned int u4PartialY;   /* 0 : min , 9 : max. */
    unsigned int u4HueAdj[PQ_HUE_ADJ_PHASE_CNT];
    unsigned int u4SatAdj[PQ_SAT_ADJ_PHASE_CNT];
    unsigned int u4Contrast;   // 0 : min , 9 : max.
    unsigned int u4Brightness; // 0 : min , 9 : max
    unsigned int lcmIndex;
} DISP_PQ_PARAM;

typedef struct{
    unsigned int GLOBAL_SAT  [GLOBAL_SAT_SIZE];
    unsigned int CONTRAST    [CONTRAST_SIZE];
    unsigned int BRIGHTNESS  [BRIGHTNESS_SIZE];
    unsigned int PARTIAL_Y    [PARTIAL_Y_INDEX][PARTIAL_Y_SIZE];
    unsigned int PURP_TONE_S  [COLOR_TUNING_INDEX][PQ_PARTIALS_CONTROL][PURP_TONE_SIZE];
    unsigned int SKIN_TONE_S  [COLOR_TUNING_INDEX][PQ_PARTIALS_CONTROL][SKIN_TONE_SIZE];
    unsigned int GRASS_TONE_S [COLOR_TUNING_INDEX][PQ_PARTIALS_CONTROL][GRASS_TONE_SIZE];
    unsigned int SKY_TONE_S   [COLOR_TUNING_INDEX][PQ_PARTIALS_CONTROL][SKY_TONE_SIZE];
    unsigned int PURP_TONE_H  [COLOR_TUNING_INDEX][PURP_TONE_SIZE];
    unsigned int SKIN_TONE_H  [COLOR_TUNING_INDEX][SKIN_TONE_SIZE];
    unsigned int GRASS_TONE_H [COLOR_TUNING_INDEX][GRASS_TONE_SIZE];
    unsigned int SKY_TONE_H   [COLOR_TUNING_INDEX][SKY_TONE_SIZE];
} DISPLAY_PQ_T;


const DISPLAY_PQ_T pqindex =
{
//GLOBAL_SAT   :
{0x70,0x74,0x78,0x7C,0x80,0x84,0x88,0x8C,0x90,0x94}, //0~9

//CONTRAST   :
{0x2A,0x32,0x38,0x44,0x4D,0x59,0x65,0x70,0x78,0x83,0x8C,0x94,0x9C,0xA9,0xB1,0xBD,0xC8, //camera
 0x30,0x3A,0x44,0x4E,0x58,0x62,0x6C,0x76,0x80,0x8F,0x9E,0xAD,0xBC,0xCB,0xDA,0xE9,0xFF}, //android

//BRIGHTNESS   :
{0x3C0,0x3D0,0x3E0,0x3F0,0x400,0x410,0x420,0x430,0x440,0x450}, //0~9

//PARTIAL_Y    :
{
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80}
},
//PURP_TONE_S  :
{//hue 0~10
    {//2
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//3
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//4
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//5
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//6
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 7
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 8
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },
    // 9
    {
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 10
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 11
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 12
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 13
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 14
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 15
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 16
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 17
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 18
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 19
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {// 20
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    }

},
//SKIN_TONE_S:
{


    {//2
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8b, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//3
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8b, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//4
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8b, 0x8e, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//5
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8b, 0x90, 0x92, 0x92, 0x92, 0x92, 0x92, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },
    {//6
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8b, 0x93, 0x95, 0x95, 0x95, 0x95, 0x95, 0x80},
        {0x78, 0x76, 0x76, 0x76, 0x76, 0x76, 0x77, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//7
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x90, 0x97, 0x99, 0x99, 0x99, 0x99, 0x99, 0x80},
        {0x75, 0x72, 0x72, 0x73, 0x73, 0x73, 0x73, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//8
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x92, 0x99, 0x9d, 0x9d, 0x9d, 0x9d, 0x9a, 0x80},
        {0x75, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//9
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x92, 0x9b, 0xa0, 0xa0, 0xa0, 0xa0, 0x9a, 0x80},
        {0x73, 0x6c, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//10
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x92, 0x9d, 0xa3, 0xa3, 0xa3, 0xa3, 0x9c, 0x80},
        {0x71, 0x69, 0x68, 0x68, 0x68, 0x68, 0x68, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//11
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x95, 0xa0, 0xa7, 0xa7, 0xa7, 0xa7, 0x9e, 0x80},
        {0x6f, 0x67, 0x66, 0x66, 0x66, 0x66, 0x66, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//12
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x98, 0xa6, 0xab, 0xab, 0xab, 0xab, 0xa3, 0x80},
        {0x6c, 0x65, 0x63, 0x63, 0x63, 0x63, 0x63, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//13
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x9b, 0xa9, 0xaf, 0xaf, 0xaf, 0xaf, 0xa5, 0x80},
        {0x69, 0x62, 0x60, 0x60, 0x60, 0x60, 0x60, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//14
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa0, 0xab, 0xb1, 0xb1, 0xb1, 0xb1, 0xa7, 0x80},
        {0x67, 0x60, 0x5e, 0x5e, 0x5e, 0x5e, 0x5e, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//15
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa0, 0xb0, 0xb5, 0xb5, 0xb5, 0xb5, 0xa7, 0x80},
        {0x66, 0x5f, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//16
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa3, 0xb3, 0xb9, 0xb9, 0xb9, 0xb9, 0xa9, 0x80},
        {0x60, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//17
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa7, 0xb6, 0xbd, 0xbd, 0xbd, 0xbd, 0xa9, 0x80},
        {0x5f, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//18
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa7, 0xb6, 0xc0, 0xc0, 0xc0, 0xc0, 0xa9, 0x80},
        {0x5f, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//19
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa7, 0xb6, 0xc3, 0xc3, 0xc3, 0xc3, 0xa9, 0x80},
        {0x5f, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//20
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa7, 0xb6, 0xc6, 0xc6, 0xc6, 0xc6, 0xa9, 0x80},
        {0x5f, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    }


},
//GRASS_TONE_S:
{


    {//2
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8c, 0x8c, 0x8c, 0x8c, 0x8b, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//3
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8e, 0x8e, 0x8e, 0x8e, 0x8b, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//4
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8b, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//5
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x92, 0x92, 0x92, 0x92, 0x8d, 0x80},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//6
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x95, 0x95, 0x95, 0x95, 0x8f, 0x80},
        {0x76, 0x76, 0x77, 0x78, 0x79, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//7
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x99, 0x99, 0x99, 0x99, 0x91, 0x80},
        {0x74, 0x72, 0x72, 0x72, 0x79, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//8
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x99, 0x9d, 0x9d, 0x9b, 0x94, 0x80},
        {0x71, 0x6f, 0x6f, 0x71, 0x77, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//9
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x9e, 0xa0, 0xa0, 0x9d, 0x95, 0x80},
        {0x6c, 0x6b, 0x6b, 0x70, 0x76, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//10
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0x9f, 0xa3, 0xa3, 0x9f, 0x97, 0x80},
        {0x69, 0x68, 0x68, 0x6f, 0x74, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//11
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa0, 0xa7, 0xa7, 0xa2, 0x9b, 0x80},
        {0x67, 0x66, 0x66, 0x6d, 0x72, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//12
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa3, 0xab, 0xab, 0xa5, 0x9b, 0x80},
        {0x67, 0x63, 0x63, 0x6a, 0x71, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//13
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa7, 0xaf, 0xaf, 0xaa, 0x9e, 0x80},
        {0x63, 0x60, 0x60, 0x67, 0x6e, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//14
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xa9, 0xb1, 0xb1, 0xac, 0xa0, 0x80},
        {0x62, 0x5e, 0x5e, 0x65, 0x6c, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//15
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xad, 0xb5, 0xb5, 0xb1, 0xa4, 0x80},
        {0x60, 0x5c, 0x5c, 0x63, 0x6c, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//16
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xb0, 0xb9, 0xb9, 0xb3, 0xa7, 0x80},
        {0x5d, 0x5a, 0x5a, 0x61, 0x6a, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//17
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xb2, 0xbd, 0xbd, 0xb6, 0xab, 0x80},
        {0x5c, 0x57, 0x57, 0x5f, 0x6a, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },

    {//18
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xb2, 0xc0, 0xc0, 0xb9, 0xab, 0x80},
        {0x5a, 0x55, 0x55, 0x5a, 0x6a, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },


    {//19
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xb2, 0xc3, 0xc3, 0xbc, 0xab, 0x80},
        {0x58, 0x53, 0x53, 0x55, 0x6a, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    },


    {//20
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},
        {0xb2, 0xc6, 0xc6, 0xbf, 0xab, 0x80},
        {0x56, 0x51, 0x51, 0x51, 0x6a, 0x80},
        {0x14, 0x14, 0x14, 0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c}
    }


},
//SKY_TONE_S:
{

    {//2
        {0x80, 0x80, 0x80},
        {0x8a, 0x8c, 0x8a},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//3
        {0x80, 0x80, 0x80},
        {0x8b, 0x8e, 0x8b},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },
    {//4
        {0x80, 0x80, 0x80},
        {0x8b, 0x8f, 0x8b},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//5
        {0x80, 0x80, 0x80},
        {0x8d, 0x92, 0x8d},
        {0x80, 0x80, 0x80},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//6
        {0x80, 0x80, 0x80},
        {0x8f, 0x95, 0x8f},
        {0x7b, 0x76, 0x7c},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//7
        {0x80, 0x80, 0x80},
        {0x92, 0x99, 0x94},
        {0x79, 0x73, 0x7b},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//8
        {0x80, 0x80, 0x80},
        {0x95, 0x9d, 0x95},
        {0x78, 0x6f, 0x76},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//9
        {0x80, 0x80, 0x80},
        {0x98, 0xa0, 0x98},
        {0x73, 0x6b, 0x73},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//10
        {0x80, 0x80, 0x80},
        {0x9b, 0xa3, 0x9b},
        {0x70, 0x68, 0x70},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//11
        {0x80, 0x80, 0x80},
        {0x9c, 0xa7, 0x9c},
        {0x6e, 0x66, 0x6e},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//12
        {0x80, 0x80, 0x80},
        {0x9d, 0xab, 0x9d},
        {0x6c, 0x63, 0x6c},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//13
        {0x80, 0x80, 0x80},
        {0xa1, 0xaf, 0xa1},
        {0x69, 0x60, 0x69},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//14
        {0x80, 0x80, 0x80},
        {0xa3, 0xb1, 0xa3},
        {0x67, 0x5e, 0x67},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//15
        {0x80, 0x80, 0x80},
        {0xa8, 0xb5, 0xa8},
        {0x65, 0x5c, 0x65},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//16
        {0x80, 0x80, 0x80},
        {0xad, 0xb9, 0xaf},
        {0x63, 0x5a, 0x63},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//17
        {0x80, 0x80, 0x80},
        {0xb2, 0xbd, 0xb4},
        {0x60, 0x57, 0x60},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//18
        {0x80, 0x80, 0x80},
        {0xb2, 0xc0, 0xb4},
        {0x5f, 0x55, 0x5f},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//19
        {0x80, 0x80, 0x80},
        {0xb2, 0xc3, 0xb4},
        {0x5e, 0x53, 0x5e},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    },

    {//20
        {0x80, 0x80, 0x80},
        {0xb2, 0xc6, 0xb4},
        {0x5d, 0x51, 0x5d},
        {0x14, 0x14, 0x14},
        {0x3c, 0x3c, 0x3c}
    }


},

//PURP_TONE_H :
{
//hue 0~2
    {0x80, 0x80, 0x80},//0
    {0x80, 0x80, 0x80},//1
    {0x80, 0x80, 0x80},//2
    {0x80, 0x80, 0x80},//3
    {0x80, 0x80, 0x80},//4
    {0x80, 0x80, 0x80},//5
    {0x80, 0x80, 0x80},//6
    {0x80, 0x80, 0x80},//7
    {0x80, 0x80, 0x80},//8
    {0x80, 0x80, 0x80},//9
    {0x80, 0x80, 0x80},//10
    {0x80, 0x80, 0x80},//11
    {0x80, 0x80, 0x80},//12
    {0x80, 0x80, 0x80},//13
    {0x80, 0x80, 0x80},//14
    {0x80, 0x80, 0x80},//15
    {0x80, 0x80, 0x80},//16
    {0x80, 0x80, 0x80},//17
    {0x80, 0x80, 0x80} //18
},

//SKIN_TONE_H:
{
//hue 3~10
    {0x80, 0x80, 0x74, 0x68, 0x63, 0x67,  0x71, 0x80},//0  -9
    {0x80, 0x80, 0x74, 0x69, 0x66, 0x69,  0x71, 0x80},//1  -8
    {0x80, 0x80, 0x75, 0x6b, 0x69, 0x6b,  0x72, 0x80},//2  -7
    {0x80, 0x80, 0x76, 0x6e, 0x6c, 0x6d,  0x73, 0x80},//3  -6
    {0x80, 0x80, 0x77, 0x70, 0x70, 0x70,  0x76, 0x80},//4  -5
    {0x80, 0x80, 0x79, 0x73, 0x73, 0x73,  0x77, 0x80},//5  -4
    {0x80, 0x80, 0x7a, 0x76, 0x76, 0x76,  0x79, 0x80},//6  -3
    {0x80, 0x80, 0x7b, 0x79, 0x79, 0x79,  0x7a, 0x80},//7  -2
    {0x80, 0x80, 0x7c, 0x7c, 0x7c, 0x7c,  0x7d, 0x80},//8  -1
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  0x80, 0x80},//9  +0
    {0x83, 0x83, 0x83, 0x83, 0x83, 0x83,  0x83, 0x80},//10 +1
    {0x84, 0x85, 0x86, 0x86, 0x86, 0x86,  0x86, 0x80},//11 +2
    {0x84, 0x87, 0x8a, 0x8a, 0x8a, 0x8a,  0x8a, 0x80},//12 +3
    {0x86, 0x8a, 0x8d, 0x8d, 0x8d, 0x8d,  0x8b, 0x80},//13 +4
    {0x87, 0x8c, 0x90, 0x90, 0x90, 0x90,  0x8c, 0x80},//14 +5
    {0x88, 0x90, 0x93, 0x93, 0x93, 0x93,  0x8d, 0x80},//15 +6
    {0x89, 0x91, 0x96, 0x96, 0x96, 0x96,  0x8e, 0x80},//16 +7
    {0x8a, 0x93, 0x99, 0x99, 0x99, 0x98,  0x8f, 0x80},//17 +8
    {0x8b, 0x96, 0x9c, 0x9c, 0x9c, 0x99,  0x90, 0x80} //18 +9
},

//GRASS_TONE_H :
{
    // hue 11~16
    {0x74,0x69, 0x64, 0x68, 0x6f, 0x80},//0 -9
    {0x76,0x6b, 0x66, 0x6b, 0x73, 0x80},//1 -8
    {0x78,0x6d, 0x69, 0x6d, 0x75, 0x80},//2 -7
    {0x79,0x6f, 0x6d, 0x70, 0x76, 0x80},//3 -6
    {0x79,0x71, 0x70, 0x71, 0x77, 0x80},//4 -5
    {0x7a,0x73, 0x73, 0x73, 0x78, 0x80},//5 -4
    {0x7b,0x76, 0x76, 0x76, 0x7a, 0x80},//6 -3
    {0x7c,0x7a, 0x7a, 0x7a, 0x7b, 0x80},//7 -2
    {0x7d,0x7d, 0x7d, 0x7d, 0x7d, 0x80},//8  -1
    {0x80,0x80, 0x80, 0x80, 0x80, 0x80},//9  +0
    {0x83,0x83, 0x83, 0x83, 0x83, 0x80},//10 +1
    {0x86,0x86, 0x86, 0x86, 0x85, 0x80},//11 +2
    {0x8a,0x8a, 0x8a, 0x8a, 0x86, 0x80},//12 +3
    {0x8b,0x8d, 0x8d, 0x8d, 0x88, 0x80},//13 +4
    {0x8d,0x90, 0x90, 0x8f, 0x8a, 0x80},//14 +5
    {0x8f,0x93, 0x93, 0x91, 0x8b, 0x80},//15 +6
    {0x90,0x96, 0x96, 0x93, 0x8c, 0x80},//16 +7
    {0x91,0x99, 0x99, 0x96, 0x8d, 0x80},//17 +8
    {0x92,0x9c, 0x9c, 0x98, 0x8e, 0x80}//18  +9
},

//SKY_TONE_H:
{   //17 ~ 19
    {0x70, 0x60, 0x70},//0   -9
    {0x70, 0x63, 0x70},//1   -8
    {0x73, 0x69, 0x72},//2   -7
    {0x75, 0x6d, 0x74},//3   -6
    {0x77, 0x70, 0x76},//4   -5
    {0x7a, 0x73, 0x79},//5   -4
    {0x7b, 0x76, 0x7b},//6   -3
    {0x7c, 0x79, 0x7c},//7   -2
    {0x7e, 0x7c, 0x7e},//8    -1
    {0x80, 0x80, 0x80},//9    +0
    {0x83, 0x83, 0x83},//10   +1
    {0x85, 0x86, 0x85},//11   +2
    {0x86, 0x8a, 0x86},//12   +3
    {0x89, 0x8d, 0x89},//13   +4
    {0x8b, 0x90, 0x8b},//14   +5
    {0x8e, 0x93, 0x8e},//15   +6
    {0x91, 0x96, 0x91},//16   +7
    {0x93, 0x99, 0x93},//17   +8
    {0x95, 0x9c, 0x95}//18    +9
},

};

DISP_PQ_PARAM pqparam_standard=
{
	9,
	0,
	{9,9,12,12},
	{16,16,16,16},
	4,
	4,
	0,
};



