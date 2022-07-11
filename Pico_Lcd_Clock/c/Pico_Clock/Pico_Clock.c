/*****************************************************************************
* Authot: Iwo Biborski 
* This applications uses graphical library provided by Waveshare team. According
* to their licence permissions we add the following:   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "Pico_Clock.h"
#include "LCD_2in.h"
#include "hardware/uart.h"
#include "math.h"
#include "clock_states.h"
#include "pico/stdlib.h"

/* Graph origin */
static int x_origin = 10;
static int y_origin = 230;

/* Control keys pins? */
static int key0 = 15; 
static int key1 = 17; 
static int key2 = 2; 
static int key3 = 3;

bool reserved_addr(uint8_t addr) {
return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void Draw_Digit(int i, int position, uint16_t x_start, uint16_t y_start)
{
    char buff[1];
    itoa(i, buff, 10);
    Paint_DrawString_EN(x_start + 12*position, y_start, buff, &Font20, BLACK,  WHITE);
}

void update_clock(Clock_T *clock)
{
    int sec = clock->sec;
    clock->sec = ++sec;
    if(sec == 60)
    {
        clock->min += 1;
        clock->hour +=1;
    }
    clock->sec = (clock->sec % 60);
    clock->min = (clock->min % 60);
    clock->hour = (clock->hour % 720);
}

Pair_T polar(float a, float b, float radius, float angle)
{
    Pair_T coord;
    coord.x = a + radius*cos(angle);
    coord.y = b + radius*sin(angle);
    return coord;
}

void draw_seconds(int seconds, uint16_t color)
{
    int sec = seconds % 60;
    Pair_T sec_p = polar(160.0, 120.0, 70.0, -M_PI_2 + ((float)sec)*(M_PI/30.0));
    Paint_DrawLine(160, 120, (int)sec_p.x, (int)sec_p.y, color, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}

void draw_minutes(int minutes, uint16_t color)
{
    int min = minutes % 60;
    Pair_T min_p = polar(160.0, 120.0, 70.0, -M_PI_2 + ((float)min)*(M_PI/30.0));
    Paint_DrawLine(160, 120, (int)min_p.x, (int)min_p.y, color, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
}

void draw_hours(int hours, uint16_t color)
{
    int sec = hours;
    Pair_T sec_p = polar(160.0, 120.0, 40.0, -M_PI_2 + ((float)sec)*(M_PI/360.0));
    Paint_DrawLine(160, 120, (int)sec_p.x, (int)sec_p.y, color, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
}

void draw_clock()
{
    Paint_DrawCircle(160, 120, 102, GREEN, DOT_PIXEL_4X4, DRAW_FILL_FULL);

    Pair_T ct_12 = polar(160.0, 120.0, 100.0, -M_PI_2);
    //Paint_DrawLine(160, 120, 160, 20, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_12.x - 15, (int)ct_12.y + 5, "12", &Font20, GREEN, BLUE);
    
    Pair_T ct_1 = polar(160.0, 120.0, 100.0, -M_PI/3.0);
    //Paint_DrawLine(160, 120, (int)ct_1.x , (int)ct_1.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_1.x -13, (int)ct_1.y + 5, "1", &Font20, GREEN, BLUE);
    
    Pair_T ct_2 = polar(160.0, 120.0, 100.0, -M_PI/6.0);
    //Paint_DrawLine(160, 120, (int)ct_2.x , (int)ct_2.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_2.x - 20, (int)ct_2.y, "2", &Font20, GREEN, BLUE);
    
    Pair_T ct_3 = polar(160.0, 120.0, 100.0, 0.0);
    //Paint_DrawLine(160, 120, (int)ct_3.x , (int)ct_3.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_3.x - 18, (int)ct_3.y - 8, "3", &Font20, GREEN, BLUE);
    
    Pair_T ct_4 = polar(160.0, 120.0, 100.0, M_PI/6.0);
    //Paint_DrawLine(160, 120, (int)ct_4.x , (int)ct_4.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_4.x - 19, (int)ct_4.y - 12, "4", &Font20, GREEN, BLUE);

    Pair_T ct_5 = polar(160.0, 120.0, 100.0, M_PI/3.0);
    //Paint_DrawLine(160, 120, (int)ct_5.x ,sec_p (int)ct_5.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_5.x - 16, (int)ct_5.y - 18, "5", &Font20, GREEN, BLUE);

    Pair_T ct_6 = polar(160.0, 120.0, 100.0, M_PI/2.0);
    //Paint_DrawLine(160, 120, (int)ct_6.x, (int)ct_6.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_6.x - 6, (int)ct_6.y - 18, "6", &Font20, GREEN, BLUE);

    Pair_T ct_7 = polar(160.0, 120.0, 100.0, M_PI/2.0 + M_PI/6.0);
    //Paint_DrawLine(160, 120, (int)ct_7.x, (int)ct_7.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_7.x + 1, (int)ct_7.y - 16, "7", &Font20, GREEN, BLUE);
    
    Pair_T ct_8 = polar(160.0, 120.0, 100.0, M_PI_2 + M_PI/3.0);
    //Paint_DrawLine(160, 120, (int)ct_8.x , (int)ct_8.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_8.x + 2, (int)ct_8.y - 15, "8", &Font20, GREEN, BLUE);

    Pair_T ct_9 = polar(160.0, 120.0, 100.0, M_PI);
    //Paint_DrawLine(160, 120, (int)ct_9.x , (int)ct_9.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_9.x + 2, (int)ct_9.y - 9, "9", &Font20, GREEN, BLUE);

    Pair_T ct_10 = polar(160.0, 120.0, 100.0, M_PI + M_PI/6.0);
    //Paint_DrawLine(160, 120, (int)ct_10.x, (int)ct_10.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_10.x +2, (int)ct_10.y - 2, "10", &Font20, GREEN, BLUE);

    Pair_T ct_11 = polar(160.0, 120.0, 100.0, M_PI + M_PI/3.0);
    //Paint_DrawLine(160, 120, (int)ct_11.x , (int)ct_11.y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawString_EN((int)ct_11.x - 4, (int)ct_11.y + 2, "11", &Font20, GREEN, BLUE);
}

int Pico_Clock(Clock_T *current_clk, Clock_T *run_clk)
{
    DEV_Delay_ms(100);

    if(DEV_Module_Init()!=0){
        return -1;
    }
    DEV_SET_PWM(50);
    /* LCD Init */
    printf("2inch LCD demo...\r\n");
    LCD_2IN_Init(HORIZONTAL);
    LCD_2IN_Clear(BLACK);
    
    //LCD_SetBacklight(1023);
    UDOUBLE Imagesize = LCD_2IN_HEIGHT*LCD_2IN_WIDTH*2;
    UWORD *BlackImage;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        //printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage,LCD_2IN.WIDTH,LCD_2IN.HEIGHT, 90, BLACK);
    Paint_SetScale(65);
    Paint_Clear(BLACK);
    Paint_SetRotate(ROTATE_270);
   
   SET_Infrared_PIN(key0);    
   SET_Infrared_PIN(key1);
   SET_Infrared_PIN(key2);
   SET_Infrared_PIN(key3);

   Paint_Clear(BLACK);
   LCD_2IN_Display((uint8_t * )BlackImage);

   draw_clock();

   State_T state = CLOCK_INIT;
   long int ts1 = 0;
   long int ts2 = 0;

   bool isSet = false;
   bool run = false;
   draw_minutes(0, RED);
   draw_seconds(0, RED);
   draw_hours(0, RED);

   while(1)
   {
       if(DEV_Digital_Read(key0) == 0 && DEV_Digital_Read(key1) == 0)
       {
           state = CLOCK_INIT;
       }
        switch(state)
        {
            case WELCOME:
            {
                break;
            }
            case CLOCK_INIT:
            {
                if(DEV_Digital_Read(key1) == 0)
                {
                    draw_minutes(current_clk->min, GREEN);
                    draw_hours(current_clk->hour, GREEN);
                    current_clk->min = ((current_clk->min + 1) % 60);
                    current_clk->hour = ((current_clk->hour + 1) % 720);
                }

                if(DEV_Digital_Read(key2) == 0)
                {
                    draw_seconds(current_clk->sec, GREEN);
                    current_clk->sec += 1;
                }

                draw_hours(current_clk->hour, RED);
                draw_minutes(current_clk->min, RED);
                draw_seconds(current_clk->sec, RED);

                if(DEV_Digital_Read(key0 ) == 0)
                {
                    state = CLOCK_RUN;
                    *run_clk = *current_clk;
                }
                break;
            }
            case CLOCK_RUN:
            {
                ts2 = time_us_64()/1000;
                if(970 <= (ts2 -ts1))
                {
                    update_clock(run_clk);
                    ts1 = ts2;
                    if(run_clk->sec != current_clk->sec)
                    {
                        draw_seconds(current_clk->sec, GREEN);
                        draw_seconds(run_clk->sec, RED);
                        draw_minutes(current_clk->min, RED);
                        draw_hours(current_clk->hour, RED);
                    }
                    if(run_clk->min != current_clk->min)
                    {
                        draw_minutes(current_clk->min, GREEN);
                        draw_minutes(run_clk->min, RED);
                        draw_hours(current_clk->hour, GREEN);
                        draw_hours(run_clk->hour, RED);
                    }
                    DEV_Delay_us(7550);
                    *current_clk = *run_clk;
                }
                break;
            }
        }
        Paint_DrawCircle(160, 120, 3, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
        LCD_2IN_Display((uint8_t * )BlackImage);       
   }

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    
    DEV_Module_Exit();
    return 0;
}
