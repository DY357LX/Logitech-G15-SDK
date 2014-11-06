//
// Logitech Gaming LCD SDK
//
// Copyright (C) 2011-2012 Logitech. All rights reserved.
//

#pragma once

#define LOGI_LCD_TYPE_MONO    (0x00000001)
#define LOGI_LCD_TYPE_COLOR   (0x00000002)


#define LOGI_LCD_MONO_BUTTON_0 (0x00000001)
#define LOGI_LCD_MONO_BUTTON_1 (0x00000002)
#define LOGI_LCD_MONO_BUTTON_2 (0x00000004)
#define LOGI_LCD_MONO_BUTTON_3 (0x00000008)

#define LOGI_LCD_COLOR_BUTTON_LEFT   (0x00000100)
#define LOGI_LCD_COLOR_BUTTON_RIGHT  (0x00000200)
#define LOGI_LCD_COLOR_BUTTON_OK     (0x00000400)
#define LOGI_LCD_COLOR_BUTTON_CANCEL (0x00000800)
#define LOGI_LCD_COLOR_BUTTON_UP     (0x00001000)
#define LOGI_LCD_COLOR_BUTTON_DOWN   (0x00002000)
#define LOGI_LCD_COLOR_BUTTON_MENU   (0x00004000)

const int LOGI_LCD_MONO_WIDTH = 160;
const int LOGI_LCD_MONO_HEIGHT = 43;

const int LOGI_LCD_COLOR_WIDTH = 320;
const int LOGI_LCD_COLOR_HEIGHT = 240;

bool LogiLcdInit(wchar_t* friendlyName, int lcdType);
bool LogiLcdIsConnected(int lcdType);
bool LogiLcdIsButtonPressed(int button);
void LogiLcdUpdate();
void LogiLcdShutdown();

// Monochrome LCD functions
bool LogiLcdMonoSetBackground(BYTE monoBitmap[]);
bool LogiLcdMonoSetText(int lineNumber, wchar_t* text);

// Color LCD functions
bool LogiLcdColorSetBackground(BYTE colorBitmap[]);
bool LogiLcdColorSetTitle(wchar_t* text, int red = 255, int green = 255, int blue = 255);
bool LogiLcdColorSetText(int lineNumber, wchar_t* text, int red = 255, int green = 255, int blue = 255);

//UDK functions, use this only if working with UDK
int LogiLcdColorSetBackgroundUDK(BYTE partialBitmap[], int arraySize);
int LogiLcdColorResetBackgroundUDK();
int LogiLcdMonoSetBackgroundUDK(BYTE partialBitmap[], int arraySize);
int LogiLcdMonoResetBackgroundUDK();