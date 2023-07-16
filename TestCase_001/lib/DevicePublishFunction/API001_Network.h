#ifndef API001_NETWORK_H__
#define API001_NETWORK_H__
#include<stdio.h>
#include<stdint.h>
#include<string.h>


#define MasterNode 0x01 
#define Device_ID 0x02


typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned long int   uint32;
typedef unsigned long long  uint64;
typedef float               float32;
typedef double              float64;


#define ERROR_FuNCTION(ERR)  Serial.println(ERR)
#define SUCCESS_FuNCTION(ERR) Serial.println(ERR)
/* Reveal Definition of the size of the payload for outgoing messages*/
#define REVEAL_PAYLOAD_SIZE  70

typedef enum _API
{
    API0 = 0,
    API1,
    API2,
    API3,
    API4,
    API5,
    APIMAX,
}API, *PARI; 

typedef enum _OPCODE
{
    OPCODE0 = 0,
	OPCODE1,
	OPCODE2,
	OPCODE3,
	OPCODE4,
	OPCODE5,
    OPCODEMAX
}OPCODE;

typedef enum { 
    SERIALIZATION_TYPE_INT8,    //signed byte/char
    SERIALIZATION_TYPE_INT16,   //signed word
    SERIALIZATION_TYPE_INT32,   //signed dword
    SERIALIZATION_TYPE_UINT8,   //unsigned byte/char
    SERIALIZATION_TYPE_UINT16,  //unsigned word
    SERIALIZATION_TYPE_UINT32,  //unsigned dword
    SERIALIZATION_TYPE_BUFFER,  //ascii buffer, must be null terminated
    SERIALIZATION_TYPE_BINARY_BUFFER, //binary buffer, first two bytes is buffer length
    SERIALIZATION_TYPE_MAX
}SERIALIZATION_TYPE_ENUM;

struct REVEAL_COMMAND_TYPE
{
    uint8 api;
    uint8 opcode;
    uint8 length = 0 ;
    // uint8 data[REVEAL_PAYLOAD_SIZE] = {0};
    char data[REVEAL_PAYLOAD_SIZE] = {0};
    bool PACKET;// = false;
};

/*
typedef struct
{
    uint8 api;
    uint8 opcode;
    //uint8 node          :4;
    //uint8 feedback      :1;
    //uint8 timeout       :1;
    //uint8 priority      :1;

    uint8 length = 0 ;
    //uint8_t length1;
    uint8 data[REVEAL_PAYLOAD_SIZE];
    // char data[REVEAL_PAYLOAD_SIZE];
    //uint8 data1[];
    //char NWDATA[REVEAL_PAYLOAD_SIZE ];

}REVEAL_COMMAND_TYPE;
*/

typedef struct  
{
    char mtemp[5];
    int mlength = 0;
}DATA_S_KEY_VALUE_ENTRY_TYPE;

/************************** PUBLIC (Function Prototypes) **********************************************/
//REVEAL_COMMAND_TYPE * Reveal__NewCommand( uint8 api, uint8 opcode); 
void Reveal__AddDataU8(REVEAL_COMMAND_TYPE* command , char u8);
int myFunction(int x, int y);
void Reveal__NewCommand1(REVEAL_COMMAND_TYPE *command ,uint8_t api, uint8_t opcode);
//void Reveal__AddDataU8(REVEAL_COMMAND_TYPE *command , uint8 u8);
void Reveal__AddDataU8Buffer(REVEAL_COMMAND_TYPE* command, uint8 *u8_buffer, uint8 length);
void Reveal__AddDataU16(REVEAL_COMMAND_TYPE* command, uint16 u16);
void Reveal__AddDataU32(REVEAL_COMMAND_TYPE* command, uint32 u32);
void PublishToSerial(REVEAL_COMMAND_TYPE *command);

void Reveal__NewCommand2(REVEAL_COMMAND_TYPE *command ,uint8_t api, uint8_t opcode);
#endif //API001_NETWORK_H__
