   

	//Płytka:
	//megaatmega2560  ATMEGA2560 16Mhz 248kB 8kB
    //Arduino Mega or Mega 2560 ATmega2560 (Mega 2560)


  
    #include <avr/io.h>
    #include <avr/interrupt.h>

    #include "SPI.h"
    #include "Wire.h"
    #include "Adafruit_BMP085.h"
    #include "OneWire.h"            //DS18b20
    #include "DallasTemperature.h"  //DS18b20
    #include "FT_VM800P43_50.h"     //Display FT800
    #include "Timer.h"              //soft timer
    #include "EEPROM.h"             //eeprom memory acces 
    #include "DS1307.h"             //RTC clock
    //#include "DS3231.h"           //RTC clock inna wersja
    #include "SD.h"                 //SD memory card
    #include "EasyTransfer.h"
    #include "digitalWriteFast.h"
    //#include <TimerThree.h>
    //#include <Flash.h>
    
    //#include "Lena_RawData.h"
    //#include "kotface2.h"

// extern volatile unsigned long timer0_overflow_count;

void AA_Manual();
void eepromRead(uint16_t addr, void* output, uint16_t length);
void SaveToEprom();
void AAc_dis_AUTO();
void AAc_0Asetup();
void AutoStartProgress();
void ClearScreen(int r, int g, int b);

    //Oto Struktura danych do wyświetlania
    //obrazków pod FT800 tu mamy definicję struktury nagłówka dla bitmapy
    //typedef struct Bitmap_header
	//{
		//uint8_t Format;
		//int16_t Width;
		//int16_t Height;
		//int16_t Stride;
		//int32_t Arrayoffset;
	//}Bitmap_header_t;

	////a tu implementacja tej struktury dla obrazka MaxGonKegBmp
	//Bitmap_header_t MaxGonKegBmp_Header[] =
	//{
		///* format,width,height,stride,arrayoffset */
		//{FT_RGB565,	40,	40,	40*2,	0	},
	//};


    // FT800 
    // --------------------------
    // FT_CS_PIN 				9 
    // FT_PDN_PIN				4
    // FT_INT_PIN 				3
    // --------------------------
    FT800IMPL_SPI FTImpl(FT_CS_PIN,FT_PDN_PIN,FT_INT_PIN);

    //Termometry na OneWire pin:2
    OneWire gTempOneWire(2);
    DallasTemperature sensors(&gTempOneWire);
    
    // Adafruit_BMP085 presure;


	//------------------------------------------|
	//------------TERMOMETRY--------------------|
	//------------------------------------------|
    //ADRESIKI: typedef uint8_t DeviceAddress[8];
    //gTempKolumna
	//PITU:blaszak
	//gTempKolumna
	//DeviceAddress gTermo1 = { 0x28, 0xFF, 0xB8, 0x1F, 0x02, 0x15, 0x02, 0x7B };
	////gTempBeczka
	//DeviceAddress gTermo2 = { 0x28, 0xFF, 0xD9, 0x52, 0x93, 0x15, 0x04, 0x84 };
	////gTempGlowica
	//DeviceAddress gTermo3 = { 0x28, 0xFF, 0x1E, 0x1E, 0x02, 0x15, 0x02, 0x5B };
	////gTempWodaWy
	//DeviceAddress gTermo4 = { 0x28, 0xFF, 0x1D, 0x29, 0x6D, 0x14, 0x04, 0x38 };
	////gTempAlarmu
	//DeviceAddress gTermo5 = {0x28, 0xFF, 0xE8, 0xA7, 0xB1, 0x15, 0x01, 0xD9  };
	//--------------------------------------------------------------------------
	
	
	//krupiniok nowe
	//gTempKolumna
  //DeviceAddress gTermo1 = { 0x28, 0xFF, 0x80, 0xBF, 0x23, 0x16, 0x03, 0x5C };
  ////gTempBeczka
  //DeviceAddress gTermo2 = { 0x28, 0x0C, 0x01, 0x07, 0x3D, 0x96, 0x01, 0xD1 };
  ////gTempGlowica
  //DeviceAddress gTermo3 = { 0x28, 0x0C, 0x01, 0x07, 0xC8, 0x9A, 0x01, 0x24 };
  ////gTempWodaWy
  //DeviceAddress gTermo4 = { 0x28, 0xFF, 0x24, 0x9C, 0x23, 0x16, 0x03, 0x88 };
  ////gTempAlarmu
  //DeviceAddress gTermo5 = { 0x28, 0x03, 0x88, 0x77, 0x91, 0x0C, 0x02, 0xEE };
  ////gTempBufor
  //DeviceAddress gTermo6 = { 0x28, 0xFF, 0xC1, 0x51, 0x93, 0x15, 0x04, 0x4E };
	//--------------------------------------------------------------------------
	
	
	
	//HERBATA
	//Found '1-Wire' device with address:
    //0x28, 0xFF, 0x7A, 0xB9, 0x23, 0x16, 0x03, 0x4E
    //0x28, 0xFF, 0x3E, 0x58, 0x00, 0x16, 0x01, 0xB2
    //0x28, 0xFF, 0xB1, 0x93, 0x23, 0x16, 0x04, 0xF4
    //0x28, 0xFF, 0xAD, 0xBA, 0x23, 0x16, 0x03, 0xC9
    //0x28, 0xFF, 0x5B, 0x47, 0x00, 0x16, 0x01, 0xD3
	//gTempKolumna
	
	
	//UFOLEC I czyli Krupinski.P:
//gTempKolumna
DeviceAddress gTermo1 = { 0x28, 0xFF, 0x35, 0x74, 0x23, 0x16, 0x04, 0xEF };
//gTempBeczka
DeviceAddress gTermo2 = { 0x28, 0x0C, 0x01, 0x07, 0x3D, 0x96, 0x01, 0xD1 };
//gTempGlowica
DeviceAddress gTermo3 = { 0x28, 0xFF, 0x9E, 0x72, 0x33, 0x16, 0x03, 0x6C };
//gTempWodaWy
DeviceAddress gTermo4 = { 0x28, 0xFF, 0xBC, 0xE9, 0x23, 0x16, 0x03, 0x28 };
//gTempAlarmu
DeviceAddress gTermo5 = { 0x28, 0xFF, 0xA9, 0x94, 0x23, 0x16, 0x04, 0x30 };

DeviceAddress gTermo6 = { 0x28, 0xFF, 0xC1, 0x51, 0x93, 0x15, 0x04, 0x4E };



//0x28, 0xFF, 0x7A, 0xB9, 0x23, 0x16, 0x03, 0x4E
//0x28, 0xFF, 0x3E, 0x58, 0x00, 0x16, 0x01, 0xB2
//0x28, 0xFF, 0xAD, 0xBA, 0x23, 0x16, 0x03, 0xC9
//0x28, 0xFF, 0x5B, 0x47, 0x00, 0x16, 0x01, 0xD3
//0x28, 0xFF, 0x8F, 0xDF, 0x33, 0x16, 0x03, 0xE9





	////gTempKolumna
	//DeviceAddress gTermo1 = { 0x28, 0xFF, 0x7A, 0xB9, 0x23, 0x16, 0x03, 0x4E };
	////gTempBeczka
	//DeviceAddress gTermo2 = { 0x28, 0xFF, 0x3E, 0x58, 0x00, 0x16, 0x01, 0xB2 };
	////gTempGlowica
	//DeviceAddress gTermo3 = { 0x28, 0xFF, 0xAD, 0xBA, 0x23, 0x16, 0x03, 0xC9 };
	////gTempWodaWy
	//DeviceAddress gTermo4 = { 0x28, 0xFF, 0x5B, 0x47, 0x00, 0x16, 0x01, 0xD3 };
	////gTempAlarmu
	//DeviceAddress gTermo5 = { 0x28, 0xFF, 0x8F, 0xDF, 0x33, 0x16, 0x03, 0xE9 };
	////gTempBufor
	//DeviceAddress gTermo6 = { 0x28, 0xFF, 0x8F, 0xDF, 0x33, 0x16, 0x03, 0x12 };
	////--------------------------------------------------------------------------
	
	//herbata 6 x DS18B20
	//0x28, 0xFF, 0x7A, 0xB9, 0x23, 0x16, 0x03, 0x4E
	//0x28, 0xFF, 0x3E, 0x58, 0x00, 0x16, 0x01, 0xB2
	//0x28, 0xFF, 0xB1, 0x93, 0x23, 0x16, 0x04, 0xF4
	//0x28, 0xFF, 0xAD, 0xBA, 0x23, 0x16, 0x03, 0xC9
	//0x28, 0xFF, 0x5B, 0x47, 0x00, 0x16, 0x01, 0xD3
	//0x28, 0xFF, 0x8F, 0xDF, 0x33, 0x16, 0x03, 0xE9
	
	//progmem text
	//const unsigned char text[] PROGMEM = {"Hello World"};
	

    //struktura opisująca lokalny czas G::M::S
    struct gTime
	{
	 uint8_t  hour   =  0;
	 uint8_t  minute =  0;
	 uint8_t  second =  0;
	}__attribute__((packed));
    gTime local_timer_manual;
     

     //Start procesu
      struct gDateTime
	  {
			uint16_t year   =  0;
			uint8_t  month  =  0;
			uint8_t  day    =  0;
			uint8_t  hour   =  0;
			uint8_t  minute =  0;
			uint8_t  second =  0;
	  }__attribute__((packed));
    //do przechowywania daty i czasu z RTC


    //#pragma pack 1
    struct gParametryPracySTR
    {
	  //parametry bierzące	temperatury pobierane od 5 czujników DS18B20
	  //wartości mogą być ujemne zwłaszcza w zimie w
	  //nieogrzewanym pomieszczeniu...
	   
	  uint16_t  gStructID = 12345;//12345 -->0
	  
      float 	gTempKolumna 	= 00.00;
      float 	gTempBeczka 	= 00.00;
      float 	gTempGlowica 	= 00.00;
      float 	gTempWodaWy 	= 00.00;
      float 	gTempAlarmu 	= 00.00;
      float 	gTempBufor	 	= 00.00;

      //Temp Dnia
      float 	gTempDnia 		= 00.00;

      //Aktualny etap procesu
      unsigned char gEtap = 0;

      	  
	  gTime gLocal_timer;


	  //Stan grzałek
	  bool		gPowerPWR1      = false;
	  bool		gPowerPWR2  	= false;
	  //----------------------------------------
	  bool		gPowerPWR3  	= false;
	  //grzałka dodatkowa włącza się w momencie
	  //rozgrzewania i zalewania na maximum
	  //mocy...........-------------------------

      //czas
      RTCDateTime CurrentDateTime;

      //----------------------------------------------------------
      //moc w manualu
      uint8_t       gMocMAN_G1	 	 = 0;     // 0-255
      uint8_t       gMocMAN_G2	 	 = 0;     // 0-255
            
      uint8_t       gMocZalaniaG1	 	  = 0;     // 0-255
      uint8_t       gMocZalaniaG2	 	  = 0;     // 0-255
      //moc stabilizacji
      uint8_t       gMocStabilizacjiG1	  = 90;     // 0-255
      uint8_t       gMocStabilizacjiG2	  = 90;     // 0-255
      //moc przedgonu
      uint8_t       gMocPrzedgonuG1		  = 0;     // 0-255
      uint8_t       gMocPrzedgonuG2	 	  = 0;     // 0-255
      //moc gonu
      uint8_t       gMocGonuG1		 	  = 0;     // 0-255
      uint8_t       gMocGonuG2	 	 	  = 0;     // 0-255
      uint8_t       gMocGonu2_G1		  = 0;     // 0-255
      uint8_t       gMocGonu2_G2	 	  = 0;     // 0-255
      float         gTempZmianyMocyGonu   = 00.00; //st C //beczka
      //-----------------------------------------------------------------

      uint16_t	gPlukanieOLM			 = 0;     //sekundy
      uint16_t  gTempUpdateTime		     = 1000;  //milisekundy 2000 = 2s

      float		gHisterezaTemperatury	 = 00.00; //st C
      float		gTempStopPogonu			 = 00.00; //st C
      float		gTempRozgrzewania		 = 00.00; //st C
      float		gTempStartPogonu 		 = 00.00; //stopnie C
      float     gTempStopGrzania		 = 00.00; //st C
      float     gTempZG2				 = 00.00; //st C

      
      gDateTime gStartAutoDateTime;

      //Aktualne czasy
      uint16_t 		gCzasProcesuGodz      =	0;
      uint16_t		gCzasProcesuMin       =	0; //minuty
      uint16_t 		gCzasProcesuSek       =	0;
      uint16_t 		gCzasProcesuTotalMin  = 0;
      uint32_t      gCzasProcesuTotalSek  = 0;

      //Aktualne czasy
	  uint16_t      gCzasZalewania 		  = 0; //minuty?
	  uint16_t      gCzasZalania          = 0; //sekundy moment zalania
	  uint16_t      gCzasStabilizacji 	  = 0;
	  uint16_t      gCzasPrzedgonu    	  = 0;
	  uint16_t      gCzasRozgrzewania     = 0;
	  uint16_t      gCzasGonu     		  = 0;
	  uint16_t      gCzasPogonu   		  = 0;
	  uint16_t      gCzasChlodzenia 	  = 0;

      //zadane czasy
      uint16_t		gZadanyCzasStabilizacji    = 0;    //minuty
      uint16_t      gZadanyCzasOdbPrzedgonuSek = 0;    //sekundy 
      uint16_t      gZadanyCzasOdbPrzedgonuMin = 0;    //minuty 
      uint16_t		gZadanyCzasStabPrzedgonu   = 0;    //minuty
      uint16_t  	gZadanyCzasZalewania       = 0;    //minuty
      uint16_t  	gZadanyCzasPrzerwyMocyZalania = 0; //sekundy
      uint16_t		gZadanyCzasChlodzenia  	      = 0; //minuty

      //temp resolution
      uint8_t gTEMPERATURE_PRECISION = 12;

      //sound volume
      uint8_t gSoundVolume = 100; //0min - 255max

      //Aktualny stan zaworków
      bool gZaworWoda 		   = false;
      bool gZaworPrzedGon 	  = false;
      bool gZaworGonu 		 = false;
      bool gZaworGonu2 		= false;

      //Tryb Pracy 2 zawory albo 1
      bool gIloscZaworowGonu = true; //false 1 true 2;

      //histereza pogonu
      bool gHistPoGonu = true;

      //PoziomZalania
      uint16_t  gPoziomZalania       = 0;    //odczyt z czujnika zalania 0-1023
      uint16_t  gZadanyPoziomZalania = 0;    //zadana wartość
      bool gCzujnikZalania           = true;//flaga włączania
      bool gCzyZalano                = false;//flaga zalania kolumny
      
      //WIFI
      uint8_t   gWIFI_MODE = 0;        //default statione=0 1=AP 2=AP-service
 
      bool gTypMocy = false; // false = grupowe; true = liniowe
      uint32_t   gCzestotliwoscMocyGrupowo = 2500;
 
      //liczniki zaworów gonu
      uint16_t gZaworGonCntr  = 0;
      uint16_t gZaworGon2Cntr = 0;

      bool gStabPrzedgon      = false;     // etap STB 4 przedgon
      bool gPotwOdbGonu       = false;     // etap 5 GON potw odbioru gonu przez usera
      bool gZaworGonu2_ON     = false;     // przejście na ZaworGon2
      bool gPrzerwaPoZalaniu  = false;
      bool gDrugaMocGonu      = false;
      bool gDuzeJeziorko      = true;     //stasbilizacja przedgonu
      
      bool gSYS_LOG           = false;
      
      uint8_t gZalanieZadaneX = 0;         //ile razy ma zalać 
      uint8_t gZalanieX       = 0;		   //bierzące zalanie
      uint32_t gPresure       = 0;	 

      uint32_t gStart_etapu     = 0;     //w sekundach
      uint8_t  gNR_Okna         = 0;  //kod bierzącego okna
      uint8_t  gSTATUS          = 0;  //status programu
	  uint8_t  g2560ToESP_order = 0;  
	  bool gKoniec = false;

       //char gSSID[22]   = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
      //char gPASS[22]   = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
      //char gSSID[22]   = "ELIBOMT-2016";
      //char gPASS[22]   = "2016-g788*aq9FpUmas";
      char gSSID[22]   = "";
      char gPASS[22]   = "";

    }__attribute__((packed))gParametryPracy;
    //========================================
    


	//RTC
    static DS1307 	RTclock;
    //static DS3231 	RTclock;


	//Tajmery-------------------i eventy---
	static Timer gTimer;			   //--
    static int   gTempSensorEvent;     //1-
    static int   gCzasProcesuEvent;    //2-
    static int   gProcessEvent;        //3-
    //static int   gCzujnikZalaniaEvent; //4-
   // static int   gWykresTempEvent;     //5-
    static int   gAwariaDSTempEvent;   //6-
    static int   gSystemBackupEvent;   //7-
    //-------------------------------------
    
    static int    gPwr1TimerEvent = 0;
    volatile bool pwr1_change_state = false;
    int  on_time  = 0;
    int  off_time = 0;
    bool is_on    = false;
    bool is_off   = false;
    
    static int    gPwr2TimerEvent = 0;
    volatile bool pwr2_change_state = false;
    int  on_time2  = 0;
    int  off_time2 = 0;
    bool is_on2    = false;
    bool is_off2   = false;
    


    //unsigned long gStartWykresTotalSek  = 0;

    static bool gStartAUTO      = false;          // start w AUTO
    static bool gStartMAN       = false;
    static bool gBrak_DS_anuluj = false;          //czy anulować sprawdzanie DS
    static bool gBrak_Chlodzenia_anuluj = false;  //czy anulować sprawdzanie chłodzenia WODY
    uint32_t    gStart_zalania    = 0;
    bool        bPotwODBGonu      = false;
    bool        www_Okidoki_POTW  = false;
    unsigned int AwariaDS_number = 0;
    
    bool gCzyWIFI_IS_Conected = false;
    //uint32_t ESP_DATA_COUNT = 0;
    //uint32_t prew_ESP_DATA_COUNT = 0;
    
    unsigned int gFreeMemory = 0; 
    

    static char TempCharBuffer[14] = "0000000000\0"; // "-2147483648\0"
   
    #define F16(s)        ((int32_t)((s) * 65536))
    #define SQ(v) (v*v)


    //Screen-size
    # define SWIDTH    480
	# define SHEIGHT   272

           
    //SERIAL------------------------------------------------
    EasyTransfer ETin, ETout; 
	
	//IP
	struct gParametryPracySTR_IN
    {
      //moc w manualu
	  uint8_t       gMocMAN_G1	 	 	  = 0;     // 0-255
      uint8_t       gMocMAN_G2	 	 	  = 0;     // 0-255
      uint8_t       gMocZalaniaG1	 	  = 0;     // 0-255
      uint8_t       gMocZalaniaG2	 	  = 0;     // 0-255
      uint8_t       gMocStabilizacjiG1	  = 0;     // 0-255
      uint8_t       gMocStabilizacjiG2	  = 0;     // 0-255
      uint8_t       gMocPrzedgonuG1		  = 0;     // 0-255
      uint8_t       gMocPrzedgonuG2	 	  = 0;     // 0-255
      uint8_t       gMocGonuG1		 	  = 0;     // 0-255
      uint8_t       gMocGonuG2	 	 	  = 0;     // 0-255
      uint8_t       gMocGonu2_G1		  = 0;     // 0-255
      uint8_t       gMocGonu2_G2	 	  = 0;     // 0-255
      float         gTempZmianyMocyGonu   = 00.00; //st C //beczka
      uint16_t	    gPlukanieOLM			  = 0;        //sekundy
      uint16_t      gTempUpdateTime		      = 0;        //milisekundy 2000 = 2s
      float		    gHisterezaTemperatury	  = 00.00;    //st C
      float		    gTempStopPogonu			  = 00.00;    //st C
      float		    gTempRozgrzewania		  = 00.00;    //st C
      float		    gTempStartPogonu 		  = 00.00;    //stopnie C
      float         gTempStopGrzania		  = 00.00;    //st C
      float         gTempZG2				  = 00.00; 	  //st C
      uint16_t		gZadanyCzasStabilizacji       = 0;    //minuty
      uint16_t      gZadanyCzasOdbPrzedgonuSek    = 0;    //sekundy 
      uint16_t      gZadanyCzasOdbPrzedgonuMin    = 0;    //minuty 
      uint16_t		gZadanyCzasStabPrzedgonu      = 0;    //minuty
      uint16_t  	gZadanyCzasZalewania          = 0;    //minuty
      uint16_t  	gZadanyCzasPrzerwyMocyZalania = 0;    //sekundy
      uint16_t		gZadanyCzasChlodzenia  	      = 0;    //minuty
      bool 			gIloscZaworowGonu  = false;           //false 1 true 2;
      bool 			gHistPoGonu        = false;
      bool 			gCzujnikZalania    = false;	          //flaga włączania
      bool 			gDuzeJeziorko      = false;           //stasbilizacja przedgonu
      uint16_t  	gZadanyPoziomZalania   = 0;           //zadana wartość
      uint8_t   	gZalanieZadaneX        = 0;           //ile razy ma zalać 
      uint8_t 		gTEMPERATURE_PRECISION = 0;
      uint8_t 		ip1 = 0;
      uint8_t 		ip2 = 0;
      uint8_t 		ip3 = 0;
      uint8_t 		ip4 = 0;
      uint8_t 		gMessageCode = 0;
      long  		gWIFI_RSSI = 0;  //power wifi
      uint8_t       gWIFI_MODE = 0;  //default statione=0 1=AP 2=AP-service
      bool          gTypMocy = false; // false = grupowe; true = liniowe
      uint32_t      gCzestotliwoscMocyGrupowo = 0;
      unsigned long gESP_MILLIS  = 0;
      char gSSID[22] = "";
      char gPASS[22] = "";
    }__attribute__((packed))gParametryPracy_RCV;
 
    unsigned long      gLAST_ESP_MILLIS  = 0;
	


    typedef struct Bitmap_header
	{
		uint8_t Format;
		int16_t Width;
		int16_t Height;
		int16_t Stride;
		int32_t Arrayoffset;
	}Bitmap_header_t;

	Bitmap_header_t Lena40_Header[] = 
	{
		/* format,width,height,width*stride,arrayoffset */
		//{FT_RGB565,	56,	72,	56*2,	0	},
		/*('file properties: ', 'resolution ', 60, 'x', 46, 'format ', 'RGB565', 'stride ', 120, ' total size ', 5520)*/ 
		{FT_RGB565,	100,	77,	200,	0	},
	};
	/* Macro for size of raw data */
	
    //PROGMEM const char home_star_icon[] = {0x78,0x9C,0xE5,0x94,0xBF,0x4E,0xC2,0x40,0x1C,0xC7,0x7F,0x2D,0x04,0x8B,0x20,0x45,0x76,0x14,0x67,0xA3,0xF1,0x0D,0x64,0x75,0xD2,0xD5,0x09,0x27,0x17,0x13,0xE1,0x0D,0xE4,0x0D,0x78,0x04,0x98,0x5D,0x30,0x26,0x0E,0x4A,0xA2,0x3E,0x82,0x0E,0x8E,0x82,0xC1,0x38,0x62,0x51,0x0C,0x0A,0x42,0x7F,0xDE,0xB5,0x77,0xB4,0x77,0x17,0x28,0x21,0x26,0x46,0xFD,0x26,0xCD,0xE5,0xD3,0x7C,0xFB,0xBB,0xFB,0xFD,0xB9,0x02,0xCC,0xA4,0xE8,0x99,0x80,0x61,0xC4,0x8A,0x9F,0xCB,0x6F,0x31,0x3B,0xE3,0x61,0x7A,0x98,0x84,0x7C,0x37,0xF6,0xFC,0xC8,0xDD,0x45,0x00,0xDD,0xBA,0xC4,0x77,0xE6,0xEE,0x40,0xEC,0x0E,0xE6,0x91,0xF1,0xD2,0x00,0x42,0x34,0x5E,0xCE,0xE5,0x08,0x16,0xA0,0x84,0x68,0x67,0xB4,0x86,0xC3,0xD5,0x26,0x2C,0x20,0x51,0x17,0xA2,0xB8,0x03,0xB0,0xFE,0x49,0xDD,0x54,0x15,0xD8,0xEE,0x73,0x37,0x95,0x9D,0xD4,0x1A,0xB7,0xA5,0x26,0xC4,0x91,0xA9,0x0B,0x06,0xEE,0x72,0xB7,0xFB,0xC5,0x16,0x80,0xE9,0xF1,0x07,0x8D,0x3F,0x15,0x5F,0x1C,0x0B,0xFC,0x0A,0x90,0xF0,0xF3,0x09,0xA9,0x90,0xC4,0xC6,0x37,0xB0,0x93,0xBF,0xE1,0x71,0xDB,0xA9,0xD7,0x41,0xAD,0x46,0xEA,0x19,0xA9,0xD5,0xCE,0x93,0xB3,0x35,0x73,0x0A,0x69,0x59,0x91,0xC3,0x0F,0x22,0x1B,0x1D,0x91,0x13,0x3D,0x91,0x73,0x43,0xF1,0x6C,0x55,0xDA,0x3A,0x4F,0xBA,0x25,0xCE,0x4F,0x04,0xF1,0xC5,0xCF,0x71,0xDA,0x3C,0xD7,0xB9,0xB2,0x48,0xB4,0x89,0x38,0x20,0x4B,0x2A,0x95,0x0C,0xD5,0xEF,0x5B,0xAD,0x96,0x45,0x8A,0x41,0x96,0x7A,0x1F,0x60,0x0D,0x7D,0x22,0x75,0x82,0x2B,0x0F,0xFB,0xCE,0x51,0x3D,0x2E,0x3A,0x21,0xF3,0x1C,0xD9,0x38,0x86,0x2C,0xC6,0x05,0xB6,0x7B,0x9A,0x8F,0x0F,0x97,0x1B,0x72,0x6F,0x1C,0xEB,0xAE,0xFF,0xDA,0x97,0x0D,0xBA,0x43,0x32,0xCA,0x66,0x34,0x3D,0x54,0xCB,0x24,0x9B,0x43,0xF2,0x70,0x3E,0x42,0xBB,0xA0,0x95,0x11,0x37,0x46,0xE1,0x4F,0x49,0xC5,0x1B,0xFC,0x3C,0x3A,0x3E,0xD1,0x65,0x0E,0x6F,0x58,0xF8,0x9E,0x5B,0xDB,0x55,0xB6,0x41,0x34,0xCB,0xBE,0xDB,0x87,0x5F,0xA9,0xD1,0x85,0x6B,0xB3,0x17,0x9C,0x61,0x0C,0x9B,0xA2,0x5D,0x61,0x10,0xED,0x2A,0x9B,0xA2,0x5D,0x61,0x10,0xED,0x2A,0x9B,0xA2,0x5D,0x61,0x10,0xED,0x2A,0x9B,0xED,0xC9,0xFC,0xDF,0x14,0x54,0x8F,0x80,0x7A,0x06,0xF5,0x23,0xA0,0x9F,0x41,0xF3,0x10,0x30,0x4F,0x41,0xF3,0x18,0x30,0xCF,0xCA,0xFC,0xFF,0x35,0xC9,0x79,0xC9,0x89,0xFA,0x33,0xD7,0x1D,0xF6,0x5E,0x84,0x5C,0x56,0x6E,0xA7,0xDA,0x1E,0xF9,0xFA,0xAB,0xF5,0x97,0xFF,0x2F,0xED,0x89,0x7E,0x29,0x9E,0xB4,0x9F,0x74,0x1E,0x69,0xDA,0xA4,0x9F,0x81,0x94,0xEF,0x4F,0xF6,0xF9,0x0B,0xF4,0x65,0x51,0x08};

    #define EEPROM_CALIBRATION_DATA_START (EEPROM.length() - 25)

	
	# define dBnTagStart    1
    # define dBnTagConfig  2
    # define dBnTagReset   3
    # define dBnTagTak       5
    # define dBnTagNie        6
    # define dBnTagInfo        7
    # define dBnTagInfobExit  8
    # define dBnTagReadNumber 9
    # define dBnTagConfigbExit 10
    # define dBnTagReadNumberbEnter 132
    # define dBnTagConfigPowerB1 12
    # define dBnTagConfigChlodzenieGlowicy 13
    # define dBnTagConfigbSave 14
    # define dBnTagStartbExit 15
    # define dBnTagStartbStartJ 16
    # define dBnTagStartbConfigs 17
    # define dBnTagStartbParamDsplay 18
    # define dBnTagStartbResetTime 19
    # define dBnTagStartbStartPWR 20
    # define dBnTagZadanyCzasOdbPrzedgonu 21
    # define dBnTagConfigPowerB2 22
    # define dBnTagZadanyCzasZalewania 23
    # define dBnTagINPUT_1 24
    # define dBnTagINPUT_2 25
    # define dBnTagINPUT_3 26
    # define dBnTagINPUT_4 27
    # define dBnTagINPUT_5 28
	# define dBnTagINPUT_6 29
	# define dBnTagINPUT_7 30
	# define dBnTagINPUT_8 31
	# define dBnTagINPUT_9 32
	# define dBnTagINPUT_0 33
	# define dBnTagINPUT_Kropka 34
	# define dBnTagINPUT_Exit   35
	# define dBnTagTempUpdateInterval    36
	# define dBnTagStartPogonu 37
	# define dBnTagHisterezaTemperatury  38
	# define dBnTagConfigTIME   41
	# define dBnTagConfigVOLUME 43
	# define dBnTagZadanyCzasStabilizacji 44
	# define dBnTagConfigStopPogonu 45
	# define dBnTagManZawWoda 46
	# define dBnTagManZawGon  47
	# define dBnTagManZawPrzedG 48
	# define dBnTagManG1 49
	# define dBnTagManG2 50
	# define dBnTagRESOLUTION 51
	# define dBnTagConfigTempRozgrzewania 52
	# define dBnTagConfigCalibration 53
	# define dBnTagPlukanieOLM 54
	# define dBnTagConfigMocZalaniaG1         56
	# define dBnTagConfigMocZalaniaG2        57
	# define dBnTagConfigMocStabilizacjiG1  58
	# define dBnTagConfigMocStabilizacjiG2 59
	# define dBnTagConfigMocPrzedgonuG1 64
	# define dBnTagConfigMocPrzedgonuG2 65
	# define dBnTagConfigMocGonuG1  66
	# define dBnTagConfigMocGonuG2 67
	# define dBnTagConfigSaveSD    68


    // Tu są rozpisane makrodefinicje
    // dla poszczegulnych przyłączy
    // dla płytki  Arduino atmega2560
	// PINY @@@@@@@@@x@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}...
	// @@@@@@@@@@@@@@x@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}......
	// @@@@@@@@@@@@@@x@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}...........
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}...............
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}.................
	//------------------------------------------------------
	# define ZaworWoda 	 	   A1             //    Woda....................
	# define ZaworPrzedGon     A2            //    PrzedGon ................
	# define ZaworGonu 		   A3           //    Gon.......................
	# define ZaworGonu2		   A4          //    Gon2.......................
	# define CzujnikZalania    A5         //   czujnik zalania..............
	// #define ZasilanieCzujnikaZalania A6 //   zasilanie czujnika zalania....
	# define PowerPWR1   	   6        //   grzałka 1......................
	# define PowerPWR2 		   8       //   grzałka 2 ......................
	# define PowerPWR3 		   10     //   grzałka 3 .......................
	# define SD_shield         49    //   karta pamięci sd..................
   // OneWreBus                2    //   DS18b20............................
   //------------------------------------------------------
   // DISPLAY: FT800--->
    //#define FT_CS_PIN 	   SS		9 
	//#define FT_PDN_PIN				4
	//#define FT_INT_PIN 				3   przerwanie
	//#define FT_SD_CSPIN 			    8   FT800 with SD
   //------------------------------------------------------
   
    // SD:
    // -------|
    // miso 50|
    // mosi 51|
    // sck  52|
    // ss   49|
    // -------|
     
   
   // zerocross:
   // PowerPWR1
   #define DETECT1     18  // zero cross detect
   #define GATE1       6   // TRIAC gate
   #define PULSE       4   // trigger pulse width (counts)  //4
   #define INTERRUPT1  5   // interrupt number for pin 18 = 5
   // PowerPWR2
   #define DETECT2     19  
   #define GATE2       8   
   #define PULSE2      4  
   #define INTERRUPT2  4  
   
   
   
   // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}..................
   // @@@@@@@@@A@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}.................
   // @@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}...............
   // @@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}.............
   // @@@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@}..........


   #define files_array_size 21 
   
   
   #define DS_ERROR_MAX 4 

char bufor[60];
const char STR_0 [] PROGMEM = "Kolumna:"; 
const char STR_1 [] PROGMEM = "Beczka:";
const char STR_2 [] PROGMEM = "Glowica:";
const char STR_3 [] PROGMEM = "Woda:";
const char STR_4 [] PROGMEM = "Bufor:";
const char STR_5 [] PROGMEM = "Czas:";
const char STR_6 [] PROGMEM = "Z Woda:";
const char STR_7 [] PROGMEM = "ON";
const char STR_8 [] PROGMEM = "OFF";
const char STR_9 [] PROGMEM = "Z PrzeGon:";
const char STR_10 [] PROGMEM = "Z Gon 1:";
const char STR_11 [] PROGMEM = "Z Gon 2:";
const char STR_12 [] PROGMEM = "m";
const char STR_13 [] PROGMEM = "WIFI ON";
const char STR_14 [] PROGMEM = "WIFI OFF";
const char STR_15 [] PROGMEM = "G1:";
const char STR_16 [] PROGMEM = "G2:";
const char STR_17 [] PROGMEM = "G3:";
const char STR_18 [] PROGMEM = "MaxGon v 2.2";
const char STR_19 [] PROGMEM = "Copyright c 2018";
const char STR_20 [] PROGMEM = "Misrocoft Corporation";
const char STR_21 [] PROGMEM = "All rights reversed";
const char STR_22 [] PROGMEM = "Wczytywanie konfiguracji...";
const char STR_23 [] PROGMEM = "Wyszukiwanie termometrow...";
const char STR_24 [] PROGMEM = "Inicjalizacja karty SD....";
const char STR_25 [] PROGMEM = "Inicjalizacja licznikow....";
const char STR_26 [] PROGMEM = "Inicjalizacja zegara RTC....";
const char STR_27 [] PROGMEM = "Konfiguracja pinow sterownika..";
const char STR_28 [] PROGMEM = "GRZALKI OFF ZAWORY ON/OFF";
const char STR_29 [] PROGMEM = "MaxGon gotowy...";
const char STR_30 [] PROGMEM = "Zalanie:";
const char STR_31 [] PROGMEM = "Czas Eta:";
const char STR_32 [] PROGMEM = "Etap:";
const char STR_33 [] PROGMEM = "- Rozgrzewanie...";
const char STR_34 [] PROGMEM = "max";
const char STR_35 [] PROGMEM = "- Zalewanie kolumny";
const char STR_36 [] PROGMEM = "- Zalewanie - przerwa w mocy";
const char STR_37 [] PROGMEM = "- Stabilizacja";
const char STR_38 [] PROGMEM = "- Odbior Przedgonu";
const char STR_39 [] PROGMEM = "- Stabilizacja przedgonu";
const char STR_40 [] PROGMEM = "- Odbior Gonu";
const char STR_41 [] PROGMEM = "- Odbior Pogonu";
const char STR_42 [] PROGMEM = "- Chlodzenie glowicy";
const char STR_43 [] PROGMEM = "- KONIEC!";
const char STR_44 [] PROGMEM = "Automat START";
const char STR_45 [] PROGMEM = "Inicjalizacja procesu......";
const char STR_46 [] PROGMEM = "TAK";
const char STR_47 [] PROGMEM = "NIE";
const char STR_48 [] PROGMEM = "Proces zostal zatrzymany z powodu braku chlodzenia !";
const char STR_49 [] PROGMEM = "AUTO:";
const char STR_50 [] PROGMEM = "OK";
const char STR_51 [] PROGMEM = "Kalibracja ekranu dotykowego";
const char STR_52 [] PROGMEM = "EXIT";
const char STR_53 [] PROGMEM = "Proces zatrzymany z powodu braku odczytu z DS  !";
const char STR_54 [] PROGMEM = "<-zapis konfiguracji w pamieci";
const char STR_55 [] PROGMEM = "0-255";
const char STR_56 [] PROGMEM = "SAVE";
const char STR_57 [] PROGMEM = "Start systemu > > >";
const char STR_58 [] PROGMEM = "Error!";
const char STR_59 [] PROGMEM = "Brak odczytu z DS18B20:";
const char STR_60 [] PROGMEM = "Awaria czujnika temperatury";
const char STR_61 [] PROGMEM = "Zatrzymanie procesu !";
const char STR_62 [] PROGMEM = "Kolumna";
const char STR_63 [] PROGMEM = "Beczka";
const char STR_64 [] PROGMEM = "Glowica";
const char STR_65 [] PROGMEM = "Woda";
const char STR_66 [] PROGMEM = "Alarm";
const char STR_67 [] PROGMEM = "ANULUJ";
const char STR_68 [] PROGMEM = "AUTO";
const char STR_69 [] PROGMEM = "MaxGon v2.2";
const char STR_70 [] PROGMEM = "Automatic water distillation system";
const char STR_71 [] PROGMEM = "STATION: podlacz do istniejacej wifi";
const char STR_72 [] PROGMEM = "AP: utworzenie wifi";
const char STR_73 [] PROGMEM = "g";
const char STR_74 [] PROGMEM = "Rozgrzewanie:";
const char STR_75 [] PROGMEM = "Zalewanie:";
const char STR_76 [] PROGMEM = "Stabilizacja:";
const char STR_77 [] PROGMEM = "Przed-Gon:";
const char STR_78 [] PROGMEM = "Gon I:";
const char STR_79 [] PROGMEM = "Gon II:";
const char STR_80 [] PROGMEM = "Po-Gon:";
const char STR_81 [] PROGMEM = "Chlodzenie:";
const char STR_82 [] PROGMEM = "System:";
const char STR_83 [] PROGMEM = "Rozgrzewanie:";
const char STR_84 [] PROGMEM = "Start chlodzenia:";
const char STR_85 [] PROGMEM = "Temp otwarcia EZ wody: glowica";
const char STR_86 [] PROGMEM = ":";
const char STR_87 [] PROGMEM = "-";
const char STR_88 [] PROGMEM = "Koniec procesu:";
const char STR_89 [] PROGMEM = "Calkowity czas:";
const char STR_90 [] PROGMEM = "min";
const char STR_91 [] PROGMEM = "ENTER";
const char STR_92 [] PROGMEM = "PULPIT";
const char STR_93 [] PROGMEM = "Desktop";
const char STR_94 [] PROGMEM = "start / auto";
const char STR_95 [] PROGMEM = "CONFIG";
const char STR_96 [] PROGMEM = "Konfiguracja";
const char STR_97 [] PROGMEM = "SD";
const char STR_98 [] PROGMEM = "Karta pamieci";
const char STR_99 [] PROGMEM = "BEKAP";
const char STR_100 [] PROGMEM = "wczytaj bekap";
const char STR_101 [] PROGMEM = "WIFI";
const char STR_102 [] PROGMEM = "obsluga sieci";
const char STR_103 [] PROGMEM = "Tryb pracy:";

const char STR_104 [] PROGMEM = "TempAlarmu:";
const char STR_105 [] PROGMEM = "StopGrzania:";
const char STR_106 [] PROGMEM = "Spuszczone";
const char STR_107 [] PROGMEM = "Przedgon:";

const char STR_108 [] PROGMEM = "TempDnia:";
const char STR_109 [] PROGMEM = "Cisnienie HPa:";
const char STR_110 [] PROGMEM = "Zalanie-X:";

const char STR_111 [] PROGMEM = "Chistereza:";
const char STR_112 [] PROGMEM = "st C";
const char STR_113 [] PROGMEM = "Moc Gonu G1:";

const char STR_114 [] PROGMEM = "jm";
const char STR_115 [] PROGMEM = "Moc Gonu G2:";
const char STR_116 [] PROGMEM = "Z Gon:";

const char STR_117 [] PROGMEM = "TempDnia:";
const char STR_118 [] PROGMEM = "Ukonczono:";

const char STR_119 [] PROGMEM = "Z Gon2:";

const char STR_120 [] PROGMEM = "Power START !";
const char STR_121 [] PROGMEM = "Power STOP !";
const char STR_122 [] PROGMEM = "Error";
const char STR_123 [] PROGMEM = "File error!";

const char STR_124 [] PROGMEM = "Brak karty pamieci";
const char STR_125 [] PROGMEM = "Nie zapisales !";

const char STR_126 [] PROGMEM = "Brak 1: DS18b20";
const char STR_127 [] PROGMEM = "Brak 2: DS18b20";
const char STR_128 [] PROGMEM = "Brak 3: DS18b20";
const char STR_129 [] PROGMEM = "Brak 4: DS18b20";
const char STR_130 [] PROGMEM = "Brak 5: DS18b20";
const char STR_131 [] PROGMEM = "Brak 6: DS18b20";

const char STR_132 [] PROGMEM = "Czy zapisac na karcie SD ?";
const char STR_133 [] PROGMEM = "Czy skalibrowac ekran ?";
const char STR_134 [] PROGMEM = "Czy zapisac do epromu ?";
const char STR_135 [] PROGMEM = "Czy usunac wszystkie ?";
const char STR_136 [] PROGMEM = "Czy usunac ten plik ?";
const char STR_137 [] PROGMEM = "Czy zaladowac ten plik ?";
const char STR_138 [] PROGMEM = "Czy zaladowac bekap ?";

const char STR_139 [] PROGMEM = "qwertyuiopasdfghjklzxcvbnm1234567890*-";
const char STR_140 [] PROGMEM = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890*-";

const char STR_141 [] PROGMEM = "Stabilizacja procesu:";
const char STR_142 [] PROGMEM = "Odbior przedgonu:";
const char STR_143 [] PROGMEM = "Czas Stabilizacji:";
const char STR_144 [] PROGMEM = "Stabilizacja przedgonu";
const char STR_145 [] PROGMEM = "Czas.odb min.sek";
const char STR_146 [] PROGMEM = "Chlodzenie glowicy:";
const char STR_147 [] PROGMEM = "Pozostale parametry:";
const char STR_148 [] PROGMEM = "Czy kontynuowac proces ?";

const char STR_149 [] PROGMEM = "Brak chlodzenia - wody!";

const char STR_150 [] PROGMEM = "Stop grzania:";
const char STR_151 [] PROGMEM = "Temp.alarm:";
const char STR_152 [] PROGMEM = "st C";
const char STR_153 [] PROGMEM = "Zalewanie kolumny:";


const char STR_154 [] PROGMEM = "Moc G1:";
const char STR_155 [] PROGMEM = "Moc G2:";

const char STR_156 [] PROGMEM = "Nazwa sieci: ";
const char STR_157 [] PROGMEM = "Haslo: ";

const char STR_158 [] PROGMEM = "AP";
const char STR_159 [] PROGMEM = "STATION";
const char STR_160 [] PROGMEM = "AP service mode";


const char STR_161 [] PROGMEM = "Grzalki:";
const char STR_162 [] PROGMEM = "zalania:";
const char STR_163 [] PROGMEM = "Czujnik";
const char STR_164 [] PROGMEM = "Czas zalania:";
const char STR_165 [] PROGMEM = "Przerwa w mocy";

const char STR_166 [] PROGMEM = "Przejscie w";
const char STR_167 [] PROGMEM = "Stabilizacji:";
const char STR_168 [] PROGMEM = "Odbior Gonu:";

const char STR_169 [] PROGMEM = "TempDnia:";
const char STR_170 [] PROGMEM = "Odczytaj";
const char STR_171 [] PROGMEM = "Przedgon";

const char STR_172 [] PROGMEM = "Zapis konfiguracji...";



 
      //FTImpl.Cmd_Text(0, 50, 23, 0, "Calkowity czas:" );
      //FTImpl.Cmd_Text(0, 70, 23, 0, "Rozgrzewanie:" );
      //FTImpl.Cmd_Text(0, 90, 23, 0, "Zalewanie:" );
      //FTImpl.Cmd_Text(0, 110, 23, 0, "Stabilizacja:" );
      //FTImpl.Cmd_Text(0, 150, 23, 0, "Gon:" );
      //FTImpl.Cmd_Text(100, 150, 23, 0, "godz" );
      //FTImpl.Cmd_Text(0, 170, 23, 0, "PoGon:" );
      //FTImpl.Cmd_Text(0, 190, 23, 0, "Chlodzenie:" );
      //FTImpl.Cmd_Text(0, 210, 23, 0, "Chistereza:" );
      //FTImpl.Cmd_Text(190, 210, 23, 0, "st C" );
      //FTImpl.Cmd_Text(0, 230, 23, 0, "Moc Gonu G1:" );
      //FTImpl.Cmd_Text(190, 230, 23, 0, "jm" );
      //FTImpl.Cmd_Text(0, 248, 23, 0, "Moc Gonu G2:" );
      //FTImpl.Cmd_Text(190, 248, 23, 0, "jm" );
      //FTImpl.Cmd_Text(277, 30, 23, 0, "Z Gon:" );
      //FTImpl.Cmd_Text(277, 50, 23, 0, "TempDnia:" );
      //FTImpl.Cmd_Text(277, 70, 23, 0, "Ukonczono:" );
      //FTImpl.Cmd_Text(277, 90, 23, 0, "Moc Stb G1:" );
      //FTImpl.Cmd_Text(435, 90, 23, 0, "jm" );
      //FTImpl.Cmd_Text(277, 110, 23, 0, "Moc Stb G2:" );
      //FTImpl.Cmd_Text(435, 110, 23, 0, "jm" );
      //FTImpl.Cmd_Text(277, 130, 23, 0, "Moc Zal G1:" );
      //FTImpl.Cmd_Text(435, 130, 23, 0, "jm" );
      //FTImpl.Cmd_Text(277, 150, 23, 0, "Moc Zal G2:" );
      //FTImpl.Cmd_Text(435, 150, 23, 0, "jm" );
      //FTImpl.Cmd_Text(277, 170, 23, 0, "Moc PzG G1:" );
      //FTImpl.Cmd_Text(435, 170, 23, 0, "jm" );
      //FTImpl.Cmd_Text(277, 190, 23, 0, "Moc PzG G2:" );
      //FTImpl.Cmd_Text(435, 190, 23, 0, "jm" );
  
//flashtext(160)


const char* const string_table[] PROGMEM = {STR_0, STR_1, STR_2,
										    STR_3, STR_4, STR_5,
										    STR_6, STR_7, STR_8,
										    STR_9, STR_10, STR_11,
										    STR_12, STR_13, STR_14,
										    STR_15, STR_16, STR_17,
										    STR_18, STR_19, STR_20,
										    STR_21, STR_22, STR_23,
										    STR_24, STR_25, STR_26,
										    STR_27, STR_28, STR_29,
										    STR_30, STR_31, STR_32,
										    STR_33, STR_34, STR_35,
										    STR_36, STR_37, STR_38,
										    STR_39, STR_40, STR_41,
										    STR_42, STR_43, STR_44,
										    STR_45, STR_46, STR_47,
										    STR_48, STR_49, STR_50,
										    STR_51, STR_52, STR_53,
										    STR_54, STR_55, STR_56,
										    STR_57, STR_58, STR_59,
										    STR_60, STR_61, STR_62,
										    STR_63, STR_64, STR_65,
										    STR_66, STR_67, STR_68,
										    STR_69, STR_70, STR_71,
										    STR_72, STR_73, STR_74,
										    STR_75, STR_76, STR_77,
										    STR_78, STR_79, STR_80,
										    STR_81, STR_82, STR_83,
										    STR_84, STR_85, STR_86,
										    STR_87, STR_88, STR_89,
										    STR_90, STR_91, STR_92,
										    STR_93, STR_94, STR_95,
										    STR_96, STR_97, STR_98,
										    STR_99, STR_100, STR_101,
										    STR_102, STR_103, STR_104,
										    STR_105, STR_106, STR_107,
										    STR_108, STR_109, STR_110,
										    STR_111, STR_112, STR_113,
										    STR_114, STR_115, STR_116,
										    STR_117, STR_118, STR_119,
										    STR_120, STR_121, STR_122,
										    STR_123, STR_124, STR_125,
										    STR_126, STR_127, STR_128,
										    STR_129, STR_130, STR_131,
										    STR_132, STR_133, STR_134,
										    STR_135, STR_136, STR_137,
										    STR_138, STR_139, STR_140,
										    STR_141, STR_142, STR_143,
										    STR_144, STR_145, STR_146,
										    STR_147, STR_148, STR_149,
										    STR_150, STR_151, STR_152,
										    STR_153, STR_154, STR_155,
										    STR_156, STR_157, STR_158,
										    STR_159, STR_160, STR_161,
										    STR_162, STR_163, STR_164,
										    STR_165, STR_166, STR_167,
                                            STR_168, STR_169, STR_170,
                                            STR_171, STR_172};



void print_work_time()
{
	Serial.print(String(gParametryPracy.gCzasProcesuGodz) + "." + String(gParametryPracy.gCzasProcesuMin) + "." + String(gParametryPracy.gCzasProcesuSek) + " ");
	
}

int prescaller = 0;
#define CLOCK_PRESCALER_256 (0x8)
void initTimer3()
{
  //cli();           // disable all interrupts
  //TCCR3A = 0;      // Clean the registers
  //TCCR3B = 0; 
  ////TCCR3B |= (1 << CS32) | (1 << CS30); // Prescaler 1024
  //TCCR3B = (1<<CS32)|(1<<CS30);
  //TCCR3B |= CLOCK_PRESCALER_256;
  //TIMSK3 |= (1 << TOIE3);              // enable timer overflow interrupt
  //sei();
  
  
  //TCCR3B = 0x00;        // Disable Timer2 while we set it up
  //TCNT3  = 130;         // Reset Timer Count  (255-130) = execute ev 125-th T/C clock
  //TIFR3  = 0x00;        // Timer2 INT Flag Reg: Clear Timer Overflow Flag
  //TIMSK3 = 0x01;        // Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  //TCCR3A = 0x00;        // Timer2 Control Reg A: Wave Gen Mode normal
  //TCCR3B = 0x0;        //  Timer2 Control Reg B: Timer Prescaler set to 1024
  
  
  //TCCR3A = 0;      // Clean the registers
  //TCCR3B = 0; 
  //TCNT3  = 0;
  
  //OCR3A = 62500; // compare match register 16MHz/256/2Hz
  //TCCR3B |= (1 << WGM32); // CTC mode
  //TCCR3B |= (1 << CS32); // 256 prescaler
  //TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt
   
}

//ISR(TIMER3_COMPA_vect)        // interrupt service routine 
//{
 //// Serial.println(F("isr")); 
 ////if(digitalRead(PowerPWR1) == LOW)
 ////{
	////digitalWriteFast(PowerPWR1,HIGH); 
 ////}else
 ////{
	////digitalWriteFast(PowerPWR1,LOW); 
 ////}
 
    //TCNT3 = 130;     // reset timer ct to 130 out of 255
   //TIFR3 = 0x00;    // timer2 int flag reg: clear timer overflow flag
  
 ////digitalWriteFast(PowerPWR1, digitalRead(PowerPWR1) ^ 1); // toggle LED pin
 
 ////prescaller++;
 ////if(prescaller >= 31250)
   ////prescaller = 0;
   
  //// OCR3A = prescaller;
  
//}

void setPwmF(int pin, int divisor)
 {
  byte mode;
      switch(divisor)
      {
      case 1: mode = 0x01; break;
      case 2: mode = 0x02; break;
      case 3: mode = 0x03; break;
      case 4: mode = 0x04; break;
      case 5: mode = 0x05; break;
      case 6: mode = 0x06; break;
      case 7: mode = 0x07; break;
      default: return;
      }
      
      switch(pin)
      {	  
      case 2:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
      case 3:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
      case 4:  TCCR0B = TCCR0B  & 0b11111000 | mode; break;
      case 5:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
      case 6:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
      case 7:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
      case 8:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
      case 9:  TCCR2B = TCCR0B  & 0b11111000 | mode; break;
      case 10: TCCR2B = TCCR2B  & 0b11111000 | mode; break;
      case 11: TCCR1B = TCCR1B  & 0b11111000 | mode; break;  
      case 12: TCCR1B = TCCR1B  & 0b11111000 | mode; break;  
      case 13: TCCR0B = TCCR0B  & 0b11111000 | mode; break;
      default: return;
    }

}
	
void discoverOneWireDevices(void)
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  byte num_devices = 0;
  
  Serial.print("Looking for 1-Wire devices...\n\r");
  while(gTempOneWire.search(addr))
  {
    Serial.print("\n\rFound \'1-Wire\' device with address:\n\r");
    num_devices++;
    for( i = 0; i < 8; i++)
    {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }
  }
  Serial.print("\n\r\n\rFound: ");
  Serial.print(num_devices);
  Serial.print(" 1-wire devices...");
  Serial.print("\n\r\n\r");
  gTempOneWire.reset_search();
  return;
}

void Update_PWR1()
{
 //cli();
 if(is_on == true)
 {
   is_on  = false;
   is_off = true;
   pwr1_change_state = true;
   gTimer.setperiod(on_time,gPwr1TimerEvent);
   return;	
 }
 if(is_off == true)
 {
   is_off = false;
   is_on  = true;
   pwr1_change_state = true; 
   gTimer.setperiod(off_time,gPwr1TimerEvent);
   return;
 }
 //sei();
}

void Update_PWR2()
{
 //cli();
 if(is_on2 == true)
 {
   is_on2  = false;
   is_off2 = true;
   pwr2_change_state = true;
   gTimer.setperiod(on_time2,gPwr2TimerEvent);
   //Serial.println(on_time);
   return;	
 }
 if(is_off2 == true)
 {
   is_off2 = false;
   is_on2  = true;
   pwr2_change_state = true; 
   gTimer.setperiod(off_time2,gPwr2TimerEvent);
   //Serial.println(off_time);
   return;
 }
 //sei();
}

void zero_Crossing_Interrupt_Grupowe()
{
  if(pwr1_change_state == true)
  {
	  if(digitalReadFast(GATE1) == LOW)
	  {
		  digitalWriteFast(GATE1, HIGH);
		  pwr1_change_state = false;
	  }else
	  {
		  digitalWriteFast(GATE1, LOW);
		  pwr1_change_state = false;
	  }
  }
}

void zero_Crossing_Interrupt_Grupowe2()
{
  if(pwr2_change_state == true)
  {
	  if(digitalReadFast(GATE2) == LOW)
	  {
		  digitalWriteFast(GATE2, HIGH);
		  pwr2_change_state = false;
	  }else
	  {
		  digitalWriteFast(GATE2, LOW);
		  pwr2_change_state = false;
	  }
  }
}

void zero_Crossing_Interrupt1()
{
  TCCR1B = 0x04; // start timer with divide by 256 input
  TCNT1  = 0;    // reset timer - count from zero
}

void zero_Crossing_Interrupt2()
{
  TCCR3B = 0x04; // start timer with divide by 256 input
  TCNT3  = 0;    // reset timer - count from zero
}

//isr I
ISR(TIMER1_COMPA_vect)
{ 
  digitalWriteFast(GATE1,HIGH);		
  TCNT1 = 65536-PULSE;    
}
ISR(TIMER1_OVF_vect)
{ 	
  digitalWriteFast(GATE1,LOW); 
  TCCR1B = 0x00;           
}

// isr II
ISR(TIMER3_COMPA_vect)
{ 
  digitalWriteFast(GATE2,HIGH);		
  TCNT3 = 65536-PULSE;         // trigger pulse width
}
ISR(TIMER3_OVF_vect)
{ 	
  digitalWriteFast(GATE2,LOW); // timer1 overflow
  TCCR3B = 0x00;               // disable timer stopd unintended triggers
}



void zero_INIT_Grupowe_zerocross()
{
  pwr1_change_state = false;
  on_time  = 0;
  off_time = 0;
  is_on    = false;
  is_off   = false;	
  pinMode(GATE1, OUTPUT);      
  digitalWrite(GATE1, LOW);
  detachInterrupt(INTERRUPT1);
  attachInterrupt(INTERRUPT1,zero_Crossing_Interrupt_Grupowe, RISING);
}

void zero_INIT_Grupowe_zerocross2()
{
  pwr2_change_state = false;
  on_time2  = 0;
  off_time2 = 0;
  is_on2    = false;
  is_off2   = false;	
  pinMode(GATE2, OUTPUT);      
  digitalWrite(GATE2, LOW);
  detachInterrupt(INTERRUPT2);
  attachInterrupt(INTERRUPT2,zero_Crossing_Interrupt_Grupowe2, RISING);
}

#define ZAKRES 520
#define ZAKRES 550
#define MAXbright 63 
void zero_INIT1_zerocross()
{
  // set up pins
  pinMode(DETECT1, INPUT);     // zero cross detect
  digitalWrite(DETECT1, HIGH); // enable pull-up resistor
  pinMode(GATE1, OUTPUT);      // TRIAC gate control
  digitalWrite(GATE1, LOW);

  // set up Timer1 
  OCR1A  = 1000;     // initialize the comparator
  TIMSK1 = 0x03;    // enable comparator A and overflow interrupts
  TCCR1A = 0x00;    // timer control registers set for
  TCCR1B = 0x00;    // normal operation, timer disabled
   
  

    //LOW to trigger the interrupt whenever the pin is low,
    //CHANGE to trigger the interrupt whenever the pin changes value
    //RISING to trigger when the pin goes from low to high,
    //FALLING for when the pin goes from high to low.
    //HIGH to trigger the interrupt whenever the pin is high.


  attachInterrupt(INTERRUPT1,zero_Crossing_Interrupt1, RISING); //RISING
  //detachInterrupt(INTERRUPT1);

  OCR1A = 1000;   // ( 60max -- 600min ) zakres: 560
                  //   100%  -- 0%
                  // -------------------
                  //   60  = 100%
                  //   600 = 0%
                  //   5%  = (600 - 40) - 5% =  532 
                  //   10% = (600 - 40) - 10% = 504 
                  //   20% = (600 - 40) - 20% = 448
                  //   30% = (600 - 40) - 30% = 392
                  //   50% = (600 - 40) - 50% = 280    
}

void zero_INIT2_zerocross()
{
  // set up pins
  pinMode(DETECT2, INPUT);     // zero cross detect
  digitalWrite(DETECT2, HIGH); // enable pull-up resistor
  pinMode(GATE2, OUTPUT);      // TRIAC gate control
  digitalWrite(GATE2, LOW);

  // set up Timer3 
  OCR3A  = 1000;     // initialize the comparator
  TIMSK3 = 0x03;    // enable comparator A and overflow interrupts
  TCCR3A = 0x00;    // timer control registers set for
  TCCR3B = 0x00;    // normal operation, timer disabled
   
  

    //LOW to trigger the interrupt whenever the pin is low,
    //CHANGE to trigger the interrupt whenever the pin changes value
    //RISING to trigger when the pin goes from low to high,
    //FALLING for when the pin goes from high to low.
    //HIGH to trigger the interrupt whenever the pin is high.


  attachInterrupt(INTERRUPT2,zero_Crossing_Interrupt2, RISING); //RISING

  OCR3A = 1000;  
}

// example of use: delay_min(20);
void delay_min(int min)
{
  for(int lop = 0;lop < min * 60;lop++)
  {
	  delay(1000);//one second delay
	  //Serial.println(F("next delay"));	
  }	
}

char *flashtext(int i) 
{
   return strcpy_P ( bufor, (char *) pgm_read_word (& (string_table [i]))); 
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#define PLOT_LENGTH 240
#define PLOT_HEIGHT 50

void plot(int plotMax, int height, bool fill,bool record,int rawAveVal)
  {
    int x = 0;
    long pY;
    float yLoc;
    static int plotIndex = 0;
    static int inputIndex = 0;
    static unsigned char plothist[PLOT_LENGTH] = {0};
    //Update the history for the plot

    //Map the value to the plot window
    //We cut the PLOT_HEIGHT in half because we want it to fit in an unsigned char variable
    pY =  mapfloat((float)rawAveVal, 0, (float)plotMax, 0, (float)PLOT_HEIGHT / 2);

    //limit to 0
    if(pY < 0)
      pY = 0;
      
    plothist[inputIndex] = pY;
    //Convert the mapped value to the screen Y location
    yLoc = 272 - pY;
    if (yLoc < (272 - height))
      yLoc = (272 - height);
    if (yLoc > 272)
      yLoc = 272;

    if(record == true)
      inputIndex++;

    if (inputIndex == PLOT_LENGTH) inputIndex = 0;
    //Print the plot using Strip lines
    FTImpl.ColorRGB(255, 0, 0);

    if (fill == true)
      FTImpl.Begin(FT_EDGE_STRIP_B);
    else
      FTImpl.Begin(FT_LINE_STRIP);
    
    //Loop through the history array and plot the current history
    //Notice we are Keeping a history of only 240 plot points, to fill the whole 480 screen width
    //we add 2 each time we loop through the for statment to effectivly double the plot width. 
    for (int hist = 0; hist < PLOT_LENGTH; hist++)
    {
      plotIndex++;
      if (plotIndex == PLOT_LENGTH)
        plotIndex = 0;
      x += 2;
      
      //Convert the mapped value to the screen Y location
      yLoc = 272 - plothist[plotIndex] * 2;
      if (yLoc < (272 - height))
        yLoc = (272 - height);
      if (yLoc > 272)
        yLoc = 272;
      FTImpl.Vertex2ii(x,yLoc, 0, 0);
    }
    
    if(record == true)
      plotIndex++;
    if (plotIndex == PLOT_LENGTH)
      plotIndex = 0;
    FTImpl.End();
    FTImpl.ColorRGB(255, 255, 255);

        
    //Print the line to border the top of the plot
    FTImpl.ColorRGB(255, 255, 255);
    FTImpl.Begin(FT_LINES);
    FTImpl.Vertex2ii(0, 272 - height, 0, 0);
    FTImpl.Vertex2ii(487, 272 - height, 0, 0);
    FTImpl.End();

}

void DrawPoint(int x,int y,int w,int h,int colorR,int colorG,int colorB)
{
        FTImpl.ColorRGB(colorR,colorG,colorB);
		FTImpl.PointSize(w * h);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2ii(x, y, w, h);
		FTImpl.End();
}
 
void DrawPoint2(int x,int y,int w,int h)
{
       	FTImpl.PointSize(w * h);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2ii(x, y, w, h);
		FTImpl.End();
}



   
void Sound_Play(uint8_t sound,uint8_t vol,uint8_t midi)
{
	    //FTImpl.PlaySound(Vol,(uint16_t)((Pitch<<8) | Sound));
		FTImpl.PlaySound((((5000 + 21) << 8) | sound));
}

void Sound_Play2(uint8_t sound,uint8_t vol,uint8_t midi)
{
	    FTImpl.PlaySound(vol,(uint16_t)((midi<<8) | sound));
}

void SetPowerON_1(int power)
{
	if(power > 0)
	{
	 analogWrite(PowerPWR1,power);
	 gParametryPracy.gPowerPWR1 = true;
	}else
	{
	 analogWrite(PowerPWR1,0);
	 gParametryPracy.gPowerPWR1 = false;
	}
}



//void SetPowerON_1(int power)
//{

 //if(gParametryPracy.gPowerPWR1 == true) return;

  ////liniowo
  //if(gParametryPracy.gTypMocy == true)
  //{
	//zero_INIT1_zerocross();
	//if(power >= 100) power = 99;	
	//if(power > 0)
	//{
	 ////OCR1A = map(power, 0, 100, ZAKRES, MAXbright);
	 //OCR1A = (ZAKRES - (ZAKRES * (0.01 * power))) + power/2;
	 //gParametryPracy.gPowerPWR1 = true;
	 ////print_work_time();
	 ////Serial.println(F("G1 ON"));
	 //if(gParametryPracy.gSYS_LOG == true) DataLog("G1 ON");
	//}else if(power == 0)
	//{
	 //OCR1A = 1000;
	 //detachInterrupt(INTERRUPT1);
	 //gParametryPracy.gPowerPWR1 = false;
	 ////print_work_time();
	 ////Serial.println(F("G1 OFF"));
	 //if(gParametryPracy.gSYS_LOG == true) DataLog("G1 OFF");
	//}
  //}else
  //{
	  ////grupowo
	  //if(power > 100) power = 100;
	  //if(power == 100)
	  //{
		  //gTimer.stop(gPwr1TimerEvent);
		  //detachInterrupt(INTERRUPT1);
	      //digitalWriteFast(GATE1,HIGH);
	      //gParametryPracy.gPowerPWR1 = true;
	      ////print_work_time();
	      ////Serial.println(F("G1 ON"));
	      //if(gParametryPracy.gSYS_LOG == true) DataLog("G1 ON");
	      //return;
	  //}
	//if(power > 0 && power < 100)
	//{
	  //zero_INIT_Grupowe_zerocross();  
	  //on_time  = ((power * 0.01) * gParametryPracy.gCzestotliwoscMocyGrupowo);
	  //off_time = gParametryPracy.gCzestotliwoscMocyGrupowo - on_time;
	  //gTimer.stop(gPwr1TimerEvent);
	  //gPwr1TimerEvent = gTimer.every(on_time,Update_PWR1);
	  //is_on = true;
	  //gParametryPracy.gPowerPWR1 = true;
	  ////print_work_time();
	  ////Serial.println(F("G1 ON"));
	  //if(gParametryPracy.gSYS_LOG == true) DataLog("G1 ON");
    //}else
    //{
	  //detachInterrupt(INTERRUPT1);
	  //digitalWriteFast(GATE1,LOW);
	  //gParametryPracy.gPowerPWR1 = false;
	  ////print_work_time();
	  ////Serial.println(F("G1 OFF")); 	
	  //if(gParametryPracy.gSYS_LOG == true) DataLog("G1 OFF");
	//}
  //}
//}


//void SetPowerON_2(int power)
//{
  //if(gParametryPracy.gPowerPWR2 == true) return;	
	
  ////liniowo	
  //if(gParametryPracy.gTypMocy == true)
  //{
	//zero_INIT2_zerocross();
	
	//if(power >= 100) power = 99;	
	//if(power > 0)
	//{
	 ////OCR1A = (ZAKRES - (ZAKRES * (0.01 * power))) + power/2;
	 //OCR3A = map(power, 0, 100, ZAKRES, MAXbright);
	 //gParametryPracy.gPowerPWR2 = true;
	 ////print_work_time();
	 ////Serial.println(F("G2 ON"));
	 //if(gParametryPracy.gSYS_LOG == true) DataLog("G2 ON");
	//}else if(power == 0)
	//{
	 //OCR3A = 1000;
	 //detachInterrupt(INTERRUPT2);
	 //gParametryPracy.gPowerPWR2 = false;
	 ////print_work_time();
	 ////Serial.println(F("G2 OFF"));
	 //if(gParametryPracy.gSYS_LOG == true) DataLog("G2 OFF");
	//}
  //}else
  //{ // Grupowe
	  ////if(power >= 100) power = 99;
	  
	  //if(power > 100) power = 100;
	  
	  //if(power == 100)
	  //{
		  //gTimer.stop(gPwr2TimerEvent);
		  //detachInterrupt(INTERRUPT2);
	      //digitalWriteFast(GATE2,HIGH);
	      //gParametryPracy.gPowerPWR2 = true;
	      ////print_work_time();
	      ////Serial.println(F("G2 ON"));
	      //if(gParametryPracy.gSYS_LOG == true) DataLog("G2 ON");
	      //return;
	  //}
		 
	  
	  
	  
	//if(power > 0)
	//{
	  //zero_INIT_Grupowe_zerocross2();  
	  //on_time2  = ((power * 0.01) * gParametryPracy.gCzestotliwoscMocyGrupowo);
	  //off_time2 = gParametryPracy.gCzestotliwoscMocyGrupowo - on_time2;
	  ////gTimer.stop(gPwr2TimerEvent);
	  //gPwr2TimerEvent = gTimer.every(on_time2,Update_PWR2);
	  //is_on2 = true;
	  //gParametryPracy.gPowerPWR2 = true;
	  ////print_work_time();
	  ////Serial.println(F("G2 ON"));
	  //if(gParametryPracy.gSYS_LOG == true) DataLog("G2 ON");
    //}else
    //{
	  //detachInterrupt(INTERRUPT2);
	  //digitalWriteFast(GATE2,LOW);
	  //gParametryPracy.gPowerPWR2 = false; 
	  ////print_work_time();
	  ////Serial.println(F("G2 OFF"));	
	  //if(gParametryPracy.gSYS_LOG == true) DataLog("G2 OFF");
	//}
	  
  //}
	
	
//}

void SetPowerON_2(int power)
{
	if(power > 0)
	{
  	 analogWrite(PowerPWR2,power);
	 gParametryPracy.gPowerPWR2 = true;
    }else
    {
	 analogWrite(PowerPWR2,0);
	 gParametryPracy.gPowerPWR2 = false;	
	}
}

void SetPowerON_1_max()
{
	analogWrite(PowerPWR1,255);
	gParametryPracy.gPowerPWR1 = true;
}

//void SetPowerON_1_max()
//{
  //if(gParametryPracy.gTypMocy == true)
  //{
	//zero_INIT1_zerocross();
	//OCR1A = MAXbright;
	//gParametryPracy.gPowerPWR1 = true;
  //}else
  //{
	 //SetPowerON_1(100); 
  //}
//}

//void SetPowerON_2_max()
//{
  //if(gParametryPracy.gTypMocy == true)
  //{
	//zero_INIT2_zerocross();
	//OCR3A = MAXbright;
	//gParametryPracy.gPowerPWR2 = true;
  //}else
  //{
	 //SetPowerON_2(100);  
  //}
//}

void SetPowerON_2_max()
{
	analogWrite(PowerPWR2,255);
	gParametryPracy.gPowerPWR2 = true;
}

void SetPowerON_3()
{
	if(gParametryPracy.gPowerPWR3 == true) return;
	digitalWriteFast(PowerPWR3,HIGH);
	gParametryPracy.gPowerPWR3 = true;
	//print_work_time();
	//Serial.println(F("G3 ON"));
	if(gParametryPracy.gSYS_LOG == true) DataLog("G3 ON");
}

void SetPowerOFF_1()
{
	analogWrite(PowerPWR1,0);
	gParametryPracy.gPowerPWR1 = false;
}

//void SetPowerOFF_1()
//{
 //// if(gParametryPracy.gPowerPWR1	== false) return; 
  //if(gParametryPracy.gTypMocy == true) //liniowe
  //{
	//OCR1A = 1000;
	//detachInterrupt(INTERRUPT1);
	//digitalWriteFast(GATE1,LOW);
	//gParametryPracy.gPowerPWR1 = false;
	////print_work_time();
	////Serial.println(F("G1 OFF"));
	//if(gParametryPracy.gSYS_LOG == true) DataLog("G1 OFF");
  //}else
  //{
	 //gTimer.stop(gPwr1TimerEvent);
	 //detachInterrupt(INTERRUPT1);
	 //digitalWriteFast(GATE1,LOW);
	 //gParametryPracy.gPowerPWR1 = false;
	 ////print_work_time();
	 ////Serial.println(F("G1 OFF")); 
	 //if(gParametryPracy.gSYS_LOG == true) DataLog("G1 OFF");
  //}
//}

//void SetPowerOFF_2()
//{
 //// if(gParametryPracy.gPowerPWR2	== false) return;	
  //if(gParametryPracy.gTypMocy == true)
  //{
	//OCR3A = 1000;
	//detachInterrupt(INTERRUPT2);
	//digitalWriteFast(GATE2,LOW);
	//gParametryPracy.gPowerPWR2 = false;
	////print_work_time();
	////Serial.println(F("G2 OFF"));
	//if(gParametryPracy.gSYS_LOG == true) DataLog("G2 OFF");
  //}else
  //{
	//gTimer.stop(gPwr2TimerEvent);
	//detachInterrupt(INTERRUPT2);
	//digitalWriteFast(GATE2,LOW);
	//gParametryPracy.gPowerPWR2 = false;
	////print_work_time();   
	////Serial.println(F("G2 OFF"));
	//if(gParametryPracy.gSYS_LOG == true) DataLog("G2 OFF");
  //}
//}

void SetPowerOFF_2()
{
	analogWrite(PowerPWR2,0);
	gParametryPracy.gPowerPWR2 = false;
}

void SetPowerOFF_3()
{
	digitalWrite(PowerPWR3,LOW);
	gParametryPracy.gPowerPWR3 = false;
	//print_work_time();
	//Serial.println(F("G3 OFF"));
	if(gParametryPracy.gSYS_LOG == true) DataLog("G3 OFF");
}

void SetValveON_M(int valve) //Otwiera dany zawórek
{
	if(digitalRead(valve) == LOW)
	return;

	//WODA
	if(valve == ZaworWoda)
	{
		digitalWrite(ZaworWoda,LOW);
		gParametryPracy.gZaworWoda = true;
		//print_work_time();
		//Serial.println(F("Zwoda ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZW ON");
		Sound_Play(0x14,100,108);
		return;
	}

	//Gon
	if(valve == ZaworGonu)
	{
		digitalWrite(ZaworGonu,LOW);
		gParametryPracy.gZaworGonu = true;
		//print_work_time();
		//Serial.println(F("Zgon ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG1 ON");
		Sound_Play(0x14,100,108);
		return;
	}

	//Gon2
	if(valve == ZaworGonu2)
	{
		digitalWrite(ZaworGonu2,LOW);
		gParametryPracy.gZaworGonu2 = true;
		//print_work_time();
		//Serial.println(F("Zgon2 ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG2 ON");
		Sound_Play(0x14,100,108);
		return;
	}

	//Przedgonu
	if(valve == ZaworPrzedGon)
	{
		digitalWrite(ZaworPrzedGon,LOW);
		gParametryPracy.gZaworPrzedGon = true;
		//print_work_time();
		//Serial.println(F("Zprzedgon ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZPG ON");
		Sound_Play(0x14,100,108);
		return;
	}
}


void SetValveON(int valve) //Otwiera dany zawórek
{
	if(digitalRead(valve) == LOW)
	return;

	//WODA
	if(valve == ZaworWoda)
	{
		digitalWrite(ZaworWoda,LOW);
		gParametryPracy.gZaworWoda = true;
		//print_work_time();
		//Serial.println(F("Zwoda ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZW ON");
		Sound_Play(0x14,100,108);
		return;
	}

	//Gon
	if(valve == ZaworGonu)
	{
		digitalWrite(ZaworGonu,LOW);
		gParametryPracy.gZaworGonu = true;
		//print_work_time();
		//Serial.println(F("Zgon ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG1 ON");
		gParametryPracy.gZaworGonCntr++;
		Sound_Play(0x14,100,108);
		return;
	}

	//Gon2
	if(valve == ZaworGonu2)
	{
		digitalWrite(ZaworGonu2,LOW);
		gParametryPracy.gZaworGonu2 = true;
		//print_work_time();
		//Serial.println(F("Zgon2 ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG2 ON");
		gParametryPracy.gZaworGon2Cntr++;
		Sound_Play(0x14,100,108);
		return;
	}

	//Przedgonu
	if(valve == ZaworPrzedGon)
	{
		digitalWrite(ZaworPrzedGon,LOW);
		gParametryPracy.gZaworPrzedGon = true;
		//print_work_time();
		//Serial.println(F("Zprzedgon ON"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZPG ON");
		Sound_Play(0x14,100,108);
		return;
	}
}

//Turn OFF valve
void SetValveOFF(int valve)
{
	if(digitalRead(valve) == HIGH)
	return;

	//WODA
	if(valve == ZaworWoda)
	{
		digitalWrite(ZaworWoda,HIGH);
		//print_work_time();
		//Serial.println(F("Zwoda OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZW OFF");
		gParametryPracy.gZaworWoda = false;
		return;
	}

	//Gon
	if(valve == ZaworGonu)
	{
		digitalWrite(ZaworGonu,HIGH);
		gParametryPracy.gZaworGonu = false;
		//print_work_time();
		//Serial.println(F("ZGonu OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG OFF");
		return;
	}

	//Gon2
	if(valve == ZaworGonu2)
	{
		digitalWrite(ZaworGonu2,HIGH);
		gParametryPracy.gZaworGonu2 = false;
		//print_work_time();
		//Serial.println(F("ZGonu2 OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG2 OFF");
		return;
	}

	//Przedgonu
	if(valve == ZaworPrzedGon)
	{
		digitalWrite(ZaworPrzedGon,HIGH);
		gParametryPracy.gZaworPrzedGon = false;
		//print_work_time();
		//Serial.println(F("Zprzedgon OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZPG OFF");
		return;
	}
}

//Turn OFF valve MAN
void SetValveOFF_M(int valve)
{
	if(digitalRead(valve) == HIGH)
	return;

	//WODA
	if(valve == ZaworWoda)
	{
		digitalWrite(ZaworWoda,HIGH);
		//print_work_time();
		//Serial.println(F("Zwoda OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZW OFF");
		gParametryPracy.gZaworWoda = false;
		return;
	}

	//Gon
	if(valve == ZaworGonu)
	{
		digitalWrite(ZaworGonu,HIGH);
		//print_work_time();
		//Serial.println(F("Zgon OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG1 OFF");
		gParametryPracy.gZaworGonu = false;
		return;
	}

	//Gon2
	if(valve == ZaworGonu2)
	{
		digitalWrite(ZaworGonu2,HIGH);
		//print_work_time();
		//Serial.println(F("Zgonu2 OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZG2 OFF");
		gParametryPracy.gZaworGonu2 = false;
		return;
	}

	//Przedgonu
	if(valve == ZaworPrzedGon)
	{
		digitalWrite(ZaworPrzedGon,HIGH);
		//print_work_time();
		//Serial.println(F("Zprzedgonu OFF"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("ZPG OFF");
		gParametryPracy.gZaworPrzedGon = false;
		return;
	}
}

void SetValvesOFF() //Zamyka wszystkie zawory jeśli nie są pozamykane
{
	if(digitalRead(ZaworWoda) == LOW)
	{
	  digitalWrite(ZaworWoda,HIGH);
	  gParametryPracy.gZaworWoda = false;
	  //print_work_time();
	  //Serial.println(F("Zwoda OFF"));
	  if(gParametryPracy.gSYS_LOG == true) DataLog("ZW OFF");
    }

    if(digitalRead(ZaworPrzedGon) == LOW)
	{
      digitalWrite(ZaworPrzedGon,HIGH);
      //print_work_time();
      //Serial.println(F("Zprzedgon OFF"));
      if(gParametryPracy.gSYS_LOG == true) DataLog("ZPG OFF");
      gParametryPracy.gZaworPrzedGon = false;
    }

    if(digitalRead(ZaworGonu) == LOW)
	{
      digitalWrite(ZaworGonu,HIGH);
      //print_work_time();
      //Serial.println(F("Zgon OFF"));
      if(gParametryPracy.gSYS_LOG == true) DataLog("ZG1 OFF");
      gParametryPracy.gZaworGonu = false;
    }

    if(digitalRead(ZaworGonu2) == LOW)
	{
     digitalWrite(ZaworGonu2,HIGH);
     //print_work_time();
     //Serial.println(F("Zgon2 OFF"));
     if(gParametryPracy.gSYS_LOG == true) DataLog("ZG2 OFF");
     gParametryPracy.gZaworGonu2 = false;
	}
}

bool WIFI_CheckIP()
{
    //checking IP string ----->255:255:255:255  192168:0 192:168:8:100
	//Serial.println(String(gParametryPracy_RCV.ip1) + "." + String(gParametryPracy_RCV.ip2) + "." + String(gParametryPracy_RCV.ip3) + "." + String(gParametryPracy_RCV.ip4));
	if( (gParametryPracy_RCV.ip1 > 0 && gParametryPracy_RCV.ip1 < 255) 
	    && (gParametryPracy_RCV.ip2 > 0 && gParametryPracy_RCV.ip2 < 255)
	    && (gParametryPracy_RCV.ip3 > 0 && gParametryPracy_RCV.ip3 < 255)
	    && (gParametryPracy_RCV.ip4 > 0 && gParametryPracy_RCV.ip4 < 255) )
	 return true;//IP seems to be OK so we connected now ???
return false;
}

void Restart_from_WMan()
{
	switch( gParametryPracy.gEtap )
	{
	 case 1: //rozgrzewanko
	 {
      //Valves CLOSE
	  SetValvesOFF();// zamknij jeśli otwarte
	  SetPowerON_1(100);
	  SetPowerON_2(100);
	  SetPowerON_3();
	 }
	 break;

	 case 2: //zalewanie
	 {
	   SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta

	   //zamknac reszte zaworów
	   SetValveOFF(ZaworPrzedGon);
	   SetValveOFF(ZaworGonu);
	   SetValveOFF(ZaworGonu2);
	   
	  
	   if(gParametryPracy.gPrzerwaPoZalaniu == false)
       {
	     SetPowerON_1(gParametryPracy.gMocZalaniaG1);
	     SetPowerON_2(gParametryPracy.gMocZalaniaG2);
	     SetPowerON_3();
	   }else
	   {
		  //gParametryPracy_OUT.gCzyZalano == true
		  //wył.. grzanie przerwa po zalaniu
		  SetPowerOFF_1();
		  SetPowerOFF_2();
		  SetPowerOFF_3();
	   }
	 }
	 break;

	 case 3: //stabilizacyja
	 {
	  SetPowerOFF_3();

	  SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
	  //jak nie zamkniete to zam.zaw.
	  SetValveOFF(ZaworPrzedGon);
	  SetValveOFF(ZaworGonu);
	  SetValveOFF(ZaworGonu2);

	  SetPowerON_1(gParametryPracy.gMocStabilizacjiG1);
	  SetPowerON_2(gParametryPracy.gMocStabilizacjiG2);
	 }
	 break;

	 case 4: //przedgony
	 {
	   SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
	   SetValveON(ZaworPrzedGon); //otwarcie zaw przedgon jeśli zamknięty

	   //zamkniecie gonu
	   SetValveOFF(ZaworGonu);
	   SetValveOFF(ZaworGonu2);

	   SetPowerOFF_3();

	   if(gParametryPracy.gStabPrzedgon == false)
	   {
	    SetPowerON_1(gParametryPracy.gMocPrzedgonuG1);
	    SetPowerON_2(gParametryPracy.gMocPrzedgonuG2);
	   }else
	   {
		SetPowerON_1(gParametryPracy.gMocGonuG1);
	    SetPowerON_2(gParametryPracy.gMocGonuG2);
	   }
	   
	    if(gParametryPracy.gDuzeJeziorko == true)
	    {
			SetValveOFF(ZaworPrzedGon);
		}else
		{
			SetValveON(ZaworPrzedGon);
		}
	   
	   
	   
	 }
	 break;

	 case 5: //gony
	 {
		SetPowerOFF_3();
		SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
		SetValveOFF(ZaworPrzedGon); //zamknięcie zaw. przedgonu jeśli otwarty

		if(gParametryPracy.gDrugaMocGonu == true)
		{
		 SetPowerON_1(gParametryPracy.gMocGonu2_G1);
	     SetPowerON_2(gParametryPracy.gMocGonu2_G2);

		}else
		{
		 SetPowerON_1(gParametryPracy.gMocGonuG1);
	     SetPowerON_2(gParametryPracy.gMocGonuG2);
		}
		
		//przywrucenie zaworów Gon1 Gon2
		if(gParametryPracy.gZaworGonu == true)
		{
		  SetValveON(ZaworGonu);
		}else
		{
		  SetValveOFF(ZaworGonu);
		}
		if(gParametryPracy.gZaworGonu2 == true)
		{
		  SetValveON(ZaworGonu2);
		}else
		{
		  SetValveOFF(ZaworGonu2);
		}

	 }
	 break;

	 case 6: //pogony
	 {
      SetPowerOFF_3();

	  SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta

	  //odtworzenie stanu zaworkow.....................
      SetValveOFF(ZaworGonu);      //zamyk. zaw gon
      SetValveOFF(ZaworGonu2);     //zamyk. zaw gon2
      SetValveON(ZaworPrzedGon);   //otw przedgon-pogon

	  SetPowerON_1(gParametryPracy.gMocGonuG1);
	  SetPowerON_2(gParametryPracy.gMocGonuG2);
	 }
	 break;

	 case 7: //chłodzenie głowycy
	 {
	  SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta

	  SetValveOFF(ZaworPrzedGon);
	  SetValveOFF(ZaworGonu);
	  SetValveOFF(ZaworGonu2);
	  //wył.. grzanie
	  SetPowerOFF_1();
	  SetPowerOFF_2();
	  SetPowerOFF_3();
	 }
	 
	 case 8: //koniec
	 {
	   SetValveOFF(ZaworPrzedGon);
	   SetValveOFF(ZaworGonu);
	   SetValveOFF(ZaworGonu2);
	   //wył.. grzanie
	   SetPowerOFF_1();
	   SetPowerOFF_2();
	   SetPowerOFF_3();
		 
	 }
	 break;
	 
    }
	
}

void ProcessMessageCode()
{
	
	if(gParametryPracy_RCV.gMessageCode == 0)
	return;
	
	if(gParametryPracy_RCV.gMessageCode == 11)
	{
		if(gStartAUTO == false)
		{
		    Sound_Play(0x14,100,108);
		    Serial.println(F("AUTO START"));
			AutoStartProgress();
			AAc_0Asetup();
		}
		return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 12)
	{
		if(gStartAUTO == true)
		{
			Serial.println(F("AUTO STOP"));
		    AAc_dis_AUTO();
	    }
	    return;
	} 
	
	if(gParametryPracy_RCV.gMessageCode == 13)
	{
		////Auto_wznowienie();
		//Serial.println(F("RESTORE-BACKUP"));
		//Sound_Play(0x14,100,108);
		//String FileName("backup.bcg");
		//if(SD_LoadConfig(FileName) == true)
		//{
		  //Auto_wznowienie();
		  //gStartAUTO = true; //uruchomic AUTOMAT jak się da?
		//}
	    return;
	}
	
	
	//OKIDOKI
	if(gParametryPracy_RCV.gMessageCode == 14)
	{
		if(bPotwODBGonu == true)
		  {
		    if(gParametryPracy.gEtap == 5)
		    {
		     Serial.println(F("POTW ODB GONU"));
		     www_Okidoki_POTW = true;
		    }
		  }else
		  {
			if(gParametryPracy.gEtap == 8)
		    {
		     gParametryPracy.gEtap = 0;
		    }
		  }
	    return;
	}  
	
	
	//LOAD options from WWW and SAVE to EEPROM
	if(gParametryPracy_RCV.gMessageCode == 15)
	{
		 Serial.println(F("LOAD OPTIONS FROM WWW"));	
		 gParametryPracy.gMocZalaniaG1 = gParametryPracy_RCV.gMocZalaniaG1;
		 gParametryPracy.gMocZalaniaG2 = gParametryPracy_RCV.gMocZalaniaG2;
		 gParametryPracy.gMocStabilizacjiG1 = gParametryPracy_RCV.gMocStabilizacjiG1;
		 gParametryPracy.gMocStabilizacjiG2 = gParametryPracy_RCV.gMocStabilizacjiG2;
		 gParametryPracy.gMocPrzedgonuG1 = gParametryPracy_RCV.gMocPrzedgonuG1;
		 gParametryPracy.gMocPrzedgonuG2 = gParametryPracy_RCV.gMocPrzedgonuG2;
		 gParametryPracy.gMocGonuG1 = gParametryPracy_RCV.gMocGonuG1;
		 gParametryPracy.gMocGonuG2 = gParametryPracy_RCV.gMocGonuG2;
		 gParametryPracy.gMocGonu2_G1 = gParametryPracy_RCV.gMocGonu2_G1;
		 gParametryPracy.gMocGonu2_G2 = gParametryPracy_RCV.gMocGonu2_G2;
		 
		 gParametryPracy.gTempZmianyMocyGonu = gParametryPracy_RCV.gTempZmianyMocyGonu;
		 gParametryPracy.gTempStopPogonu = gParametryPracy_RCV.gTempStopPogonu;
		 gParametryPracy.gTempStartPogonu = gParametryPracy_RCV.gTempStartPogonu;
		 gParametryPracy.gTempRozgrzewania = gParametryPracy_RCV.gTempRozgrzewania;
		 gParametryPracy.gTempStopGrzania = gParametryPracy_RCV.gTempStopGrzania;
		 gParametryPracy.gTempZG2 = gParametryPracy_RCV.gTempZG2;
		 
		 gParametryPracy.gPlukanieOLM = gParametryPracy_RCV.gPlukanieOLM;
		 gParametryPracy.gZalanieZadaneX = gParametryPracy_RCV.gZalanieZadaneX;
		 gParametryPracy.gZadanyPoziomZalania = gParametryPracy_RCV.gZadanyPoziomZalania;
		 gParametryPracy.gHisterezaTemperatury = gParametryPracy_RCV.gHisterezaTemperatury;
		 
		 gParametryPracy.gZadanyCzasStabilizacji = gParametryPracy_RCV.gZadanyCzasStabilizacji;
		 gParametryPracy.gZadanyCzasOdbPrzedgonuSek = gParametryPracy_RCV.gZadanyCzasOdbPrzedgonuSek;
		 gParametryPracy.gZadanyCzasOdbPrzedgonuMin = gParametryPracy_RCV.gZadanyCzasOdbPrzedgonuMin;
		 gParametryPracy.gZadanyCzasStabPrzedgonu = gParametryPracy_RCV.gZadanyCzasStabPrzedgonu;
		 gParametryPracy.gZadanyCzasZalewania = gParametryPracy_RCV.gZadanyCzasZalewania;
		 gParametryPracy.gZadanyCzasPrzerwyMocyZalania = gParametryPracy_RCV.gZadanyCzasPrzerwyMocyZalania;
		 gParametryPracy.gZadanyCzasChlodzenia = gParametryPracy_RCV.gZadanyCzasChlodzenia;
		 
		 gParametryPracy.gTempUpdateTime = gParametryPracy_RCV.gTempUpdateTime;
		 gParametryPracy.gTEMPERATURE_PRECISION = gParametryPracy_RCV.gTEMPERATURE_PRECISION;
		 
		 gParametryPracy.gIloscZaworowGonu = gParametryPracy_RCV.gIloscZaworowGonu;
		 
		 gParametryPracy.gHistPoGonu = gParametryPracy_RCV.gHistPoGonu;
		 gParametryPracy.gCzujnikZalania = gParametryPracy_RCV.gCzujnikZalania;
		 gParametryPracy.gDuzeJeziorko = gParametryPracy_RCV.gDuzeJeziorko;
		 
		 gParametryPracy.gWIFI_MODE = gParametryPracy_RCV.gWIFI_MODE;


		 gTimer.setperiod(gParametryPracy_RCV.gTempUpdateTime,gTempSensorEvent);
		 
		 Serial.println(F("AND SAVE TO EPROM"));	
		 SaveToEprom();
		 
	    return;
	} 
	
	
	//LOAD from eprom
	if(gParametryPracy_RCV.gMessageCode == 17)
	{
		Serial.println(F("LOAD FROM EEPROM"));	
		eepromRead(0, &gParametryPracy, sizeof(gParametryPracy));
		return;
	}
	
	//MAN START
	if(gParametryPracy_RCV.gMessageCode == 18)
	{
		if(gStartMAN == false)
		{
		 Serial.println(F("MAN START")); 
		 //gStartMAN = true;
		 AA_Manual();
		 //gParametryPracy.gNR_Okna = 78;//MAN
		}
		return;
	}
	
	
	//MAN STOP
	if(gParametryPracy_RCV.gMessageCode == 19)
	{
		if(gStartMAN == true)
		{
		  if(gStartAUTO == true)
		  {
		   Restart_from_WMan();
		   gStartMAN = false;	
	      }else
	      {
		   gStartMAN = false;
		   SetPowerOFF_1();
		   SetPowerOFF_2();
		   SetPowerOFF_3();
		   SetValvesOFF();
	      }
		}
		gParametryPracy.gNR_Okna = 0;
		Serial.println(F("MAN STOP")); 
		return;
	}
	
	//MAN-PWR_1-ON
	if(gParametryPracy_RCV.gMessageCode == 20)
	{
		if(gStartMAN == true)
		 SetPowerON_1(255);
		return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 21)
	{
		if(gStartMAN == true)
		   SetPowerOFF_1();
		return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 22)
	{
		if(gStartMAN == true)
		   SetPowerON_2(255);
		  return;
	}
	
	
	if(gParametryPracy_RCV.gMessageCode == 23)
	{
		if(gStartMAN == true)
		  SetPowerOFF_2();
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 24)
	{
		if(gStartMAN == true)
		   SetPowerON_3();
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 25)
	{
		if(gStartMAN == true)
		   SetPowerOFF_3();
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 26)
	{
		if(gStartMAN == true)
		   SetValveON_M(ZaworWoda);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 27)
	{
		 if(gStartMAN == true)
		   SetValveOFF_M(ZaworWoda);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 28)
	{
		 if(gStartMAN == true)
		   SetValveON_M(ZaworGonu);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 29)
	{
		 if(gStartMAN == true)
		   SetValveOFF_M(ZaworGonu);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 30)
	{
		 if(gStartMAN == true)
		   SetValveON_M(ZaworGonu2);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 31)
	{
		if(gStartMAN == true)
		   SetValveOFF_M(ZaworGonu2);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 32)
	{
		if(gStartMAN == true)
		   SetValveON_M(ZaworPrzedGon);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 33)
	{
		if(gStartMAN == true)
		  SetValveOFF_M(ZaworPrzedGon);
		  return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 34)
	{
		Sound_Play(0x14,100,108);
		if(FTImpl.Read(REG_PWM_DUTY) == 0)
		{
		  FTImpl.Write(REG_PWM_DUTY,127);
		  Serial.println(F("DISPLAY ON"));
		  return;
	    }
	    
		if(FTImpl.Read(REG_PWM_DUTY) == 127)
		{
		  FTImpl.Write(REG_PWM_DUTY,0);
		  Serial.println(F("DISPLAY OFF"));
	    }
		
		return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 35)
	{
		Sound_Play(0x14,100,108);
		Serial.println(F("SAVE WIFI DATA TO EPROM"));
		memset(gParametryPracy.gSSID,0,sizeof(gParametryPracy.gSSID));
		memset(gParametryPracy.gPASS,0,sizeof(gParametryPracy.gPASS));
		memcpy(gParametryPracy.gSSID,gParametryPracy_RCV.gSSID,sizeof(gParametryPracy.gSSID));
		memcpy(gParametryPracy.gPASS,gParametryPracy_RCV.gPASS,sizeof(gParametryPracy.gPASS));
		gParametryPracy.gWIFI_MODE = gParametryPracy_RCV.gWIFI_MODE;
		SaveToEprom();
		return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 36)
	{
		if(gStartMAN == true)
		{
			Sound_Play(0x14,100,108);
			gParametryPracy.gMocMAN_G1 = gParametryPracy_RCV.gMocMAN_G1;
			if(gParametryPracy_RCV.gMocMAN_G1 > 0)
			{
			 SetPowerON_1(gParametryPracy.gMocMAN_G1);
		    }else
		    {
			 SetPowerOFF_1();	
			}
			Serial.println(F("SET G1 power: "));
			Serial.print(gParametryPracy_RCV.gMocMAN_G1);
		}
		  
	return;
	}
	
	if(gParametryPracy_RCV.gMessageCode == 37)
	{
		if(gStartMAN == true)
		{
			Sound_Play(0x14,100,108);
			gParametryPracy.gMocMAN_G2 = gParametryPracy_RCV.gMocMAN_G2;
			if(gParametryPracy_RCV.gMocMAN_G2 > 0)
			{
			 SetPowerON_2(gParametryPracy.gMocMAN_G2);
		    }else
		    {
			 SetPowerOFF_2();	
			}			
			Serial.println(F("SET G2 power: "));
			Serial.print(gParametryPracy_RCV.gMocMAN_G2);
		}
		  
	return;
	}
	
	
	
	
}

void Receive_Struct()
{
  if(ETin.receiveData())
  {
	//Serial.println(sizeof(gParametryPracy_RCV));  
	ProcessMessageCode();
  }
} 

//klawiatura numeryczna ekranowa
float InputNumber(String& stringol, char* opis, char* opis2,int maxinput,int input_textsize,int info_textsize)
{
      sTagXY sTagxy;
      int tagoption = 0;
      int32_t CurrTextIdx = 0;
      uint8_t colorr = 0;
      float number = 0;

      char CharBuffer[25] = "|\0";

      do
      {
	   gParametryPracy.gNR_Okna = 9;	  
		  
       //MAX input
       if(CurrTextIdx >= maxinput)
       {
         CurrTextIdx = 0;
		 CharBuffer[0] = '|';
		 CharBuffer[1] = '\0';
       }

      FTImpl.DLStart();
	  FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230, 15, info_textsize, 0, opis ); //opis
      FTImpl.Cmd_Text(230, 150, info_textsize, 0, opis2 ); //opis
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(255, 90, input_textsize, 0,  CharBuffer ); // text input

      if(gStartAUTO == true)
      {
		 colorr+=5;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(5720, 2967);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(290 ,175, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }

      FTImpl.GetTagXY(sTagxy);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);

      // dBnTagINPUT_1 press 1
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_1);
      if (sTagxy.tag == dBnTagINPUT_1)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(20, 20, 60, 55,  31,  tagoption,"1");

      // dBnTagINPUT_2 press 2
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_2);
      if (sTagxy.tag == dBnTagINPUT_2)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(90, 20, 60, 55,  31,  tagoption,"2");

      // dBnTagINPUT_3 press 3
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_3);
      if (sTagxy.tag == dBnTagINPUT_3)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160, 20, 60, 55,  31,  tagoption,"3");

      // dBnTagINPUT_4 press 4
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_4);
      if (sTagxy.tag == dBnTagINPUT_4)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(20, 85, 60, 55,  31,  tagoption,"4");

      // dBnTagINPUT_5 press 5
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_5);
      if (sTagxy.tag == dBnTagINPUT_5)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(90, 85, 60, 55,  31,  tagoption,"5");

      // dBnTagINPUT_6 press 6
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_6);
      if (sTagxy.tag == dBnTagINPUT_6)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160, 85, 60, 55,  31,  tagoption,"6");

      // dBnTagINPUT_7 press 7
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_7);
      if (sTagxy.tag == dBnTagINPUT_7)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(20, 150, 60, 55,  31,  tagoption,"7");

      // dBnTagINPUT_8 press 8
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_8);
      if (sTagxy.tag == dBnTagINPUT_8)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(90, 150, 60, 55,  31,  tagoption,"8");

      // dBnTagINPUT_9 press 9
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_9);
      if (sTagxy.tag == dBnTagINPUT_9)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160, 150, 60, 55,  31,  tagoption,"9");


      // dBnTagINPUT_0 press 0
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_0);
      if (sTagxy.tag == dBnTagINPUT_0)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(20, 215, 60, 40,  30,  tagoption,"0");


      // dBnTagINPUT_Kropka press .
      tagoption = 0;
      FTImpl.Tag(dBnTagINPUT_Kropka);
      if (sTagxy.tag == dBnTagINPUT_Kropka)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(100, 215, 80, 40,  31,  tagoption,".");


      // CLR
      tagoption = 0;
      FTImpl.Tag(88);
      if (sTagxy.tag == 88)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(210, 215, 70, 40,  24,  tagoption,"clr");


      // Jesli wykryto dBnTagConfigbExit EXIT to main menu
      tagoption = 0;
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Tag(dBnTagINPUT_Exit);
      if (sTagxy.tag == dBnTagINPUT_Exit)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);

      FTImpl.Cmd_Button(310, 205, 130, 60,  24,  tagoption,flashtext(91));

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();
      FTImpl.Finish();

	//Button 1
	if (sTagxy.tag == dBnTagINPUT_1)
	{
		CharBuffer[CurrTextIdx] = '1';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
		CurrTextIdx++;
		Sound_Play(0x14,100,108);
		delay(250);
    }
    //Button 2
	if (sTagxy.tag == dBnTagINPUT_2)
	{
		CharBuffer[CurrTextIdx] = '2';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
		CurrTextIdx++;
		Sound_Play(0x14,100,108);
		delay(250);
    }
    //Button 3
	if (sTagxy.tag == dBnTagINPUT_3)
	{
		CharBuffer[CurrTextIdx] = '3';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
		CurrTextIdx++;
		Sound_Play(0x14,100,108);
		delay(250);
    }
    //Button 4
	if (sTagxy.tag == dBnTagINPUT_4)
	{
		CharBuffer[CurrTextIdx] = '4';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
		CurrTextIdx++;
		Sound_Play(0x14,100,108);
		delay(250);
    }
    //Button 5
	if (sTagxy.tag == dBnTagINPUT_5)
	{
		CharBuffer[CurrTextIdx] = '5';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button 6
	if (sTagxy.tag == dBnTagINPUT_6)
	{
		CharBuffer[CurrTextIdx] = '6';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button 7
	if (sTagxy.tag == dBnTagINPUT_7)
	{
		CharBuffer[CurrTextIdx] = '7';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button 8
	if (sTagxy.tag == dBnTagINPUT_8)
	{
		CharBuffer[CurrTextIdx] = '8';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button 9
	if (sTagxy.tag == dBnTagINPUT_9)
	{
		CharBuffer[CurrTextIdx] = '9';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button 0
	if (sTagxy.tag == dBnTagINPUT_0)
	{
		CharBuffer[CurrTextIdx] = '0';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button dBnTagINPUT_Kropka .
	if (sTagxy.tag == dBnTagINPUT_Kropka)
	{
		CharBuffer[CurrTextIdx] = '.';
		CharBuffer[CurrTextIdx + 1] = '|';
        CharBuffer[CurrTextIdx + 2] = '\0';
        CurrTextIdx++;
		delay(250);
		Sound_Play(0x14,100,108);
    }
    //Button CLR
	if (sTagxy.tag == 88)
	{
		if(CurrTextIdx > 0)
		{
		 CharBuffer[CurrTextIdx - 1] = '|';
		 CharBuffer[CurrTextIdx] = '\0';
         CurrTextIdx--;
		 Sound_Play(0x14,100,108);
		 delay(250);
	 }
    }
    
    
    //manual
	if(gStartMAN == true)
	{
		 //gTimer.update_by_ID(gPwr1TimerEvent);
		 //gTimer.update_by_ID(gPwr2TimerEvent);
		 gTimer.update_by_ID(gTempSensorEvent);
		 gTimer.update_by_ID(gAwariaDSTempEvent);
		 //gTimer.update_by_ID(gSendTOEspEvent);
    }else
    {
		//gTimer.update_by_ID(gPwr1TimerEvent);
		//gTimer.update_by_ID(gPwr2TimerEvent);
		//Update timer gTempSensorEvent gCzasProcesuEvent gProcessEvent
		gTimer.update_by_ID(gTempSensorEvent);
		gTimer.update_by_ID(gCzasProcesuEvent);
		gTimer.update_by_ID(gProcessEvent);
		//gTimer.update_by_ID(gWykresTempEvent);
		gTimer.update_by_ID(gAwariaDSTempEvent);
		gTimer.update_by_ID(gSystemBackupEvent);
		//gTimer.update_by_ID(gSendTOEspEvent);
    }

    Receive_Struct();

  	//while if exit not press
    }while(sTagxy.tag != dBnTagINPUT_Exit);


    
    CharBuffer[CurrTextIdx]  = '\0';
    stringol = String(CharBuffer);
	number =  stringol.toFloat();

	delay(250);
	Sound_Play(0x1b,100,108);

   return number;
}

//INFO MODULE
void InfoScreen(int del,int s,int x,int y,const char* text)
{
	gParametryPracy.gNR_Okna = 8;
	
      FTImpl.DLStart();
      FTImpl.Cmd_BGColor(0xFF0000);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(x, y, s, 0, text);
	  FTImpl.DLEnd();
      FTImpl.Finish();
    delay(del);
}

void Brak_Chlodzenia_info_s(int s,int x,int y,const char* text)
{
	  sTagXY sTagxy;
	  bool exit = false;
	  unsigned int pykadlo = 0;

     do
     {
	
	  int tagoption = 0;
	  
	  gParametryPracy.gNR_Okna = 4;
	  	 
      FTImpl.DLStart();
      FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(x, y, s, 0, text);
      FTImpl.ColorRGB(0x00,0xFF,0x00);

      //temp Alarma
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      dtostrf(gParametryPracy.gTempAlarmu, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(240 ,14, 31,0, TempCharBuffer);
      FTImpl.Cmd_Text(50 ,20, 24,0, flashtext(104));

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempStopGrzania, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(240 ,62, 31,0, TempCharBuffer);
      FTImpl.Cmd_Text(50 ,70, 24,0, flashtext(105));
      
      
      FTImpl.GetTagXY(sTagxy);
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      if (sTagxy.tag == 12)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(12);
      FTImpl.Cmd_Button(395, 222, 70, 40,  24,  tagoption,flashtext(50));
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      if (sTagxy.tag == 13)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(13);
      FTImpl.Cmd_Button(250, 222, 110, 40,  24,  tagoption,"POMIN");
      
      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();

	  //Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
	  gTimer.update_by_ID(gTempSensorEvent);
	  gTimer.update_by_ID(gAwariaDSTempEvent);
	  //gTimer.update_by_ID(gSendTOEspEvent);


	  if(gParametryPracy.gTempAlarmu < gParametryPracy.gTempStopGrzania)
	  {
		exit = true;
	  }

      pykadlo++;

      //alarm sound
      if(pykadlo > 25)
      {
       Sound_Play(0x14,100,108);
       pykadlo = 0;
      }
      
      //OK EXIT
      if (sTagxy.tag == 12)
      {
	    exit = true;
	  }
	  
	  //ANULUJ
	  if (sTagxy.tag == 13)
      {
	   gBrak_Chlodzenia_anuluj = true;
	   exit = true;
	  }
      
       Receive_Struct();

    }while(exit == false);

	delay(400);
	Sound_Play(0x14,100,108);
}

//Brak_Chlodzenia TAK NIE screen
bool Brak_Chlodzenia_TakNie(int x, int y, int sizet, char* text)
{
      sTagXY sTagxy;
      bool result = false;

     do
     {
      int tagoption1 = 0;
      int tagoption2 = 0;
       
      FTImpl.DLStart();
      FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(x , y, sizet, 0, text);

      FTImpl.GetTagXY(sTagxy); // Pobieramy X,Y,TAG

      // Jesli wykryto tag TAK
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption1 = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
        tagoption2 = 0;
        result = true;
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH/2 - 120, 160, 90, 60,  24,  tagoption1,flashtext(46));


      // Jesli wykryto tag NIE
      if (sTagxy.tag == dBnTagNie)
      {
        tagoption2 = FT_OPT_FLAT;
        tagoption1 = 0;
        FTImpl.Cmd_FGColor(0xFF0000);
        result = false;
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagNie);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH/2 + 40, 160, 90, 60,  24,  tagoption2,flashtext(47));

      FTImpl.Cmd_Text(30 ,25, 22,0, flashtext(48));

      FTImpl.DLEnd();
      FTImpl.Finish();

    }while(sTagxy.tag != dBnTagNie && sTagxy.tag != dBnTagTak);

    delay(380);
    return result;
}

//Gdy zabraknie wody w kranie:)
//wyłączyć grzanie i podać info na ekranik
void Brak_ChlodzeniaWodyM()
{
	 //wył.grzanie
	 SetPowerOFF_1();
	 SetPowerOFF_2();
	 SetPowerOFF_3();
	 
	 SetValvesOFF();
	 
	 SetValveON(ZaworWoda);
	 
	 Serial.println(F("Brak chlodzenia MAN ON"));

	 Brak_Chlodzenia_info_s(30,130,140,"Brak chlodzenia wody!");

	 if(Brak_Chlodzenia_TakNie(60,60,30,"Czy wznowic proces ?") == true)
	 {
      SetValveON(ZaworWoda);// w razie czego otw... zaw wody
      SetPowerON_1(gParametryPracy.gMocMAN_G1);
      SetPowerON_2(gParametryPracy.gMocMAN_G2);
      //SetPowerON_3();
      Sound_Play(0x14,100,108);
	  InfoScreen(600,31,115,110,"Power START !");
	 }else
	 {
      Sound_Play(0x14,100,108);
	  InfoScreen(600,31,115,110,"Power STOP !");
	 }
}

//programowy zegarek ciekawe czy dokładny:)
void Akt_Czas_MAN()
{
    local_timer_manual.second++;

	if(local_timer_manual.second == 60)
	{
	 local_timer_manual.minute++;
	 local_timer_manual.second = 0;
	}

	if(local_timer_manual.minute == 60)
	{
	 local_timer_manual.hour++;
	 local_timer_manual.minute = 0;
	}

	if(local_timer_manual.hour > 144)
	{
		local_timer_manual.hour = 0; //jeśli przekorczy 144 zerujemy
		local_timer_manual.minute = 0;
		local_timer_manual.second = 0;
	}

    //brak chlodzenia wódy
    if(gParametryPracy.gTempAlarmu > gParametryPracy.gTempStopGrzania)
	{
	 Brak_ChlodzeniaWodyM();
	}
}

void AA_Manual()
{
	 Serial.println(F("MANUAL ON"));
	
	 ClearScreen(255, 255, 255);
     
     gStartMAN = true;
     //gStartAUTO = false;
     
     AwariaDS_number = 0;
     gBrak_DS_anuluj = false;
     
     	
     sTagXY sTagxy;
     int tagoption = 0;
     uint8_t colorr = 0;
     uint8_t colorr_napisu = 0;
     bool upp = true;

     Timer LocalTimer;
         
     //deklaracja timera ----> na funkcję Akt_Czas_MAN()
     int LocalTimerEventID = LocalTimer.every(1000, Akt_Czas_MAN); // 1 sekundos

     local_timer_manual.hour = 0;
     local_timer_manual.minute = 0;
     local_timer_manual.second = 0;
     
     
     switch( gParametryPracy.gEtap )
		  {
			 
			case 0://off
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
				break;
				  
			case 1://rozgrzewanie
				  gParametryPracy.gMocMAN_G1 = 100;
				  gParametryPracy.gMocMAN_G2 = 100;
				break;

			case 2://zalewanie
				if(gParametryPracy.gPrzerwaPoZalaniu == false)
				{
				 gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocZalaniaG1;
				 gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocZalaniaG2;
			    }else
			    {
		    	  gParametryPracy.gMocMAN_G1 = 0;
				  gParametryPracy.gMocMAN_G2 = 0;
				}
				break;


			case 3://stabilizacja
				 {
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocStabilizacjiG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocStabilizacjiG2;
			     }
				break;

			case 4://przedgon
				if(gParametryPracy.gStabPrzedgon == true)
				{
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;	
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			    }else
			    {
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocPrzedgonuG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocPrzedgonuG2;
				}
				break;

			case 5://gon
				if(gParametryPracy.gDrugaMocGonu == false)
				{
				 gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;
				 gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			    }else
			    {
			     gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonu2_G1;
			     gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonu2_G2;
				}
				break;
				
				case 6://pogon
				 if(gParametryPracy.gDrugaMocGonu == false)
				 {
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			     }else
			     {
			      gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonu2_G1;
			      gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonu2_G2;
				 }
				 break;
				 
				 case 7://chlodzenie
				  gParametryPracy.gMocMAN_G1 = 0;
				  gParametryPracy.gMocMAN_G2 = 0;
				break;
				
				case 8://koniec
				  gParametryPracy.gMocMAN_G1 = 0;
				  gParametryPracy.gMocMAN_G2 = 0;
				break;
			//default:
			//    FTImpl.Cmd_Text(270,130, 27,0, "ON");
			//	FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocZadanaG2 );
			//break;

			}//end switch
	   //}else
	   //{
		   //gParametryPracy.gMocZadanaG1 = 0;
		   //gParametryPracy.gMocZadanaG2 = 0;
	   //}

     do
     {
	  //gParametryPracy.gNR_Okna = 3;
	  gParametryPracy.gNR_Okna = 78;//MAN	 
		 
      FTImpl.DLStart();
      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.Cmd_BGColor(0x000000);
      FTImpl.Cmd_GradColor(0xffffff);

      if(gStartAUTO == true)
      {
		 colorr += 6;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysujemy kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(6100, 3900);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(310 ,233, 23,0, flashtext(49));//AUTO:
		 if(colorr >= 255)
		colorr = 0;
	  }
	  
	  if(upp == true)
      {
	   colorr_napisu += 5;
        if(colorr_napisu >= 255)
		 upp = false;
      }else
      {
		colorr_napisu -= 5;
        if(colorr_napisu <= 0)
		 upp = true;
	  }

      //opis temperatur:
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Text(15,190, 22,0,flashtext(0));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(120,190, 22,0,flashtext(1));
      FTImpl.ColorRGB(0xFF,0x88,0x00); 
      FTImpl.Cmd_Text(220,190, 22,0,flashtext(2));
      FTImpl.ColorRGB(0x00,0x00,0xFF);
      FTImpl.Cmd_Text(320,190, 22,0,flashtext(3));
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(410,190, 22,0,"Bufor:");


      //Display temperatures
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      dtostrf(gParametryPracy.gTempKolumna, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(0 ,160, 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempBeczka, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(100 ,160 , 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0xFF,0x88,0x00);
      dtostrf(gParametryPracy.gTempGlowica, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(205 ,160, 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0x00,0x00,0xFF);
      dtostrf(gParametryPracy.gTempWodaWy, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(300 ,160, 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      dtostrf(gParametryPracy.gTempBufor, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(390 ,160, 28,0, TempCharBuffer);

      //current job time
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(5,230, 29,0, flashtext(5));
      FTImpl.Cmd_Number(95, 230, 29, 0, local_timer_manual.hour );
      FTImpl.Cmd_Text(120, 230, 29, 0, flashtext(86) );
      FTImpl.Cmd_Number(130, 230, 29, 0, local_timer_manual.minute );
      FTImpl.Cmd_Text(160, 230, 29, 0, flashtext(86) );
      FTImpl.Cmd_Number(175, 230, 29, 0, local_timer_manual.second );
      
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
     // FTImpl.Cmd_Text(230, 225, 30, 0, "MANUAL" );

      FTImpl.GetTagXY(sTagxy);

      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagManZawWoda
      tagoption = 0;
      FTImpl.Tag(dBnTagManZawWoda);
      if (sTagxy.tag == dBnTagManZawWoda)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
        if(gParametryPracy.gZaworWoda == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
      }
      FTImpl.Cmd_Button(10, 5, 70, 65,  24,  tagoption,"Woda");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      
      if(digitalRead(ZaworWoda) == LOW)
      {
        //if(gParametryPracy.gZaworWoda == true)
		FTImpl.Cmd_Text(30,45, 28,0, flashtext(7));
	  }else
	  {
	    FTImpl.Cmd_Text(25,45, 28,0, flashtext(8));
	  }



      // Jesli wykryto dBnTagManZawGon
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagManZawGon);
      if (sTagxy.tag == dBnTagManZawGon)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
        if(gParametryPracy.gZaworGonu == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
      }
      FTImpl.Cmd_Button(100, 5, 120, 65,  24,  tagoption,"Gon-1");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      
      if(digitalRead(ZaworGonu) == LOW)
      {
       
		FTImpl.Cmd_Text(130,45, 28,0, flashtext(7));
	  }else
	  {
	    FTImpl.Cmd_Text(125,45, 28,0, flashtext(8));
	  }
      
      
    
      //Jesli wykryto dBnTagManZawPrzedG
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagManZawPrzedG  );
      if (sTagxy.tag == dBnTagManZawPrzedG )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
        if(gParametryPracy.gZaworPrzedGon == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
      }
      FTImpl.Cmd_Button(240 , 5, 120, 65,  24,  tagoption,"PrzedG");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      
      if(digitalRead(ZaworPrzedGon) == LOW)
      {
       
		FTImpl.Cmd_Text(265,45, 28,0, flashtext(7));
	  }else
	  {
	    FTImpl.Cmd_Text(260,45, 28,0, flashtext(8));
	  }
      
   
	  //Grzałka 1
	   // Jesli wykryto dBnTagManG1
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagManG1  );
      if (sTagxy.tag == dBnTagManG1 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
		if(gParametryPracy.gPowerPWR1 == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
      }
      FTImpl.Cmd_Button(380 , 5, 60, 65,  24,  tagoption,flashtext(15));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      if(gParametryPracy.gPowerPWR1 == true)
			FTImpl.Cmd_Text(390,45, 28,0, flashtext(7));
			else FTImpl.Cmd_Text(390,45, 28,0, flashtext(8));


      //Grzałka 2
	  // Jesli wykryto dBnTagManG2
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagManG2  );
      if (sTagxy.tag == dBnTagManG2 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
        if(gParametryPracy.gPowerPWR2 == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
	  }
      FTImpl.Cmd_Button(290 , 80, 60, 65,  24,  tagoption,flashtext(16));
	  FTImpl.ColorRGB(0x00,0xFF,0x00);
	  if(gParametryPracy.gPowerPWR2 == true)
			FTImpl.Cmd_Text(300,120, 28,0, flashtext(7));
			else FTImpl.Cmd_Text(300,120, 28,0, flashtext(8));
			
			
			
	  //Grzałka 3
	  // Jesli wykryto dBnTagManG2
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(178);
      if (sTagxy.tag == 178 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
        if(gParametryPracy.gPowerPWR3 == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
	  }
      FTImpl.Cmd_Button(380 , 80, 60, 65,  24,  tagoption,flashtext(17));
	  FTImpl.ColorRGB(0x00,0xFF,0x00);
	  if(gParametryPracy.gPowerPWR3 == true)
			FTImpl.Cmd_Text(390,120, 28,0, flashtext(7));
			else FTImpl.Cmd_Text(390,120, 28,0, flashtext(8));		


	  //Moc G1:
	  FTImpl.ColorRGB(0xFF,0x00,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigPowerB1);
      if (sTagxy.tag == dBnTagConfigPowerB1)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 80, 70, 65,  24,  tagoption,"Moc1:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(15, 120,23, 0, gParametryPracy.gMocMAN_G1 );
      FTImpl.Cmd_Text(55 ,120, 23,0, "%");


      //Moc G2:
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigPowerB2);
      if (sTagxy.tag == dBnTagConfigPowerB2)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(100, 80, 70, 65,  24,  tagoption,"Moc2:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(110, 120,23, 0, gParametryPracy.gMocMAN_G2 );
      FTImpl.Cmd_Text(145 ,120, 23,0, "%");


      //ZaworGonu2
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(177);
      if (sTagxy.tag == 177)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else
      {
        if(gParametryPracy.gZaworGonu2 == true)
		{  
         long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	    }else
	    {
		 FTImpl.Cmd_FGColor(0x000088);
		}
      }
      FTImpl.Cmd_Button(190, 80, 70, 65,  24,  tagoption,"Gon2:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      
      if(digitalRead(ZaworGonu2) == LOW)
      {
       
		FTImpl.Cmd_Text(215,120, 28,0, flashtext(7));
	  }else
	  {
	    FTImpl.Cmd_Text(210,120, 28,0, flashtext(8));
	  }
      
      
      
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);


	  //przycisk exit info
      if (sTagxy.tag == dBnTagInfobExit)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  FTImpl.Cmd_FGColor(0x000088);
		   tagoption = 0;
	  }
      FTImpl.Tag(dBnTagInfobExit);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH - 80, FT_DISPLAYHEIGHT- 50, 70, 40,  24,  tagoption,flashtext(52));

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();
      FTImpl.Finish();


      //ZawWoda
	  if (sTagxy.tag == dBnTagManZawWoda)
	  {
		 if(digitalRead(ZaworWoda) == LOW)
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveOFF_M(ZaworWoda);
		 }else
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveON_M(ZaworWoda);
		 }
	  }


	  //ZawPrzedG
	  if (sTagxy.tag == dBnTagManZawPrzedG)
	  {
		 if(digitalRead(ZaworPrzedGon) == LOW)
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveOFF_M(ZaworPrzedGon);
		 }else
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveON_M(ZaworPrzedGon);
		 }
	  }


	  //ZawGon I
	  if (sTagxy.tag == dBnTagManZawGon)
	  {
		 if(digitalRead(ZaworGonu) == LOW)
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveOFF_M(ZaworGonu);
		 }else
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveON_M(ZaworGonu);
		 }
	  }


	  //ZaworGonu2  II
	  if (sTagxy.tag == 177)
	  {
		  
		 //if(gParametryPracy.gZaworGonu2 == false)
		 if(digitalRead(ZaworGonu2) == LOW)
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveOFF_M(ZaworGonu2);
		 }else
		 {
		  delay(300);
		  Sound_Play(0x14,100,108);
		  SetValveON_M(ZaworGonu2);
		 }
	  }


	    //G1
		if (sTagxy.tag == dBnTagManG1)
		{
			if(gParametryPracy.gPowerPWR1 == false)
			{
			  delay(300);
			  Sound_Play(0x14,100,108);
			  SetPowerON_1(gParametryPracy.gMocMAN_G1);
     		}
			else
			{
			   delay(300);
			   Sound_Play(0x14,100,108);
			   SetPowerOFF_1();
		    }
		}

		//G2
		if (sTagxy.tag == dBnTagManG2)
		{
	        if(gParametryPracy.gPowerPWR2 == false)
	        {
			   delay(300);
			   Sound_Play(0x14,100,108);
			   SetPowerON_2(gParametryPracy.gMocMAN_G2);
			}
			else
			{
			   delay(300);
			   Sound_Play(0x14,100,108);
			   SetPowerOFF_2();
			}
		}
		
		//G3
		if (sTagxy.tag == 178)
		{
	        if(gParametryPracy.gPowerPWR3 == false)
	        {
			   delay(300);
			   Sound_Play(0x14,100,108);
			   SetPowerON_3();
			}
			else
			{
			   delay(300);
			   Sound_Play(0x14,100,108);
			   SetPowerOFF_3();
			}
		}

	    //Button PWR1
		if (sTagxy.tag == dBnTagConfigPowerB1)
		{
			 delay(300);
			 Sound_Play(0x14,100,108);
			 String stringol;
			 int number = InputNumber(stringol,"Moc grzania G1: 0-100%","",7,31,27);
			 if(number > 100)
			  number = 100;
			 if(number <= 0)
			  number = 0;
			 gParametryPracy.gMocMAN_G1 = number;
			 SetPowerON_1(gParametryPracy.gMocMAN_G1);
		}

		//Button PWR2
		if (sTagxy.tag == dBnTagConfigPowerB2)
		{
			 delay(300);
			 Sound_Play(0x14,100,108);
			 String stringol;
			 int number = InputNumber(stringol,"Moc grzania G2: 0-100%","",7,31,27);
			 if(number > 100)
			  number = 100;
			 if(number <= 0)
			  number = 0;
			 gParametryPracy.gMocMAN_G2 = number;
			 SetPowerON_2(gParametryPracy.gMocMAN_G2);
		}

    //gTimer.update_by_ID(gPwr1TimerEvent);
    //gTimer.update_by_ID(gPwr2TimerEvent); 
	gTimer.update_by_ID(gTempSensorEvent);
	gTimer.update_by_ID(gAwariaDSTempEvent);
	LocalTimer.update_by_ID(LocalTimerEventID);
    
    Receive_Struct();

    }while(sTagxy.tag != dBnTagInfobExit && gStartMAN == true);

    gStartMAN = false;
       
    if(gStartAUTO == true)
    {
       //Auto_wznowienie();
       Restart_from_WMan();
       Serial.println(F("Auto wznowienie z manualu"));
    }else
    {
	   SetValveOFF(ZaworPrzedGon);
	   SetValveOFF(ZaworGonu);
	   SetValveOFF(ZaworGonu2);
	   SetValveOFF(ZaworWoda);
	   //wył.. grzanie
	   SetPowerOFF_1();
	   SetPowerOFF_2();
	   SetPowerOFF_3();
	   //Serial.println(F("2"));
	}
    
    Serial.println(F("MANUAL OFF"));
    
    delay(350);
    Sound_Play(0x14,100,108);
}

//Read from eprom mem
void eepromRead(uint16_t addr, void* output, uint16_t length)
{
    uint8_t* src;
    uint8_t* dst;
    src = (uint8_t*)addr;
    dst = (uint8_t*)output;
    for (uint16_t i = 0; i < length; i++)
    {
        *dst++ = eeprom_read_byte(src++);
    }
}

void SaveToEprom()
{
     int counter = 0;
     uint8_t* src;
     uint8_t* dst;
     src = (uint8_t*)&gParametryPracy;
     dst = (uint8_t*)0;
     do
      {
		gParametryPracy.gNR_Okna = 23;  
        FTImpl.DLStart();
        FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x008800);
        FTImpl.ColorRGB(0xFF,0xFF,0x00);
        FTImpl.Cmd_Progress(55, 135, 360, 30, 0, counter ,sizeof(gParametryPracy));
        FTImpl.Cmd_Number(FT_DISPLAYWIDTH/2 - 20, 70, 30, 0,counter );
        FTImpl.Cmd_Text(170, 180, 21, 0, flashtext(172));
        FTImpl.DLEnd();
        FTImpl.Finish();
	    eeprom_write_byte(dst++, *src++);
        counter++;
        Sound_Play(random(0,255),245,random(0,255));
     }while(counter < sizeof(gParametryPracy));
      //eepromWrite(0, &gParametryPracy, sizeof(gParametryPracy));
      //EEPROM_writeAnything(0, gParametryPracy);
      Sound_Play(0x14,100,108);
}

//Wyłączenie AUTOMAT----->
void AAc_dis_AUTO()
{
	  //wył.grzałek i zaworków
	  SetPowerOFF_1();
	  SetPowerOFF_2();
	  SetPowerOFF_3();
	  SetValvesOFF();

       gParametryPracy.gCzasProcesuMin     = 0;
	   gParametryPracy.gCzasProcesuGodz    = 0;
	   gParametryPracy.gCzasProcesuSek     = 0;
	   gParametryPracy.gLocal_timer.second = 0;
	   gParametryPracy.gLocal_timer.minute = 0;
	   gParametryPracy.gLocal_timer.hour   = 0;
	   gParametryPracy.gTempDnia           = 0;

	   gParametryPracy.gCzyZalano           = false;
	   gParametryPracy.gPoziomZalania 		= 0;
	   gParametryPracy.gPrzerwaPoZalaniu 	= false;
	   gParametryPracy.gStabPrzedgon 		= false;
	   gParametryPracy.gDrugaMocGonu 		= false;
	   gParametryPracy.gPotwOdbGonu 		= false;
	   gParametryPracy.gZaworGonu2_ON 		= false;
	   gParametryPracy.gKoniec              = false;
	   gParametryPracy.gCzasRozgrzewania    = 0;
	   gParametryPracy.gCzasZalewania       = 0;
	   gParametryPracy.gCzasZalania         = 0;
	   gParametryPracy.gCzasStabilizacji    = 0;
	   gParametryPracy.gCzasPrzedgonu       = 0;
	   gParametryPracy.gCzasGonu            = 0;
	   gParametryPracy.gCzasPogonu       	= 0;
	   gParametryPracy.gCzasChlodzenia      = 0;
	   gParametryPracy.gCzasProcesuTotalMin = 0;
	   gParametryPracy.gCzasProcesuTotalSek = 0;
	   gParametryPracy.gZaworGonCntr  = 0;
	   gParametryPracy.gZaworGon2Cntr = 0;
	   gParametryPracy.gStart_etapu   = 0;
       gStart_zalania            = 0;
       gParametryPracy.gZalanieX = 0;
       gParametryPracy.gEtap     = 0;
       gStart_zalania            = 0;


	  Sound_Play(0x14,100,108);
	  InfoScreen(600,31,115,110,"Power STOP !");
	  
	  Serial.println(F("AUTO OFF"));
	  
	  gParametryPracy.gSTATUS  = 0; //OFF
	  gParametryPracy.gNR_Okna = 0;

	  gStartAUTO = false;
}

//uruchamia się tylko raz
//podczas startu automatu i załącza oraz
//zeruje wszystko co trzeba
void AAc_0Asetup()
{
	   SD.remove("log.txt");
	
	   gParametryPracy.gStartAutoDateTime.hour   = gParametryPracy.CurrentDateTime.hour;
	   gParametryPracy.gStartAutoDateTime.minute = gParametryPracy.CurrentDateTime.minute;
	   gParametryPracy.gStartAutoDateTime.second = gParametryPracy.CurrentDateTime.second;
	   gParametryPracy.gStartAutoDateTime.year   = gParametryPracy.CurrentDateTime.year;
	   gParametryPracy.gStartAutoDateTime.month  = gParametryPracy.CurrentDateTime.month;
	   gParametryPracy.gStartAutoDateTime.day    = gParametryPracy.CurrentDateTime.day;

	   gParametryPracy.gCzasProcesuMin   = 0;
	   gParametryPracy.gCzasProcesuGodz  = 0;
	   gParametryPracy.gCzasProcesuSek   = 0;

	   gParametryPracy.gLocal_timer.second = 0;
	   gParametryPracy.gLocal_timer.minute = 0;
	   gParametryPracy.gLocal_timer.hour   = 0;

	   gParametryPracy.gTempDnia = 0;

	   gStartAUTO = true;

       gParametryPracy.gCzyZalano           = false;
	   gParametryPracy.gPoziomZalania 		= 0;
	   gParametryPracy.gPrzerwaPoZalaniu 	= false;
	   gParametryPracy.gStabPrzedgon 		= false;
	   gParametryPracy.gDrugaMocGonu 		= false;
	   gParametryPracy.gPotwOdbGonu 		= false;
	   gParametryPracy.gZaworGonu2_ON 		= false;
	   
	   gParametryPracy.gKoniec = false;

	   gParametryPracy.gCzasRozgrzewania    = 0;
	   gParametryPracy.gCzasZalewania       = 0;
	   gParametryPracy.gCzasZalania         = 0;
	   gParametryPracy.gCzasStabilizacji    = 0;
	   gParametryPracy.gCzasPrzedgonu       = 0;
	   gParametryPracy.gCzasGonu            = 0;
	   gParametryPracy.gCzasPogonu       	= 0;

	   gParametryPracy.gCzasProcesuTotalMin    = 0;
	   gParametryPracy.gCzasProcesuTotalSek    = 0;

	   gParametryPracy.gZaworGonCntr  = 0;
	   gParametryPracy.gZaworGon2Cntr = 0;
	   
	  // if(gParametryPracy.gZalanieZadaneX > 0)
	  // {
		 gParametryPracy.gZalanieX = 0;
	  // }

       gBrak_DS_anuluj         = false;
       gBrak_Chlodzenia_anuluj = false; 
       
       gStart_zalania          = 0;
       
       gParametryPracy.gSTATUS = 1;// Auto ON

	   //podczas startu upewniamy sie czy zawory są w stanie zamknięty
	   //Valves CLOSE
	   SetValvesOFF();

	   //Obie CZY 3 Grzoły na maximum
       //g1 g2 g3
       SetPowerON_1(100);
	   SetPowerON_2(100);
	   SetPowerON_3(); //trzecia tylko do szybszego rozgrzewania i zalewania

       //start rozgrzewania
       gParametryPracy.gStart_etapu = 0;
       
       bPotwODBGonu = false;

	   gParametryPracy.gEtap = 1; //włączam etap I czyli rozgrzewanie nastawu
	   
	   gParametryPracy.gNR_Okna = 0; //zero actions
	   
	   gParametryPracy.g2560ToESP_order = 0;
	   
	   AwariaDS_number = 0;
	   
	   	   
       Serial.println(F("Rozgrzewanie ON"));
       
       if(gParametryPracy.gSYS_LOG == true) DataLog("Grzanie ON"); 	   
	   
}

void AutoStartProgress()
{
      unsigned int bazyl = 0;
      int Xpos = -150;
      do
     {
		  gParametryPracy.gNR_Okna = 22;
		  
		  FTImpl.DLStart();
		  FTImpl.Cmd_BGColor(0xFF0000);
		  FTImpl.ColorRGB(0xFF,0xFF,0xFF);
		  if(Xpos < 80)
		  {
		   FTImpl.Cmd_Text(Xpos ,40, 31,0, flashtext(44)); //80
	      }else
	      {
		   FTImpl.Cmd_Text(80 ,40, 31,0, flashtext(44)); //80	  
		  }
		  Xpos+=12;
		  FTImpl.ColorRGB(0xFF,0xFF,0x00);
		  FTImpl.Cmd_Text(95 ,195, 24,0, flashtext(45));
		  FTImpl.ColorRGB(0xFF,0xFF,0x00);
		  FTImpl.Cmd_Progress(55, 145, 360, 40, 0, bazyl ,100);
		  FTImpl.ColorRGB(0x00,0xFF,0x00);
		  FTImpl.Cmd_Number(FT_DISPLAYWIDTH/2 - 30, 110, 25, 0,bazyl );
		  FTImpl.DLEnd();
		  FTImpl.Finish();
		  bazyl++;
		   Sound_Play(random(0,255),245,random(0,255));
		  delay(10);
		  gTimer.update_by_ID(gTempSensorEvent);//update temperature
	  }while(bazyl < 100);
	  Sound_Play(0x14,50,108);
}

void Calibrate()//kalibracja ekranu
{
  FTImpl.DLStart();
     FTImpl.ClearColorRGB(64,64,64);
       FTImpl.Clear(1,1,1);
        FTImpl.ColorRGB(0xff, 0xff, 0xff);
       FTImpl.Cmd_Text((FT_DISPLAYWIDTH/2), (FT_DISPLAYHEIGHT/2), 27, FT_OPT_CENTER, flashtext(51)); //display string at the center of the screen using inbuilt font handle 29
     FTImpl.Cmd_Calibrate(0);
  FTImpl.Finish();
  
  for (int i = 0; i < 24; i++)
  {
	  EEPROM.write(EEPROM_CALIBRATION_DATA_START + i, FTImpl.Read(REG_TOUCH_TRANSFORM_A + i));
  }
  EEPROM.write(EEPROM_CALIBRATION_DATA_START, 0x7c);
   
}
 
//klawiatura textowa ekranowa
void InputText(String& stringol, char* opis,int maxinput,int textsize)
{

      sTagXY sTagxy;
      int tagoption = 0;
      int32_t CurrTextIdx = 0;
      uint8_t colorr = 0;
      char CharBuffer[30] = "|\0";
      //String Alfa_becik =  "qwertyuiopasdfghjklzxcvbnm1234567890*-";
      //String Alfa_becikB = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890*-";
      bool D_litery = false;
      String Alfa_becik =  flashtext(139);
      String Alfa_becikB = flashtext(140);

     do
     {

      gParametryPracy.gNR_Okna = 10;

      //MAX input--->
      if(CurrTextIdx >= maxinput)
      {
         CurrTextIdx = 0;
		 CharBuffer[0] = '|';
		 CharBuffer[1] = '\0';
      }

      FTImpl.DLStart();
      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(180, 5, 29, 0, opis );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);

      //wyświetlamy buforek
      FTImpl.Cmd_Text(20, 40, textsize, 0,  CharBuffer );

      if(gStartAUTO == true)
      {
		 colorr+=25;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(5600, 4100);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(270 ,244, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }


      FTImpl.GetTagXY(sTagxy);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);



    if(D_litery == false)
    {
      //rysowanie na ekranie klawiatury ekranowy z buttonów
      int x = 20;
      int y = 110;
      for(unsigned int cntr = 0;cntr < Alfa_becik.length() ;cntr++ )
      {
 		  tagoption = 0;
		  FTImpl.Tag(cntr + 1);
		  if (sTagxy.tag == cntr + 1)
		  {
			tagoption = FT_OPT_FLAT;
			FTImpl.Cmd_FGColor(0xFF0000);
		  } else  FTImpl.Cmd_FGColor(0x000088);
		  String lytera(Alfa_becik[cntr]);
		  FTImpl.Cmd_Button(x, y, 30, 30,  23,  tagoption, lytera.c_str());

		  x += 35;
		  if(cntr == 9)
		  {
			  x = 20;
			  y+= 37;
		  }
		  if(cntr == 19)
		  {
			  x = 20;
			  y+= 37;
		  }
		  if(cntr == 29)
		  {
			  x = 20;
			  y+= 37;
		  }
		  if(cntr == 39)
		  {
			  x = 20;
			  y+= 37;
		  }
      }
  }else
  {
	  
	  //rysowanie na ekranie klawiatury ekranowy z buttonów
      int x = 20;
      int y = 110;
      for(unsigned int cntr = 0;cntr < Alfa_becikB.length() ;cntr++ )
      {
 		  tagoption = 0;
		  FTImpl.Tag(cntr + 1);
		  if (sTagxy.tag == cntr + 1)
		  {
			tagoption = FT_OPT_FLAT;
			FTImpl.Cmd_FGColor(0xFF0000);
		  } else  FTImpl.Cmd_FGColor(0x000088);
		  String lytera(Alfa_becikB[cntr]);
		  FTImpl.Cmd_Button(x, y, 30, 30,  23,  tagoption, lytera.c_str());

		  x += 35;
		  if(cntr == 9)
		  {
			  x = 20;
			  y+= 37;
		  }
		  if(cntr == 19)
		  {
			  x = 20;
			  y+= 37;
		  }
		  if(cntr == 29)
		  {
			  x = 20;
			  y+= 37;
		  }
		  if(cntr == 39)
		  {
			  x = 20;
			  y+= 37;
		  }
      }
	  
	  
  }


      // Jesli wykryto dBnTagConfigbExit EXIT to main menu
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Tag(77);
      if (sTagxy.tag == 77)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(420, 220, 50, 40,  23,  tagoption,flashtext(50));


      //Przycisk CLR do kasowania textu
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Tag(78);
      if (sTagxy.tag == 78)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(390, 110, 60, 40,  23,  tagoption,"clr");
      
      
      //Przycisk duze lytery
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Tag(79);
      if (sTagxy.tag == 79)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(390, 160, 60, 40,  24,  tagoption,"D");

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();
      FTImpl.Finish();

      
    if(D_litery == false)
    {
      //czy nacisnoł jakiś button na klawiaturce ekranowy
      //jeśli tak to tę literę wpisujemy do buforka
      for(unsigned int liczor = 0;liczor < Alfa_becik.length();liczor++)
       {
		if(sTagxy.tag ==  liczor + 1)
        {
			CharBuffer[CurrTextIdx] = Alfa_becik[liczor];
		    CharBuffer[CurrTextIdx + 1] = '|';
            CharBuffer[CurrTextIdx + 2] = '\0';
		    CurrTextIdx++;
			delay(200);
			Sound_Play(0x14,100,108);
	    }
       }
   }else
   {
	   //czy nacisnoł jakiś button na klawiaturce ekranowy
      //jeśli tak to tę literę wpisujemy do buforka
      for(unsigned int liczor = 0;liczor < Alfa_becikB.length();liczor++)
       {
		if(sTagxy.tag ==  liczor + 1)
        {
			CharBuffer[CurrTextIdx] = Alfa_becikB[liczor];
		    CharBuffer[CurrTextIdx + 1] = '|';
            CharBuffer[CurrTextIdx + 2] = '\0';
		    CurrTextIdx++;
			delay(200);
			Sound_Play(0x14,100,108);
	    }
       }
	   
   }

    //Button CLR
	if (sTagxy.tag == 78)
	{
		if(CurrTextIdx > 0)
		{
		 CharBuffer[CurrTextIdx - 1] = '|';
		 CharBuffer[CurrTextIdx] = '\0';
         CurrTextIdx--;
		 Sound_Play(0x14,100,108);
		 delay(250);
	    }
	 }
	if (sTagxy.tag == 79)
	{
		 if(D_litery == true)
		 {
			 D_litery = false;
		 }else
		 {
			 D_litery = true;
		 } 
		 Sound_Play(0x14,100,108);
		 delay(250);
	 }
	 
    
    //manual
	if(gStartMAN == true)
	{   
		 //gTimer.update_by_ID(gPwr1TimerEvent);
		 //gTimer.update_by_ID(gPwr2TimerEvent);
		 gTimer.update_by_ID(gTempSensorEvent);
		 gTimer.update_by_ID(gAwariaDSTempEvent);
		 //gTimer.update_by_ID(gSendTOEspEvent);
    }else
    {
		//Update timer gTempSensorEvent gCzasProcesuEvent gProcessEvent
		//gTimer.update_by_ID(gPwr1TimerEvent);
		//gTimer.update_by_ID(gPwr2TimerEvent);
		gTimer.update_by_ID(gTempSensorEvent);
		gTimer.update_by_ID(gCzasProcesuEvent);
		gTimer.update_by_ID(gProcessEvent);
	    //gTimer.update_by_ID(gWykresTempEvent);
		gTimer.update_by_ID(gAwariaDSTempEvent);
		gTimer.update_by_ID(gSystemBackupEvent);
		//gTimer.update_by_ID(gSendTOEspEvent);
    }

    Receive_Struct();

  	//while if exit not press
    }while(sTagxy.tag != 77);


    CharBuffer[CurrTextIdx]  = '\0';
    stringol = String(CharBuffer);

	delay(250);
	Sound_Play(0x1b,100,108);

   return;
}

//TAK NIE screen
bool TakNie(int x, int y, int sizet, const char* text)
{

      sTagXY sTagxy;
      bool result = false;

     do
     {
      int tagoption1 = 0;
      int tagoption2 = 0;
      
      gParametryPracy.gNR_Okna = 18;

      FTImpl.DLStart();
      FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(x , y, sizet, 0, text);


      FTImpl.GetTagXY(sTagxy); // Pobieramy X,Y,TAG

      // Jesli wykryto tag TAK
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption1 = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
        tagoption2 = 0;
        result = true;
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH/2 - 120, FT_DISPLAYHEIGHT/2, 90, 60,  24,  tagoption1,flashtext(46));


      // Jesli wykryto tag NIE
      if (sTagxy.tag == dBnTagNie)
      {
        tagoption2 = FT_OPT_FLAT;
        tagoption1 = 0;
        FTImpl.Cmd_FGColor(0xFF0000);
        result = false;
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagNie);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH/2 + 40, FT_DISPLAYHEIGHT/2, 90, 60,  24,  tagoption2,flashtext(47));

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();

    //Update timer gTempSensorEvent gCzasProcesuEvent gProcessEvent
    //gTimer.update_by_ID(gPwr1TimerEvent);
    //gTimer.update_by_ID(gPwr2TimerEvent);
	gTimer.update_by_ID(gTempSensorEvent);
	gTimer.update_by_ID(gCzasProcesuEvent);
	gTimer.update_by_ID(gProcessEvent);
    //gTimer.update_by_ID(gWykresTempEvent);
	gTimer.update_by_ID(gAwariaDSTempEvent);
	gTimer.update_by_ID(gSystemBackupEvent);
	//gTimer.update_by_ID(gSendTOEspEvent);

    }while(sTagxy.tag != dBnTagNie && sTagxy.tag != dBnTagTak);

    delay(380);
    Sound_Play(0x14,100,108);

    return result;
}

void ErrorScreen()
{
	gParametryPracy.gNR_Okna = 6;
      FTImpl.DLStart();
      FTImpl.Cmd_BGColor(0xFF0000);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.ClearColorRGB(255,0,0);
	  FTImpl.Clear(1,1,1);
      FTImpl.Cmd_Text(150, 100, 31, 0, flashtext(58));
	  FTImpl.DLEnd();
      FTImpl.Finish();
    delay(200);
}

//ekran informacyjny o brak udczytu z czujnika temp
void Brak_DS_info_screen()
{
	 sTagXY sTagxy;
	 unsigned int pykadlo = 0;
	 
	 Serial.println(F("Brak DS...info.."));

     do
     {
      int tagoption = 0;
      
      gParametryPracy.gNR_Okna = 5;

      FTImpl.DLStart();

      if(pykadlo > 30)
	  {
	   FTImpl.ClearColorRGB(255,255,255);
       FTImpl.Clear(1,1,1);

      }else
      {
       FTImpl.ClearColorRGB(0,35,50);
       FTImpl.Clear(1,1,1);
      }

      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Text(60 , 10, 25, 0, flashtext(59));
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(45 , 60, 25, 0, flashtext(60));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Text(100 , 120, 29, 0, flashtext(61));


      if (gParametryPracy.gTempKolumna   == -127.00)
      {
		FTImpl.ColorRGB(0x00,0xFF,0x00);
        FTImpl.Cmd_Text(10,160, 23,0,    flashtext(62));
        FTImpl.ColorRGB(0xFF,0x00,0x00);
        dtostrf(gParametryPracy.gTempKolumna, 6, 2, TempCharBuffer);
        FTImpl.Cmd_Text(10 ,195 , 23,0, TempCharBuffer);
	  }
	  if (gParametryPracy.gTempBeczka   == -127.00)
      {
		FTImpl.ColorRGB(0x00,0xFF,0x00);
        FTImpl.Cmd_Text(100,160, 23,0,  flashtext(63));
        FTImpl.ColorRGB(0xFF,0x00,0x00);
        dtostrf(gParametryPracy.gTempBeczka, 6, 2, TempCharBuffer);
        FTImpl.Cmd_Text(100 ,195 , 23,0, TempCharBuffer);
	  }
	  if (gParametryPracy.gTempGlowica   == -127.00)
      {
		FTImpl.ColorRGB(0x00,0xFF,0x00);
        FTImpl.Cmd_Text(200,160, 23,0,  flashtext(64));
        FTImpl.ColorRGB(0xFF,0x00,0x00);
        dtostrf(gParametryPracy.gTempGlowica, 6, 2, TempCharBuffer);
        FTImpl.Cmd_Text(200 ,195 , 23,0, TempCharBuffer);
	  }
	  if (gParametryPracy.gTempWodaWy   == -127.00)
      {
		FTImpl.ColorRGB(0x00,0xFF,0x00);
        FTImpl.Cmd_Text(307,160, 23,0,  flashtext(65));
        FTImpl.ColorRGB(0xFF,0x00,0x00);
        dtostrf(gParametryPracy.gTempWodaWy, 6, 2, TempCharBuffer);
        FTImpl.Cmd_Text(307 ,195 , 23,0, TempCharBuffer);
	  }
	  if (gParametryPracy.gTempAlarmu   == -127.00)
      {
		FTImpl.ColorRGB(0x00,0xFF,0x00);
        FTImpl.Cmd_Text(400,160, 23,0,  flashtext(66));
        FTImpl.ColorRGB(0xFF,0x00,0x00);
        dtostrf(gParametryPracy.gTempAlarmu, 6, 2, TempCharBuffer);
        FTImpl.Cmd_Text(400 ,195 , 23,0, TempCharBuffer);
	  }


      FTImpl.GetTagXY(sTagxy);

	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.Cmd_Button(395, 222, 70, 40,  24,  tagoption,flashtext(50));
      
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      if (sTagxy.tag == 12)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(12);
      FTImpl.Cmd_Button(250, 222, 110, 40,  24,  tagoption,flashtext(67));
      
      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();


	  //alarm sound
	  if(pykadlo > 40)
	  {
	   Sound_Play(0x14,255,108);
	   pykadlo = 0;
	  }
      pykadlo++;
      
      //BUTTON ANULUJ
      if(sTagxy.tag == 12)
      {
		 delay(300); 
		 Sound_Play(0x14,255,108); 
		 gBrak_DS_anuluj = true;
		 break;
	  }
	  
	  //gdyby zadziałało to jedziemy dalej
	  if (        gParametryPracy.gTempKolumna != -127.00
			   || gParametryPracy.gTempBeczka  != -127.00
			   || gParametryPracy.gTempGlowica != -127.00
			   || gParametryPracy.gTempWodaWy  != -127.00
			   || gParametryPracy.gTempAlarmu  != -127.00)
		{
		  break; 
		}
	  
	   Receive_Struct();
	
    gTimer.update_by_ID(gTempSensorEvent);

    }while(sTagxy.tag != dBnTagTak);

	delay(180);
}

//wznowienie procesu po wyłączeniu manualnym albo awaryjnym
//np w przypadku uszkodzenia czujników albo braku chłodziwa
void Auto_wznowienie()
{
	Serial.println(F("AUTO wznowienie..."));
	
	//w zależności od etapu jaki był przywracany jest stan zaworków
	//oraz moce grzałek
	switch( gParametryPracy.gEtap )
	{
	 case 1: //rozgrzewanko
	 {
      //Valves CLOSE
	  SetValvesOFF();// zamknij jeśli otwarte
	  SetPowerON_1(100);
	  SetPowerON_2(100);
	  SetPowerON_3();
	 }
	 break;

	 case 2: //zalewanie
	 {
	   SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta

	   //zamknac reszte zaworów
	   SetValveOFF(ZaworPrzedGon);
	   SetValveOFF(ZaworGonu);
	   SetValveOFF(ZaworGonu2);
	   
	
	   if(gParametryPracy.gPrzerwaPoZalaniu == false)
       {
	     SetPowerON_1(gParametryPracy.gMocZalaniaG1);
	     SetPowerON_2(gParametryPracy.gMocZalaniaG2);
	     SetPowerON_3();
	   }else
	   {
		  //gParametryPracy.gCzyZalano == true
		  //wył.. grzanie przerwa po zalaniu
		  SetPowerOFF_1();
		  SetPowerOFF_2();
		  SetPowerOFF_3();
	   }
	 }
	 break;

	 case 3: //stabilizacyja
	 {
	  SetPowerOFF_3();

	  SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
	  //jak nie zamkniete to zam.zaw.
	  SetValveOFF(ZaworPrzedGon);
	  SetValveOFF(ZaworGonu);
	  SetValveOFF(ZaworGonu2);

	  SetPowerON_1(gParametryPracy.gMocStabilizacjiG1);
	  SetPowerON_2(gParametryPracy.gMocStabilizacjiG2);
	 }
	 break;

	 case 4: //przedgony
	 {
	   SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
	   SetValveON(ZaworPrzedGon); //otwarcie zaw przedgon jeśli zamknięty

	   //zamkniecie gonu
	   SetValveOFF(ZaworGonu);
	   SetValveOFF(ZaworGonu2);

	   SetPowerOFF_3();

	   if(gParametryPracy.gStabPrzedgon == false)
	   {
	    SetPowerON_1(gParametryPracy.gMocPrzedgonuG1);
	    SetPowerON_2(gParametryPracy.gMocPrzedgonuG2);
	   }else
	   {
		SetPowerON_1(gParametryPracy.gMocGonuG1);
	    SetPowerON_2(gParametryPracy.gMocGonuG2);
	    
	    if(gParametryPracy.gDuzeJeziorko == true)
	    {
			SetValveOFF(ZaworPrzedGon);
		}else
		{
			SetValveON(ZaworPrzedGon);
		}
	    
	   }
	 }
	 break;

	 case 5: //gony
	 {
		SetPowerOFF_3();
		SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
		SetValveOFF(ZaworPrzedGon); //zamknięcie zaw. przedgonu jeśli otwarty

		if(gParametryPracy.gDrugaMocGonu == true)
		{
		 SetPowerON_1(gParametryPracy.gMocGonu2_G1);
	     SetPowerON_2(gParametryPracy.gMocGonu2_G2);

		}else
		{
		 SetPowerON_1(gParametryPracy.gMocGonuG1);
	     SetPowerON_2(gParametryPracy.gMocGonuG2);
		}
		
		//przywrucenie zaworów Gon1 Gon2
		if(gParametryPracy.gZaworGonu == true)
		{
		  SetValveON(ZaworGonu);
		}else
		{
		  SetValveOFF(ZaworGonu);
		}
		if(gParametryPracy.gZaworGonu2 == true)
		{
		  SetValveON(ZaworGonu2);
		}else
		{
		  SetValveOFF(ZaworGonu2);
		}

	 }
	 break;

	 case 6: //pogony
	 {
      SetPowerOFF_3();

	  SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta

	  //odtworzenie stanu zaworkow.....................
      SetValveOFF(ZaworGonu);      //zamyk. zaw gon
      SetValveOFF(ZaworGonu2);     //zamyk. zaw gon2
      SetValveON(ZaworPrzedGon);   //otw przedgon-pogon

	  SetPowerON_1(gParametryPracy.gMocGonuG1);
	  SetPowerON_2(gParametryPracy.gMocGonuG2);
	 }
	 break;

	 case 7: //chłodzenie głowycy
	 {
	  SetValveON(ZaworWoda);//otwarcie wody jeśli nie otwarta
	  SetValveOFF(ZaworPrzedGon);
	  SetValveOFF(ZaworGonu);
	  SetValveOFF(ZaworGonu2);
	  //wył.. grzanie
	  SetPowerOFF_1();
	  SetPowerOFF_2();
	  SetPowerOFF_3();
	 }
    }
    
    gParametryPracy.gSTATUS = 1;
    
    AwariaDS_number = 0;
    
    //gStartAUTO = true;
}

//Brak_DS TAK NIE screen
bool Brak_DS_TakNie(int x, int y, int sizet, char* text)
{
     sTagXY sTagxy;
     bool result = false;

     do
     {
      int tagoption1 = 0;
      int tagoption2 = 0;

      FTImpl.DLStart();
      FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(x , y, sizet, 0, text);


      FTImpl.GetTagXY(sTagxy); // Pobieramy X,Y,TAG

      // Jesli wykryto tag TAK
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption1 = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
        tagoption2 = 0;
        result = true;
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH/2 - 120, 160, 90, 60,  24,  tagoption1,flashtext(46));


      // Jesli wykryto tag NIE
      if (sTagxy.tag == dBnTagNie)
      {
        tagoption2 = FT_OPT_FLAT;
        tagoption1 = 0;
        FTImpl.Cmd_FGColor(0xFF0000);
        result = false;
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagNie);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH/2 + 40, 160, 90, 60,  24,  tagoption2,flashtext(47));

      FTImpl.Cmd_Text(50 ,25, 22,0, flashtext(53));
      
      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();
      
       Receive_Struct();


    }while(sTagxy.tag != dBnTagNie && sTagxy.tag != dBnTagTak);

    delay(380);
    return result;

}

//Gdy padnie któryś z DS
//wyłączyć grzanie i podać info na ekranik	i zatrzymać proces !!!
void Brak_Odczytu_DSA()
{
	  //wył.grzałek i wszystkich zaworków
	  SetPowerOFF_1();
	  SetPowerOFF_2();
	  SetPowerOFF_3();
	  
	  SetValvesOFF();
	  
	  SetValveON(ZaworWoda);

	 //wyswietlamy informację o tym co się tutaj stało:
	 Brak_DS_info_screen();
	 delay(100);

	 if(Brak_DS_TakNie(100,90,29,"Czy kontynuowac proces ?") == true)
	 {
	  	 
	  if(gStartMAN == false)
	  {
		  Auto_wznowienie();
	      Sound_Play(0x14,100,108);
	      InfoScreen(600,31,115,110,"Power START !");
	  }
	  
	 }else
	 {
	   AAc_dis_AUTO();
	 }
}

//Gdy zabraknie wody w kranie:)
//wyłączyć grzanie i podać info na ekranik
void Brak_ChlodzeniaWodyA()
{
	 //wył grzanie
	 SetPowerOFF_1();
	 SetPowerOFF_2();
	 SetPowerOFF_3();
	 
	 SetValvesOFF();
	 
	 SetValveON(ZaworWoda);
	 
	 if(gParametryPracy.gSYS_LOG == true) DataLog("BRAK CHLODZENIA");
	 
	 Serial.println(F("Brak chlodzenia AUTO ON"));
	 
	 Brak_Chlodzenia_info_s(30,80,120,flashtext(149));
	 delay(200);
	 
	 if(gStartAUTO == true)
	 {
		 if(Brak_Chlodzenia_TakNie(100,90,29,"Czy kontynuowac proces ?") == true)
		 {
		   SetValveON(ZaworWoda);
		   Auto_wznowienie();
		   Sound_Play(0x14,100,108);
		   InfoScreen(600,31,115,110,"Power START !");
		 }else
		 {
		   AAc_dis_AUTO();
		 }
     }
	 
}

//How many free ram
int MemsizeBytes()
{
	 int memsize = 8192; // 8kb
     byte *buf;
     while ((buf = (byte *) malloc(--memsize)) == NULL);
     free(buf);
     return memsize;
     //memset(array,0,sizeof(array));
}

//odczyt z czujnika zalewania wywoływany co sekundę:
//void Akt_CzujkiZalania()
//{
//	  gParametryPracy.gPoziomZalania = (1023 - analogRead(CzujnikZalania));
//}//-------------------------------------------------

//sparwdzanie czy nie popadały DSy ----> sensory temperatury
void Akt_AwariaDS()
{
	
	
	
		//jeśli pracuje w trybie AUTO to sprawdzamy
        //czy jakiś czujnik temperatury po prostu nie padł
        //wtedy naoguł odczyt jest -127.00
        if(gStartAUTO == true)
        {
			if (gParametryPracy.gTempKolumna   == -127.00
			   || gParametryPracy.gTempBeczka  == -127.00
			   || gParametryPracy.gTempGlowica == -127.00
			   || gParametryPracy.gTempWodaWy  == -127.00
			   || gParametryPracy.gTempAlarmu  == -127.00)
			{
			  //Serial.println(F("Brak odczytu z sensora temperatury DS18B20"));
			  //wywołaj obsługę tego błędu:
			  
			  Serial.println(F("Awaria DS"));
			  if(gParametryPracy.gSYS_LOG == true) DataLog("DS18b20 error!"); 
			
			AwariaDS_number++;
			
			//---------------------
			if(gBrak_DS_anuluj == false)//jak anulowano nie wchodzić...
			{
				//display error ds
			    InfoScreen(1000,31,65,110,"Error :  DS18b20");
				if(AwariaDS_number > DS_ERROR_MAX)
				   Brak_Odczytu_DSA();
		    }
			//---------------------
			}
	    }
	    
	        
	    if(AwariaDS_number > DS_ERROR_MAX)
	    {    
	         Sound_Play(0x14,100,108);  
	    }       
	    
	    if(gParametryPracy_RCV.gESP_MILLIS > gLAST_ESP_MILLIS)
	    {
			if( WIFI_CheckIP() == true )
			{
			  gCzyWIFI_IS_Conected = true;
			}else
			{
			  gCzyWIFI_IS_Conected = false;
			  gParametryPracy_RCV.gWIFI_RSSI = 0;
			}
	
		}else
		{
			gCzyWIFI_IS_Conected = false;
			gParametryPracy_RCV.gWIFI_RSSI = 0;
		}
         gLAST_ESP_MILLIS = gParametryPracy_RCV.gESP_MILLIS;
	         
	         
	    //if( WIFI_CheckIP() == true )
		//{
		  //gCzyWIFI_IS_Conected = true;
		//}else
		//{
		  //gCzyWIFI_IS_Conected = false;
		//}   
	    
	    
	    //DIAGNOSTYKA------------------------------ na razie wyłączone
	    //************************************************************
	    //Serial.print(F("IP:"));
	    //Serial.println(String(gParametryPracy_RCV.ip1) + "." + String(gParametryPracy_RCV.ip2) + "." + String(gParametryPracy_RCV.ip3) + "." + String(gParametryPracy_RCV.ip4));
	    ////Serial.print("Free memory:");
        ////Serial.println(MemsizeBytes());
        //Serial.print(F("gEtap:"));
        //Serial.println(gParametryPracy.gEtap);
        //Serial.print(F("gNR_Okna:"));
        //Serial.println(gParametryPracy.gNR_Okna);
        ////Serial.println(gParametryPracy.gSSID);
        //Serial.print(F("ESP MILLIS:")); 
        //Serial.println(gParametryPracy_RCV.gESP_MILLIS);  
        //Serial.println(String(gParametryPracy.gCzasProcesuGodz) + "." + String(gParametryPracy.gCzasProcesuMin) + "." + String(gParametryPracy.gCzasProcesuSek));
	    //Serial.println(sizeof(gParametryPracy_RCV));
	    //Serial.println(sizeof(gParametryPracy)); 
	    //Serial.println("");
	    
	    
	    
	 //   Akt_Temp();
	    
	    
}

void PotwODBGonu()
{
	 sTagXY sTagxy;

	 uint16_t 	Tstart_m = gParametryPracy.gCzasProcesuTotalMin;
	 uint16_t 	Tstart_s = gParametryPracy.gCzasProcesuSek;
	 unsigned long Tstart_all_S = (Tstart_m * 60) + Tstart_s; //czas startu wyskoku okna w sek
	 unsigned long Tcurr_all_S = 0;

	 uint8_t pykadlo = 0;

	 uint8_t colorr = 0;
	 bool valve = true;
	 
	 bPotwODBGonu = true;

	 //gon open
	 SetValveON(ZaworGonu);

     do
     {
      int tagoption = 0;

      //gParametryPracy.gNR_Okna = 12;
     
      if(gStartMAN == true)
	  {
		gParametryPracy.gNR_Okna = 78;
      }
      if(gStartAUTO == true && gStartMAN == false)
      {
		gParametryPracy.gNR_Okna = 66;  
	  }

      FTImpl.DLStart();

      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(80 , 0, 31, 0, "Plukanie OLM I:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);

      colorr+=5;
		FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1260, 4100);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(10 ,244, 23,0, flashtext(49));
		 if(colorr >= 255)
	  colorr = 0;

      FTImpl.GetTagXY(sTagxy);

	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.Cmd_Button(105, 60, 160, 70,  30,  tagoption,flashtext(46));

      if(valve == true)
      {
       Tcurr_all_S = (gParametryPracy.gCzasProcesuTotalMin * 60) + gParametryPracy.gCzasProcesuSek;
      }

	  if(valve == false)
	  {
	   FTImpl.Cmd_Text(120 ,210, 31,0, flashtext(106));
	  }

	  FTImpl.Cmd_Number(300 , 70, 31, 0,Tcurr_all_S - Tstart_all_S);
	  FTImpl.ColorRGB(0x00,0xFF,0x00);
	  FTImpl.Cmd_Text(430 ,85, 23,0, "Sek");
	  FTImpl.ColorRGB(0xFF,0x00,0x00);
	  FTImpl.Cmd_Progress(25, 150, 425, 40, 0, Tcurr_all_S - Tstart_all_S ,gParametryPracy.gPlukanieOLM);

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();


	  if(valve == true)
	  {
		  //alarm sound
		  if(pykadlo > 15)
		  {
		   Sound_Play(0x14,100,108);
		   pykadlo = 0;
		  }
      }else
      {
		  //alarm sound
		  if(pykadlo > 65)
		  {
		   Sound_Play(0x14,100,108);
		   pykadlo = 0;
		  }
	  }
	  
	  pykadlo++;

      //czas płukanki OLM
      if(valve == true)
      {
		  if(Tcurr_all_S - Tstart_all_S == gParametryPracy.gPlukanieOLM )
		  {
			 SetValveOFF(ZaworGonu);
			 valve = false;
		  }
      }

      //OVERTIME exit 60 minut
      if(gParametryPracy.gCzasProcesuTotalMin - Tstart_m > 60)
       break;


      //Aktualizacja timer gTempSensorEvent oraz CzasProcesuEvent
      //gTimer.update_by_ID(gPwr1TimerEvent);
      //gTimer.update_by_ID(gPwr2TimerEvent);
	  gTimer.update_by_ID(gTempSensorEvent);
	  
	  if(gStartMAN == false)
	  {
	   gTimer.update_by_ID(gCzasProcesuEvent);
	  }
	  
	  gTimer.update_by_ID(gAwariaDSTempEvent);
	//  gTimer.update_by_ID(gWykresTempEvent);
	  gTimer.update_by_ID(gSystemBackupEvent);
	  //gTimer.update_by_ID(gSendTOEspEvent);

      Receive_Struct();

    if(www_Okidoki_POTW == true)
      break;

    }while(sTagxy.tag != dBnTagTak && gStartAUTO == true);
	
	//www_Okidoki_POTW == false && gStartAUTO == true
	 //otrzymano potwierdzenie---->
	 //otrzymano potwierdzenie---->
	 if(gStartAUTO == true)
     {
	  gParametryPracy.gPotwOdbGonu = true;
	  SetValveON(ZaworGonu);
     }
	 gParametryPracy.gNR_Okna = 0;
	 www_Okidoki_POTW = false;
	 bPotwODBGonu = false;
	 delay(380);
}

void SD_save_conf()
{
		uint8_t* src = (uint8_t*)&gParametryPracy;

		String filename;
		InputText(filename,"Nazwa pliku:",8,29);
		filename += String(".BCG");

		File plik_wr;
		plik_wr = SD.open(filename.c_str(), FILE_WRITE); //FILE_WRITE_TR

		if (plik_wr)
		{
		 plik_wr.seek(0); 
		 plik_wr.write(src, sizeof(gParametryPracy)); //write whole structure to new file
		 plik_wr.close();
	 	 InfoScreen(500,31,200,120,"OK");
	  	} else
		{
		 InfoScreen(1000,31,100,110,"File error!");
		}
}

void AKoniec_procesu()
{
	    //1) Czas procesu destylacji
		//2) Czas odbioru gonu
		//3) Czas odbioru z EZ1
		//4) Czas odbioru z EZ2
		//4) Czas rozgrzewaia beczki
		//5) Czas zalewania
		//6) TemDnia
		//7) EZ gonu 1 (ile razy się otworzył)
		//8) EZ gonu 2 (ile razy się otworzył)
		//9) EZ gonu 1 (przy jakiej tem się zamknął)
		//10) EZ gonu 2 (przy jakiej tem się zamknął)
	
	  sTagXY sTagxy;
	 
	  int gon_godziny = 0;
	  int minutt = 0;
	  int reszta_min = 0;

	  for(unsigned int cntr = 0;cntr < gParametryPracy.gCzasGonu;cntr++)
	  {
		if(minutt == 60)
		{
		 gon_godziny++;
		 minutt = 0;
		}
		 minutt++;
	  }

	  reszta_min = gParametryPracy.gCzasGonu - (gon_godziny * 60);
	  
	  uint8_t colorr2 = 0;
	  uint8_t pykadlo = 0;

     do
     {
      int tagoption = 0;
      
      gParametryPracy.gNR_Okna = 21;

      FTImpl.DLStart();

      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      
      

      
      
      colorr2+=7;
	  if(colorr2 >= 255)
	  colorr2 = 0; 
      
      FTImpl.ColorRGB(colorr2, colorr2 ,colorr2);  
      FTImpl.Cmd_Text(5 , 3, 30, 0, flashtext(88));
      
      FTImpl.ColorRGB(0xFF,0x77,0x00);

      String datetime(gParametryPracy.gStartAutoDateTime.year);//"-"
      datetime += flashtext(87);
      datetime += gParametryPracy.gStartAutoDateTime.month;
      datetime += flashtext(87);
      datetime += gParametryPracy.gStartAutoDateTime.day;
      datetime += flashtext(87);
      datetime += gParametryPracy.gStartAutoDateTime.hour;
      datetime += flashtext(87);
      datetime += gParametryPracy.gStartAutoDateTime.minute;
      datetime += flashtext(87);
      datetime += gParametryPracy.gStartAutoDateTime.second;

      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(260 , 0, 23, 0, datetime.c_str() );

      
      //czas trwania
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 40, 23, 0, flashtext(89) );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(145, 30, 30, 0, gParametryPracy.gCzasProcesuGodz );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(185, 30, 30, 0, flashtext(86) );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(195, 30, 30, 0, gParametryPracy.gCzasProcesuMin );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(240, 30, 30, 0, flashtext(86) );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(250, 30, 30, 0, gParametryPracy.gCzasProcesuSek );


      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 70, 23, 0, flashtext(74) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 70, 23, 0, gParametryPracy.gCzasRozgrzewania );
      FTImpl.Cmd_Text(190, 70, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 90, 23, 0, flashtext(75) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 90, 23, 0, gParametryPracy.gCzasZalewania );
      FTImpl.Cmd_Text(190, 90, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 110, 23, 0, flashtext(76) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 110, 23, 0, gParametryPracy.gCzasStabilizacji );
      FTImpl.Cmd_Text(190, 110, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 130, 23, 0, flashtext(107) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 130, 23, 0, gParametryPracy.gCzasPrzedgonu );
      FTImpl.Cmd_Text(190, 130, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 150, 23, 0, "Gon:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(57, 150, 23, 0, gon_godziny );
      FTImpl.Cmd_Text(92, 150, 23, 0, "godz" );
      FTImpl.Cmd_Number(150, 150, 23, 0, reszta_min );
      FTImpl.Cmd_Text(190, 150, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 170, 23, 0, flashtext(80) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 170, 23, 0, gParametryPracy.gCzasPogonu );
      FTImpl.Cmd_Text(190, 170, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 190, 23, 0, flashtext(81) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 190, 23, 0, gParametryPracy.gCzasChlodzenia );
      FTImpl.Cmd_Text(190, 190, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 210, 23, 0, flashtext(111) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(190, 210, 23, 0, flashtext(112) );
      dtostrf(gParametryPracy.gHisterezaTemperatury, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(130 ,210 , 23,0, TempCharBuffer);

     
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(297, 50, 23, 0, flashtext(116) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(410, 50, 23, 0, gParametryPracy.gZaworGonCntr );
      
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(297, 70, 23, 0, flashtext(119) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(410, 70, 23, 0, gParametryPracy.gZaworGon2Cntr );

    

	  //tempdnia	
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(297, 90, 23, 0, flashtext(117) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      dtostrf(gParametryPracy.gTempDnia, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(400 ,90 , 23,0, TempCharBuffer);

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(245, 150, 30, 0, flashtext(118) );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      if(gParametryPracy.gKoniec == true)
      {
		FTImpl.Cmd_Text(418 + random(-3,3) ,150 + random(-3,3) , 30,0, flashtext(46));
	  }else
	  {
	    FTImpl.Cmd_Text(418 + random(-3,3) ,150 + random(-3,3) , 30,0, flashtext(47));
	  }

      
      FTImpl.ColorRGB(0x00,0xFF,0x00);

      FTImpl.GetTagXY(sTagxy);

      tagoption = 0;
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(375, 210, 77, 50,  29,  tagoption,flashtext(50));
      
      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();
      
      //akt temperature timer
      gTimer.update_by_ID(gTempSensorEvent);

      Receive_Struct();
      
      
      //alarm sound
      if(pykadlo > 150)
      {
       Sound_Play(random(0,255),245,random(0,255));
       pykadlo = 0;
      }
      
      pykadlo++;

    }while(sTagxy.tag != dBnTagTak);


    delay(300);
	if(TakNie(60,60,30,"Czy zapisac na karcie SD ?") == true)
	{
	  Sound_Play(0x14,100,108);
	  SD_save_conf();
	}else
	{
	  InfoScreen(600,31,100,110,"Nie zapisales !");
	  Sound_Play(0x14,100,108);
	}

    delay(380);
}

void PotwODBGonu_2()
{
	 sTagXY sTagxy;

	 uint16_t 	Tstart_m = gParametryPracy.gCzasProcesuTotalMin;
	 uint16_t 	Tstart_s = gParametryPracy.gCzasProcesuSek;
	 unsigned long Tstart_all_S = (Tstart_m * 60) + Tstart_s; //czas startu wyskoku okna w sek
	 unsigned long Tcurr_all_S = 0;

	 uint8_t pykadlo = 0;

	 uint8_t colorr = 0;
	 
	 Receive_Struct();

	 //open ZaworGon2
	 SetValveON(ZaworGonu2);
	 //close ZaworGon
	 SetValveOFF(ZaworGonu);
	 
	 bPotwODBGonu = true;

     do
     {
      int tagoption = 0;
      
      //gParametryPracy.gNR_Okna = 13;
      
      if(gStartMAN == true)
	  {
		gParametryPracy.gNR_Okna = 78;
      }
      if(gStartAUTO == true && gStartMAN == false)
      {
	    gParametryPracy.gNR_Okna = 77;  
	  }

      FTImpl.DLStart();

      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(140 , 30, 30, 0, "Plukanie OLM II");
      FTImpl.ColorRGB(0x00,0xFF,0x00);

      colorr+=5;
		FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1260, 4100);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(10 ,244, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;

      FTImpl.GetTagXY(sTagxy);


      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.Cmd_Button(370, 205, 80, 50,  28,  tagoption,flashtext(52));


      Tcurr_all_S = (gParametryPracy.gCzasProcesuTotalMin * 60) + gParametryPracy.gCzasProcesuSek;

	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
	  FTImpl.Cmd_Number(220 , 100, 31, 0, Tcurr_all_S - Tstart_all_S);

	  FTImpl.ColorRGB(0xFF,0x00,0x00);
	  FTImpl.Cmd_Progress(25, 150, 425, 40, 0, Tcurr_all_S - Tstart_all_S ,gParametryPracy.gPlukanieOLM);

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();
      FTImpl.Finish();


      //czas płukanki OLM
      if(Tcurr_all_S - Tstart_all_S == gParametryPracy.gPlukanieOLM )
	  {
		SetValveOFF(ZaworGonu2);
	   break;
	  }


      //OVERTIME exit 60 minut
      if(gParametryPracy.gCzasProcesuTotalMin - Tstart_m > 60)
       break;

      //Update timer gTempSensorEvent CzasProcesuEvent
	  gTimer.update_by_ID(gTempSensorEvent);
	  //gTimer.update_by_ID(gPwr1TimerEvent);
	  //gTimer.update_by_ID(gPwr2TimerEvent);
	  
	  if(gStartMAN == false)
	  {
	   gTimer.update_by_ID(gCzasProcesuEvent);
	  }
	  
	  gTimer.update_by_ID(gAwariaDSTempEvent);
	//  gTimer.update_by_ID(gWykresTempEvent);
	  gTimer.update_by_ID(gSystemBackupEvent);
	  //gTimer.update_by_ID(gSendTOEspEvent);

      Receive_Struct();
      
      //alarm sound
      if(pykadlo > 60)
      {
       Sound_Play(0x14,100,108);
       pykadlo = 0;
      }
      
      pykadlo++;

      if(www_Okidoki_POTW == true)
      break;

    }while(sTagxy.tag != dBnTagTak && gStartAUTO == true);


	if(gStartAUTO == true)
    {
	 //otrzymano potwierdzenie---->
	 gParametryPracy.gPotwOdbGonu = true;
	 SetValveOFF(ZaworGonu2);
     SetValveON(ZaworGonu); //kontynuujemy sposzczanie gonu na ZG1
    }
    
    gParametryPracy.gNR_Okna = 0;
	www_Okidoki_POTW = false;
	bPotwODBGonu = false;

    delay(380);
        
}

//Zakończenie procesu
void AAc_8Zakonczenie()
{
    SetValvesOFF();

	gParametryPracy.gKoniec = true;
	gStartAUTO = false;
	gParametryPracy.gSTATUS = 0; //OFF

	
	AKoniec_procesu(); //wywołanie ekranu zakończenia

	//gParametryPracy.gEtap		         = 0;
	//gParametryPracy.gStabPrzedgon      = false;
	//gParametryPracy.gPotwOdbGonu       = false;
	//gParametryPracy.gZaworGonu2_ON	 = false;
	//gParametryPracy.gPrzerwaPoZalaniu  = false;
	//gParametryPracy.gDrugaMocGonu      = false;
	//gParametryPracy.gCzyZalano         = false;
}

//Chłodzenie głowicy
void AAc_7Chlodzenie()
{
    gParametryPracy.gCzasChlodzenia = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;

	if(gParametryPracy.gCzasProcesuTotalSek >= gParametryPracy.gStart_etapu + (gParametryPracy.gZadanyCzasChlodzenia*60))
	{
		//Wył wody i koniec
		SetValveOFF(ZaworWoda);
		//TIME OVER
		gParametryPracy.gEtap = 8;
		Serial.println(F("KONIEC !"));
		if(gParametryPracy.gSYS_LOG == true) DataLog("THE END");
		Sound_Play(0x14,100,108);
	}	

}

//Pogon
void AAc_6Pogon()
{
 gParametryPracy.gCzasPogonu  = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;

 if(gParametryPracy.gTempGlowica >= gParametryPracy.gTempStopPogonu)
  {
	//zamyk przedgon-pogon
	SetValveOFF(ZaworPrzedGon);

	//wył grzanie
	SetPowerOFF_1();
	SetPowerOFF_2();
	gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
	gParametryPracy.gEtap = 7;
	Serial.println(F("Chlodzenie ON"));
	if(gParametryPracy.gSYS_LOG == true) DataLog("CHLODZ ON");
	Sound_Play(0x14,100,108);
  }	
}

//Przedgon
void AAc_4Przedgon()
{
    gParametryPracy.gCzasPrzedgonu = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;
	
	if(gParametryPracy.gStabPrzedgon == false)
	 {
		 if(gParametryPracy.gCzasProcesuTotalSek >=
		  gParametryPracy.gStart_etapu + 
		  (gParametryPracy.gZadanyCzasOdbPrzedgonuMin * 60)
		  + gParametryPracy.gZadanyCzasOdbPrzedgonuSek)
		   {
			  gParametryPracy.gStabPrzedgon = true;
			  
			  if(gParametryPracy.gDuzeJeziorko == true)
			  {
			   SetValveOFF(ZaworPrzedGon);
		      }else
		      {
			   SetValveON(ZaworPrzedGon); 	  
			  }
			  SetPowerON_1(gParametryPracy.gMocGonuG1);
			  SetPowerON_2(gParametryPracy.gMocGonuG2);
			  Sound_Play(0x14,100,108);
		   }
	 }

   if(gParametryPracy.gStabPrzedgon == true)//potem stabilizacja przedgonu na czas
   {
		 if(gParametryPracy.gCzasProcesuTotalSek >=
		  gParametryPracy.gStart_etapu + (gParametryPracy.gZadanyCzasOdbPrzedgonuMin*60)
		           + gParametryPracy.gZadanyCzasOdbPrzedgonuSek
		           + (gParametryPracy.gZadanyCzasStabPrzedgonu*60))
			{
			  SetValveOFF(ZaworPrzedGon);
			  gParametryPracy.gTempDnia = gParametryPracy.gTempKolumna;
			  Sound_Play(0x14,100,108);
			  gParametryPracy.gEtap = 5;
			  Serial.println(F("Gon ON"));
			  if(gParametryPracy.gSYS_LOG == true) DataLog("GON ON");
			}
   }	
	
}

//Stabilizacja
void AAc_3Stabilizacja()
{
 gParametryPracy.gCzasStabilizacji = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;
 if(gParametryPracy.gCzasProcesuTotalSek >=
   gParametryPracy.gStart_etapu + (gParametryPracy.gZadanyCzasStabilizacji * 60))
   {
	 SetValveON(ZaworPrzedGon);
	 gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
	 SetPowerON_1(gParametryPracy.gMocPrzedgonuG1);
	 SetPowerON_2(gParametryPracy.gMocPrzedgonuG2);
	 gParametryPracy.gEtap = 4;
	 Serial.println(F("Przedgon ON"));
	 if(gParametryPracy.gSYS_LOG == true) DataLog("PRZG ON");
	 Sound_Play(0x14,100,108);
	 Sound_Play(0x14,100,108);
	 Sound_Play(0x14,100,108);
   }	
}

//Zalewanie
void AAc_2Zalewanie()
{
	//timer0_overflow_count = 0;
	
  gParametryPracy.gCzasZalewania = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;

  //UWAGA !!!
  //odczyt co 1 sekundę //deprecated
  //gCzujnikZalaniaEvent = gTimer.every(1000,Akt_CzujkaZalania);
  //po 20 sekundach od startu zalewania dopiero mozna
  //odczytać wartości z czuja zalania... 
  //tu jest podwujny warunek jeśli jest użyty czujnik zalania
  //i jednocześnie nie zalano jeszcze to wchodzimy i sprawdzamy czy zalano
  //potem jeśli zalanie nastąpiło to ustawiamy flagę zalania na true
 if(gParametryPracy.gCzujnikZalania == true
                       && gParametryPracy.gCzyZalano == false)
 {
	 if(gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu > 5)
	 {
		 //gTimer.update_by_ID(gCzujnikZalaniaEvent);
		 //odczytanie czujnika zalania
		 gParametryPracy.gPoziomZalania = (1023 - analogRead(CzujnikZalania));
	 }

	 //Warunek zalania na podstawie
	 //danych z czujnika zalania kolumny pozalaniu system
	 //przechodzi do przerwy zalania ustawianej w sekundach
	 if(gParametryPracy.gPoziomZalania > gParametryPracy.gZadanyPoziomZalania)
	 {
		gParametryPracy.gCzyZalano = true;
		Sound_Play(0x14,100,108);
		//gTimer.stop(gCzujnikZalaniaEvent);
		//digitalWrite(ZasilanieCzujnikaZalania,LOW);
	 }
 }

 //zalewanie---->
 if(gParametryPracy.gPrzerwaPoZalaniu == false)
 {
	 
    if(gParametryPracy.gCzasProcesuTotalSek >=
	gStart_zalania + (gParametryPracy.gZadanyCzasZalewania * 60)
	|| gParametryPracy.gCzyZalano == true)
	{
		gParametryPracy.gPrzerwaPoZalaniu = true;//idziemy do przerwy P.Z
		gParametryPracy.gCzasZalania = gParametryPracy.gCzasProcesuTotalSek - gStart_zalania;//gParametryPracy.gStart_etapu;//sek04.04.2017 11:42:19
		
		
		
		//wyłączam moc...
				 //zeby...
				     //była...
				          //przerwa w mocy po zalaniu tako jakoś...
		SetPowerOFF_1();
		SetPowerOFF_2();
		SetPowerOFF_3();//?
		Sound_Play(0x14,100,108);
	}
 }

//przerwa w mocy po zalaniu w sekundach
// if(gParametryPracy.gCzasProcesuTotalSek >=
//      gParametryPracy.gStart_etapu + (gParametryPracy.gZadanyCzasZalewania * 60)
//      + gParametryPracy.gZadanyCzasPrzerwyMocyZalania) 
 if(gParametryPracy.gPrzerwaPoZalaniu == true)
 {
    if(gParametryPracy.gCzasProcesuTotalSek >=
                          gStart_zalania + 
                          gParametryPracy.gCzasZalania
                        + gParametryPracy.gZadanyCzasPrzerwyMocyZalania) 
	{
	  gStart_zalania = gParametryPracy.gCzasProcesuTotalSek;
	  

	  //SetPowerOFF_3();//wyłączyć 3 cią grzałkę rozgrzewającą

	  //jeśli był w uzyciu czujnik zalania ale przeszedł czas
	  //a on nie zadziałał to czyśćimy po nim:
	//  if(gParametryPracy.gCzujnikZalania == true)
	//  {
	   //clear timer event for zalanie
	   //gTimer.stop(gCzujnikZalaniaEvent);
	   //*****************************************
	   //wyłączenia zasilania czujnika zalania
	   //digitalWrite(ZasilanieCzujnikaZalania,LOW);
	   //*****************************************
	//  }
	
	  //włączyć spowrotem grzanie 
	  SetPowerON_1(gParametryPracy.gMocZalaniaG1);
	  SetPowerON_2(gParametryPracy.gMocZalaniaG2);
	  SetPowerON_3();      
	        
      gParametryPracy.gCzyZalano = false;
      
      //czy zalaliśmy juz wystarczająco razy?
      if(gParametryPracy.gZalanieX == gParametryPracy.gZalanieZadaneX)
      {
	   
	   //Tu mamy Koniec tego etapu ileś zalewań:
	   //digitalWrite(ZasilanieCzujnikaZalania,LOW);	//wył zasiłkę czujnika ZAL.  
       gParametryPracy.gEtap = 3;
       Serial.println(F("Stabilizacja ON"));
       if(gParametryPracy.gSYS_LOG == true) DataLog("STB ON");
       //gParametryPracy.gZalanieX = gParametryPracy.gZalanieX - 1;
       //przechodzima na mocu stabilizacji
       SetPowerON_1(gParametryPracy.gMocStabilizacjiG1);
	   SetPowerON_2(gParametryPracy.gMocStabilizacjiG2);
       SetPowerOFF_3();// wyłączam 3 grzołę
       gParametryPracy.gCzyZalano = true; //Zalaliśmy X razy
       gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
       return;
      }
 
      //zwiekszamy licznik zalania
      gParametryPracy.gZalanieX++;
      gParametryPracy.gPrzerwaPoZalaniu = false;
      Sound_Play(0x14,100,108);
    }
 }
}

//Rozgrzewanie
void AAc_1Rozgrzewanie()
{
  gParametryPracy.gCzasRozgrzewania = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;
  if(gParametryPracy.gTempGlowica >= gParametryPracy.gTempRozgrzewania) //org >
  {
	SetValveON(ZaworWoda);
	gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
	gStart_zalania = gParametryPracy.gCzasProcesuTotalSek;
	gParametryPracy.gEtap = 2;
	//Serial.println(F("Zalewanie ON"));
	if(gParametryPracy.gSYS_LOG == true) DataLog("Zalew.ON");
	SetPowerON_1(gParametryPracy.gMocZalaniaG1);
	SetPowerON_2(gParametryPracy.gMocZalaniaG2);
	
	if(gParametryPracy.gZalanieZadaneX > 0)
	{
	 gParametryPracy.gZalanieX = 1;
    }
	
	Sound_Play(0x14,100,108);
	//jeśli mamy czujnik zalania wybrany w config to:
	if(gParametryPracy.gCzujnikZalania == true)
    {
		//*************************************!!!!!!!!
		//włączenie zasilania czujnika zalania
		//digitalWrite(ZasilanieCzujnikaZalania,HIGH);
		//*************************************!!!!!!!!
		//włączenie eventu timera dla czujnika zalewania
		//gCzujnikZalaniaEvent = gTimer.every(1000,Akt_CzujkiZalania);
    }
  }
}

//♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥
//♥ GON-GON-GON ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥
//♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥			
void AAc_5Gon()
{
    gParametryPracy.gCzasGonu  = (gParametryPracy.gCzasProcesuTotalSek - gParametryPracy.gStart_etapu)/60;

	//jeżeli temp na beczce przekroczy gTempZmianyMocyGonu
	//to system maxgon przełączy się na drugą moc w gonie...
	if(gParametryPracy.gDrugaMocGonu == false)
	{
		if(gParametryPracy.gTempBeczka > gParametryPracy.gTempZmianyMocyGonu)
		{
		  SetPowerON_1(gParametryPracy.gMocGonu2_G1);
		  SetPowerON_2(gParametryPracy.gMocGonu2_G2);
		  Sound_Play(0x14,100,108);
		  gParametryPracy.gDrugaMocGonu = true;
		}
	}

	if(gParametryPracy.gPotwOdbGonu == false)
	{
	   if(gParametryPracy.gIloscZaworowGonu == false) //jeden I
	   {
	     PotwODBGonu();    //płukanieOLM na jedyn zawór
	     gParametryPracy.gPotwOdbGonu = true;
	     gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
	     Sound_Play(0x14,100,108);
	   }else//dwa zawory gona II
	   {
		 PotwODBGonu_2();  //płukanieOLM na dwa zawory
	     gParametryPracy.gPotwOdbGonu = true;
	     gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
	     Sound_Play(0x14,100,108);
	   }
	}


	//ALG I
	//W zależności od gTempDnia > akt-temp-kolumna + histereza = zamykamy zaw ZaworGonu
	//gTempDnia < akt-temp-kolumna - histereza = otwieramy zaw ZaworGonu
	//ALG: II
    //jeżeli temp. na kolumnie jest większa od
    //Temperatura dnia + Histereza to zawór się zamyka.
    //A otwiera jeżeli temp. na kolumnie jest mniejsza od tem dnia+histereza
    if(gParametryPracy.gIloscZaworowGonu == false) //jeden I
	{
		//Zamykamy zaw gonu
		if(gParametryPracy.gTempKolumna > gParametryPracy.gTempDnia + gParametryPracy.gHisterezaTemperatury )
		{
			SetValveOFF(ZaworGonu);
			//Sound_Play(0x14,100,108);
		}
		//otw zawor gonu
		if(gParametryPracy.gTempKolumna < gParametryPracy.gTempDnia + gParametryPracy.gHisterezaTemperatury )
		{
			SetValveON(ZaworGonu);
			//Sound_Play(0x14,100,108);
		}
    }else //dwa zawory II
    {   //jeśli nie przełączyło jedzie na ZaworGonu1
		if(gParametryPracy.gZaworGonu2_ON == false) 
		{
			  //Temperatura w menu gTempZG2
			  if(gParametryPracy.gTempBeczka >= gParametryPracy.gTempZG2 )
			  {
				  gParametryPracy.gZaworGonu2_ON = true;
				  SetValveOFF(ZaworGonu);
			  }else
			  {
				  //Zamykamy zaw gonu
				  if(gParametryPracy.gTempKolumna > gParametryPracy.gTempDnia + gParametryPracy.gHisterezaTemperatury )
				  {
					SetValveOFF(ZaworGonu);
					//Sound_Play(0x14,100,108);
				  }
				  //otw zawor gonu
				  if(gParametryPracy.gTempKolumna < gParametryPracy.gTempDnia + gParametryPracy.gHisterezaTemperatury )
				  {
					SetValveON(ZaworGonu);
					//Sound_Play(0x14,100,108);
				  }
		      }
			  
		}else //przełączone pracuje na ZaworGonu2
	    {
			  //Zamykamy zaw gonu
			  if(gParametryPracy.gTempKolumna > gParametryPracy.gTempDnia + gParametryPracy.gHisterezaTemperatury )
			  {
				SetValveOFF(ZaworGonu2);
				//Sound_Play(0x14,100,108);
			  }
			  //otw zawor gonu
			  if(gParametryPracy.gTempKolumna < gParametryPracy.gTempDnia + gParametryPracy.gHisterezaTemperatury )
			  {
				SetValveON(ZaworGonu2);
				//Sound_Play(0x14,100,108);
			  }
	    }
	}


	//KONIEC GON???
	// sprawdzenie czy koniec gonu wg temp na beczce start to 99 st C
	if(gParametryPracy.gTempBeczka >=  gParametryPracy.gTempStartPogonu)
	{
		//HIST POGONU?
		//dodatkowo histereza pogonu jesli jest włączona
		//jeśli temp na kolumnie przekroczy
		//temp dnia + hist.temperatury to przejdzie w pogon
		//a jak nie to destyluję dalej...
		if(gParametryPracy.gHistPoGonu == true)
		{
			if(gParametryPracy.gTempKolumna > gParametryPracy.gTempDnia +
			gParametryPracy.gHisterezaTemperatury)
			{
			  SetValveOFF(ZaworGonu);        //zamyk. zaw gon
			  SetValveOFF(ZaworGonu2);     //zamyk. zaw gon2
			  SetValveON(ZaworPrzedGon);//otw przedgon-pogon
			  gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
			  gParametryPracy.gEtap 	= 6;
			  Serial.println(F("Pogon ON"));
			  if(gParametryPracy.gSYS_LOG == true) DataLog("POGON ON");
			  Sound_Play(0x14,100,108);
			}
		}else
		{
 			 SetValveOFF(ZaworGonu);        //zamyk. zaw gon
			 SetValveOFF(ZaworGonu2);     //zamyk. zaw gon2
			 SetValveON(ZaworPrzedGon);//otw przedgon-pogon
			 gParametryPracy.gStart_etapu = gParametryPracy.gCzasProcesuTotalSek;
			 gParametryPracy.gEtap 	= 6;
			 Sound_Play(0x14,100,108);
		}
	}
}


void AAc_0AUTO()
{
	if(gParametryPracy.gTempAlarmu > gParametryPracy.gTempStopGrzania)
	{
	  if(gBrak_Chlodzenia_anuluj == false)//jeśli true to anulowano nie wywołac okna !!!
	  {	
	   Brak_ChlodzeniaWodyA();
      }
	}
	
	Receive_Struct();
	
	 //if(gStartAUTO == false) return;	//nima aktualizacyji
	 if(gStartAUTO == false || gStartMAN == true) return;	//nima aktualizacyji

	 switch( gParametryPracy.gEtap )
	 {
		case 1://rozgrzewanie etap 1 
		{
			AAc_1Rozgrzewanie();	
		break;
		}
		
		case 2://zalewanie etap 2 
		{
			AAc_2Zalewanie();
		break;
		}
		
		case 3://stabilizacja etap 3 
		{
			 AAc_3Stabilizacja();   
		break;
		}
		
		case 4://przedgon etap 4 
		{
			 AAc_4Przedgon();
        break;
	    }
		
		case 5://ODB GONU
		{
			 AAc_5Gon();
		break;
		}
    	
    	case 6://pogon etap 6 
		{
	         AAc_6Pogon();
		break;
		}
		
		case 7://chlodzenie glowicy etap 7
		{
			 AAc_7Chlodzenie();
		break;
		}
		
		case 8://podsumowanie etap 8 
		{
			AAc_8Zakonczenie();
      	break;
		}
     }

	Receive_Struct();
}

//initialize display FT800
bool Init_Display()
{
      uint32_t chipid = 0;

      Serial.println(F("Inicjalizacja ekranu"));

      // Inicjalizujemy ekran
      FTImpl.Init(FT_DISPLAY_RESOLUTION);

      //? z przykładów wzięte
      delay(50);

      chipid = FTImpl.Read32(FT_ROM_CHIPID);
      if (chipid != FT800_CHIPID)
      {
        Serial.println(F("Nie obslugiwany uklad: 0x"));
        Serial.println(chipid, HEX);
       return false;
      }

      Serial.println(F("Obslugiwany uklad: 0x"));
      Serial.println(chipid, HEX);

      //These bits control the touch screen resistance threshold. Host can
      //adjust the touch screen touching sensitivity by setting this register. The default
	  //value after reset is 0xFFFF and it means the lightest touch will be accepted by the
	  //touch engine of the FT800. The host can set this register by doing experiments. The
      //typical value is 1200.
      //FTImpl.Write16(REG_TOUCH_RZTHRESH,1200);

      //These bits control the touch screen oversample factor. The higher
      //value of this register causes more accuracy with more power consumption, but
      //may not be necessary. The valid range is from 1 to 15.
      FTImpl.Write16(REG_TOUCH_OVERSAMPLE ,15);

      // Wlaczamy ekran
      FTImpl.DisplayOn();

      //These bits define the backlight PWM output duty cycle. The valid
      //range is from 0 to 128. 0 means backlight complete off, 128 means backlight in
      //max brightness.
      //FTImpl.Write(REG_PWM_DUTY,0);


     //Calibrate();
    
     //Jeśli nie ma danych w pamięci eprom to
     //będzie zrobiona kalibracja ekranu a daane zostaną
     //zapisane w eepromie sterownika liczba kontrolna to 0x7c
     //24 dane na końcu pamięci - 25
     #define EEPROM_CALIBRATION_DATA_START (EEPROM.length() - 25)
	 if (EEPROM.read(EEPROM_CALIBRATION_DATA_START) != 0x7c)
	 {
		 Calibrate();
		 // for (int i = 0; i < 24; i++)
		 // {
		 // EEPROM.write(EEPROM_CALIBRATION_DATA_START + i, FTImpl.Read(REG_TOUCH_TRANSFORM_A + i));
		 // }
		 // EEPROM.write(EEPROM_CALIBRATION_DATA_START, 0x7c);
	 }
	 else
	 {
	      for (int i = 0; i < 24; i++)
	      {
		   FTImpl.Write(REG_TOUCH_TRANSFORM_A + i, EEPROM.read(EEPROM_CALIBRATION_DATA_START + i));
	      }
     }
     //Enable audio
     FTImpl.SetAudioEnablePin(FT_AUDIOENABLE_PIN);
     FTImpl.AudioOn();
     
     //brightnes
     FTImpl.Write(REG_PWM_DUTY,127);

    return true;
}




void Update_gMocMAN()
{
          switch( gParametryPracy.gEtap )
		  {
			  
			case 0://off
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			     break;  
			  
			case 1://rozgrzewanie
				  gParametryPracy.gMocMAN_G1 = 100;
				  gParametryPracy.gMocMAN_G2 = 100;
				break;

			case 2://zalewanie
				if(gParametryPracy.gPrzerwaPoZalaniu == false)
				{
				 gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocZalaniaG1;
				 gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocZalaniaG2;
			    }else
			    {
		    	  gParametryPracy.gMocMAN_G1 = 0;
				  gParametryPracy.gMocMAN_G2 = 0;
				}
				break;


			case 3://stabilizacja
				 {
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocStabilizacjiG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocStabilizacjiG2;
			     }
				break;

			case 4://przedgon
				if(gParametryPracy.gStabPrzedgon == true)
				{
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;	
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			    }else
			    {
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocPrzedgonuG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocPrzedgonuG2;
				}
				break;

			case 5://gon
				if(gParametryPracy.gDrugaMocGonu == false)
				{
				 gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;
				 gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			    }else
			    {
			     gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonu2_G1;
			     gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonu2_G2;
				}
				break;
				
				case 6://pogon
				 if(gParametryPracy.gDrugaMocGonu == false)
				 {
				  gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonuG1;
				  gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonuG2;
			     }else
			     {
			      gParametryPracy.gMocMAN_G1 = gParametryPracy.gMocGonu2_G1;
			      gParametryPracy.gMocMAN_G2 = gParametryPracy.gMocGonu2_G2;
				 }
				 break;
				 
				 case 7://chlodzenie
				  gParametryPracy.gMocMAN_G1 = 0;
				  gParametryPracy.gMocMAN_G2 = 0;
				break;
				
				case 8://koniec
				  gParametryPracy.gMocMAN_G1 = 0;
				  gParametryPracy.gMocMAN_G2 = 0;
				break;
			//default:
			//    FTImpl.Cmd_Text(270,130, 27,0, "ON");
			//	FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocZadanaG2 );
			//break;

			}//end switch
}			




//CONFIG SCREEN
void AA_Config()
{
      sTagXY sTagxy;
      int tagoption = 0;
      uint8_t colorr = 0;
      int page = 1;
      
      int kropkaX = 120;
      int kropkaY = 0;
 
     do
     {
		 
      gParametryPracy.gNR_Okna = 2;
      		 
      FTImpl.DLStart();
      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);

      if(gStartAUTO == true)
      {
		 colorr+=25;
		  FTImpl.ColorRGB(colorr,0,0);
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(7500, 3370);
		//FTImpl.Vertex2ii(120, 90, 0, 0);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(400 ,200, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }
	  


      FTImpl.ColorRGB(0xFF,0xFF,0x00); 
      FTImpl.GetTagXY(sTagxy); 
      FTImpl.Cmd_GradColor(0xffffff);

      
      if(page == 1)
      {
      //rozgrzewanie
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(210 );
      if (sTagxy.tag == 210 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10,10, 140, 50,  23,  tagoption,flashtext(74));

      //Zalewanie pały
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(211 );
      if (sTagxy.tag == 211 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(170,10, 140, 50,  23,  tagoption,flashtext(75));

      //Stabilizacja
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(212 );
      if (sTagxy.tag == 212 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(330,10, 140, 50,  23,  tagoption,flashtext(76));

      //Przedgon
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(213 );
      if (sTagxy.tag == 213 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10,75, 140, 50,  23,  tagoption,flashtext(77));

      //Gon
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(214 );
      if (sTagxy.tag == 214 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(170,75, 140, 50,  23,  tagoption,flashtext(78));

      //Gon II
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(215 );
      if (sTagxy.tag == 215 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(330,75, 140, 50,  23,  tagoption,flashtext(79));

      //PoGon
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(216 );
      if (sTagxy.tag == 216 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10,145, 90, 50,  23,  tagoption,flashtext(80));

      //Chłodzenie głowicy
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(217 );
      if (sTagxy.tag == 217 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(120,145, 110, 50,  23,  tagoption,flashtext(81));

      //Pozostałe
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(218 );
      if (sTagxy.tag == 218 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0x000000);
      } else  FTImpl.Cmd_FGColor(0xFF0000);
      FTImpl.Cmd_Button(255,145, 85, 50,  23,  tagoption,flashtext(82));
      
      
      //Grzałki
      //FTImpl.ColorRGB(0x00,0x00,0x00);
      //tagoption = 0;
      //FTImpl.Tag(228 );
      //if (sTagxy.tag == 228 )
      //{
		//tagoption = FT_OPT_FLAT;
        //FTImpl.Cmd_FGColor(0xFFFFFF);
      //} else  FTImpl.Cmd_FGColor(0xFFB900);
      //FTImpl.Cmd_Button(365,145, 95, 50,  23,  tagoption,flashtext(161));
      

      FTImpl.Cmd_Text(90 ,232, 21,0, flashtext(54));

  }//end main menu


  //menu rozgrzewanie
  if(page == 2)
  {
      FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(83));

      // Jesli wykryto dBnTagConfigTempRozgrzewania
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigTempRozgrzewania );
      if (sTagxy.tag == dBnTagConfigTempRozgrzewania )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10,10, 210, 80,  24,  tagoption,flashtext(84));
      FTImpl.Cmd_Text(20 ,20, 20,0, flashtext(85));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempRozgrzewania, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(30 ,62, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(120 ,62, 22,0, "st C");

      // Jesli wykryto TmpStopGrzania
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(88 );
      if (sTagxy.tag == 88 )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(245,10, 220, 80,  24,  tagoption,flashtext(150));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempStopGrzania, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(255 ,18, 21,0, flashtext(151));
      FTImpl.Cmd_Text(270 ,62, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(370 ,62, 22,0, flashtext(152));

      //temp Alarma
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      dtostrf(gParametryPracy.gTempAlarmu, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(360 ,14, 28,0, TempCharBuffer);

  }//end rozgrzewanie

  //menu zalewanie
  if(page == 3)
  {
	FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(153));

	  //MOC zalewania G1
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigPowerB Set POWER
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocZalaniaG1);
      if (sTagxy.tag == dBnTagConfigMocZalaniaG1)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 10, 120, 75,  24,  tagoption,flashtext(154));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(15, 55,24, 0, gParametryPracy.gMocZalaniaG1 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(85 ,64, 22,0, flashtext(55));

      //MOC zalewania G2
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocZalaniaG2);
      if (sTagxy.tag == dBnTagConfigMocZalaniaG2)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(145, 10, 120, 75,  24,  tagoption,flashtext(155));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(160, 55,24, 0, gParametryPracy.gMocZalaniaG2 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(220 ,64, 22,0, flashtext(55));


	  //czujnik zalania TAK/NIE
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(115);
      if (sTagxy.tag == 115)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(280, 10, 100, 75,  23,  tagoption,flashtext(162));
      FTImpl.Cmd_Text(300 ,18, 23,0, flashtext(163));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      if(gParametryPracy.gCzujnikZalania == false)
       FTImpl.Cmd_Text(318 ,60, 28,0, flashtext(47));
       else FTImpl.Cmd_Text(318 ,60, 28,0, flashtext(46));
       
       
      //Zalanie X
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(227);
      if (sTagxy.tag == 227)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(395, 10, 75, 75,  23,  tagoption,"X:");
      FTImpl.Cmd_Text(405 ,18, 22,0, "ile razy");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(423, 58,23, 0, gParametryPracy.gZalanieZadaneX);
      


	  // Jesli wykryto dBnTagZadanyCzasZalewania
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagZadanyCzasZalewania);
      if (sTagxy.tag == dBnTagZadanyCzasZalewania)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 100, 150, 75,  24,  tagoption,flashtext(164));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(40, 150,23, 0, gParametryPracy.gZadanyCzasZalewania );
      FTImpl.Cmd_Text(95 ,150, 22,0, flashtext(90));


      //gZadanyCzasPrzerwyMocyZalania
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(113);
      if (sTagxy.tag == 113)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(180, 100, 150, 75,  23,  tagoption,"po zalaniu:");
      FTImpl.Cmd_Text(185 ,110, 23,0, flashtext(165));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(220, 150,23, 0, gParametryPracy.gZadanyCzasPrzerwyMocyZalania );
      FTImpl.Cmd_Text(260 ,150, 22,0, "sek");


      //gPoziomZalania
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(114);
      if (sTagxy.tag == 114)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(345, 100, 120, 75,  23,  tagoption,"zalanie:");
      FTImpl.Cmd_Text(360 ,110, 22,0, flashtext(166));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(360, 150,23, 0, gParametryPracy.gZadanyPoziomZalania );
      FTImpl.Cmd_Text(410 ,150, 22,0, "0-1023");


  }//end zalewanie

  //menu stabilizacja
  if(page == 4)
  {
	  FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(141));


      //MOC stabilizacji G1
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigPowerB Set POWER
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocStabilizacjiG1);
      if (sTagxy.tag == dBnTagConfigMocStabilizacjiG1)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 10, 190, 75,  24,  tagoption,"Moc  G1:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(45, 55,24, 0, gParametryPracy.gMocStabilizacjiG1 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(120 ,60, 22,0, "0 - 255");


      //MOC stabilizacji G2
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocStabilizacjiG2);
      if (sTagxy.tag == dBnTagConfigMocStabilizacjiG2)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(220, 10, 190, 75,  24,  tagoption,"Moc  G2:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(240, 55,24, 0, gParametryPracy.gMocStabilizacjiG2 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(320 ,60, 22,0, "0 - 255");


      // Jesli wykryto dBnTagZadanyCzasStabilizacji
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagZadanyCzasStabilizacji );
      if (sTagxy.tag == dBnTagZadanyCzasStabilizacji)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10 , 100, 140, 65,  24,  tagoption,flashtext(167));
      FTImpl.Cmd_Text(55 , 103, 22, 0, "Czas");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(20 , 140, 23, 0, gParametryPracy.gZadanyCzasStabilizacji );
      FTImpl.Cmd_Text(85 , 140, 22, 0, "minut");
  }


  //menu przedgon
  if(page == 5)
  {
	 FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(142));

	   //MOC przedgonu G1
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigPowerB Set POWER
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocPrzedgonuG1);
      if (sTagxy.tag == dBnTagConfigMocPrzedgonuG1)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 10, 120, 75,  24,  tagoption,"Moc G1:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(25, 59,23, 0, gParametryPracy.gMocPrzedgonuG1 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(75 ,62, 22,0, flashtext(55));


      //MOC przedgonu G2
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigPowerB Set POWER
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocPrzedgonuG2);
      if (sTagxy.tag == dBnTagConfigMocPrzedgonuG2)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160, 10, 120, 75,  24,  tagoption,"Moc G2:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(165, 59,23, 0, gParametryPracy.gMocPrzedgonuG2 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(217 ,62, 22,0, flashtext(55));


      // Jesli wykryto pobierz TempDnia
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(112);
      if (sTagxy.tag == 112)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(310, 10, 125, 75,  24,  tagoption,flashtext(169));
      FTImpl.Cmd_Text(340 ,15, 22,0, flashtext(170));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempDnia, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(320 ,59, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(385 ,63, 22,0, "st C");


	  tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagZadanyCzasOdbPrzedgonu );
      if (sTagxy.tag == dBnTagZadanyCzasOdbPrzedgonu)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10 , 100, 130, 75,  24,  tagoption,flashtext(171));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      
           
      FTImpl.Cmd_Number(20 , 152, 23, 0, gParametryPracy.gZadanyCzasOdbPrzedgonuMin );
      FTImpl.Cmd_Number(80 , 152, 23, 0, gParametryPracy.gZadanyCzasOdbPrzedgonuSek );
      FTImpl.Cmd_Text(23 ,105, 21,0, flashtext(145));


      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(77 );
      if (sTagxy.tag == 77)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160 , 100, 200, 75,  24,  tagoption,flashtext(143));
      FTImpl.Cmd_Text(181 , 105, 22, 0, flashtext(144));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(200 , 150, 23, 0, gParametryPracy.gZadanyCzasStabPrzedgonu );
      FTImpl.Cmd_Text(260 , 150, 22, 0, "minuty");

      //EZ elektrozawór od stabilizacji przedgonu
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(177 );
      if (sTagxy.tag == 177)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(380 , 100, 80, 75,  24,  tagoption,"EZ:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(395 , 105, 22, 0, "off / on");
      if(gParametryPracy.gDuzeJeziorko == true)
      {
       FTImpl.Cmd_Text(405 , 155, 22, 0, flashtext(8));
      }else FTImpl.Cmd_Text(405 , 155, 22, 0, flashtext(7));

      FTImpl.Cmd_Text(362 , 120, 30, 0, ">");


  }


  //menu gon
  if(page == 6)
  {
    FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(168));


	  //MOC gonu G1
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigPowerB Set POWER
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocGonuG1);
      if (sTagxy.tag == dBnTagConfigMocGonuG1)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 10, 120, 75,  24,  tagoption,"Moc G1:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(20, 58,23, 0, gParametryPracy.gMocGonuG1 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(70 ,63, 22,0, flashtext(55));


      //MOC gonu G2
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigPowerB Set POWER
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigMocGonuG2);
      if (sTagxy.tag == dBnTagConfigMocGonuG2)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160, 10, 120, 75,  24,  tagoption,"Moc G2:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(170, 58,23, 0, gParametryPracy.gMocGonuG2 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(220 ,63, 22,0, flashtext(55));


      //Ilość zaworów gonu
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(89);
      if (sTagxy.tag == 89)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x640000);
      FTImpl.Cmd_Button(310, 10, 120, 75,  24,  tagoption,"Zawory:");
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      if(gParametryPracy.gIloscZaworowGonu == false)
          FTImpl.Cmd_Number(330, 57,24, 0, 1 );
      else
          FTImpl.Cmd_Number(330, 57,24, 0, 2 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(385 ,58, 22,0, "1-2");


	   // Jesli wykryto dBnTagPlukanieOLM
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagPlukanieOLM );
      if (sTagxy.tag == dBnTagPlukanieOLM)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(150 , 105, 170, 65,  24,  tagoption,"Plukanie OLM:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(175 , 148, 23, 0, gParametryPracy.gPlukanieOLM );
      FTImpl.Cmd_Text(230 , 148, 22, 0, "sekundy");


      // Jesli wykryto Temp.ZG.2
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(90 );
      if (sTagxy.tag == 90)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(340, 105, 130, 65,  24,  tagoption,"Temp.ZG.2:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempZG2, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(350 ,148, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(415 ,148, 22,0, "st C");


      // Jesli wykryto dBnTagHisterezaTemperatury
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagHisterezaTemperatury);
      if (sTagxy.tag == dBnTagHisterezaTemperatury)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 105, 120, 65,  24,  tagoption,"Histereza:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gHisterezaTemperatury, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(20 ,148, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(80 ,148, 22,0, "st C");

  }


  //menu gon II
  if(page == 7)
  {
      FTImpl.Cmd_Text(120 ,190, 24,0, "Odb.Gonu 2:");
      //tag 222->
      //MOC gonu II G1
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(222);
      if (sTagxy.tag == 222)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 10, 120, 75,  24,  tagoption,"Moc2 G1:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(20, 58,23, 0, gParametryPracy.gMocGonu2_G1 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(70 ,63, 22,0, flashtext(55));

      //MOC gonu II G2
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(223);
      if (sTagxy.tag == 223)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(160, 10, 120, 75,  24,  tagoption,"Moc2 G2:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(170, 58,23, 0, gParametryPracy.gMocGonu2_G2 );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(220 ,63, 22,0, flashtext(55));


      //Temp przełączania
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(224);
      if (sTagxy.tag == 224)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 105, 180, 75,  24,  tagoption,"TempPrzejscia:");
      FTImpl.Cmd_Text(70 ,105, 22,0, "Beczka");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempZmianyMocyGonu, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(20 ,154, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(115 ,154, 22,0, "st C");

  }


  //menu po-gon
  if(page == 8)
  {

	  FTImpl.Cmd_Text(120 ,185, 24,0, "Odbior pogonu:");

	  // Jesli wykryto dBnTagConfigStopPogonu
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigStopPogonu );
      if (sTagxy.tag == dBnTagConfigStopPogonu )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 5, 180, 65,  24,  tagoption,"Stop Pogonu:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempStopPogonu, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(30 ,48, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(95 ,50, 22,0, "stopnie C");

      // Jesli wykryto dBnTagStartPogonu
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagStartPogonu);
      if (sTagxy.tag == dBnTagStartPogonu)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 80, 180, 65,  24,  tagoption,"Start Pogonu:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      dtostrf(gParametryPracy.gTempStartPogonu, 5, 2, TempCharBuffer);
      FTImpl.Cmd_Text(30 ,122, 23,0, TempCharBuffer);
      FTImpl.Cmd_Text(95 ,122, 22,0, "stopnie C");


	  // Jesli wykryto histPogonu  zmienna: gHistPoGonu
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(100);
      if (sTagxy.tag == 100)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(210, 5, 180, 140,  24,  tagoption,"Hist.Pogonu:");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      if(gParametryPracy.gHistPoGonu == false)
       FTImpl.Cmd_Text(270 ,100, 30,0, flashtext(47));
       else FTImpl.Cmd_Text(270 ,100, 30,0, flashtext(46));

  }



  //menu chłodzenie
  if(page == 9)
  {
       FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(146));

	   // Jesli wykryto dBnTagConfigChlodzenieGlowicy
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigChlodzenieGlowicy);
      if (sTagxy.tag == dBnTagConfigChlodzenieGlowicy)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 5, 260, 83,  24,  tagoption,flashtext(146));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(60, 60,23, 0, gParametryPracy.gZadanyCzasChlodzenia );
      FTImpl.Cmd_Text(120 ,60, 22,0, "minuty");

}




  //INNE
  if(page == 10)
  {
	  FTImpl.Cmd_Text(120 ,185, 24,0, flashtext(147));


	   // Jesli wykryto dBnTagRESOLUTION
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagRESOLUTION  );
      if (sTagxy.tag == dBnTagRESOLUTION )
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(235 , 80, 220, 65,  24,  tagoption,"Termometrow:");
      FTImpl.Cmd_Text(305 , 85, 22, 0, "czulosc");
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(275 , 123, 23, 0, gParametryPracy.gTEMPERATURE_PRECISION );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(305 , 123, 22, 0, ":  9 10 11 12");


	   FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigVOLUME Set VOLUME
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigVOLUME);
      if (sTagxy.tag == dBnTagConfigVOLUME)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 5, 70, 65,  24,  tagoption,"Vol:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(35, 45,23, 0, gParametryPracy.gSoundVolume );
    

      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigTIME Set TIME
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigTIME);
      if (sTagxy.tag == dBnTagConfigTIME)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(90, 5, 70, 65,  24,  tagoption,"Czas:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(100 ,45, 23,0, "g:m:s");
      

      // Jesli wykryto dBnTagTempUpdateInterval
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Tag(dBnTagTempUpdateInterval);
      if (sTagxy.tag == dBnTagTempUpdateInterval)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(10, 80, 210, 65,  24,  tagoption,"Aktualizacja Tmp:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(40, 122,23, 0, gParametryPracy.gTempUpdateTime );
      FTImpl.Cmd_Text(130 ,122, 22,0, "milisekundy");


      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      // Jesli wykryto dBnTagConfigCalibration CALIBRE
      tagoption = 0;
      FTImpl.Tag(dBnTagConfigCalibration);
      if (sTagxy.tag == dBnTagConfigCalibration)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(170, 5, 160, 65,  24,  tagoption,"Kalib Ekranu:");
      
      
      //LOGI
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      tagoption = 0;
      FTImpl.Tag(231);
      if (sTagxy.tag == 231)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      if(gParametryPracy.gSYS_LOG == true)
      {      
       FTImpl.Cmd_Button(340, 5, 115, 65,  23,  tagoption,"TAK");
      }else
      {
	   FTImpl.Cmd_Button(340, 5, 115, 65,  23,  tagoption,"NIE");  
	  }
	  FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Text(348 ,8, 22,0, "LOG:");
      
      
}

//if(page == 11)
  //{
	  //Update_gMocMAN();

       //FTImpl.Cmd_Text(120 ,185, 24,0, "Rodzaj sterowania");

	  ////typ sterowania mocy
	  //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //tagoption = 0;
      //FTImpl.Tag(225);
      //if (sTagxy.tag == 225)
      //{
		//tagoption = FT_OPT_FLAT;
        //FTImpl.Cmd_FGColor(0xFF0000);
      //} else  FTImpl.Cmd_FGColor(0x000088);
      
      //if(gParametryPracy.gTypMocy == false)
      //{
		//FTImpl.ColorRGB(0xFF,0x00,0x00);  
       //FTImpl.Cmd_Button(10, 5, 160, 73,  24,  tagoption,"Grupowe");
      //}else
      //{
		  //FTImpl.ColorRGB(0xFF,0x00,0x00); 
	   //FTImpl.Cmd_Button(10, 5, 160, 73,  24,  tagoption,"Liniowe");
      //}
      //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //FTImpl.Cmd_Text(25 ,10, 22,0, "Sterowanie mocy:");
      
      ////częstotliwość sterowania mocy
	  //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //tagoption = 0;
      //FTImpl.Tag(226);
      //if (sTagxy.tag == 226)
      //{
		//tagoption = FT_OPT_FLAT;
        //FTImpl.Cmd_FGColor(0xFF0000);
      //} else  FTImpl.Cmd_FGColor(0x000088);
      
      //FTImpl.Cmd_Button( 200, 5, 150, 83,  24,  tagoption,"");
      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text( 220 ,10, 22,0, "Grupowo:");
      
      //FTImpl.ColorRGB(0xFF,0x00,0x00);
      //FTImpl.Cmd_Number( 220, 35,24, 0, gParametryPracy.gCzestotliwoscMocyGrupowo );
      
      //FTImpl.ColorRGB(0xFF,0x00,0x00);
      //FTImpl.Cmd_Number( 35, 90,23, 0, gParametryPracy.gMocMAN_G1 );
      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text( 75 ,90, 23,0, "%  = ");
      
      //FTImpl.ColorRGB(0xFF,0x00,0x00);
      //FTImpl.Cmd_Number( 35, 120,23, 0, gParametryPracy.gMocMAN_G2 );
      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text( 75 ,120, 23,0, "%  = ");
      
      //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      
      //if(gParametryPracy.gTypMocy == false)
      //{
      
          //float llon1  = ((gParametryPracy.gMocMAN_G1 * 0.01) * gParametryPracy.gCzestotliwoscMocyGrupowo);
		  //float lloff1 = gParametryPracy.gCzestotliwoscMocyGrupowo - llon1;
		  //llon1  = llon1  * 0.001;
		  //lloff1 = lloff1 * 0.001;
		  
		  
		  //dtostrf(llon1,6, 3, TempCharBuffer);
          //FTImpl.Cmd_Text(125 ,90, 23,0, TempCharBuffer);
		  //FTImpl.Cmd_Text(220 ,90, 23,0, "s ON");
		  //dtostrf(lloff1, 6, 3, TempCharBuffer);
          //FTImpl.Cmd_Text(300 ,90, 23,0, TempCharBuffer);
          //FTImpl.Cmd_Text(400 ,90, 23,0, "s OFF");
		  
		 	  
		  //float llon2  = ((gParametryPracy.gMocMAN_G2 * 0.01) * gParametryPracy.gCzestotliwoscMocyGrupowo);
		  //float lloff2 = gParametryPracy.gCzestotliwoscMocyGrupowo - llon2;
		  //llon2 = llon2 * 0.001;
		  //lloff2 = lloff2 * 0.001;
		  
		  //dtostrf(llon2, 6, 3, TempCharBuffer);
          //FTImpl.Cmd_Text(125 ,120, 23,0, TempCharBuffer);
		  //FTImpl.Cmd_Text( 220 ,120, 23,0, "s ON");
		  //dtostrf(lloff2, 6, 3, TempCharBuffer);
          //FTImpl.Cmd_Text(300 ,120, 23,0, TempCharBuffer);
          //FTImpl.Cmd_Text( 400 ,120, 23,0, "s OFF");
	
      //}
      
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Text( 350 ,6, 21,0, "< --- okres pracy");
      //FTImpl.Cmd_Text( 320 ,45, 21,0, "ms");
      //FTImpl.Cmd_Text( 5 ,93, 21,0, "G1:");
      //FTImpl.Cmd_Text( 5 ,123, 21,0, "G2:");
      
//}






      //########################
      //########################
      //########################
      //sTagxy.tag 219 i 220  i 221
      //Elementy wspólne save i exit and back to main page
	  //Button SAVE
	   FTImpl.ColorRGB(0xFF,0xFF,0xFF);
	  tagoption = 0;
      FTImpl.Tag(219);
      if (sTagxy.tag == 219)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0x000000);
      } else  FTImpl.Cmd_FGColor(0xFF0000);
      FTImpl.Cmd_Button(12, 222, 70, 40,  24,  tagoption,flashtext(56));
      
      FTImpl.Cmd_Text( 120 ,215, 22,0, "< MaxGon v2.2 >");
      //FTImpl.Cmd_Text( 120 ,230, 23,0, "< KONFIGURACJA >");
      
      kropkaX += 1;
      kropkaY = 216;
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Text( kropkaX ,kropkaY, 31,0, ".");
      if(kropkaX > 300)
        kropkaX = 120;


      // Back to main page
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Tag(221);
      if (sTagxy.tag == 221)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x00AF0C);
      FTImpl.Cmd_Button(310, 222, 70, 40,  31,  tagoption,"<");


      //exit
      tagoption = 0;
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Tag(220);
      if (sTagxy.tag == 220)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Cmd_Button(FT_DISPLAYWIDTH - 85, FT_DISPLAYHEIGHT- 50, 70, 40,  24,  tagoption,flashtext(52));


	  if(page == 1)
	  {	
      FTImpl.ColorRGB(0x2A,0xFF,0x00);
      switch(gParametryPracy.gEtap)
	  {
		 case 1://grzanie
		  {
			  DrawPoint2(10,10,10,10);
			  break;
		  }
		  case 2://zalew
		  {
			  DrawPoint2(170,10,10,10);
			  break;
		  }
		  case 3://stab
		  {
			  DrawPoint2(330,10,10,10);
			  break;
		  }
		  case 4://przedgon
		  {
			  DrawPoint2(10,75,10,10);
			  break;
		  }
		  case 5://gon
		  {
			  DrawPoint2(170,75,10,10);
			  break;
		  }
		  case 6://pogon
		  {
			  DrawPoint2(10,145,10,10);
			  break;
		  }
		  case 7://chlodzenie
		  {
			  DrawPoint2(120,145,10,10);
			  break;
		  }
		  
	  }
     }
	  
	  
	  




      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();  
      FTImpl.Finish();



	 //Rozgrzewanie------------------------------------------------
     // Button Temp rozgrzewania st C
    if (sTagxy.tag == dBnTagConfigTempRozgrzewania)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 //InputNumber(String& stringol, char* opis,int maxinput,int input_textsize,int info_textsize)
		 float number = InputNumber(stringol,"Rozgrzewanie: 0-100 st C","",7,31,27);
		 if(number > 100)
          number = 0;
         if(number <= 0)
          number = 0;
		 gParametryPracy.gTempRozgrzewania = number;

	}
	// Button Temp StopGrzania
    if (sTagxy.tag == 88)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"StopGrzania: 0-100 st C","",7,31,27);
		 if(number > 100)
          number = 0;
         if(number <= 0)
          number = 0;
		 gParametryPracy.gTempStopGrzania = number;

	}


	//Zalewanie----------------------------------------
	//Zalewanie moc G1
	if (sTagxy.tag == dBnTagConfigMocZalaniaG1)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc zalania G1:  0-255 %","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocZalaniaG1 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_1(gParametryPracy.gMocZalaniaG1);
	      }
    }
   //Zalewanie moc G2
	if (sTagxy.tag == dBnTagConfigMocZalaniaG2)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc zalania G2:  0-255%","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocZalaniaG2 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
				SetPowerON_2(gParametryPracy.gMocZalaniaG2);
	      }
	}
	//czas przerwy w mocy po zalaniu
	if (sTagxy.tag == 113)
	{
		  delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Przerwa w mocy: 0-1000 sek","",7,31,27);
		 if(number > 1000)
           number = 0;
         if(number <= 0)
           number = 0;
		 gParametryPracy.gZadanyCzasPrzerwyMocyZalania = number;
	}
	//wartość przy jakiej przechodzi w zalanie
	//zmienna globalna to : gZadanyPoziomZalania
	if (sTagxy.tag == 114)
	{
		  delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Przejscie w zalanie: 0-1023","",7,31,27);
		 if(number > 1023)
           number = 0;
         if(number <= 0)
           number = 0;
		 gParametryPracy.gZadanyPoziomZalania = number;
	}
	//Określa czy jest użyty czujnik zalania
	//zmienna globalna to : gCzujnikZalania
	if (sTagxy.tag == 115)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 if(gParametryPracy.gCzujnikZalania == true)
		   gParametryPracy.gCzujnikZalania = false;
		 else gParametryPracy.gCzujnikZalania = true;
	}
	//Button Zalewania
	if (sTagxy.tag == dBnTagZadanyCzasZalewania) 
	{
	     delay(300);
	     Sound_Play(0x14,100,108);
	     String stringol;
		 int number = InputNumber(stringol,"Zalewanie:    0-60 min ","",7,31,27);
		 if(number > 60)
          number = 0;
         if(number <= 0)
          number = 0;
		 gParametryPracy.gZadanyCzasZalewania = number;

	}
	//ZalanieX
	if (sTagxy.tag == 227) 
	{
	     delay(300);
	     Sound_Play(0x14,100,108);
	     String stringol;
		 int number = InputNumber(stringol,"Zalanie X:      0-112","",7,31,27);
		 if(number > 112)
          number = 0;
         if(number <= 0)
          number = 0;
		 gParametryPracy.gZalanieZadaneX = number;
	}



	//Stabilizacja:-----------------------------------------
	// Button czasu stabilizacji
    if (sTagxy.tag == dBnTagZadanyCzasStabilizacji) //minuty
	{
		  delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Stabilizacja: 0-120 min","",7,31,27);
		 if(number > 120)
           number = 0;
         if(number <= 0)
           number = 0;
		 gParametryPracy.gZadanyCzasStabilizacji = number;
	}
	//Button moc stabilizacji G1
	if (sTagxy.tag == dBnTagConfigMocStabilizacjiG1)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc stab. G1: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocStabilizacjiG1 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_1(gParametryPracy.gMocStabilizacjiG1);
	      }
    }
    //Button stabilizacja moc G2
	if (sTagxy.tag == dBnTagConfigMocStabilizacjiG2)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc stab. G2: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocStabilizacjiG2 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_2(gParametryPracy.gMocStabilizacjiG2);
	      }
    }


    //Przedgon-----------------------------------
    //Button moc przedgonu G1
	if (sTagxy.tag == dBnTagConfigMocPrzedgonuG1)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc grzania G1: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocPrzedgonuG1 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_1(gParametryPracy.gMocPrzedgonuG1);
	      }
    }
    //Button przedgonu moc G2
	if (sTagxy.tag == dBnTagConfigMocPrzedgonuG2)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc grzania G2: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocPrzedgonuG2 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_2(gParametryPracy.gMocPrzedgonuG2);
	      }
	}
    // Button TempDnia st C
    if (sTagxy.tag == 112)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 gParametryPracy.gTempDnia = gParametryPracy.gTempKolumna;
	}
	// Button PrzedGonu
    //w minutach i sekundach min.sek np: 5.45 5min i 45 sek.
    if (sTagxy.tag == dBnTagZadanyCzasOdbPrzedgonu) //minuty i sekundy
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Przedgon: 0-500 min.sek","",8,31,27);
		 if(number > 500)
           number = 45;
         if(number <= 0)
           number = 0;
           
      		 
		 //String indexOf() and lastIndexOf() Method np: 15.25   5.25-1
		 int kropka = stringol.indexOf('.');
		 if(kropka > -1 && kropka < 4)
		 {
		  gParametryPracy.gZadanyCzasOdbPrzedgonuMin = stringol.substring(0,kropka).toInt();
		  gParametryPracy.gZadanyCzasOdbPrzedgonuSek = stringol.substring(kropka + 1).toInt();
		 }else
		 {
	      gParametryPracy.gZadanyCzasOdbPrzedgonuMin = 0;
		  gParametryPracy.gZadanyCzasOdbPrzedgonuSek = 0;
		  ErrorScreen();
	 	 }
	
		 
	}
	//Button przedgonu stabilizacja przedgonu
	if (sTagxy.tag == 77)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Stabilizacja: 0-200 min","",7,31,27);
		 if(number > 200)
           number = 100;
         if(number <= 0)
           number = 0;
		 gParametryPracy.gZadanyCzasStabPrzedgonu = number;
    }
    //Button EZ podczas stabilizacji
	if (sTagxy.tag == 177)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 if(gParametryPracy.gDuzeJeziorko == true) gParametryPracy.gDuzeJeziorko = false;
		 else gParametryPracy.gDuzeJeziorko = true;
    }
    
     



    //GON-----------------------------------
    //Button moc gonu G1
	if (sTagxy.tag == dBnTagConfigMocGonuG1)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc grzania G1: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocGonuG1 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_1(gParametryPracy.gMocGonuG1);
	      }


    }
     //Button gonu moc G2
	if (sTagxy.tag == dBnTagConfigMocGonuG2)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc grzania G2: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocGonuG2 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_2(gParametryPracy.gMocGonuG2);
	      }
    }
    // Button ilość zaworków
    if (sTagxy.tag == 89)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 if(gStartAUTO == false)
         {
	     	if(gParametryPracy.gIloscZaworowGonu == true)
			   gParametryPracy.gIloscZaworowGonu = false;
			 else
			   gParametryPracy.gIloscZaworowGonu = true;
		 }
	}
	// Button temp ZG2
    if (sTagxy.tag == 90)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Temp.ZG.2: 0-120 st C","",7,31,27);
		 if(number > 120)
          number = 0.00;
         if(number <= 0)
          number = 0.00;
		 gParametryPracy.gTempZG2 = number;

	}
	// Button Plukanie OLM
    if (sTagxy.tag == dBnTagPlukanieOLM)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Pluk OLM: 0-600 sek","",7,31,27);
		 if(number > 600)
           number = 0;
         if(number <= 0)
           number = 0;
		 gParametryPracy.gPlukanieOLM = number;

	}
	//Button Histereza Temperatury
    if (sTagxy.tag == dBnTagHisterezaTemperatury)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Hist: 0.00-5.00 st C","",7,31,27);
		 if(number > 5)
          number = 0.00;
         if(number <= 0)
          number = 0.00;
		 gParametryPracy.gHisterezaTemperatury = number;

	}


	//GON II
    //tag 222
    //Button moc gonu 2 G1
	if (sTagxy.tag == 222)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc grzania G1: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocGonu2_G1 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_1(gParametryPracy.gMocGonu2_G1);
	      }
	}
     //Button gonu moc G2
	if (sTagxy.tag == 223)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Moc grzania G2: 0-255","",7,31,27);
		 if(number > 255)
          number = 0;
         if(number <= 0)
          number = 0;
	     gParametryPracy.gMocGonu2_G2 = number;
	     if(gStartAUTO == true)
	      {
			 if(gParametryPracy.gEtap != 1)
	          SetPowerON_2(gParametryPracy.gMocGonu2_G2);
	      }
    }
    // Button gTempZmianyMocyGonu
    if (sTagxy.tag == 224)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Temp.zmiany 0-150","",7,31,27);
		 if(number > 150)
          number = 0.00;
         if(number <= 0)
          number = 0.00;
		 gParametryPracy.gTempZmianyMocyGonu = number;
	}




	//POGON----------------------------------
	// Button stop pogonu st C
    if (sTagxy.tag == dBnTagConfigStopPogonu)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Stop POG: 0-120 st C","",7,31,27);
		 if(number > 120)
          number = 0;
         if(number <= 0)
          number = 0;
		 gParametryPracy.gTempStopPogonu = number;

	}
	//Button Start Pogonu
    if (sTagxy.tag == dBnTagStartPogonu)
	{
		  delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Start PoGonu: 0-120 st C","",7,31,27);
		 if(number > 120)
          number = 0.00;
         if(number <= 0)
          number = 0.00;
		 gParametryPracy.gTempStartPogonu = number;

	}
	// Button HistPogonu tak/nie
    if (sTagxy.tag == 100)
	{
	     delay(300);
		 Sound_Play(0x14,100,108);
		 if(gParametryPracy.gHistPoGonu == true)
		   gParametryPracy.gHistPoGonu = false;
		 else gParametryPracy.gHistPoGonu = true;
	}




	//CHLODZENIE--------------------------
	//Button dBnTagConfigChlodzenieGlowicy
    if (sTagxy.tag == dBnTagConfigChlodzenieGlowicy)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 float number = InputNumber(stringol,"Chlodzenie Gl: 0-100 min","",7,31,27);
		 if(number > 100)
          number = 0;
         if(number <= 0)
          number = 0;
		 gParametryPracy.gZadanyCzasChlodzenia = number;

	}


	//INNE---------------------------->
	//Button dBnTagConfigTIME
    if (sTagxy.tag == dBnTagConfigTIME)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 InputNumber(stringol,"rrrr.mm.dd.gg.mm.ss","rok.mies.dzien.godz",20,23,23);
										           //12.25.15
         InfoScreen(1600,24,100,110,stringol.c_str());
         if(stringol.length() == 19)
         {
			 InfoScreen(600,24,100,110,stringol.c_str());
			 String rok;
			 String miesiac;
			 String dzien;
			 String godz;
			 String min;
			 String sek;
			 rok = stringol.substring(0,4);
			 miesiac = stringol.substring(5,7);
			 dzien = stringol.substring(8,10);
			 godz = stringol.substring(11,13);
			 min = stringol.substring(14,16);
			 sek = stringol.substring(17,19);
			 RTclock.setDateTime(rok.toInt(),
								 miesiac.toInt(),
								 dzien.toInt(),
								 godz.toInt(),
								 min.toInt(),
								 sek.toInt());
		 }						// 2016.01.18.14.19.10	0-18
		 else
		 {
			 InfoScreen(1600,24,100,110,"Error!");
		 }

         //int nnumber =  stringol.toFloat();

         // Recznie (YYYY, MM, DD, HH, II, SS
		 // clock.setDateTime(2014, 4, 13, 19, 21, 00);
		 // RTclock.setDateTime(__DATE__, __TIME__);


	}
	//Button dBnTagConfigCalibration
    if (sTagxy.tag == dBnTagConfigCalibration)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 //Kalibracja ekranu i zapisanie danych w pamięci eeprom
		 //arduinosa  dane kalibracji zapisano na końcu
		 //EEPROM.length() - 25
		if (TakNie(50,60,30,"Czy skalibrowac ekran ?") == true)
        {
         #define EEPROM_CALIBRATION_DATA_START (EEPROM.length() - 25)

		  Calibrate();
		  for (int i = 0; i < 24; i++)
		  {
		   EEPROM.write(EEPROM_CALIBRATION_DATA_START + i, FTImpl.Read(REG_TOUCH_TRANSFORM_A + i));
		  }
		  EEPROM.write(EEPROM_CALIBRATION_DATA_START, 0x7c);

		InfoScreen(500,31,200,120,"OK");
		}

	}
	//Button dBnTagConfigVOLUME
    if (sTagxy.tag == dBnTagConfigVOLUME)
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Volume: 0-255","",7,31,27);
		 if(number > 255)
           number = 0;
         if(number <= 0)
           number = 0;
		 gParametryPracy.gSoundVolume = number;
		 FTImpl.Write(REG_VOL_SOUND,number);
	}
	// Button czasu R.E.S
    if (sTagxy.tag == dBnTagRESOLUTION) //9,10,11,12
	{
		  delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"TempPrec: 9,10,11,12","",7,31,27);
		 if(number > 12)
           number = 0;
         if(number < 9)
           number = 0;
		 gParametryPracy.gTEMPERATURE_PRECISION = number;

	}
	// Button TempUpdateTime interval
    if (sTagxy.tag == dBnTagTempUpdateInterval) //sekundy
	{
		 delay(300);
		 Sound_Play(0x14,100,108);
		 String stringol;
		 int number = InputNumber(stringol,"Akt temp: 0-30000 msek ","",7,31,27);
		 if(number > 30000)
           number = 2000;
         if(number <= 0)
           number = 2000;
		 gParametryPracy.gTempUpdateTime = number;
		 gTimer.setperiod(number,gTempSensorEvent);
	}
	
	//LOG
	if(sTagxy.tag == 231)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		if(gParametryPracy.gSYS_LOG == true)
		{
			gParametryPracy.gSYS_LOG = false;
		}else
		{
			gParametryPracy.gSYS_LOG = true;
		}
		
	}
	
	
	//end inne


	   //##################################
      //##################################
     //##################################
    //rozgrzewanie
    if (sTagxy.tag == 210)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		page = 2;
	}

	//Zalewanie
    if (sTagxy.tag == 211)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		page = 3;
	}

	//stabilizacja
    if (sTagxy.tag == 212)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		page = 4;
	}

	//przegon
    if (sTagxy.tag == 213)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		page = 5;
	}

	//gon
    if (sTagxy.tag == 214)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		page = 6;
	}

	//gon2
    if (sTagxy.tag == 215)
	{
		delay(300);
		 Sound_Play(0x14,100,108);
		page = 7;
	}

	//pogon
    if (sTagxy.tag == 216)
	{
		delay(300);
		 Sound_Play(0x14,100,108);
		page = 8;
	}

	//chłodzenie
    if (sTagxy.tag == 217)
	{
		delay(300);
		 Sound_Play(0x14,100,108);
		page = 9;
	}

	//inne
    if (sTagxy.tag == 218)
	{
		delay(300);
		 Sound_Play(0x14,100,108);
		page = 10;
	}
	
	//grzoły
    //if (sTagxy.tag == 228)
	//{
		//delay(300);
		 //Sound_Play(0x14,100,108);
		//page = 11;
	//}


	//back to main page <
	if (sTagxy.tag == 221)
	{
		delay(300);
		 Sound_Play(0x14,100,108);
		// if(page == 1)
		// {
		// 	page = 11;
		// }else if(page != 1)
		// {
			page = 1;
		// }
	}
	

    //if (sTagxy.tag == 225) 
	//{
		//delay(300);
		 //Sound_Play(0x14,100,108);
		 //if(gParametryPracy.gTypMocy == true)
		 //{
			 //gParametryPracy.gTypMocy = false;
		 //}else
		 //{
			 //gParametryPracy.gTypMocy = true; 
		 //}
		 
		 
	//}
	
	//gCzestotliwoscMocyGrupowo
	//if (sTagxy.tag == 226) //button frequency power grupowy
	//{
		//delay(300);
		 //Sound_Play(0x14,100,108);
		//String stringol;
		 //uint32_t number = InputNumber(stringol,"Czestotliwosc: 0-120000 msek ","",7,31,27);
		 //if(number > 120000)
           //number = 2000;
         //if(number <= 0)
           //number = 2000;
		 //gParametryPracy.gCzestotliwoscMocyGrupowo = number;
		 
		 
	//}



     //Button SAVE do EPRoMU
	if (sTagxy.tag == 219)
	{
		delay(300);
		Sound_Play(0x14,100,108);
		if (TakNie(50,60,30,"Czy zapisac do epromu ?") == true)
        {
          SaveToEprom();
        }

    }

	//Update timer gTempSensorEvent gCzasProcesuEvent gProcessEvent
	//gTimer.update_by_ID(gPwr1TimerEvent);
	//gTimer.update_by_ID(gPwr2TimerEvent);
	
	gTimer.update_by_ID(gTempSensorEvent);
	gTimer.update_by_ID(gCzasProcesuEvent);
	gTimer.update_by_ID(gProcessEvent);
	//gTimer.update_by_ID(gWykresTempEvent);
	gTimer.update_by_ID(gAwariaDSTempEvent);
	gTimer.update_by_ID(gSystemBackupEvent);
	//gTimer.update_by_ID(gSendTOEspEvent);
	
	Receive_Struct();

	//if exit End main loop
    }while(sTagxy.tag != 220);



    delay(250);
    Sound_Play(0x14,100,108);


}


////ABOUT SCREEN---->
//void Info()
//{
	
	
     //sTagXY sTagxy;
     //int tagoption = 0;
     //uint8_t colorr = 0;
     //uint8_t colorr_napisu = 0;
     //bool upp = true;

     //ClearScreen(255,255,255);
     //ClearScreen(255,255,255);
     //ClearScreen(255,255,255);

     //int memsize = MemsizeBytes();
     //char drawadlo = 0;



     //do
     //{
      //gParametryPracy.gNR_Okna = 7;

      //FTImpl.DLStart();
      //FTImpl.ClearColorRGB(0,35,50);
      //FTImpl.Clear(1,1,1);
      //FTImpl.Cmd_BGColor(0x00234C);

      //if(upp == true)
      //{
	   //colorr_napisu += 5;
       //FTImpl.ColorRGB(colorr_napisu,colorr_napisu,colorr_napisu);
       //FTImpl.Cmd_Text(SWIDTH/2 -80, 30, 29, 0, "MaxGon v2.0");
       //if(colorr_napisu >= 255)
		//upp = false;
      //}else
      //{
		 //colorr_napisu -= 5;
       //FTImpl.ColorRGB(colorr_napisu,colorr_napisu,colorr_napisu);
       //FTImpl.Cmd_Text(SWIDTH/2 -80, 30, 29, 0, "MaxGon v2.0");
       //if(colorr_napisu <= 0)
		//upp = true;
	  //}

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(SWIDTH/2 - 130 , 70, 29, 0, "Sterownik kolumny DST");
      //FTImpl.Cmd_Text(385  , 110, 29, FT_OPT_RIGHTX | FT_OPT_CENTERY, "2016 Misrocoft Corporation");
      //FTImpl.Cmd_Text(80  , 120, 29, 0, "free memory:");
      //FTImpl.Cmd_Number(230, 120, 29, 0,memsize );
      //FTImpl.Cmd_Text(295, 120, 29, 0, "bajtow");

      //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //FTImpl.Cmd_Number(165, 160, 29, 0,random(0,999999999) );


      //if(drawadlo > 15)
      //{
      //int loopsik = 0;//25 kropek
      //for(loopsik = 0; loopsik < 35;loopsik++)
      //{
		//FTImpl.ColorRGB(random(0,255),random(0,255),random(0,255));
        //FTImpl.Cmd_Text(110 + random(0,200), 175 + random(0,50), 31, 0, ".");
      //}
      //drawadlo = 0;
      //}
      //drawadlo++;



       //if(gStartAUTO == true)
      //{
		 //colorr += 25;
		  //FTImpl.ColorRGB(colorr,0,0);
		///* rysuje my kropkę jak włączony */
		//FTImpl.PointSize(12 * 12);
		//FTImpl.Begin(FT_POINTS);
		//FTImpl.Vertex2f(1260, 4100);
		//FTImpl.End();
		//FTImpl.ColorRGB(0xFF,0x00,0x00);
		//FTImpl.Cmd_Text(10 ,244, 23,0, "AUTO:");
		 //if(colorr >= 255)
		//colorr = 0;
	  //}


      //FTImpl.GetTagXY(sTagxy);

	  //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      ////przycisk exit info
      //if (sTagxy.tag == dBnTagInfobExit)
      //{
		  //tagoption = FT_OPT_FLAT;
		  //FTImpl.Cmd_FGColor(0xFF0000);
	  //} else
	  //{
		  //FTImpl.Cmd_FGColor(0x000088);
		   //tagoption = 0;
	  //}
      //FTImpl.Tag(dBnTagInfobExit);
      //FTImpl.Cmd_Button(FT_DISPLAYWIDTH - 85, FT_DISPLAYHEIGHT- 50, 70, 40,  24,  tagoption,"EXIT");

      //FTImpl.DLEnd();
      //FTImpl.Finish();

	  ////Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
	  //gTimer.update_by_ID(gTempSensorEvent);
	  //gTimer.update_by_ID(gCzasProcesuEvent);
	  //gTimer.update_by_ID(gProcessEvent);
	 //// gTimer.update_by_ID(gWykresTempEvent);
	  //gTimer.update_by_ID(gAwariaDSTempEvent);
	  //gTimer.update_by_ID(gSystemBackupEvent);
	  ////gTimer.update_by_ID(gSendTOEspEvent);



	  //Sound_Play(random(0,255),180,random(0,255));


    //}while(sTagxy.tag != dBnTagInfobExit);

    //delay(250);
    //Sound_Play(0x14,100,108);

//}



bool SD_LoadConfig(String& filename)
{
	  uint8_t* src_param = (uint8_t*)&gParametryPracy;

	  File root;
      File plik_re;//O_WRITE | O_CREAT | O_TRUNC
      root = SD.open("/");
      root.rewindDirectory();
	  plik_re = SD.open(filename.c_str(), FILE_READ);
	  if(plik_re)//jeśli plik istnieje wczytujemy:
	  {
		//read file
		for(unsigned int cntr = 0; cntr < sizeof(gParametryPracy);cntr++)
		{
		  src_param[cntr] = plik_re.read();
		}
		plik_re.close();
	 	root.close();
	 	InfoScreen(500,31,200,120,"OK");
	 	return true;
      }else
      {
		InfoScreen(1000,31,140,110,"File error!");

      }
      root.close();
      return false;
}


void SD_DeleteALLFiles()
{
	  File root;
      File plik;
      root = SD.open("/");
      root.rewindDirectory();
	  if(TakNie(60,60,30,"Czy usunac wszystkie ?") == true)
	  {
		  while (true)
		  {
			plik =  root.openNextFile();
			if (! plik) break;

			if(plik.isDirectory() == false)
			{
			 SD.remove(plik.name());
			}
			plik.close();
		  }
      }
	 root.close();
}




void SD_DisplayALLFiles()
{
	
	
	  sTagXY sTagxy;
	  uint8_t colorr = 0;
      int numAllFiles = 0;

      String string_Array[files_array_size];

      File root;
      File plik;

      root = SD.open("/");
      root.rewindDirectory();

	  while (true)
	  {
		plik =  root.openNextFile();
		if (! plik)
		{
		  plik.rewindDirectory(); // no more files
		  break;
		}

		//if(plik.isDirectory() == false)
	//	{
		 string_Array[numAllFiles] = String(plik.name());
		
		//}
        numAllFiles++;
		plik.close();
		if(numAllFiles >= files_array_size)	break;//więcej nie wczytujemy
	  }

	 root.close();

	 bool refresh = false;

     do
     {
      int tagoption = 0;

      //refresh file list
      if(refresh == true)
	  {
		root = SD.open("/");
		root.rewindDirectory();
		numAllFiles = 0;

    	  while (true)
		  {
			plik =  root.openNextFile();
			if (! plik)
			{
			 plik.rewindDirectory();
			 break;
			}
			if(plik.isDirectory() == false)
			{
			 string_Array[numAllFiles] = String(plik.name());
		     numAllFiles++;
			}

			plik.close();
			if(numAllFiles >= files_array_size)	break;//więcej nie wczytujemy

		  }
   	    root.close();
	    refresh = false;
	  }

     gParametryPracy.gNR_Okna = 14;

     FTImpl.DLStart();

     FTImpl.ClearColorRGB(0,35,50);
     FTImpl.Clear(1,1,1);
     FTImpl.Cmd_BGColor(0x00234C);

    // FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);

     FTImpl.ColorRGB(0xFF,0xFF,0x00);
     FTImpl.Cmd_Text(130 , 0, 28, 0, "Wszystkie pliki:");


     FTImpl.ColorRGB(0x00,0xFF,0x00);
     int y = 40;
     int x = 5;
      for(int liczor = 0;liczor < numAllFiles;liczor++)
       {
	      FTImpl.Cmd_Text(x, y, 22,  0,string_Array[liczor].c_str() );
		 y += 20;
		 if(liczor == 8)
		 {
			 y = 0;
			 x += 30;
		 }
       }

       if(gStartAUTO == true)
      {
		 colorr+=25;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1260, 4100);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(10 ,244, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }


      FTImpl.GetTagXY(sTagxy); // Pobieramy X,Y,TAG

      // Jesli wykryto tag KASUJ
      if (sTagxy.tag == 77)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(77);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(300, 210, 80, 50,  30,  tagoption,"Clear");


      // Jesli wykryto tag TAK
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(405, 210, 60, 50,  30,  tagoption,flashtext(50));

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();

	  if(sTagxy.tag == 77)
	  {
		  delay(400);
		  Sound_Play(0x14,100,108);
		  SD_DeleteALLFiles();
		  numAllFiles = 0;
          refresh = true;
	  }

        //gTimer.update_by_ID(gPwr1TimerEvent);
        //gTimer.update_by_ID(gPwr2TimerEvent);
	    //Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
		gTimer.update_by_ID(gTempSensorEvent);
		gTimer.update_by_ID(gCzasProcesuEvent);
		gTimer.update_by_ID(gProcessEvent);
		//gTimer.update_by_ID(gWykresTempEvent);
		gTimer.update_by_ID(gAwariaDSTempEvent);
		gTimer.update_by_ID(gSystemBackupEvent);
		//gTimer.update_by_ID(gSendTOEspEvent);

       Receive_Struct();

    }while(sTagxy.tag != dBnTagTak);

	delay(400);
    Sound_Play(0x14,100,108);

}



// gSendTOEspEvent = gTimer.every(2000,SendDatoToESP);
void WIFI_SendDataToESP()
{
//	Serial.println(sizeof(ET_send_struct)); 
 	ETout.sendData();
}


void SD_DeleteFile(String& filename)
{
		if(SD.remove(filename.c_str()) == true)
		{
			InfoScreen(500,31,190,120,"OK");
		}else
		{
			InfoScreen(500,31,140,120,"Error");
		}
}


void SD_DisplayFile(String& filename)
{
	
	
	  sTagXY sTagxy;
	  gParametryPracySTR params;
	  uint8_t* src_param = (uint8_t*)&params;
	  uint8_t colorr = 0;


	  File plik_re;
	  plik_re = SD.open(filename.c_str(), FILE_READ);
	  if(plik_re == false)
	  {
		  delay(1);
      }
      {   //read file
		  for(unsigned int cntr = 0; cntr < sizeof(params);cntr++)
		  {
			  src_param[cntr] = plik_re.read();
		  }
      }
	  plik_re.close();


      int gon_godziny = 0;
	  int minutt = 0;
	  int reszta_min = 0;


	  for(unsigned int cntr = 0;cntr < params.gCzasGonu;cntr++)
	  {
		if(minutt == 60)
		{
		 gon_godziny++;
		 minutt = 0;
		}
		 minutt++;
	  }

	  reszta_min = params.gCzasGonu - (gon_godziny * 60);


     do
     {
      int tagoption = 0;
      
      gParametryPracy.gNR_Okna = 15;

      FTImpl.DLStart();

      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);

      //FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);

      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(90 , 0, 28, 0, filename.c_str());


      String datetime(params.gStartAutoDateTime.year);
      datetime += "-";
      datetime += params.gStartAutoDateTime.month;
      datetime += "-";
      datetime += params.gStartAutoDateTime.day;
      datetime += "-";
      datetime += params.gStartAutoDateTime.hour;
      datetime += "-";
      datetime += params.gStartAutoDateTime.minute;
      datetime += "-";
      datetime += params.gStartAutoDateTime.second;


      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(280 , 0, 23, 0, datetime.c_str() );


      
      //czas trwania
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 50, 23, 0, "Calkowity czas:" );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(150, 50, 23, 0, params.gCzasProcesuGodz );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(170, 50, 23, 0, flashtext(86) );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(185, 50, 23, 0, params.gCzasProcesuMin );
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(210, 50, 23, 0, flashtext(86) );
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(230, 50, 23, 0, params.gCzasProcesuSek );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 70, 23, 0, "Rozgrzewanie:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 70, 23, 0, params.gCzasRozgrzewania );
      FTImpl.Cmd_Text(190, 70, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 90, 23, 0, "Zalewanie:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 90, 23, 0, params.gCzasZalewania );
      FTImpl.Cmd_Text(190, 90, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 110, 23, 0, "Stabilizacja:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 110, 23, 0, params.gCzasStabilizacji );
      FTImpl.Cmd_Text(190, 110, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 130, 23, 0, flashtext(107) );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 130, 23, 0, params.gCzasPrzedgonu );
      FTImpl.Cmd_Text(190, 130, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 150, 23, 0, "Gon:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(65, 150, 23, 0, gon_godziny );
      FTImpl.Cmd_Text(100, 150, 23, 0, "godz" );
      FTImpl.Cmd_Number(165, 150, 23, 0, reszta_min );
      FTImpl.Cmd_Text(190, 150, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 170, 23, 0, "PoGon:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 170, 23, 0, params.gCzasPogonu );
      FTImpl.Cmd_Text(190, 170, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 190, 23, 0, "Chlodzenie:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 190, 23, 0, params.gCzasChlodzenia );
      FTImpl.Cmd_Text(190, 190, 23, 0, flashtext(90) );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 210, 23, 0, "Chistereza:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(190, 210, 23, 0, "st C" );
      dtostrf(params.gHisterezaTemperatury, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(130 ,210 , 23,0, TempCharBuffer);

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 230, 23, 0, "Moc Gonu G1:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 230, 23, 0, params.gMocGonuG1 );
      FTImpl.Cmd_Text(190, 230, 23, 0, "jm" );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(0, 248, 23, 0, "Moc Gonu G2:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(150, 248, 23, 0, params.gMocGonuG2 );
      FTImpl.Cmd_Text(190, 248, 23, 0, "jm" );


      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 30, 23, 0, "Z Gon:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(390, 30, 23, 0, params.gZaworGonCntr );


      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 50, 23, 0, "TempDnia:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      dtostrf(params.gTempDnia, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(390 ,50 , 23,0, TempCharBuffer);


      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 70, 23, 0, "Ukonczono:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      if(params.gKoniec == true)
      {
		FTImpl.Cmd_Text(390 ,70 , 23,0, flashtext(46));
	  }else
	  {
	    FTImpl.Cmd_Text(390 ,70 , 23,0, flashtext(47));
	  }

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 90, 23, 0, "Moc Stb G1:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(400, 90, 23, 0, params.gMocStabilizacjiG1 );
      FTImpl.Cmd_Text(435, 90, 23, 0, "jm" );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 110, 23, 0, "Moc Stb G2:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(400, 110, 23, 0, params.gMocStabilizacjiG2 );
      FTImpl.Cmd_Text(435, 110, 23, 0, "jm" );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 130, 23, 0, "Moc Zal G1:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(400, 130, 23, 0, params.gMocZalaniaG1 );
      FTImpl.Cmd_Text(435, 130, 23, 0, "jm" );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 150, 23, 0, "Moc Zal G2:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(400, 150, 23, 0, params.gMocZalaniaG2 );
      FTImpl.Cmd_Text(435, 150, 23, 0, "jm" );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 170, 23, 0, "Moc PzG G1:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(400, 170, 23, 0, params.gMocPrzedgonuG1 );
      FTImpl.Cmd_Text(435, 170, 23, 0, "jm" );

      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Text(277, 190, 23, 0, "Moc PzG G2:" );
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Number(400, 190, 23, 0, params.gMocPrzedgonuG2 );
      FTImpl.Cmd_Text(435, 190, 23, 0, "jm" );

       if(gStartAUTO == true)
      {
		 colorr+=25;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1100, 180);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(0 ,0, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }



      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.GetTagXY(sTagxy);

	  tagoption = 0;
      // Jesli wykryto tag TAK
      if (sTagxy.tag == dBnTagTak)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(dBnTagTak);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(415, 220, 50, 40,  28,  tagoption,flashtext(50));


      tagoption = 0;
      // Jesli wykryto tag DELETE
      if (sTagxy.tag == 76)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(76);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(360, 220, 50, 40,  28,  tagoption,"Del");

      tagoption = 0;
      // Jesli wykryto tag LOAD
      if (sTagxy.tag == 77)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(77);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(293, 220, 60, 40,  28,  tagoption,"Load");

	  //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      FTImpl.DLEnd();
      FTImpl.Finish();


      //SD Delete
	   if(sTagxy.tag ==  76)
       {
		   delay(300);
		   if(TakNie(60,60,30,"Czy usunac ten plik ?") == true)
		   {
			 Sound_Play(0x14,100,108);
			 SD_DeleteFile(filename);
			 break;

		   }else
		   {
			 Sound_Play(0x14,100,108);
		   }
	   }

	   //SD LOAD
	   if(sTagxy.tag == 77)
       {
		   delay(300);
		   if(TakNie(60,60,30,"Czy zaladowac ten plik ?") == true)
		   {
			 Sound_Play(0x14,100,108);
			 SD_LoadConfig(filename);

		   }else
		   {
			 Sound_Play(0x14,100,108);
		   }
	   }

        //gTimer.update_by_ID(gPwr1TimerEvent);
        //gTimer.update_by_ID(gPwr2TimerEvent);
	   //Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
		gTimer.update_by_ID(gTempSensorEvent);
		gTimer.update_by_ID(gCzasProcesuEvent);
		gTimer.update_by_ID(gProcessEvent);
	//	gTimer.update_by_ID(gWykresTempEvent);
		gTimer.update_by_ID(gAwariaDSTempEvent);
		gTimer.update_by_ID(gSystemBackupEvent);
		//gTimer.update_by_ID(gSendTOEspEvent);
 

        Receive_Struct();

    }while(sTagxy.tag != dBnTagTak);

	delay(400);
	Sound_Play(0x14,100,108);

}

//Obsługa SD-------------------------------
void SD_card()
{
	  sTagXY sTagxy;
	  uint8_t colorr = 0;

	  unsigned int numAllFiles = 0;
      unsigned int numConfFiles = 0;

      String string_Array[files_array_size];

      File root;
      File plik;

      root = SD.open("/");
      root.rewindDirectory();

	  while (true)
	  {
		plik =  root.openNextFile();
		if (! plik)
		{
		 plik.rewindDirectory();
		 break;
		}

		if(plik.isDirectory() == false)
		{
			 if( String(plik.name()).substring(String(plik.name()).indexOf(".")) == String(".BCG") )//.bcg
			 {
			  string_Array[numConfFiles] = String(plik.name());
			  numConfFiles++;
			 }
		 numAllFiles++;
		}
		plik.close();
		if(numConfFiles >= files_array_size)
			break;

	  }

	 root.close();
	 bool refresh = false;


     do //screen loop
     {
      int tagoption = 0;

      //refresh file list
      if(refresh == true)
	  {
		root = SD.open("/");
		root.rewindDirectory();
	   	  while (true)
		  {
			plik =  root.openNextFile();
			if (! plik)
			{
			 plik.rewindDirectory();
			 break;
			}
			if(plik.isDirectory() == false)
			{
				 if( String(plik.name()).substring(String(plik.name()).indexOf(".")) == String(".BCG") )//.bcg
				 {
				  string_Array[numConfFiles] = String(plik.name());
				  numConfFiles++;
				 }
			 numAllFiles++;
			}
			plik.close();
			if(numConfFiles >= files_array_size)	break;
		  }
   	    root.close();
	    refresh = false;
	   }

      gParametryPracy.gNR_Okna = 16;

      FTImpl.DLStart();
      //FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x888888);

      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);

      FTImpl.ColorRGB(0xFF,0xFF,0x00); // Ustawiamy kolor zolty (R,G,B)
      FTImpl.Cmd_Text(160 , 0, 28, 0, "Pamiec karty:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);

       if(gStartAUTO == true)
      {
		 colorr+=25;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1260, 4100);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(10 ,244, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }


      FTImpl.GetTagXY(sTagxy); // Pobieramy X,Y,TAG

      int tages = 0;
      int y = 40;
      int x = 5;
      for(unsigned int liczor = 0;liczor < numConfFiles;liczor++)
       {

		 if (sTagxy.tag == liczor + 1)
		 {
		   tages = FT_OPT_FLAT;
		   FTImpl.Cmd_FGColor(0xFF0000);
		  } else
		  {
		   FTImpl.Cmd_FGColor(0x000088);
		   tages = 0;
	      }

		   FTImpl.Tag(liczor + 1);
		   FTImpl.ColorRGB(0xFF,0xFF,0xFF);
		   FTImpl.Cmd_Button(x, y, 100, 25,  21,  tages,string_Array[liczor].c_str() );
		 if(liczor == 5)
		 {
		  x = 120;
		  y = 5;
	     }
		 if(liczor == 11)
		 {
		  x = 230;
		  y = 5;
	     }
	     if(liczor == 15)
		 {
		  x = 340;
		  y = 5;
	     }
	     y += 35;
       }


	  tagoption = 0;
      // Jesli wykryto tag TAK
      if (sTagxy.tag == 78)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(78);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(405, 210, 60, 50,  30,  tagoption,flashtext(50));

      tagoption = 0;
      // Jesli wykryto tag ALL
      if (sTagxy.tag == 77)
      {
        tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x000088);
      FTImpl.Tag(77);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Button(310, 210, 80, 50,  30,  tagoption,"Pliki");
      
      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();
      FTImpl.Finish();



	   for(unsigned int liczor = 0;liczor < numConfFiles;liczor++)
       {
		if(sTagxy.tag ==  liczor + 1)
        {
			delay(400);
			Sound_Play(0x14,100,108);
			SD_DisplayFile(string_Array[liczor]);
			numAllFiles = 0;
            numConfFiles = 0;
			refresh = true;
	    }
	   }


       if(sTagxy.tag == 77)
       {
		delay(500);
		Sound_Play(0x14,100,108);
		SD_DisplayALLFiles();
		numAllFiles = 0;
        numConfFiles = 0;
		refresh = true;
	   }




       //gTimer.update_by_ID(gPwr1TimerEvent);
       //gTimer.update_by_ID(gPwr2TimerEvent);
	   //Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
		gTimer.update_by_ID(gTempSensorEvent);
		gTimer.update_by_ID(gCzasProcesuEvent);
		gTimer.update_by_ID(gProcessEvent);
		//gTimer.update_by_ID(gWykresTempEvent);
		gTimer.update_by_ID(gAwariaDSTempEvent);
		gTimer.update_by_ID(gSystemBackupEvent);
		//gTimer.update_by_ID(gSendTOEspEvent);

        Receive_Struct();

    }while(sTagxy.tag != 78);

    delay(400);
    Sound_Play(0x14,100,108);

}



//WIFI SCREEN---->
void WIFI()
{
	 ClearScreen(255, 255, 255);
	
     sTagXY sTagxy;
     int tagoption = 0;
     uint8_t colorr = 0;
     uint8_t colorr2 = 0;
     int Xpos = 0;
     int loopLock = 0;
              
     String StempStr;

     do
     {
      gParametryPracy.gNR_Okna = 19;
      
      FTImpl.DLStart();
      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);

      
       if(gStartAUTO == true)
      {
		 colorr += 25;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1260, 4100);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(10 ,244, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }


      //WIFI
      colorr2+=3;
	  if(colorr2 >= 255)
	  colorr2 = 0; 
      
      if(loopLock > 7)
	  {
		  loopLock = 0;
		  Xpos+=5;
		  if(Xpos > 100)
		  Xpos = 0;
	  }
      
      //FTImpl.ColorRGB(0x1E,0xD1,0xB0);//#1ED1B0
      if(gCzyWIFI_IS_Conected == true) 
      { 
		FTImpl.ColorRGB(0,colorr2 - 35 ,colorr2);  
	    FTImpl.Cmd_Text(320, 120, 30, 0, "WIFI ON" );
	    FTImpl.ColorRGB(0xFF,0xFF,0x80);
	    FTImpl.Cmd_Text(320 + Xpos, 70, 31, 0, ">" );
	  }else
	  {
		FTImpl.ColorRGB(0xFF,0x93,0x00);//  #FF9300
		FTImpl.Cmd_Text(320, 120, 30, 0, "WIFI OFF" );
	  }
  
      //itoa(gParametryPracy_RCV.gESP_MILLIS,TempCharBuffer,10);	
      dtostrf(gParametryPracy_RCV.gESP_MILLIS, 13, 0, TempCharBuffer);
      FTImpl.Cmd_Text(280 ,190 , 22,0, TempCharBuffer);
	  
	  if(gParametryPracy_RCV.gWIFI_MODE == 0)
	  {
	   FTImpl.ColorRGB(0xFF,0x00,0x00); 	  
	   itoa(gParametryPracy_RCV.gWIFI_RSSI,TempCharBuffer,10);	  
	   FTImpl.Cmd_Text(323 ,160, 24,0, TempCharBuffer);
	   FTImpl.ColorRGB(0x00,0xFF,0x00); 	  
	   FTImpl.Cmd_Text(373, 160, 24, 0, " dBm" );
      }
       

      FTImpl.GetTagXY(sTagxy);
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      
      FTImpl.Cmd_Text(5, 180, 22, 0, flashtext(71));
      FTImpl.Cmd_Text(5, 200, 22, 0, flashtext(72));
      
      FTImpl.ColorRGB(0x00,0x8D,0xFF);
      
      FTImpl.Cmd_Text(75, 228, 21, 0, "Reset WIFI--->");
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
           
      FTImpl.Cmd_Text(5, 75, 23, 0, "Adres IP:");
      
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      
      if(gCzyWIFI_IS_Conected == true) 
      { 
        StempStr = String(String(gParametryPracy_RCV.ip1) + "." + String(gParametryPracy_RCV.ip2) + "." + String(gParametryPracy_RCV.ip3) + "." + String(gParametryPracy_RCV.ip4) );
        FTImpl.Cmd_Text(115, 75, 23, 0, StempStr.c_str());
      
		  if(gParametryPracy_RCV.gWIFI_MODE == 1)
		  {
			FTImpl.ColorRGB(0xFF,0xFF,0x00);    
			FTImpl.Cmd_Text(5, 55, 23, 0, flashtext(103));  
			FTImpl.ColorRGB(0xFF,0x00,0x00);
			FTImpl.Cmd_Text(110, 55, 23, 0, flashtext(158));
		  }else if(gParametryPracy_RCV.gWIFI_MODE == 0)
		  {
			FTImpl.ColorRGB(0xFF,0xFF,0x00);  
			FTImpl.Cmd_Text(5, 55, 23, 0, flashtext(103));   
			FTImpl.ColorRGB(0xFF,0x00,0x00);
			FTImpl.Cmd_Text(115, 55, 23, 0, flashtext(159));  
		  }else if(gParametryPracy_RCV.gWIFI_MODE == 2)
		  {
			FTImpl.ColorRGB(0xFF,0xFF,0x00);  
			FTImpl.Cmd_Text(5, 55, 23, 0, flashtext(103));   
			FTImpl.ColorRGB(0xFF,0x00,0x00);
			FTImpl.Cmd_Text(115, 55, 23, 0, flashtext(160));  
		  }
   
          FTImpl.ColorRGB(0x00,0xFF,0x00);
          FTImpl.Cmd_Text(115 , 5, 23, 0, gParametryPracy_RCV.gSSID );
          FTImpl.Cmd_Text(115 , 28, 23, 0, gParametryPracy_RCV.gPASS );  
     
      }
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(5 , 5, 23, 0, flashtext(156) );
      FTImpl.Cmd_Text(5 , 28, 23, 0, flashtext(157) );
      
      
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //przycisk Connect to wifi
      if (sTagxy.tag == 12)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  FTImpl.Cmd_FGColor(0x000088);
		   tagoption = 0;
	  }
      FTImpl.Tag(12);
      FTImpl.Cmd_Button(20, 110, 110, 50,  29,  tagoption,"STATION");
      
      //przycisk Create network
      if (sTagxy.tag == 13)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  FTImpl.Cmd_FGColor(0x000088);
		   tagoption = 0;
	  }
      FTImpl.Tag(13);
      FTImpl.Cmd_Button(170, 110, 110, 50,  29,  tagoption,"AP");
   
   
   

	  FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //przycisk exit info
      if (sTagxy.tag == dBnTagInfobExit)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  FTImpl.Cmd_FGColor(0x000088);
		   tagoption = 0;
	  }
      FTImpl.Tag(dBnTagInfobExit);
      FTImpl.Cmd_Button(395, 222, 70, 40,  24,  tagoption,flashtext(52));




      FTImpl.ColorRGB(0x00,0xFF,0x00);
      //przycisk SEVE config
      if (sTagxy.tag == 15)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  FTImpl.Cmd_FGColor(0x000088);
		   tagoption = 0;
	  }
      FTImpl.Tag(15);
      FTImpl.Cmd_Button(285, 222, 80, 40,  24,  tagoption,flashtext(56));
      // SWIDTH    480 SHEIGHT   272
      
      
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      //przycisk RST
      if (sTagxy.tag == 16)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  FTImpl.Cmd_FGColor(0x000088);
		   tagoption = 0;
	  }
      FTImpl.Tag(16);
      FTImpl.Cmd_Button(170 , 222 , 80, 40,  24,  tagoption,"RST");
	 
      
      
          

      //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }


      FTImpl.DLEnd();
      FTImpl.Finish();
      
      loopLock++;

	  //MENU ACTIONS:
      switch(sTagxy.tag)
      {
		 case 12://STATION
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
		   
		   String stringol;
		   InputText(stringol,"Nazwa sieci:",20,30);
		   for(unsigned int cntr = 0;cntr < sizeof(gParametryPracy.gSSID);cntr++)
		   {
			 gParametryPracy.gSSID[cntr] = stringol[cntr];
		   }
		   stringol = "";
		   InputText(stringol,"Haslo:",20,30);
		   for(unsigned int cntr = 0;cntr < sizeof(gParametryPracy.gPASS);cntr++)
		   {
			 gParametryPracy.gPASS[cntr] = stringol[cntr];
		   }
		   gParametryPracy.gWIFI_MODE = 0;
		  
		   
		  break;
		 }
		 case 13://AP
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
		   
		   String stringol;
		   InputText(stringol,"Nazwa sieci:",12,30);
		   for(unsigned int cntr = 0;cntr < sizeof(gParametryPracy.gSSID);cntr++)
		   {
			 gParametryPracy.gSSID[cntr] = stringol[cntr];
		   }
		   stringol = "";
		   InputText(stringol,"Haslo:",12,30);
		   for(unsigned int cntr = 0;cntr < sizeof(gParametryPracy.gPASS);cntr++)
		   {
			 gParametryPracy.gPASS[cntr] = stringol[cntr];
		   }
		   gParametryPracy.gWIFI_MODE = 1;
		   
		  break;
		 }      
		 
	     case 15://SAVE
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
		   SaveToEprom();
		   break;
	     }
	     
	     case 16://RST
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
		   gParametryPracy.g2560ToESP_order = 1;  //RST
		   	   
		   
		   break;
	     }
	 }
	  
	  
		//gTimer.update_by_ID(gPwr1TimerEvent);
		//gTimer.update_by_ID(gPwr2TimerEvent);
	//Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
	gTimer.update_by_ID(gTempSensorEvent);
	gTimer.update_by_ID(gCzasProcesuEvent);
	gTimer.update_by_ID(gProcessEvent);
	//gTimer.update_by_ID(gWykresTempEvent);
	gTimer.update_by_ID(gAwariaDSTempEvent);
	gTimer.update_by_ID(gSystemBackupEvent);
	//gTimer.update_by_ID(gSendTOEspEvent);
	
	
	Receive_Struct();  

    
    }while(sTagxy.tag != dBnTagInfobExit);

    delay(250);
    Sound_Play(0x14,100,108);

}




void Menu()
{
	  ClearScreen(255, 255, 255);
	  ClearScreen(255, 255, 255);
	  ClearScreen(255, 255, 255);
	  ClearScreen(255, 255, 255);
	
      sTagXY sTagxy;
      int tagoption = 0;
      uint8_t colorr = 0;
      uint8_t colorr_napisu = 0;
      bool upp = true;
      int frame_skip = 0;
      int posx[16] = {0};
      int posy[16] = {0};
      int sizex[16] = {0};
      int sizey[16] = {0};
      uint8_t cR[16] = {0};
      uint8_t cG[16] = {0};
      uint8_t cB[16] = {0};
     
     
     do
     {
		 
	  gParametryPracy.gNR_Okna = 11;
	   	 
      FTImpl.DLStart();
      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      
        
      FTImpl.Cmd_BGColor(0x00234C);
   
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      long RGB;// = ((long)random(0,255) << 16L) | ((long)random(0,255) << 8L) | (long)random(0,255);
	  //FTImpl.ColorRGB(RGB);
      FTImpl.Cmd_Text(10, 0, 29, 0, flashtext(69));
      
      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(200, 5, 22, 0, flashtext(70));


      if(upp == true)
      {
	   colorr_napisu += 5;
        if(colorr_napisu >= 255)
		 upp = false;
      }else
      {
		colorr_napisu -= 5;
        if(colorr_napisu <= 0)
		 upp = true;
	  }

      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(185 , 45, 31, 0, "MENU");


	  //Display time
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(10 , 30, 21, 0, gParametryPracy.CurrentDateTime.hour);
      FTImpl.Cmd_Text(27 , 30, 21, 0, flashtext(86));
      FTImpl.Cmd_Number(32 , 30, 21, 0, gParametryPracy.CurrentDateTime.minute);
      FTImpl.Cmd_Text(50, 30, 21, 0, flashtext(86));
      FTImpl.Cmd_Number(56 , 30, 21, 0, gParametryPracy.CurrentDateTime.second);
      FTImpl.Cmd_Text(79, 30, 21, 0, flashtext(87));
      FTImpl.Cmd_Number(90 , 30, 21, 0, gParametryPracy.CurrentDateTime.day);
      FTImpl.Cmd_Text(110, 30, 21, 0, flashtext(87));
      FTImpl.Cmd_Number(115 , 30, 21, 0, gParametryPracy.CurrentDateTime.month);
      FTImpl.Cmd_Text(136, 30, 21, 0, flashtext(87));
      FTImpl.Cmd_Number(144 , 30, 21, 0, gParametryPracy.CurrentDateTime.year);
      
      FTImpl.Cmd_Text(345, 217, 21, 0, "Mem: ");
      FTImpl.Cmd_Number(390 , 217, 21, 0, gFreeMemory);

      //przyciski
      FTImpl.ColorA(255);
      FTImpl.Cmd_BGColor(0x402000);

	  FTImpl.GetTagXY(sTagxy);

      tagoption = 0;
      FTImpl.Tag(dBnTagStart);
      if (sTagxy.tag == dBnTagStart)
      {
		tagoption = FT_OPT_FLAT;
		FTImpl.ColorRGB(0xFF,0xFF,0x00);
        FTImpl.Cmd_FGColor(0xFF0000);
       } else
       {
		 FTImpl.ColorRGB(0xFF,0xFF,0xFF);
		 //mrygający guzik PULPIT
		 //long RGB = ((long)R << 16L) | ((long)G << 8L) | (long)B;
		 RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		 FTImpl.Cmd_FGColor(RGB);
	   }


      FTImpl.Cmd_GradColor(0xffFFFF);
      FTImpl.Cmd_Button(40, 100,  115, 80,  24,  tagoption,flashtext(92));
      FTImpl.Cmd_Text(70, 106, 22, 0, flashtext(93));
      FTImpl.Cmd_Text(54, 155, 22, 0, flashtext(94));


      FTImpl.ColorRGB(0xFF,0xFF,0xFF);


	  tagoption = 0;
      if (sTagxy.tag == dBnTagConfig)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x1b7d25);
      FTImpl.Tag(dBnTagConfig);
      FTImpl.Cmd_GradColor(0xffffff);
      FTImpl.Cmd_Button(186, 100,  115, 80,  24,  tagoption,flashtext(95));
      FTImpl.Cmd_Text(200, 155, 22, 0, flashtext(96));

      tagoption = 0;
      if (sTagxy.tag == dBnTagReset)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0xFF840D);
      FTImpl.Tag(dBnTagReset);
      FTImpl.Cmd_GradColor(0xffffFF);
      FTImpl.Cmd_Button(330, 100,  115, 80,  24,  tagoption,flashtext(97));
      FTImpl.Cmd_Text(341 ,155, 22, 0, flashtext(98));


      //przywrócenie z BEKAPu systemu
      tagoption = 0;
      if (sTagxy.tag == 77)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x0D46FF);
      FTImpl.Tag(77);
      FTImpl.Cmd_GradColor(0xffffFF);
      FTImpl.Cmd_Button(186, 197,  115, 60,  24,  tagoption,flashtext(99));
      FTImpl.Cmd_Text(199 ,236, 21, 0, flashtext(100));
      
      //WIFI
      tagoption = 0;
      if (sTagxy.tag == 88)
      {
		tagoption = FT_OPT_FLAT;
        FTImpl.Cmd_FGColor(0xFF0000);
      } else  FTImpl.Cmd_FGColor(0x0D46FF);
      FTImpl.Tag(88);
      FTImpl.Cmd_GradColor(0xffffFF);
      FTImpl.Cmd_Button(40, 197,  115, 60,  24,  tagoption,flashtext(101));
      FTImpl.Cmd_Text(54 ,236, 21, 0, flashtext(102));


	  ////INFO
      //tagoption = 0;
      //if (sTagxy.tag == dBnTagInfo)
      //{
		//tagoption = FT_OPT_FLAT;
        //FTImpl.Cmd_FGColor(0xFF0000);
      //} else  FTImpl.Cmd_FGColor(0x101020);
      //FTImpl.Tag(dBnTagInfo);
      //FTImpl.Cmd_GradColor(0xffffff);
      //FTImpl.Cmd_Button(330, 197,  115, 60,  24,  tagoption,"INFO");
      
      if(gStartAUTO == true)
      {
		 colorr+=25;
		  FTImpl.ColorRGB(colorr,0,0);
		/* rysuje my kropkę jak AUTO włączony */
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(1260, 1000);
		FTImpl.End();
		FTImpl.ColorRGB(0xFF,0x00,0x00);
		FTImpl.Cmd_Text(10 ,50, 23,0, flashtext(49));
		 if(colorr >= 255)
		colorr = 0;
	  }
	  
	  //TOUCH wake UP
	  if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }

      
       
      if(frame_skip > 25)
      {
	   int bubu = 0;	  
	   for(bubu = 0;bubu < 15;bubu++)
	   {
		  cR[bubu] = 0;
		  cG[bubu] = random(110,255);
		  cB[bubu] = 0; 
		  FTImpl.ColorRGB(cR[bubu],cG[bubu],cB[bubu]);
		  
		  posx[bubu]  =  360 + random(0,70);
		  posy[bubu]  =  35  + random(0,70);
		  
		  sizex[bubu] =  random(0,15);
		  sizey[bubu] =  random(0,15);
		  
		 // randnumber[bubu] = random(0,15);
		  
		  
		  DrawPoint2(posx[bubu],posy[bubu],sizex[bubu],sizey[bubu]);
	   }
       frame_skip = 0;
      }else
      {
	   int bubu = 0;	  
	   for(bubu = 0;bubu < 15;bubu++)
	   {
		 FTImpl.ColorRGB(cR[bubu],cG[bubu],cB[bubu]);
		 DrawPoint2(posx[bubu],posy[bubu],sizex[bubu],sizey[bubu]);
		 FTImpl.ColorRGB(255,255,255);
		 //FTImpl.Cmd_Number(posx[bubu] + 3, posy[bubu] - 3, 19, 0, randnumber[bubu] );
		 //FTImpl.Cmd_Text(posx[bubu] + 3 ,posy[bubu] - 3,21,0, randomletter[bubu]);
	   } 
	  }
  
      frame_skip++;
      
      FTImpl.DLEnd();
      FTImpl.Finish();


      //MENU ACTIONS:
      switch(sTagxy.tag)
      {
		 case dBnTagConfig://CONFIG
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
		   AA_Config();
		  break;
		 }
		 case dBnTagReset: //SD
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
	       SD_card();
		  break;
		 }
		 case dBnTagInfo: //INFO
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
	       //Info();
		  break;
		 }
		 case 77: //BACKUPU
		 {
		   delay(300);
		   if(TakNie(80,60,30,"Czy zaladowac bekap ?") == true)
		   {
			 Sound_Play(0x14,100,108);
			 String FileName("backup.bcg");
			 if(SD_LoadConfig(FileName) == true)
			 {
			  
			  if(gParametryPracy.gEtap == 5)
			  if(TakNie(80,60,30,"Czy wlaczyc MAN ?") == true)
			  {
				  SetValveOFF(ZaworGonu);
				  SetValveOFF(ZaworGonu2);
				  AA_Manual();
			  }
			  Auto_wznowienie();
			  gStartAUTO = true; //uruchomic AUTOMAT jak się da?
		     }
		   }else
		   {
			 Sound_Play(0x14,100,108);
		   }

		  break;
		 }
		 case 88: //INFO
		 {
		   delay(350);
		   Sound_Play(0x14,100,108);
	       WIFI();
		  break;
		 }
	 }


        //gTimer.update_by_ID(gPwr1TimerEvent);
        //gTimer.update_by_ID(gPwr2TimerEvent);
		gTimer.update_by_ID(gTempSensorEvent);
		gTimer.update_by_ID(gCzasProcesuEvent);
		gTimer.update_by_ID(gProcessEvent);
		//gTimer.update_by_ID(gWykresTempEvent);
		gTimer.update_by_ID(gAwariaDSTempEvent);
		gTimer.update_by_ID(gSystemBackupEvent);
		//gTimer.update_by_ID(gSendTOEspEvent);
		
		Receive_Struct();

    }while(sTagxy.tag != dBnTagStart);

     delay(350);
	 Sound_Play(0x14,100,108);

 }



////STATUS SCREEN
//void StatusScreen()
//{
	    ////------------------------------------------
	    ////1)  Czas procesu destylacji
		////2)  Czas odbioru gonu
		////3)  Czas odbioru z EZ1
		////4)  Czas odbioru z EZ2
		////4)  Czas rozgrzewania beczki
		////5)  Czas zalewania
		////6)  TemDnia
		////7)  EZ gonu 1 (ile razy się otworzył)
		////8)  EZ gonu 2 (ile razy się otworzył)
		////9)  EZ gonu 1 (przy jakiej tem się zamknął)
		////10) EZ gonu 2 (przy jakiej tem się zamknął)
		////-------------------------------------------- 
	
	  //sTagXY sTagxy;
	
	  //int gon_godziny = 0;
	  //int minutt = 0;
	  //int reszta_min = 0;


	  //for(int cntr = 0;cntr < gParametryPracy.gCzasGonu;cntr++)
	  //{
		//if(minutt == 60)
		//{
		 //gon_godziny++;
		 //minutt = 0;
		//}
		 //minutt++;
	  //}

	  //reszta_min = gParametryPracy.gCzasGonu - (gon_godziny * 60);

     //do
     //{
      //int tagoption = 0;
      
      //gParametryPracy.gNR_Okna = 17;

      //FTImpl.DLStart();

      //FTImpl.ClearColorRGB(0,35,50);
      //FTImpl.Clear(1,1,1);
      //FTImpl.Cmd_BGColor(0x00234C);

      //FTImpl.ColorRGB(0xFF,0xFF,0x00); // Ustawiamy kolor zolty (R,G,B)
      //FTImpl.Cmd_Text(100 , 0, 28, 0, "Stan procesu:");

      //String datetime(gParametryPracy.gStartAutoDateTime.year);
      //datetime += "-";
      //datetime += gParametryPracy.gStartAutoDateTime.month;
      //datetime += "-";
      //datetime += gParametryPracy.gStartAutoDateTime.day;
      //datetime += "-";
      //datetime += gParametryPracy.gStartAutoDateTime.hour;
      //datetime += "-";
      //datetime += gParametryPracy.gStartAutoDateTime.minute;
      //datetime += "-";
      //datetime += gParametryPracy.gStartAutoDateTime.second;

      //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //FTImpl.Cmd_Text(260 , 0, 23, 0, datetime.c_str() );

      ////nickname
      //FTImpl.ColorRGB(0xFF,0xFF,0x00);
      //FTImpl.Cmd_Text(0 , 20, 23, 0, "Ksywa:" );
      //FTImpl.Cmd_Text(100 , 20, 23, 0, gParametryPracy.gKsywka );

      ////czas trwania
      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 50, 23, 0, "Calkowity czas:" );
      //FTImpl.ColorRGB(0xFF,0x00,0x00);
      //FTImpl.Cmd_Number(150, 50, 23, 0, gParametryPracy.gCzasProcesuGodz );
      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(170, 50, 23, 0, ":" );
      //FTImpl.ColorRGB(0xFF,0x00,0x00);
      //FTImpl.Cmd_Number(185, 50, 23, 0, gParametryPracy.gCzasProcesuMin );
      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(210, 50, 23, 0, ":" );
      //FTImpl.ColorRGB(0xFF,0x00,0x00);
      //FTImpl.Cmd_Number(230, 50, 23, 0, gParametryPracy.gCzasProcesuSek );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 70, 23, 0, "Rozgrzewanie:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 70, 23, 0, gParametryPracy.gCzasRozgrzewania );
      //FTImpl.Cmd_Text(190, 70, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 90, 23, 0, "Zalewanie:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 90, 23, 0, gParametryPracy.gCzasZalewania );
      //FTImpl.Cmd_Text(190, 90, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 110, 23, 0, "Stabilizacja:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 110, 23, 0, gParametryPracy.gCzasStabilizacji );
      //FTImpl.Cmd_Text(190, 110, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 130, 23, 0, "Przedgon:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 130, 23, 0, gParametryPracy.gCzasPrzedgonu );
      //FTImpl.Cmd_Text(190, 130, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 150, 23, 0, "Gon:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(57, 150, 23, 0, gon_godziny );
      //FTImpl.Cmd_Text(92, 150, 23, 0, "godz" );
      //FTImpl.Cmd_Number(150, 150, 23, 0, reszta_min );
      //FTImpl.Cmd_Text(190, 150, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 170, 23, 0, "PoGon:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 170, 23, 0, gParametryPracy.gCzasPogonu );
      //FTImpl.Cmd_Text(190, 170, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 190, 23, 0, "Chlodzenie:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 190, 23, 0, gParametryPracy.gCzasChlodzenia );
      //FTImpl.Cmd_Text(190, 190, 23, 0, "min" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 210, 23, 0, "Chistereza:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Text(190, 210, 23, 0, "st C" );
      //dtostrf(gParametryPracy.gHisterezaTemperatury, 6, 2, TempCharBuffer);
      //FTImpl.Cmd_Text(130 ,210 , 23,0, TempCharBuffer);

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 230, 23, 0, "Moc Gonu G1:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 230, 23, 0, gParametryPracy.gMocGonuG1 );
      //FTImpl.Cmd_Text(190, 230, 23, 0, "jm" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(0, 248, 23, 0, "Moc Gonu G2:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(150, 248, 23, 0, gParametryPracy.gMocGonuG2 );
      //FTImpl.Cmd_Text(190, 248, 23, 0, "jm" );


      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 30, 23, 0, "Z Gon:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 30, 23, 0, gParametryPracy.gZaworGonCntr );


      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 50, 23, 0, "TempDnia:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //dtostrf(gParametryPracy.gTempDnia, 6, 2, TempCharBuffer);
      //FTImpl.Cmd_Text(390 ,50 , 23,0, TempCharBuffer);


      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 70, 23, 0, "Ukonczono:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //if(gParametryPracy.gKoniec == true)
      //{
		//FTImpl.Cmd_Text(400 ,70 , 23,0, "TAK");
	  //}else
	  //{
	    //FTImpl.Cmd_Text(400 ,70 , 23,0, "NIE");
	  //}

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 90, 23, 0, "Moc Stb G1:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 90, 23, 0, gParametryPracy.gMocStabilizacjiG1 );
      //FTImpl.Cmd_Text(435, 90, 23, 0, "jm" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 110, 23, 0, "Moc Stb G2:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 110, 23, 0, gParametryPracy.gMocStabilizacjiG2 );
      //FTImpl.Cmd_Text(435, 110, 23, 0, "jm" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 130, 23, 0, "Moc Zal G1:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 130, 23, 0, gParametryPracy.gMocZalaniaG1 );
      //FTImpl.Cmd_Text(435, 130, 23, 0, "jm" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 150, 23, 0, "Moc Zal G2:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 150, 23, 0, gParametryPracy.gMocZalaniaG2 );
      //FTImpl.Cmd_Text(435, 150, 23, 0, "jm" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 170, 23, 0, "Moc PzG G1:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 170, 23, 0, gParametryPracy.gMocPrzedgonuG1 );
      //FTImpl.Cmd_Text(435, 170, 23, 0, "jm" );

      //FTImpl.ColorRGB(0x00,0xFF,0x00);
      //FTImpl.Cmd_Text(277, 190, 23, 0, "Moc PzG G2:" );
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Number(400, 190, 23, 0, gParametryPracy.gMocPrzedgonuG2 );
      //FTImpl.Cmd_Text(435, 190, 23, 0, "jm" );


      //FTImpl.ColorRGB(0x00,0xFF,0x00);

      //FTImpl.GetTagXY(sTagxy); // Pobieramy X,Y,TAG

	  //tagoption = 0;
      //// Jesli wykryto tag TAK
      //if (sTagxy.tag == dBnTagTak)
      //{
        //tagoption = FT_OPT_FLAT;
        //FTImpl.Cmd_FGColor(0xFF0000);
      //} else  FTImpl.Cmd_FGColor(0x000088);
      //FTImpl.Tag(dBnTagTak);
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Button(420, 228, 40, 35,  28,  tagoption,"OK");

      //tagoption = 0;
      //// Jesli wykryto tag dBnTagConfigSaveSD
      //if (sTagxy.tag == dBnTagConfigSaveSD)
      //{
        //tagoption = FT_OPT_FLAT;
        //FTImpl.Cmd_FGColor(0xFF0000);
      //} else  FTImpl.Cmd_FGColor(0x000088);
      //FTImpl.Tag(dBnTagConfigSaveSD);
      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //FTImpl.Cmd_Button(365, 228, 40, 35,  28,  tagoption,"SD");

      //FTImpl.DLEnd();
      //FTImpl.Finish();


      ////SD SAVE
	   //if(sTagxy.tag ==  dBnTagConfigSaveSD)
       //{
		   //delay(300);
		   //if(TakNie(60,60,30,"Czy zapisac na karcie SD ?") == true)
		   //{
			 //Sound_Play(0x14,100,108);
			 //SD_save_conf();
		   //}else
		   //{
			 //delay(300);
			 //Sound_Play(0x14,100,108);
			 //InfoScreen(600,31,100,110,"Nie zapisales !");
		   //}
	   //}

	   ////Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
	   //gTimer.update_by_ID(gTempSensorEvent);
	   //gTimer.update_by_ID(gCzasProcesuEvent);
	   //gTimer.update_by_ID(gProcessEvent);
	  //// gTimer.update_by_ID(gWykresTempEvent);
	   //gTimer.update_by_ID(gAwariaDSTempEvent);
	   //gTimer.update_by_ID(gSystemBackupEvent);
	   ////gTimer.update_by_ID(gSendTOEspEvent);

    //}while(sTagxy.tag != dBnTagTak);

	//Sound_Play(0x14,100,108);
    //delay(480);
//}



//void CreateRandomFile()
//{
   //String filename;
   //int ass = 0;
   //for(ass = 0;ass < 8;ass++)
   //{
	 //filename += random(0,9);
   //}
   
   //filename += ".bcg";
   
  
   //uint8_t* src = (uint8_t*)&gParametryPracy;
   
  //// File root;
   //File plik_wr;//O_WRITE | O_CREAT | O_TRUNC
  //// root = SD.open("/");
  //// root.rewindDirectory();
	
	
	//plik_wr = SD.open(filename.c_str(), FILE_WRITE);
	//if (plik_wr == true)//czy udało się otworzyc plik do zapisu ?
	//{
	 //plik_wr.seek(0); 
	 //plik_wr.write(src, sizeof(gParametryPracy)); //write whole structure to file
	 //plik_wr.close();
	 //InfoScreen(500,31,100,110,filename.c_str());
	//// InfoScreen(100,31,160,120,"SAVE OK");
	//} else
	//{
	//// InfoScreen(100,31,100,110,"File error!");
	//}
	////root.close();

 
//}



void SD_BACKUP_conf()
{
		if(gStartAUTO == true)
		{
			uint8_t* src = (uint8_t*)&gParametryPracy;
			String filename = "backup.bcg";
			File root;
            File plik_wr;//O_WRITE | O_CREAT | O_TRUNC
            root = SD.open("/");
            root.rewindDirectory();
			plik_wr = SD.open(filename.c_str(), FILE_WRITE);
			if (plik_wr == true)//czy udało się otworzyc plik do zapisu ?
			{
			 plik_wr.seek(0); 
			 plik_wr.write(src, sizeof(gParametryPracy)); //write whole structure to file
			 plik_wr.close();
			 //InfoScreen(500,31,160,120,"SAVE OK");
			 Serial.println(F("Backup CONFIG OK"));
			} else
			{
			 //InfoScreen(1000,31,100,110,"File error!");
			 Serial.println(F("Backup CONFIG ERROR!"));
			}
			root.close();
	    }
	    
   gFreeMemory = MemsizeBytes();
	    
}



void AA_MENU()
{
	 ClearScreen(255, 255, 255);
	
     sTagXY sTagxy;
     int tagoption = 0;
     uint8_t colorr = 0;
     uint8_t colorr2 = 0;
     uint8_t colorr_napisu = 0;
     bool upp = true;
           
     do
     {
      
      Receive_Struct();
      
      gParametryPracy.gNR_Okna = 1;

      FTImpl.DLStart();
      FTImpl.ClearColorRGB(0,35,50);
      FTImpl.Clear(1,1,1);
      FTImpl.Cmd_BGColor(0x00234C);
      
     
      //opis temperatur:
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Text(5,5, 28,0,flashtext(0));
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(5,25, 28,0,  flashtext(1));
      FTImpl.ColorRGB(0xFF,0xB6,0x00);//#FFB600
      FTImpl.Cmd_Text(5,45, 28,0,  flashtext(2));
      FTImpl.ColorRGB(0x00,0x00,0xFF);
      FTImpl.Cmd_Text(5,65, 28,0,  flashtext(3));
      FTImpl.ColorRGB(0xFF,0x00,0xF1);//#FF00F1
      FTImpl.Cmd_Text(5,85, 28,0,  flashtext(4));
      
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(5,120, 29,0, flashtext(5));

      
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,30, 27,0, flashtext(6));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      if(gParametryPracy.gZaworWoda == true)
			FTImpl.Cmd_Text(360,30, 27,0, flashtext(7));
			else FTImpl.Cmd_Text(360,30, 27,0, flashtext(8));


      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,50, 27,0, flashtext(9));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      if(gParametryPracy.gZaworPrzedGon == true)
			FTImpl.Cmd_Text(360,50, 27,0, flashtext(7));
			else FTImpl.Cmd_Text(360,50, 27,0, flashtext(8));


      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,70, 27,0, flashtext(10));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      if(gParametryPracy.gZaworGonu == true)
			FTImpl.Cmd_Text(360,70, 27,0, flashtext(7));
			else FTImpl.Cmd_Text(360,70, 27,0, flashtext(8));

	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,90, 27,0, flashtext(11));
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      if(gParametryPracy.gZaworGonu2 == true)
			FTImpl.Cmd_Text(360,90, 27,0, flashtext(7));
			else FTImpl.Cmd_Text(360,90, 27,0, flashtext(8));



	  //G3	
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(360,110, 27,0, flashtext(17));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      if(gParametryPracy.gPowerPWR3 == true)
      {
	     FTImpl.Cmd_Text(390,110, 27,0, flashtext(7));//40
	  }else
	  {
		 FTImpl.Cmd_Text(390,110, 27,0, flashtext(8));
	  }


      Receive_Struct();

	  //G1
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,110, 27,0, flashtext(15));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      if(gParametryPracy.gPowerPWR1 == true)
      {

		  switch( gParametryPracy.gEtap )
		  {
			case 1://rozgrzewanie
				FTImpl.Cmd_Text(270,110, 27,0, flashtext(7));
		        FTImpl.Cmd_Number(320, 110 , 27, 0, 255 );
				break;

			case 2://zalewanie

				if(gParametryPracy.gPrzerwaPoZalaniu == false)
				{
				  FTImpl.Cmd_Text(270,110, 27,0, flashtext(7));
		          FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocZalaniaG1 );
			    }else
			    {
				  FTImpl.Cmd_Text(270,110, 27,0, flashtext(8));
				  FTImpl.Cmd_Number(320, 110 , 27, 0, 0 );
				}
				break;


			case 3://stabilizacja
				FTImpl.Cmd_Text(270,110, 27,0, flashtext(7));
		        FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocStabilizacjiG1 );
				break;

			case 4://przedgon
				FTImpl.Cmd_Text(270,110, 27,0, flashtext(7));

				if(gParametryPracy.gStabPrzedgon == true)
				{
				  FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocGonuG1 );
			    }else
			    {
				  FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocPrzedgonuG1 );
				}
				break;

			case 5://gon

				FTImpl.Cmd_Text(270,110, 27,0, flashtext(7));
				if(gParametryPracy.gDrugaMocGonu == false)
				{
				 FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocGonuG1 );
			    }else
			    {
			     FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocGonu2_G1 );
				}
				break;

			//default:
			//    FTImpl.Cmd_Text(270,110, 27,0, "ON");
			//	FTImpl.Cmd_Number(320, 110 , 27, 0, gParametryPracy.gMocZadanaG1 );
			//break;
			}//end switch

	   }else
	   {
		   FTImpl.Cmd_Text(270,110, 27,0, flashtext(8));
		   FTImpl.Cmd_Number(320, 110 , 27, 0, 0 );
	   }

      Receive_Struct();

	  //G2
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,130, 27,0, flashtext(16));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      if(gParametryPracy.gPowerPWR2 == true)
      {

		  switch( gParametryPracy.gEtap )
		  {
			case 1://rozgrzewanie
				FTImpl.Cmd_Text(270,130, 27,0, flashtext(7));
		        FTImpl.Cmd_Number(320, 130 , 27, 0, 255 );
				break;

			case 2://zalewanie
				if(gParametryPracy.gPrzerwaPoZalaniu == false)
				{
				  FTImpl.Cmd_Text(270,130, 27,0, flashtext(7));
		          FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocZalaniaG2 );
			    }else
			    {
				  FTImpl.Cmd_Text(270,130, 27,0, flashtext(8));
				  FTImpl.Cmd_Number(320, 130 , 27, 0, 0 );
				}
				break;


			case 3://stabilizacja
				FTImpl.Cmd_Text(270,130, 27,0, flashtext(7));
		        FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocStabilizacjiG2 );
				break;

			case 4://przedgon
				FTImpl.Cmd_Text(270,130, 27,0, flashtext(7));
				if(gParametryPracy.gStabPrzedgon == true)
				{
				  FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocGonuG2 );
			    }else
			    {
				  FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocPrzedgonuG2 );
				}
				break;

			case 5://gon
				FTImpl.Cmd_Text(270,130, 27,0, flashtext(7));
				if(gParametryPracy.gDrugaMocGonu == false)
				{
				 FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocGonuG2 );
			    }else
			    {
			     FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocGonu2_G2 );
				}
				break;
			//default:
			//    FTImpl.Cmd_Text(270,130, 27,0, "ON");
			//	FTImpl.Cmd_Number(320, 130 , 27, 0, gParametryPracy.gMocZadanaG2 );
			//break;

			}//end switch
	   }else
	   {
		   FTImpl.Cmd_Text(270,130, 27,0, flashtext(8));
		   FTImpl.Cmd_Number(320, 130 , 27, 0, 0 );
	   }


      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(230,146,22,0, "CCP:");
      FTImpl.ColorRGB(0x00,0xFF,0x00);
      FTImpl.Cmd_Number(280, 146 , 22, 0, gParametryPracy.gCzasProcesuTotalSek );

	  //dane z czujnika poziom-zalania na ekran-->
	  //zmienna globalna to: gPoziomZalania
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
      FTImpl.Cmd_Text(360,130, 27,0, flashtext(30));
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      FTImpl.Cmd_Number(423, 130 , 27, 0, gParametryPracy.gPoziomZalania );


      //Display temperatures
      FTImpl.ColorRGB(0xFF,0x00,0x00);
      dtostrf(gParametryPracy.gTempKolumna, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(112 ,5, 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0xFF,0xFF,0x00);
      dtostrf(gParametryPracy.gTempBeczka, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(112 ,25 , 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0xFF,0xB6,0x00);
      dtostrf(gParametryPracy.gTempGlowica, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(112 ,45, 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0x88,0x88,0xFF);
      dtostrf(gParametryPracy.gTempWodaWy, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(112 ,65, 28,0, TempCharBuffer);
      FTImpl.ColorRGB(0xFF,0x00,0xF1);
      dtostrf(gParametryPracy.gTempBufor, 6, 2, TempCharBuffer);
      FTImpl.Cmd_Text(112 ,85, 28,0, TempCharBuffer);

      Receive_Struct();

      //moc
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(5, 142 , 28, 0, flashtext(31) );
    
      //rozgrzewanie
      if(gParametryPracy.gEtap == 1)
      {
         FTImpl.Cmd_Number(123, 142 , 28, 0, gParametryPracy.gCzasRozgrzewania );
         FTImpl.Cmd_Text(175, 142 , 28, 0, flashtext(12) );
	  }

	  //zalewanie
      if(gParametryPracy.gEtap == 2)
      {
         FTImpl.Cmd_Number(123, 142 , 28, 0, gParametryPracy.gCzasZalewania );
         FTImpl.Cmd_Text(175, 142 , 28, 0, flashtext(12) );
	  }

	  //zstabilizacja
      if(gParametryPracy.gEtap == 3)
      {
         FTImpl.Cmd_Number(123, 142 , 28, 0, gParametryPracy.gCzasStabilizacji );
         FTImpl.Cmd_Text(175, 142 , 28, 0, flashtext(12) );
	  }

	  //przedgonik
      if(gParametryPracy.gEtap == 4)
      {
         FTImpl.Cmd_Number(123, 142 , 27, 0, gParametryPracy.gCzasPrzedgonu );
         FTImpl.Cmd_Text(175, 142 , 27, 0, flashtext(12) );
	  }

	  //Gon
	  if(gParametryPracy.gEtap == 5)
      {
		  FTImpl.Cmd_Number(98, 142 , 28, 0, gParametryPracy.gCzasGonu / 60 );
          FTImpl.Cmd_Text(135, 142 , 28, 0, flashtext(73) );
          FTImpl.Cmd_Number(165, 142 , 28, 0, gParametryPracy.gCzasGonu % 60 );
          FTImpl.Cmd_Text(200, 142 , 28, 0, flashtext(12) );
          //12 = m  flashtext(73) = g
          
	  }

	  //pogon
      if(gParametryPracy.gEtap == 6)
      {
         FTImpl.Cmd_Number(123, 142 , 28, 0, gParametryPracy.gCzasPogonu );
         FTImpl.Cmd_Text(175, 142 , 28, 0, flashtext(12) );
	  }

	  //chlodzenie gł
      if(gParametryPracy.gEtap == 7)
      {
         FTImpl.Cmd_Number(123, 142 , 28, 0, gParametryPracy.gCzasChlodzenia );
         FTImpl.Cmd_Text(175, 142 , 28, 0, flashtext(12) );
	  }

      Receive_Struct();

	  //etapy
	  FTImpl.ColorRGB(0xFF,0xFF,0x00);
	  FTImpl.Cmd_Text(5, 163 , 28, 0, flashtext(32)  );
	  FTImpl.ColorRGB(0x00,0xFF,0x00);
	  FTImpl.Cmd_Number(65, 163 , 28, 0, gParametryPracy.gEtap );

	  if(gParametryPracy.gEtap == 1)
	  {
		  FTImpl.ColorRGB(0x12,0xFF,0x88);
		  FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(33) );
		  FTImpl.Cmd_Text(300,110, 20,0, flashtext(34));
		  FTImpl.Cmd_Text(300,130, 20,0, flashtext(34));
	  }


	  if(gParametryPracy.gEtap == 2)
	  {
		if(gParametryPracy.gPrzerwaPoZalaniu == false)
		{
		  FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(35) );
	    }else
	    {
		  FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(36) );
		}
	  }


	  if(gParametryPracy.gEtap == 3)
	  {
		  FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(37) );
	  }


	  if(gParametryPracy.gEtap == 4)
	  {
		  if(gParametryPracy.gStabPrzedgon == false)
		  {
			  FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(38) );
		  }else
		  {
			  FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(39) );
		  }
	  }


	  if(gParametryPracy.gEtap == 5) FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(40) );

	  if(gParametryPracy.gEtap == 6) FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(41) );

	  if(gParametryPracy.gEtap == 7) FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(42) );
	  
	  if(gParametryPracy.gEtap == 8) FTImpl.Cmd_Text(90, 163 , 28, 0, flashtext(43) );


	  //if(gStartAUTO == true || gStartMAN == true)
      //{
		///* rysuje my kropkę jak włączony */
		//FTImpl.ColorRGB(0xFF,0x00,0x00);
		//FTImpl.PointSize(144);
		//FTImpl.Begin(FT_POINTS);
		//FTImpl.Vertex2f(2200, 2320);
		//FTImpl.End();
	  //}

	    FTImpl.ColorRGB(0xFF,0xFF,0x00);
	    FTImpl.Cmd_Text(5, 192 , 23, 0, "ZG1:" );
	    FTImpl.ColorRGB(0x00,0xFF,0x00);
	    FTImpl.Cmd_Number(65, 192 , 23, 0, gParametryPracy.gZaworGonCntr );

	    FTImpl.ColorRGB(0xFF,0xFF,0x00);
	    FTImpl.Cmd_Text(5, 212 , 23, 0, "ZG2:" );
	    FTImpl.ColorRGB(0x00,0xFF,0x00);
	    FTImpl.Cmd_Number(65, 212 , 23, 0, gParametryPracy.gZaworGon2Cntr );


		//ZalanieX
		FTImpl.ColorRGB(0xFF,0xFF,0x00);
		FTImpl.Cmd_Text(150, 212 , 23, 0, flashtext(110) );
	    FTImpl.ColorRGB(0x00,0xFF,0x00);
	    FTImpl.Cmd_Number(240, 212 , 23, 0, gParametryPracy.gZalanieX );



		dtostrf(gParametryPracy.gTempDnia, 5, 2, TempCharBuffer);
		FTImpl.ColorRGB(0xFF,0x00,0xDE);
		FTImpl.Cmd_Text(225, 5 , 28, 0, flashtext(108) );
		FTImpl.ColorRGB(0x00,0xFF,0x00);
		FTImpl.Cmd_Text(355 ,5, 28,0, TempCharBuffer);
		
		FTImpl.ColorRGB(0x00,0xFF,0x00);

		//ETAPY 7
		//progresbar
		FTImpl.Cmd_Progress(15, 254, 360, 15, 0, gParametryPracy.gEtap * 1000, 8000);

		//ciśnienie HPA
		FTImpl.ColorRGB(0xFF,0xFF,0x00);
		FTImpl.Cmd_Text(145, 197 , 21, 0, flashtext(109) );
		FTImpl.ColorRGB(0x00,0xFF,0x00);
		FTImpl.Cmd_Number(240 , 197, 21, 0, gParametryPracy.gPresure);

        Receive_Struct();

		//FTImpl.Cmd_Text(230,130, 27,0, "G2:");
		//temp Alarma
        FTImpl.ColorRGB(0xFF,0x00,0x00);
        dtostrf(gParametryPracy.gTempAlarmu, 6, 2, TempCharBuffer);
        FTImpl.Cmd_Text(112 ,105, 22,0, TempCharBuffer);
        FTImpl.Cmd_Text(5 ,105, 22,0, "Alarm:");
        
	    //1CBFA5
	    FTImpl.ColorRGB(0x1C,0xBF,0xA5);
        FTImpl.Cmd_FGColor(0x000088);

	  //Display rtc time
	   FTImpl.Cmd_Number(5 , 232, 23, 0, gParametryPracy.CurrentDateTime.hour);
       FTImpl.Cmd_Text(27 , 232, 23, 0, flashtext(86));
       FTImpl.Cmd_Number(32 , 232, 23, 0, gParametryPracy.CurrentDateTime.minute);
       FTImpl.Cmd_Text(52, 232, 23, 0, flashtext(86));
       FTImpl.Cmd_Number(57 , 232, 23, 0, gParametryPracy.CurrentDateTime.second);
       FTImpl.Cmd_Text(84, 232, 23, 0, flashtext(87));
       FTImpl.Cmd_Number(92 , 232, 23, 0, gParametryPracy.CurrentDateTime.day);
       FTImpl.Cmd_Text(116, 232, 23, 0, flashtext(87));
       FTImpl.Cmd_Number(123 , 232, 23, 0, gParametryPracy.CurrentDateTime.month);
       FTImpl.Cmd_Text(145, 232, 23, 0, flashtext(87));
       FTImpl.Cmd_Number(155 , 232, 23, 0, gParametryPracy.CurrentDateTime.year);

       //current job time
       FTImpl.ColorRGB(0xFF,0xFF,0xFF);
       FTImpl.Cmd_Number(85, 120, 29, 0, gParametryPracy.gCzasProcesuGodz );
       FTImpl.ColorRGB(0x00,0xFF,0x00);
       FTImpl.Cmd_Text(113, 120, 29, 0, flashtext(86) );
       FTImpl.ColorRGB(0xFF,0xFF,0xFF);
       FTImpl.Cmd_Number(123, 120, 29, 0, gParametryPracy.gCzasProcesuMin );
       FTImpl.ColorRGB(0x00,0xFF,0x00);
       FTImpl.Cmd_Text(153, 120, 29, 0, flashtext(86) );
       FTImpl.ColorRGB(0xFF,0xFF,0xFF);
       FTImpl.Cmd_Number(175, 120, 29, 0, gParametryPracy.gCzasProcesuSek );

       
      //WIFI
      colorr2+=5;
	  if(colorr2 >= 255)
	  colorr2 = 0; 
      
      //FTImpl.ColorRGB(0x1E,0xD1,0xB0);//#1ED1B0
      if(gCzyWIFI_IS_Conected == true) 
      { 
		FTImpl.ColorRGB(0,colorr2 - 35 ,colorr2);  
	    FTImpl.Cmd_Text(317, 190, 21, 0, flashtext(13) );
	  }else
	  {
		FTImpl.ColorRGB(0x00,0xBE,0xFF);  //#00BEFF
		FTImpl.Cmd_Text(314, 190, 21, 0, flashtext(14) );
	  }

      
      
      
      FTImpl.GetTagXY(sTagxy);
      
      //FTImpl.ColorRGB(0xB4,0x00,0x00);
      //if( (sTagxy.x && sTagxy.y > 0)        &&
           //sTagxy.tag != dBnTagStartbExit   &&
           //sTagxy.tag != dBnTagStartbStartJ && 
           //sTagxy.tag != dBnTagStartbStartPWR )
      //{
      // DrawPoint2(sTagxy.x,sTagxy.y,25,25);
      // FTImpl.ColorRGB(0xFF,0x00,0x00);
      // DrawPoint2(sTagxy.x,sTagxy.y,12,12);
      ////FTImpl.PlaySound((((300 + 21) << 8) | random(0,75)));
      //}  
	  
	  FTImpl.ColorRGB(0xFF,0xFF,0xFF);

      FTImpl.ColorA(255);
      FTImpl.Cmd_BGColor(0x402000);

	  tagoption = 0;
      //przycisk exit to MENU
      FTImpl.Cmd_GradColor(0x000088);
      FTImpl.Cmd_BGColor(0x402000);
      if (sTagxy.tag == dBnTagStartbExit)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else{
		   FTImpl.Cmd_FGColor(0xee8f15);
		   tagoption = 0;
	  }
	  FTImpl.Tag(dBnTagStartbExit);
	  FTImpl.Cmd_GradColor(0xffffff);
      FTImpl.Cmd_Button(312, 210, 65, 37,  23,  tagoption,"MENU");

       if(upp == true)
      {
	   colorr_napisu += 5;
        if(colorr_napisu >= 255)
		 upp = false;
      }else
      {
		colorr_napisu -= 5;
        if(colorr_napisu <= 0)
		 upp = true;
	  }

      Receive_Struct();


      //przycisk START JOB 480 X 272
      if (sTagxy.tag == dBnTagStartbStartJ)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else
	  {
		  if(gStartAUTO == true)
          {
		   long RGB = ((long)colorr_napisu << 16L) | ((long)0 << 8L) | (long)0;
		   FTImpl.Cmd_FGColor(RGB);
		   //FTImpl.Cmd_FGColor(0x640000);
		   tagoption = 0;
	      }else
	      {
		   FTImpl.Cmd_FGColor(0x640000);
		   tagoption = 0; 
		  }
	  }
      FTImpl.Tag(dBnTagStartbStartJ);
      FTImpl.Cmd_Button(400,225 , 70, 40,  24,  tagoption,flashtext(68));

	  //KROPKA	
      if(gStartAUTO == true)//kropka
      {
		colorr+=25;
		FTImpl.ColorRGB(colorr,0,0);
		FTImpl.PointSize(12 * 12);
		FTImpl.Begin(FT_POINTS);
		FTImpl.Vertex2f(6400, 3630);
		FTImpl.End();
		 if(colorr >= 255)
		colorr = 0;

	  }

      //FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      ////przycisk WYKRESSSS
      //if (sTagxy.tag == 133)
      //{
		  //tagoption = FT_OPT_FLAT;
		  //FTImpl.Cmd_FGColor(0xFF0000);
	  //} else {
		  //FTImpl.Cmd_FGColor(0x3699be);
		  //tagoption = 0;
	  //}
      //FTImpl.Tag(133);
      //FTImpl.Cmd_Button(425,10 , 40, 40,  24,  tagoption,"W");


      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      //przycisk start --->    MANUAL
      if (sTagxy.tag == dBnTagStartbStartPWR)
      {
		  tagoption = FT_OPT_FLAT;
		  FTImpl.Cmd_FGColor(0xFF0000);
	  } else {
		  FTImpl.Cmd_FGColor(0x000088);
		  tagoption = 0;
	  }
      FTImpl.Tag(dBnTagStartbStartPWR);
      FTImpl.Cmd_Button(400,175 , 70, 40,  24,  tagoption,"MAN");


      FTImpl.ColorRGB(0xFF,0xFF,0xFF);


      //uint32_t ReadWord = FTImpl.Read32( REG_TOUCH_DIRECT_XY);
      //int16_t pendown = (int16_t)((ReadWord>>31) & 0x01); //0 - nacisniety | 1 - nie naciśnięty
      if(((int16_t)(( FTImpl.Read32( REG_TOUCH_DIRECT_XY) >>31) & 0x01)) == 0)
      {
		if(FTImpl.Read(REG_PWM_DUTY) < 1)
		  FTImpl.Write(REG_PWM_DUTY,127);
	  }
            
            
      //FTImpl.Cmd_Number(275, 200, 29, 0, FTImpl.Read(REG_PWM_DUTY)  );
      
          
            
      FTImpl.DLEnd();
      FTImpl.Finish();

      Receive_Struct();

      // MANUAL MANUAL MANUAL
      if(sTagxy.tag == dBnTagStartbStartPWR)
       {
		 delay(300);
		 Sound_Play(0x14,100,108);
		 
		// if(gStartAUTO == true)
		 //{
			 if(TakNie(60,60,30,"Czy wchodzisz w MANUAL ?") == true)
			 {
			   
			   Sound_Play(0x14,100,108);
			   AA_Manual();
			 }else
		     {
			   Sound_Play(0x14,100,108);
			   //AA_Manual();
		     }
	    
	    }


		//AUTOMATIC
       if(sTagxy.tag == dBnTagStartbStartJ)
       {
		   if(gStartAUTO == false)
		   {
			delay(300);
		    Sound_Play(0x14,100,108);
		    AutoStartProgress();
			AAc_0Asetup();
		   } else
		   {
			   delay(300);
			   if(TakNie(60,60,30,"Czy zatrzymac tryb auto ?") == true)
			   {
				AAc_dis_AUTO();
			   }
		   }
	   }


	   if(sTagxy.tag ==  dBnTagStartbExit)
       {
			delay(300);
			Sound_Play(0x14,100,108);
			Menu();
	   }

	   if(sTagxy.tag ==  133) //Graph
       {
			delay(300);
			Sound_Play(0x14,100,108);
			//Wykresy_Tmp();
	   }


	   ////Status screen
	   //if(sTagxy.tag ==  dBnTagStartbResetTime)
       //{
		   //delay(350);
		   //Sound_Play(0x14,100,108);
		   //StatusScreen();
	   //}

        
        //gTimer.update_by_ID(gPwr1TimerEvent);
        //gTimer.update_by_ID(gPwr2TimerEvent);
        
        
	  //Update timer gTempSensorEvent CzasProcesuEvent gProcessEvent
	  gTimer.update_by_ID(gTempSensorEvent);
	  gTimer.update_by_ID(gCzasProcesuEvent);
	  gTimer.update_by_ID(gProcessEvent);
	 // gTimer.update_by_ID(gWykresTempEvent);
	  gTimer.update_by_ID(gAwariaDSTempEvent);
	  gTimer.update_by_ID(gSystemBackupEvent);
	  //gTimer.update_by_ID(gSendTOEspEvent);
	  
	   Receive_Struct();
   
    }while(1);//forever

     delay(250);
     Sound_Play(0x14,100,108);
}

void ClearScreen(int r, int g, int b)
{
		FTImpl.DLStart();
		FTImpl.ClearColorRGB(r,g,b);
		FTImpl.Clear(1,1,1);
		FTImpl.DLEnd();
		FTImpl.Finish();
}


//INTRO
void IntroScreen()
{
	uint8_t rozzut = 128;
	uint8_t lop = 0;
	     
	//FTImpl.Writefromflash(FT_RAM_G,&RawData[p_bmhdr->Arrayoffset], p_bmhdr->Stride*p_bmhdr->Height);
	
	
	//FTImpl.DLStart();
     //Draw_Bitmap(20,126,(Bitmap_header_t *)&Lena40_Header[0],(const char*)&kotface);
    //FTImpl.DLEnd();
    //FTImpl.Finish();	     
	     
	for(lop = 0;lop < 128;lop++)
	{
      FTImpl.DLStart();
      //Draw_Bitmap(20,126,(Bitmap_header_t *)&Lena40_Header[0],(const char*)&kotface);
      //FTImpl.Cmd_BGColor(0xFF0000);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(110 + random(-rozzut,rozzut), 80 + random(-rozzut,rozzut), 31, 0, flashtext(18));
      FTImpl.Cmd_Text(180 + random(-rozzut,rozzut), 130 + random(-rozzut,rozzut), 21, 0, flashtext(19));
      FTImpl.Cmd_Text(166 + random(-rozzut,rozzut), 150 + random(-rozzut,rozzut), 21, 0, flashtext(20));
      FTImpl.Cmd_Text(170, 170, 21, 0, flashtext(21));
      FTImpl.DLEnd();
      FTImpl.Finish();
      delay(lop/4);
      FTImpl.PlaySound((((300 + 21) << 8) | random(0,75)));
      FTImpl.Write(REG_PWM_DUTY,lop);
      rozzut--;
    }
    for(lop = 0;lop < 60;lop++)
	{
      FTImpl.DLStart();
      //FTImpl.Cmd_BGColor(0xFF0000);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      FTImpl.Cmd_Text(110 + random(-1,1), 80 + random(-1,1), 31, 0, flashtext(18));
      FTImpl.Cmd_Text(180 + random(-1,2), 130 + random(-2,1), 21, 0, flashtext(19));
      FTImpl.Cmd_Text(166 + random(-1,1), 150 + random(-1,1), 21, 0, flashtext(20));
      FTImpl.Cmd_Text(170, 170, 21, 0, flashtext(21));
      FTImpl.DLEnd();
      FTImpl.Finish();
      delay(7);
    }
    delay(1500);
      
}

//INTRO test
void TestScreen()
{
	uint8_t lop = 0;
	for(lop = 0;lop < 112;lop++)
	{
      FTImpl.DLStart();
      FTImpl.Cmd_BGColor(0xFF0000);
      FTImpl.ColorRGB(0xFF,0xFF,0xFF);
      for(int lop2 = 0;lop2 < 100;lop2++)
      {
       DrawPoint(random(485),random(275),random(0,25),random(0,25),random(255),random(255),random(255));
      }
      FTImpl.DLEnd();
      FTImpl.Finish();
    }

}


static int16_t v() 
{
  return random(64)-32;
}



//Write to eprommem
void eepromWrite(uint16_t addr, void* input, uint16_t length)
{
    uint8_t* src;
    uint8_t* dst;
    src = (uint8_t*)input;
    dst = (uint8_t*)addr;
    for (uint16_t i = 0; i < length; i++)
    {
        eeprom_write_byte(dst++, *src++);
    }
}

void Akt_Temp() //5 czujników
{
	
	 
			
			//Odczyt temperatur wedle adresów
			gParametryPracy.gTempKolumna = sensors.getTempC(gTermo1);
			gParametryPracy.gTempBeczka  = sensors.getTempC(gTermo2);
			gParametryPracy.gTempGlowica = sensors.getTempC(gTermo3);
			gParametryPracy.gTempWodaWy  = sensors.getTempC(gTermo4);
			gParametryPracy.gTempAlarmu  = sensors.getTempC(gTermo5);
			gParametryPracy.gTempBufor   = sensors.getTempC(gTermo6);
 	

        // do testów-----------------------------------
        //gParametryPracy.gTempKolumna = random(20,50);
        //gParametryPracy.gTempBeczka  = random(20,50);
        //gParametryPracy.gTempGlowica = random(20,50);
        //gParametryPracy.gTempWodaWy  = random(20,50);
        //gParametryPracy.gTempAlarmu  = random(20,50);
        //---------------------------------------------
        //gParametryPracy.gTempBeczka  = 0;
        //gParametryPracy.gTempKolumna = 80;
        //gParametryPracy.gTempGlowica = 90;
        //gParametryPracy.gTempWodaWy  = 50;
        //gParametryPracy.gTempAlarmu  = random(20,50);
		//---------------------------------------------
		
		
		//ciśnienie
	    gParametryPracy.gPresure = 0; //presure.readPressure()/100;
			    
        WIFI_SendDataToESP();
        gParametryPracy.g2560ToESP_order = 0;
       
        
       
        sensors.requestTemperaturesnodelay();
        
        
        
        // Serial.println(gParametryPracy.gTempBeczka);
        
 
}

void Akt_Czas()
{
	 gParametryPracy.CurrentDateTime = RTclock.getDateTime();  //Get RTC date & time

	 Receive_Struct();

	 if(gStartAUTO == true && gStartMAN == false)
	 {
	  gParametryPracy.gLocal_timer.second++;

	  if(gParametryPracy.gLocal_timer.second == 60)
	  {
		gParametryPracy.gLocal_timer.minute++;
		gParametryPracy.gLocal_timer.second = 0;
	  }

	  if(gParametryPracy.gLocal_timer.minute == 60)
	  {
		gParametryPracy.gLocal_timer.hour++;
		gParametryPracy.gLocal_timer.minute = 0;
	  }

	  if(gParametryPracy.gLocal_timer.hour > 144)
	  {
		  gParametryPracy.gLocal_timer.hour   = 0; //jeśli przekorczy 144 zerujemy
		  gParametryPracy.gLocal_timer.minute = 0;
		  gParametryPracy.gLocal_timer.second = 0;
	  }

	 }

	   //********************************ASSXC
	  //local_timer.second
	  //local_timer.minute
	  //local_timer.hour
	  //(((((((((((((((((.)))))))))))))))))))))
	  
	  Receive_Struct();

	  gParametryPracy.gCzasProcesuMin  = gParametryPracy.gLocal_timer.minute;
	  gParametryPracy.gCzasProcesuGodz = gParametryPracy.gLocal_timer.hour;
	  gParametryPracy.gCzasProcesuSek  = gParametryPracy.gLocal_timer.second;

	  unsigned long calkowity_czas_min     = (gParametryPracy.gLocal_timer.hour * 60) + gParametryPracy.gLocal_timer.minute;
	  gParametryPracy.gCzasProcesuTotalMin = calkowity_czas_min;
	  gParametryPracy.gCzasProcesuTotalSek = (calkowity_czas_min * 60) + gParametryPracy.gLocal_timer.second;
	
	  Receive_Struct();
	  
	  String dataString = "";
	  int val = analogRead(CzujnikZalania);
	  dataString += String(val);
	  File dataFile = SD.open("log.txt", FILE_WRITE);
	  if (dataFile)
	  {
	   dataFile.print(String(gParametryPracy.gCzasProcesuGodz) + "." + String(gParametryPracy.gCzasProcesuMin) + "." + String(gParametryPracy.gCzasProcesuSek) + " ");
	   dataFile.println(dataString);
       dataFile.close();
	  }
      else
      {
        Serial.println("error opening log.txt");
      }
	  //print_work_time();
      //Serial.println(val);  
	  
}

// gParametryPracy.gSYS_LOG
void DataLog(String txt)
{
	File dataFile = SD.open("log.txt", FILE_WRITE);
	if (dataFile)
	{
	  dataFile.print(String(gParametryPracy.gCzasProcesuGodz) + "." + String(gParametryPracy.gCzasProcesuMin) + "." + String(gParametryPracy.gCzasProcesuSek) + " ");
	  dataFile.println(txt);
      dataFile.close();
	}
    else
    {
      Serial.println("error opening log.txt");
    }
}

void init_pins() //init pinis :)))
{
	 //POWER PIN MODE:
    // pinMode(PowerPWR1, OUTPUT);   //6
	 //pinMode(PowerPWR2, OUTPUT);   //8
	 
	// pinMode(GATE1, OUTPUT); 
	// pinMode(GATE2, OUTPUT);     
	 
	 
	 //pinMode(PowerPWR3, OUTPUT);   //9
	 setPwmF(PowerPWR1,5);
	 setPwmF(PowerPWR2,5);
	 setPwmF(PowerPWR3,5);
	 
	 # define PowerPWR1   	   6 G1    
	 # define PowerPWR2 		   8 G2
	 # define PowerPWR3 		   9 G3


	//This pins are together, can not modify frequency individually,same timmer):
	//pin 13, 4
	//pin 12, 11
	//pin 10, 9
	//pin 5, 3, 2
	//pin 8, 7, 6
	//For pins 13,4 (DO NOT MODIFY pins 13 & 4 is the one on which rely
	//all time functions in Arduino: i.e., if you change the frequency of this pins,
	//function like delay() or millis() will continue to work but at a different timescale
	//quicker or slower!))
    //Divisor 	        Frequency
    //1 62500 Hz
    //2 7812.5 Hz
    //3 976.5625 Hz  <--DEFAULT Diecimila bootloader
	//4 244.140625 Hz
	//5 61.03515625 Hz
	//For pins 2 to 13 EXCEPT 13,4:
	//Divisor 	 Frequency
	//1  31372.55 Hz
	//2	 3921.16  Hz
	//3	 490.20    Hz   <--DEFAULT Diecimila bootloader
	//4	 122.55    Hz
	//5	 30.610    Hz


	 //PIN 2 termometry DS18B20
	 
	 Serial.println(F("Inicjalizacja pinow...."));

     pinMode(ZaworWoda, OUTPUT);               //Z 1 Woda
     delay(500);
     SetValveOFF(ZaworWoda);
	 
     
     pinMode(ZaworPrzedGon, OUTPUT);           //Z 2 PrzedGon
     delay(500);
     SetValveOFF(ZaworPrzedGon);
	 
     
     pinMode(ZaworGonu, OUTPUT);               //ZaworGonu I
     delay(500);
	 SetValveOFF(ZaworGonu);
     
     pinMode(ZaworGonu2, OUTPUT);              //ZaworGonu II
     delay(500);
	 SetValveOFF(ZaworGonu2);
	 
	 
     //pinMode(CzujnikZalania, INPUT);             //Zalanie wejście: 0v min - 5v max
     //pinMode(ZasilanieCzujnikaZalania,OUTPUT); //Zasilanie czujnika zalania
     
     SetPowerOFF_1();
     delay(100);
	 SetPowerOFF_2();
	 delay(100);
	 SetPowerOFF_3();
	 delay(100);
	 
	
}

void init_RTC()
{
		  // UNIX timestamp
		  // clock.setDateTime(1397408400);
		  // Recznie (YYYY, MM, DD, HH, II, SS
		  // clock.setDateTime(2014, 4, 13, 19, 21, 00);

		  Serial.println(F("Pobrano czas od plytki RTC ...."));
		  RTclock.begin();

		  // Jeśli nie ustawiono daty, ustawiamy
		  if (!RTclock.isReady())
		  {
			Serial.println(F("Ustawienie czasu z kompilacji programu."));
			// Data i czas z momentu kompilacji
			RTclock.setDateTime(__DATE__, __TIME__);
		  }
		  // 1Hz
		  RTclock.setOutput(DS1307_1HZ);
		  //RTclock.setOutput(DS3231_1HZ);
}

void init_timers()
{
		  Serial.println(F("Inicjalizacja licznikow ...."));
		  
		  // 10(min) * 60 * 1000
		  //aktualizacja temperatur ustawiana z menu config normalnie co około 0,5 do 1 sek
		  //to jest 500  do 1000 milisekund ale jak kto chce tak ustawi
		  
		  gTempSensorEvent = gTimer.every(gParametryPracy.gTempUpdateTime, Akt_Temp);

		  //aktualizacja czasu odliczającego proces AUTO
		  gCzasProcesuEvent = gTimer.every(1000, Akt_Czas); //1 sek nie podlega zmianom

		  //aktualizacja algorytmu procesu	na oko:) 0,2 sekundy TERAS 0
		  gProcessEvent = gTimer.every(200,AAc_0AUTO);
		 
		  //aktualizacja sprawdzania czy DSy nie popadały co 15 sekund
		  gAwariaDSTempEvent = gTimer.every(10000,Akt_AwariaDS);

		  //Bekap systemu w razie awarii zasilania co 60 sekund to jest 1 minuty
		  gSystemBackupEvent = gTimer.every(60000,SD_BACKUP_conf);
		  
		  //gTempSensorEvent = gTimer.every(gParametryPracy.gTempUpdateTime, Akt_Temp);

}

void init_sd()
{
		 pinMode(SD_shield, OUTPUT);
		 Serial.println(F("Inicjalizacja karty SD ..."));
		 if (!SD.begin(SD_shield))
		 {
		    Serial.println(F("SD initialization failed comunication ERROR!"));
		    Serial.println(F("1"));
		    InfoScreen(1500,31,60,110,"Brak karty pamieci");
		    
		      if (!SD.begin(SD_shield))
		      {
				
			   Serial.println(F("SD initialization failed comunication ERROR!"));
			   Serial.println(F("2"));
		       InfoScreen(1500,31,60,110,"Brak karty pamieci");
			 	
			 	
					if (!SD.begin(SD_shield))
					{
					   Serial.println(F("SD initialization failed comunication ERROR!"));
					   Serial.println(F("3"));
					   InfoScreen(1500,31,60,110,"Brak karty pamieci");
					   return;
					
					}else
					{
					   Serial.println(F("Inicjalizacja karty SD OK."));
					   return;
					}
			
			  }else
			  {
				Serial.println(F("Inicjalizacja karty SD OK."));
				return;
			 }
		        
		    
		 }else
		 {
		  Serial.println(F("Inicjalizacja karty SD OK."));
		 }
}

void init_termo()
{
		 // Setup temp sensory
		  sensors.begin();
		  int deviceCount = sensors.getDeviceCount();

		  Serial.print(F("Znaleziono DS: "));
		  Serial.println(deviceCount);

		  Serial.println(F("Sprawdzenie termometrow...."));

			   if(sensors.isConnected(gTermo1))
			   {
				 Serial.println(F("1: DS18B20 OK"));
				 sensors.setResolution(gTermo1, gParametryPracy.gTEMPERATURE_PRECISION);
			   }else
			   {
			     Serial.println(F("Brak 1: DS18B20"));
			     InfoScreen(1000,31,65,110,"Brak 1: DS18b20");
			   }
			   if(sensors.isConnected(gTermo2))
			   {
				 Serial.println(F("2: DS18B20 OK"));
				 sensors.setResolution(gTermo2, gParametryPracy.gTEMPERATURE_PRECISION);
			   }else
			   {
			     Serial.println(F("Brak 2: DS18B20"));
			      InfoScreen(1000,31,65,110,"Brak 2: DS18b20");
			   }
			   if(sensors.isConnected(gTermo3))
			   {
				 Serial.println(F("3: DS18B20 OK"));
				 sensors.setResolution(gTermo3, gParametryPracy.gTEMPERATURE_PRECISION);
			   }else
			   {
			     Serial.println(F("Brak 3: DS18B20"));
			      InfoScreen(1000,31,65,110,"Brak 3: DS18b20");
			   }
			   if(sensors.isConnected(gTermo4))
			   {
				 Serial.println(F("4: DS18B20 OK"));
				 sensors.setResolution(gTermo4, gParametryPracy.gTEMPERATURE_PRECISION);
			   }else
			   {
			     Serial.println(F("Brak 4: DS18B20"));
			      InfoScreen(1000,31,65,110,"Brak 4: DS18b20");
			   }
			   if(sensors.isConnected(gTermo5))
			   {
				 Serial.println(F("5: DS18B20 OK"));
				 sensors.setResolution(gTermo5, gParametryPracy.gTEMPERATURE_PRECISION);
			   }else
			   {
			     Serial.println(F("Brak 5: DS18B20"));
			      InfoScreen(1000,31,65,110,"Brak 5: DS18b20");
			   }
			   if(sensors.isConnected(gTermo6))
			   {
				 Serial.println(F("6: DS18B20 OK"));
				 sensors.setResolution(gTermo5, gParametryPracy.gTEMPERATURE_PRECISION);
			   }else
			   {
			     Serial.println(F("Brak 6: DS18B20"));
			      InfoScreen(1000,31,65,110,"Brak 6: DS18b20");
			   }
		  sensors.setWaitForConversion(false);
		  //sensors.setCheckForConversion(false);
		  sensors.requestTemperaturesnodelay();
		  
		  //PRESURE BMP
		  //if (!presure.begin())
          //{
	       //Serial.println(F("Brak czujnika cisnienia! sprawdzic kable!"));
	       ////while (1) {}//zapętlenie się.........
          //}
}

void init_read_conf()
{
	  Serial.println(F("Wczytanie konfiguracji z eprom...."));
     
      eepromRead(0,&gParametryPracy,sizeof(gParametryPracy));
	 
	  //Serial.println(F("inicjalizacja zmiennych ...."));
	  Serial.print(F("OUT struct size: "));
	  Serial.print(sizeof(gParametryPracy));
	  Serial.println(" ");
	  
	  if(gParametryPracy.gStructID  != 12345)//29.04.2017 20:08:37 pitu house wifi old flash error
	    gParametryPracy.gStructID = 12345;
	 
 	  if(gParametryPracy.gMocMAN_G1 <= 0 || gParametryPracy.gMocMAN_G1 > 255)
		gParametryPracy.gMocMAN_G1 = 0;

	  if(gParametryPracy.gMocMAN_G2 <= 0 || gParametryPracy.gMocMAN_G2 > 255)
		gParametryPracy.gMocMAN_G2 = 0;

	  if(gParametryPracy.gMocZalaniaG1 <= 0 || gParametryPracy.gMocZalaniaG1 > 255)
		gParametryPracy.gMocZalaniaG1 = 0;

	  if(gParametryPracy.gMocGonu2_G1 <= 0 || gParametryPracy.gMocGonu2_G1 > 255)
		gParametryPracy.gMocGonu2_G1 = 0;

	  if(gParametryPracy.gMocGonu2_G2 <= 0 || gParametryPracy.gMocGonu2_G2 > 255)
		gParametryPracy.gMocGonu2_G2 = 0;

	  if(gParametryPracy.gTempZmianyMocyGonu < 0 || gParametryPracy.gTempZmianyMocyGonu > 155)
		gParametryPracy.gTempZmianyMocyGonu = 0;

	  if(gParametryPracy.gMocZalaniaG2 <= 0 || gParametryPracy.gMocZalaniaG2 > 255)
		gParametryPracy.gMocZalaniaG2 = 0;

	  if(gParametryPracy.gMocStabilizacjiG1 <= 0 || gParametryPracy.gMocStabilizacjiG1 > 255)
		gParametryPracy.gMocStabilizacjiG1 = 0;

	  if(gParametryPracy.gMocStabilizacjiG2 <= 0 || gParametryPracy.gMocStabilizacjiG2 > 255)
		gParametryPracy.gMocStabilizacjiG2 = 0;

	  if(gParametryPracy.gMocPrzedgonuG1 <= 0 || gParametryPracy.gMocPrzedgonuG1 > 255)
		gParametryPracy.gMocPrzedgonuG1 = 50;

	  if(gParametryPracy.gMocPrzedgonuG2 <= 0 || gParametryPracy.gMocPrzedgonuG2 > 255)
		gParametryPracy.gMocPrzedgonuG2 = 0;

	  if(gParametryPracy.gMocGonuG1 <= 0 || gParametryPracy.gMocGonuG1 > 255)
		gParametryPracy.gMocGonuG1 = 0;

	  if(gParametryPracy.gMocGonuG2 <= 0 || gParametryPracy.gMocGonuG2 > 255)
		gParametryPracy.gMocGonuG2 = 0;

	  if(gParametryPracy.gTempUpdateTime <= 0 || gParametryPracy.gTempUpdateTime > 30000)
	  	gParametryPracy.gTempUpdateTime = 1000;

	  if(gParametryPracy.gZadanyCzasOdbPrzedgonuMin <= 0 || gParametryPracy.gZadanyCzasOdbPrzedgonuMin > 600)
	  	gParametryPracy.gZadanyCzasOdbPrzedgonuMin = 0;
	  	
	  if(gParametryPracy.gZadanyCzasOdbPrzedgonuSek <= 0 || gParametryPracy.gZadanyCzasOdbPrzedgonuSek > 600)
	  	gParametryPracy.gZadanyCzasOdbPrzedgonuSek = 0;	

	  if(gParametryPracy.gZadanyCzasZalewania <= 0 || gParametryPracy.gZadanyCzasZalewania > 100)
	  	gParametryPracy.gZadanyCzasZalewania = 0;

	  if(gParametryPracy.gZadanyCzasPrzerwyMocyZalania <= 0 || gParametryPracy.gZadanyCzasPrzerwyMocyZalania > 1000)
	  	gParametryPracy.gZadanyCzasPrzerwyMocyZalania = 0;

	  if(gParametryPracy.gZadanyCzasChlodzenia <= 0 || gParametryPracy.gZadanyCzasChlodzenia > 100)
	  	gParametryPracy.gZadanyCzasChlodzenia = 0;

	  if(gParametryPracy.gZadanyCzasStabilizacji <= 0 || gParametryPracy.gZadanyCzasStabilizacji > 250)
	  	gParametryPracy.gZadanyCzasStabilizacji = 0;

	  if(gParametryPracy.gZadanyCzasStabPrzedgonu  <= 0 || gParametryPracy.gZadanyCzasStabPrzedgonu  > 200)
	  	gParametryPracy.gZadanyCzasStabPrzedgonu  = 0;

	  if(gParametryPracy.gHisterezaTemperatury < 0 || gParametryPracy.gHisterezaTemperatury > 25)
	  	gParametryPracy.gHisterezaTemperatury = 0;

	  if(gParametryPracy.gTempStopPogonu < 0 || gParametryPracy.gTempStopPogonu > 125)
	  	gParametryPracy.gTempStopPogonu = 0;

	  if(gParametryPracy.gTempStartPogonu  < 0 || gParametryPracy.gTempStartPogonu  > 125)
	  	gParametryPracy.gTempStartPogonu  = 0;

 	  gParametryPracy.gTempDnia = 0;
 	  gParametryPracy.gPoziomZalania = 0;

 	  if(gParametryPracy.gTEMPERATURE_PRECISION  < 9 || gParametryPracy.gTEMPERATURE_PRECISION  > 12)
	  	gParametryPracy.gTEMPERATURE_PRECISION  = 12;

	  if(gParametryPracy.gSoundVolume  <= 0 || gParametryPracy.gSoundVolume  >= 255)
	  	gParametryPracy.gSoundVolume  = 150;

	  if(gParametryPracy.gTempRozgrzewania  < 0 || gParametryPracy.gTempRozgrzewania  > 120)
	  	gParametryPracy.gTempRozgrzewania  = 0;

	  if(gParametryPracy.gTempStopGrzania  < 0 || gParametryPracy.gTempStopGrzania  > 120)
	  	gParametryPracy.gTempStopGrzania  = 0;

	  if(gParametryPracy.gZadanyPoziomZalania <= 0 || gParametryPracy.gZadanyPoziomZalania  > 2023)
	  	gParametryPracy.gZadanyPoziomZalania  = 0;
	  	
	  	
	  //disable reconnect on startup
	  //gParametryPracy.gWIFI_status = 0;
	  
	  //Serial.println("xxxxxass:"); 
	  
	  
	  
	  //if (gParametryPracy.gWIFI_MODE == 0)
	  //{
	   //Serial.println("ass:   0"); 
	  //}
	  
	  //if (gParametryPracy.gWIFI_MODE == 1)
	  //{
	   //Serial.println("ass:   1"); 
	  //}
	  
	  
	  
	  

}

void setup()
{
		 delay(100);	
			
		 Serial2.begin(115200);//460800  115200--->OK
         Serial.begin(115200);
         
         
         //RT--->TX comm........
         ETout.begin(details(gParametryPracy), &Serial2);
         ETin.begin(details(gParametryPracy_RCV), &Serial2);

         delay(100);
         
         
         
         
        // pinMode(PowerPWR1, OUTPUT);
        // initTimer3();
         
         
         
         
         //delay_min(5);

         Serial.println(F("Wlaczanie ekranu...."));
		 Serial.println(F("########################################"));
		 Serial.println(F("######## @@ MAX GON v 2.0 @@ ###########"));
		 Serial.println(F("########################################"));

                 

		 bool display = false;
		 do
		 {
		    display = Init_Display();	 
			 if(display == false)
			 {
				 Serial.println(F("Error! brak komunikacji z:  FT800 LCD"));
				 Serial.println(F("Co sekunde sprwdzam ponownie LCD"));
				 Sound_Play(0x14,50,108);
				 delay(1000);
			 }else break;
		 }while(1);

         int stage = 1;
         
         delay(1000);
         
         Sound_Play(0x14,50,108);
         
        
	     //delay(500);
	     //Sound_Play2(FT_PIANO,255,FT_MIDI_C_6);
         
         delay(500);

		 //Metaball();
         //TestScreen();  
         IntroScreen();

         int delayy = 500;


         


     do
     {
		  FTImpl.DLStart();
		  FTImpl.Cmd_Gradient(0, 0, 0x202020, 0, 180, 0x008800);
		  FTImpl.ColorRGB(0xFF,0xFF,0xFF);
	

		  FTImpl.Cmd_Text(56 ,190, 31,0, flashtext(57));
		  FTImpl.ColorRGB(0xFF,0xFF,0x00);
		   switch(stage)
		  {
			case 1:// read eprom
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 150 ,50, 29,0, flashtext(22));
			break;
			case 2:// szukanie termometrów.
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 160 ,50, 29,0, flashtext(23));
			break;
			case 3:// inicjalizacja karty SD.
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 140 ,50, 29,0, flashtext(24));
			break;
			case 4:// inicjalizacja liczników.
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 140 ,50, 29,0, flashtext(25));
			break;
			case 5:// inicjalizacja RTC.
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 140 ,50, 29,0, flashtext(26));
			break;
			case 6:// inicjalizacja pinów.
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 170 ,50, 29,0, flashtext(27));
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 170 ,85, 22,0, flashtext(28));
			break;
			case 7:// finisz
			       FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2 - 100 ,50, 29,0, flashtext(29));
			       
			    
			break;
		  }

		 
		  FTImpl.Cmd_Progress(55, 145, 360, 10, 0, stage * 1000 ,7000);
		  FTImpl.Cmd_Number(FT_DISPLAYWIDTH/2 - 20, 110, 25, 0,stage );
		  FTImpl.DLEnd();
		  FTImpl.Finish();
		  
		  ETin.receiveData();
          


		//0x63,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x10,0x11,
		//0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,
		//0x1b,0x1c,0x1d,0x1e,0x1f,0x23,0x2a,0x30,0x31,0x32,0x33,
		//0x34,0x35,0x36,0x37,0x38,0x39,0x40,0x41,0x42,0x43,
		//0x44,0x45,0x46,0x47,0x48,0x49,0x50,0x51,0x52,0x53,
		//0x54,0x55,0x56,0x57,0x58,0x60,0x61



			  switch(stage)
			  {
				   case 1:// read config eprom
					      Serial.println(F("poziom 1..."));
						  init_read_conf();
						  stage++;
						  Sound_Play(0x10,100,108);
						  delay(delayy);
				   break;

				   case 2:// inicjalizacja termometrów
					      Serial.println(F("poziom 2..."));
						  init_termo();
						  stage++;
						  delay(delayy);
						  Sound_Play(0x10,100,108);
				   break;

				   case 3:// init sd
					      Serial.println(F("poziom 3..."));
						  //init_sd();
						  stage++;
						  delay(delayy);
						  Sound_Play(0x10,100,108);

				   break;

				   case 4:// init timers
				          Serial.println(F("poziom 4..."));
						  init_timers();
						  stage++;
						  delay(delayy);
						  Sound_Play(0x10,100,108);
				   break;

				   case 5:// init RTC
					      Serial.println(F("poziom 5..."));
						  init_RTC();
						  stage++;
						  delay(delayy);
						  Sound_Play(0x10,100,108);
				   break;

				   case 6:// setup pinmode
						  Serial.println(F("poziom 6..."));
						  init_pins();
						  stage++;
						  delay(delayy);
						  Sound_Play(0x10,100,108);
				   break;

				   case 7:// finish setup
						  // start na wył
						  Serial.println(F("poziom 7.."));
						  

						  gParametryPracy.gCzasProcesuMin        = 0;
						  gParametryPracy.gCzasProcesuGodz       = 0;
						  gParametryPracy.gCzasProcesuSek        = 0;

						  gParametryPracy.gCzasProcesuTotalMin   = 0;
						  gParametryPracy.gCzasProcesuTotalSek   = 0;
						  gParametryPracy.gCzasZalewania 		 = 0;
						  gParametryPracy.gCzasZalania           = 0;
						  gParametryPracy.gCzasStabilizacji 	 = 0;
						  gParametryPracy.gCzasPrzedgonu    	 = 0;
						  gParametryPracy.gCzasRozgrzewania      = 0;
						  gParametryPracy.gCzasGonu     		 = 0;
						  gParametryPracy.gCzasPogonu   		 = 0;
						  gParametryPracy.gCzasChlodzenia 	     = 0;

						  gParametryPracy.gZaworGonCntr   = 0;
						  gParametryPracy.gZaworGon2Cntr  = 0;

						  gParametryPracy.gPoziomZalania  = 0;
						  
						  gParametryPracy.gZalanieX = 0;
						  
						  //poprawka do bekapu
						  //gParametryPracy.gCzasProcesuMin  = gParametryPracy.gLocal_timer.minute;
						  //gParametryPracy.gCzasProcesuGodz = gParametryPracy.gLocal_timer.hour;
						  //gParametryPracy.gCzasProcesuSek  = gParametryPracy.gLocal_timer.second;
						  
						  
						  gParametryPracy.gLocal_timer.second = 0;
						  gParametryPracy.gLocal_timer.minute = 0;
						  gParametryPracy.gLocal_timer.hour   = 0;


						 // gParametryPracy.gStartAutoDateTime.hour     = 0;
						 // gParametryPracy.gStartAutoDateTime.minute   = 0;
						 // gParametryPracy.gStartAutoDateTime.second   = 0;
						 // gParametryPracy.gStartAutoDateTime.year     = 0;
						 // gParametryPracy.gStartAutoDateTime.month    = 0;
						 // gParametryPracy.gStartAutoDateTime.day      = 0;

						 // gParametryPracy.gKoniec = false;
												  
						  gParametryPracy.gEtap = 0;

						  //set global sound volume
						  FTImpl.Write(REG_VOL_SOUND,gParametryPracy.gSoundVolume);
						  
						  gCzyWIFI_IS_Conected = false;
						  
						  gParametryPracy.gSTATUS = 0;

	
	
						  
						  ETin.receiveData();
						  Akt_AwariaDS();
						  
						  gFreeMemory = MemsizeBytes();
						  
						  					  
						  init_sd();
						  
						  discoverOneWireDevices();
					   
					      Serial.println("WIFI data:");
					      Serial.println(gParametryPracy.gSSID);
		                  Serial.println(gParametryPracy.gPASS);
					      Serial.println(".");
					      Serial.println(".");
					      Serial.println("."); 
					      Serial.println(F("MaxGon v 2.2"));
						  Serial.println(F("GOTOWY..."));
						  Serial.println(F("Mozesz zaczac destylacje..."));
						  Serial.println(".");
						  Serial.println(".");
						  Serial.println(". --->");
						  stage++;
					  
					  
						  delay(delayy + 100);
						  Sound_Play(0x14,100,108);
				
				   break;
			  }
      }while(stage < 8);
      
 //Wykresy_1();
}

void loop()         
{                   
       	AA_MENU();
       	
              	
       	//AKoniec_procesu();  
}                   

//PITU: blaszak
//gTempKolumna
//DeviceAddress gTermo1 = { 0x28, 0xFF, 0xB8, 0x1F, 0x02, 0x15, 0x02, 0x7B };
//gTempBeczka
//DeviceAddress gTermo2 = { 0x28, 0xFF, 0xD9, 0x52, 0x93, 0x15, 0x04, 0x84 };
//gTempGlowica
//DeviceAddress gTermo3 = { 0x28, 0xFF, 0x1E, 0x1E, 0x02, 0x15, 0x02, 0x5B };
//gTempWodaWy
//DeviceAddress gTermo4 = { 0x28, 0xFF, 0x1D, 0x29, 0x6D, 0x14, 0x04, 0x38 };
//gTempAlarmu
//DeviceAddress gTermo5 = { 0x28, 0xFF, 0xE8, 0xA7, 0xB1, 0x15, 0x01, 0xD9 };


//UFOLEC I czyli Krupinski.P:
//gTempKolumna
//DeviceAddress gTermo1 = { 0x28, 0xFF, 0x35, 0x74, 0x23, 0x16, 0x04, 0xEF };
//gTempBeczka
//DeviceAddress gTermo2 = { 0x28, 0xFF, 0x4D, 0x94, 0x23, 0x16, 0x04, 0xF5 };
//gTempGlowica
//DeviceAddress gTermo3 = { 0x28, 0xFF, 0x9E, 0x72, 0x33, 0x16, 0x03, 0x6C };
//gTempWodaWy
//DeviceAddress gTermo4 = { 0x28, 0xFF, 0xBC, 0xE9, 0x23, 0x16, 0x03, 0x28 };
//gTempAlarmu
//DeviceAddress gTermo5 = { 0x28, 0xFF, 0xA9, 0x94, 0x23, 0x16, 0x04, 0x30 };









//----------------------<S.K.A.N.E.R>---------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------|
//SKANER do skanowania DS   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|
//-----------------------   ???????????????>>>>>>>>>>>>>>>>>>>>|
//-----------------------   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|
//-------------------------------------------------------------|
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//#include <OneWire.h>
//#include <DallasTemperature.h>
//#define ONE_WIRE_BUS 2
//#define TEMPERATURE_PRECISION 9
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);
//int numberOfDevices;
//DeviceAddress tempDeviceAddress;
//void setup(void)
//{
  //Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");
  //sensors.begin();
  //numberOfDevices = sensors.getDeviceCount();
  //Serial.print("Locating devices...");
  //Serial.print("Found ");
  //Serial.print(numberOfDevices, DEC);
  //Serial.println(" devices.");
  //Serial.print("Parasite power is: ");
  //if (sensors.isParasitePowerMode()) Serial.println("ON");
  //else Serial.println("OFF");
  //for(int i=0;i<numberOfDevices; i++)
  //{
    //if(sensors.getAddress(tempDeviceAddress, i))
	//{
		//Serial.print("Found device ");
		//Serial.print(i, DEC);
		//Serial.print(" with address: ");
		//printAddress(tempDeviceAddress);
		//Serial.println();
		//Serial.print("Setting resolution to ");
		//Serial.println(TEMPERATURE_PRECISION, DEC);
		//sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
	    //Serial.print("Resolution actually set to: ");
		//Serial.print(sensors.getResolution(tempDeviceAddress), DEC);
		//Serial.println();
	//}else{
		//Serial.print("Found ghost device at ");
		//Serial.print(i, DEC);
		//Serial.print(" but could not detect address. Check power and cabling");
	//}
  //}
//}
//void printTemperature(DeviceAddress deviceAddress)
//{
  //float tempC = sensors.getTempC(deviceAddress);
  //Serial.print("Temp C: ");
  //Serial.print(tempC);
  //Serial.print(" Temp F: ");
  //Serial.println(DallasTemperature::toFahrenheit(tempC));
//}
//void loop(void)
//{
  //Serial.print("Requesting temperatures...");
  //sensors.requestTemperatures();
  //Serial.println("DONE");
  //for(int i=0;i<numberOfDevices; i++)
  //{
    //if(sensors.getAddress(tempDeviceAddress, i))
	//{
		//Serial.print("Temperature for device: ");
		//Serial.println(i,DEC);
		//printTemperature(tempDeviceAddress);
	//}
  //}
//}
//void printAddress(DeviceAddress deviceAddress)
//{
  //for (uint8_t i = 0; i < 8; i++)
  //{
    //if (deviceAddress[i] < 16) Serial.print("0");
    //Serial.print(deviceAddress[i], HEX);
  //}
//}




//kontynułacja histerezy zabezpieczająca urobek przed wyłączeniem prądu 
//Jeżeli temperatura na beczce jest mniejsza od tem. dnia + histereza to EZ OFF
//dnia "-" histereza to EZ OFF
//Coś♥ pojebałem
//jeszcze raz

//Jeżeli temp. dnia wynosi 10 st. a histereza ma 0,3 a tem na beczce 9,6 to EZ jest OFF a jeżeli tem. dnia ma 10 histereza 0,3 beczka 9,7 to jest jeszcze EZ w ON
//czyli jeżeli tem na beczce jest mniejsza od tem dnia o histerezę to EZ musi być w off
//teraz dobrze



//Pobierz archiwum z gra i crackiem
//Wypakuj i zainstaluj
//Wpisz kod H5E4-EF588-988IT-G66CK- 923J
//Wklej zawartosc folderu crack do folderu gdzie została zainstalowana gra
//https://gloria.tv/video/8tLmwM86Fg2MDgzEqDGuQHFxf



//Kolejna ofiara illuminatów – Chris Cornell, wokalista zespołów Soundgarden i Audioslave zmarł w środę wieczorem; miał 52 lata.
//http://muzyka.onet.pl/rock/chris-cornell-popelnil-samobojstwo/fks1f3
//Podobnie zmarło wiele gwiazd tzw. show biznesu.Najpierw illuminati pomogli im wejść na szczyt, a gdy im się już znudzili, pozbyli się ich jak niepotrzebnych zabawek. To jest prosta metoda na wypromowanie nowych gwiazd.Przykładem może być Rihanna, która szczyt sławy osiągnęła w roku 2012. W tym samym roku zmarła Whitney Houston.
//Można sprawdzić jak odbywa się ceremonia koronacji nowych gwiazd illuminati.
//Rihanna illuminati
//http://odnajdz-swiatlo.blog.pl/2016/06/02/rihanna-album-anti-christ/
//Jak wygląda sam proceder przyjęcia do illuminati. Na pewno nie jest to takie proste. Możliwe, że oni sami wyszukują takich osób z odpowiednimi predyspozycjami do osiągnięcia sukcesu w danej dziedzinie(film, muzyka, sport, biznes), a później im to ułatwiają. Z tym to nie mają żadnego problemu.
//Znalazłem ciekawą stronę, gdzie zamieszczono informację:
//KORZYŚCI DLA NOWYCH CZŁONKÓW, KTÓRYCH PRZYJMUJE ILLUMINATI.
//1. Nagroda pieniężna w wysokości 500 000 USD w USD
//2. Nowy samochód o wyrafinowanym wyglądzie, o wartości 300 000 USD
//3. Dream House kupił w kraju własnym wyborem
//4. Wakacje na miesiąc (w pełni opłacone) do miejsca przeznaczenia.
//5. Ogólny pakiet dla użytkowników golfowych
//6. Ochrona VIP na wszystkich lotniskach na świecie
//7. Całkowita zmiana stylu życia
//8. Access to Grove Czeskie
//9. Miesięczna płatność w wysokości 1.000.000 USD na konto bankowe każdego miesiąca jako członka
//10.Onominutowe spotkanie z 5 największymi światowymi liderami i 5 największych gwiazd na świecie.
//Jeśli wstawisz do domu bogaty e-mail, nasz nowy adres eamil jointhehouseofriches@gmail.com
//https://illuminatiadamz.wordpress.com/
//Jeden drobny szczegół tej umowy – musisz im oddać swoją duszę.
//Wiele osób na taką umowę zgadza się. Po co im dusza, której nawet nie widać i nie wiadomo czy w ogóle istnieje.
//Dopiero później zaczynają się problemy, ale od tej umowy nie ma już odwrotu.


// 600, 60, 6



//na pewno potrza coś takiego że jak się nie ustabilizuje po wybranym czasie
//to się wyłączy oczywiście po osiągnięciu wybranej tem na beczce
//to trzeba by dodatkowy parametr w ustawieniach dodać
//jeżeli temp. na beczce osiągnie (wybraną temp.) + czas w którym nie włączy
//się EZ to przechodzi w pogon




//https://www.visuino.com/


//forum search
//pwm heater site:http://forum.arduino.cc

//power: when you want 50% power, instead of 0.5 sec on then 0.5 sec off 
//Have you tried using a zero-crossing SSR and switching it on/off 
//potentially on every cycle of the mains? For example, when you want 50% power,
//instead of 0.5 sec on then 0.5 sec off (which might give a noticeable flicker),
//turn it on for 1 cycle, then off for 1 cycle, then on for 1 cycle etc.









//PI
//wget https://raw.githubusercontent.com/blogmotion/BitBangingDS18B20/master/configDS18B20.c
//gcc -o configDS18B20 configDS18B20.c
//sudo ./configDS18B20



//PII:
//wget https://raw.githubusercontent.com/blogmotion/BitBangingDS18B20/master/configDS18B20.c
//sudo nano configDS18B20.c


//Change "BCM2708_PERI_BASE "0x20000000" to BCM2708_PERI_BASE "0x3F000000" (ignore any errors)
//Save (Ctrl+X, Y, ENTER)

//gcc -o configDS18B20 configDS18B20.c
//sudo ./configDS18B20

//Now type 9,10,11, or 12 to change resolution:

    //9 bit : 0.5°c
    //10 bit : 0.25°c
    //11 bit : 0.125°c
    //12 bit : 0.0625°c


//UBRAŁ SIĘ DIABEŁ W ORNAT I OGONEM NA MSZĘ DZWONI 



//Wyliczenie mocy dla grza³ki 
//1) 1500 W 240V    1500W:100= 15W TO 1% 1500W:240V=6,25A  
//2) 2000 W 240V    2000W:100= 20W TO 1%
//3) 2500 W 240V    2500W:100= 25W TO 1%

//4) 3000 W 400V 


//Algorytm dla mocy. Wpisujemy dane
//np: mamy grza³kê 1500W i 6,25A a napiêcie w sieci 215V
//215v*6,25A= 1343,75W:100=13,4W   To 1%



 //Zadanie I:
 //Sterujemy pracą grzałki włączając ją i wyłączając
 //na określony czas w cyklu dwu minutowym.
 //Przyjmując że grzałka włączona non stop
 //przez dwie minuty równa się 100% mocy.
 //Pytanie: ile czasu ma być grzałka włączona a ile wyłączona
 //dla mocy 3% ???




// support@clipgrab.org



// odbior przedgon przedgonu
// on mały kropelkowy off szybki odbiór



//std::string send_message_to_arduino(const char* message)
//{
	//std::string result = system_send(message);
	//return result;
//}

















//In SPI, the following connections are used:

    //MISO (Master In Slave Out) - a data line for sending data from the slave to the master
    //MOSI (Master Out Slave In) - a data line for sending data from the master to the slave
    //SCK (Serial Clock) - a clock generated by the master for clocking the bits on MISO and MOSI
    //SS (Slave Select) - a data line from the master to a particular slave.

//There is one SS for every slave device. MISO, MOSI, and SCK are shared between all the devices on the bus.

//In your case, pin 4 is SS for the SD card interface while pin 10 is SS for the ethernet controller.






