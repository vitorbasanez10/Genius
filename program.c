/*
 * app.c
 *
 *  Created on: Aug 10, 2022
 *      Author: vitor.yan
 */

//-----------------------------------------------------------------------------------------------------------------------

#include "main.h"
#include "stdlib.h"
#include  "usbh_hid.h"
#include  <stdbool.h>

//-----------------------------------------------------------------------------------------------------------------------

static int delay;
static uint8_t blink_led[20];
static uint8_t pressed_keys[20];
int key_level = 0;

int level = 3;
static uint8_t key = 0;
static uint8_t key_pressed = 0;
int h = 0;
int f = 0;
uint8_t ik=0;

//-----------------------------------------------------------------------------------------------------------------------

uint8_t led_green = 12;
uint8_t key_green = 50;
//tecla 2

uint8_t led_orange = 13;
uint8_t key_orange = 52;
//tecla 4

uint8_t led_red = 14;
uint8_t key_red = 56;
//tecla 8

uint8_t led_blue = 15;
uint8_t key_blue = 54;
//tecla 6

//-----------------------------------------------------------------------------------------------------------------------

void USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{
	if(USBH_HID_GetDeviceType(phost) == HID_KEYBOARD)  // if the HID is Mouse
	{
		HID_KEYBD_Info_TypeDef *Keyboard_Info;
		Keyboard_Info = USBH_HID_GetKeybdInfo(phost);  // get the info
		key = USBH_HID_GetASCIICode(Keyboard_Info);  // get the key pressed
	}
}

//-----------------------------------------------------------------------------------------------------------------------

static enum
{
	INIT,
	BLINK,
	CHECK,
	ERR
}game_sm = INIT;

//-----------------------------------------------------------------------------------------------------------------------

void setup()
{
	delay = 100;
}

//-----------------------------------------------------------------------------------------------------------------------

int led = 0; 
int lc = 0;

//-----------------------------------------------------------------------------------------------------------------------

