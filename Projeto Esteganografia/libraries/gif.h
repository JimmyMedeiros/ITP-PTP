#ifndef GIF_H
#define GIF_H

#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"

// 6 bytes
typedef struct{
	char signature[3];// GIF em ASCII
	char version[3];// 87a ou 89a em ASCII
}GIF_Header;
// 7 bytes
#pragma pack (1)
typedef struct{
	unsigned short width;
	unsigned short height;
	unsigned char pckdFlds;// G CCC S TTT
	unsigned char bg_color_index;
	unsigned char pxl_Aspect_Ratio;
}Logical_Screen_Description;
// 8 bytes
typedef struct{
	char intro; // contém hexadecimal 0x21
	char label;// contém hexadecimal 0xF9
	char block_size; // Tamanho do bloco sem contar o terminator
	char pckdFlds; // RRR DDD U T
	short delay;
	char transparent_color_index;
	char block_terminator;
}Graphic_Control_Extension;
// Total: 21 bytes
typedef struct{
	GIF_Header hdr;// 6 bytes
	Logical_Screen_Description LgScrDsc;// 7 bytes
	PixelRGB* color_table;
	// Talvez tenha algo aqui antes do GCE
	Graphic_Control_Extension GrphCtrlExt;// 8 bytes
}CONTROL_BLOCK;

// 10 bytes*/
typedef struct{
	char separator;
	short left_pos;
	short top_pos;
	unsigned short width;
	short height;
	char pckdFlds; // L I S RR CCC
}img_Descriptor;
// quantos bytes?
typedef struct{
	img_Descriptor desc; // 10 bytes
	//Color_Table clr_Tbl;
	//Talbe_Based_Image_Data TB_Img_Data;
	//Plain_Text_Extension Plain_Txt_Ext;
}IMAGE_RENDERING;

/*typedef struct
{
	
}Color_Table;

typedef struct
{
	
}SPECIAL_PURPOSE;

typedef struct
{
	
}Trailer;*/

int encipher_GIF(FILE *imagem, FILE *saida, FILE *texto);

void decipher_GIF (FILE *img, FILE *textoSaida);

#endif