void loop()
{
	switch (game_sm)
	{
	case INIT:
	{
		for (uint8_t a = 0; a < 2; a++)
		{
			HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_RESET);
			HAL_Delay(50);
		}

		for (uint8_t b = 0; b < 2; b++)
		{
			HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_SET);
			HAL_Delay(250);
			HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_SET);
			HAL_Delay(250);
			HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_SET);
			HAL_Delay(250);
			HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_RESET);
			HAL_Delay(250);
			HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_RESET);
			HAL_Delay(25);
		}

		for (uint8_t c = 0; c < 3; c++)
		{
			HAL_GPIO_TogglePin(led_azul_GPIO_Port, led_azul_Pin);
			HAL_GPIO_TogglePin(led_verde_GPIO_Port, led_verde_Pin);
			HAL_GPIO_TogglePin(led_laranja_GPIO_Port, led_laranja_Pin);
			HAL_GPIO_TogglePin(led_vermelho_GPIO_Port, led_vermelho_Pin);
			HAL_Delay(500);
			HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_RESET);
			HAL_Delay(500);
		}
		game_sm = BLINK;
	}
	break;

	case BLINK:
	{
		for(h=0; h < 20; h++){
			pressed_keys[h] = 0;
		}

		ik = 0;

		for(uint8_t i = 0; i < level; i++){

			while(lc == led){
				lc = (random() % 4);
			}

			led = lc;
			GPIOD->ODR |= (1  <<  (led + 12));
			blink_led[i] = (led + 12);
			HAL_Delay(1000);
			GPIOD->ODR &= ~(1  << (led + 12));
		}

		game_sm = CHECK;
	}
	break;

	case CHECK:
	{

		if(key_level == (level)){
			level++;
			key_level = 0;

			for (uint8_t e = 0; e < 1; e++)
			{
				HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_SET);
				HAL_Delay(250);
				HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_SET);
				HAL_Delay(250);
				HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_SET);
				HAL_Delay(250);
				HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_RESET);
				HAL_Delay(250);
				HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_RESET);
				HAL_Delay(25);
			}

			for (uint8_t d = 0; d < 2; d++)
			{
				HAL_GPIO_TogglePin(led_azul_GPIO_Port, led_azul_Pin);
				HAL_GPIO_TogglePin(led_verde_GPIO_Port, led_verde_Pin);
				HAL_GPIO_TogglePin(led_laranja_GPIO_Port, led_laranja_Pin);
				HAL_GPIO_TogglePin(led_vermelho_GPIO_Port, led_vermelho_Pin);
				HAL_Delay(200);
			}
			HAL_Delay(200);
			game_sm = BLINK;
		}
		//		else if(key_level != (level)){
		//
		//		}



		if(key > 0){
			key_pressed = key;
			HAL_Delay(200);
			key = 0;
		}
		else if(key_pressed != key){

			switch (key_pressed){
			case 54:
				pressed_keys[ik++] = led_blue;
				HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_RESET);
				if(pressed_keys[ik-1] == blink_led[ik-1]){
					game_sm = CHECK;
					key_level++;
				}
				else if(pressed_keys != blink_led){
					game_sm = ERR;
				}
				break;
			case 50:
				pressed_keys[ik++] = led_green;
				HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_RESET);
				if(pressed_keys[ik-1] == blink_led[ik-1]){
					game_sm = CHECK;
					key_level++;
				}
				else if(pressed_keys != blink_led){
					game_sm = ERR;
				}
				break;
			case 52:
				pressed_keys[ik++] = led_orange;
				HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(led_laranja_GPIO_Port, led_laranja_Pin, GPIO_PIN_RESET);
				if(pressed_keys[ik-1] == blink_led[ik-1]){
					game_sm = CHECK;
					key_level++;
				}
				else if(pressed_keys != blink_led){
					game_sm = ERR;
				}break;
			case 56:
				pressed_keys[ik++] = led_red;
				HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(led_vermelho_GPIO_Port, led_vermelho_Pin, GPIO_PIN_RESET);
				if(pressed_keys[ik-1] == blink_led[ik-1]){
					game_sm = CHECK;
					key_level++;
				}
				else if(pressed_keys != blink_led){
					game_sm = ERR;
				}break;
			default:
				break;
			}

			HAL_Delay(200);
			key_pressed = 0;
		}

		// se ok
		//game_sm = BLINK;

		// se erro
		//game_sm = ERR;
	}
	break;

	case ERR:
	{
		for(f=0; f < 20; f++){
			blink_led[f] = 0;
		}
		level = 3;
		for (uint8_t d = 0; d < 5; d++)
		{
			HAL_GPIO_TogglePin(led_azul_GPIO_Port, led_azul_Pin);
			HAL_GPIO_TogglePin(led_verde_GPIO_Port, led_verde_Pin);
			HAL_GPIO_TogglePin(led_laranja_GPIO_Port, led_laranja_Pin);
			HAL_GPIO_TogglePin(led_vermelho_GPIO_Port, led_vermelho_Pin);
			HAL_Delay(250);
		}
		game_sm = INIT;
	}
	break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------

//
//	for(uint8_t i = 0; i < level; i++)
//	{
//		GPIOD->ODR &= ~(1  << (led + 12));
//		while(lc == led)
//		{
//			lc = (random() % 4);
//		}
//		led = lc;
//		GPIOD->ODR |= (1  <<  (led + 12));
//
//		blink_led[i] = (1  <<  (led + 12));
//
//		HAL_Delay(1000);
//	}

//
//	//		GPIOD->ODR &= ~(1  << (led + 12));
//	//		led = (random() % 4);
//	//		GPIOD->ODR |= (1  <<  (led + 12));
//
//	//		GPIOD->ODR &= ~(1  << ((led++) + 12));
//	//		led = (led % 4);
//	//		GPIOD->ODR |= (1  <<  (led + 12));
//}

//-----------------------------------------------------------------------------------------------------------------------
