#include<stdio.h>
#include"API001_Network.h"
#include <Arduino.h>

// If Debug trace 1 = ON , 0 = OFF
// int DEBUG_TRACE = 1;

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

/* Add an 8-bit uint8 data type to a Reveal message*/
void Reveal__AddDataU8(REVEAL_COMMAND_TYPE *command , char u8 ) //uint8 u8
{
    if(command->PACKET == false)
        {
            if (command->length < REVEAL_PAYLOAD_SIZE)
            {
                command->data[command->length ] = u8;
                command->length += 1;
                SUCCESS_FuNCTION("Success: Reveal__AddDataU8");
            }
        }
        else{
            ERROR_FuNCTION("Error:Reveal__AddDataU8");
    }
}
/**
 *    @brief    Add a character buffer to a Reveal message.
 *
 *    @details  This function is a helper method and should only be used when a a character buffer
 *              is to be added to a message. It should be used with caution as it does not manage
 *              endianess like the other AddData functions in this module. The maximum size of a
 *              buffer to add is equal to the max REVEAL_PAYLOAD_SIZE.
 *
 *    @param    *command - pointer to the reveal message struct
 *    @param    *u8_buffer - pointer to the character buffer to add to the message
 *    @param    length - length of the character buffer
 *    @return   void
 */
void Reveal__AddDataU8Buffer(REVEAL_COMMAND_TYPE *command, uint8 *u8_buffer, uint8 length)
{
    int i,j = 0;
    int Tem;
    Tem = command->length;
    if (command->data != (REVEAL_COMMAND_TYPE *)NULL)
    {
        if(length > (REVEAL_PAYLOAD_SIZE - command->length))
        {
            length = (uint8)(REVEAL_PAYLOAD_SIZE - command->length);
            Serial.print("Error");
        }
        //memcpy(&command->data[command->length],u8_buffer,length);
        // delay(2000);
        Serial.print("length: ");
        Serial.println(length);
        for( i = 0, j=0; i< length;i++,j++){
           command->data[(Tem) + i] = u8_buffer[j];
            Serial.print("Buffer[");
            Serial.print((Tem) + i);
            Serial.print("] = ");
            Serial.println(command->data[(Tem) + i],HEX);
            //Tem += 1;
            delay(50);
        }
        command->length += length;
    }
}
/**
 *    @brief    Add a 16-bit uint16 data type to a Reveal message.
 *
 *    @details  This function adds the specified data type to a Reveal queue driver message. This is a
 *              memory endianess independent method that will result in a big endian message. This function
 *              should be called in order each time another piece of data needs to be packed into the
 *              message structure.
 *
 *    @param    command* - pointer to the reveal message structure
 *    @param    u16 - the 16-bit data to add to the message
 *    @return   void
 */
void Reveal__AddDataU16(REVEAL_COMMAND_TYPE* command, uint16 u16)
{
    uint8 index;
    // if (command->data != (REVEAL_COMMAND_TYPE *)NULL)
    if(command->PACKET == false)
    {
        index = command->length;
        if (index < (REVEAL_PAYLOAD_SIZE - 1))
        {
            command->data[ index   ] = (uint8)(u16>>8);
            command->data[(index)+1] = (uint8) u16;
            command->length += 2;
            SUCCESS_FuNCTION("Success: Reveal__AddDataU16");
        }
    }
    else{
        ERROR_FuNCTION("Error:Reveal__AddDataU16");
    }
}
/**
 *    @brief    Add a 32-bit uint32 data type to a Reveal message.
 *
 *    @details  This function adds the specified data type to a Reveal queue driver message. This is a
 *              memory Endianess independent method that will result in a big endian message. This function
 *              should be called in order each time another piece of data needs to be packed into the
 *              message structure.
 *
 *    @param    command* - pointer to the reveal message structure
 *    @param    u32 - the 32-bit data to add to the message
 *    @return   void
 */
void Reveal__AddDataU32(REVEAL_COMMAND_TYPE* command, uint32 u32)
{
    uint8 index;
    // if (command->data != (REVEAL_COMMAND_TYPE *)NULL)
    if(command->PACKET == false)
    {
        index = command->length;
        if (index < (REVEAL_PAYLOAD_SIZE - 3))
        {
            command->data[ index   ] = (uint8)(u32>>24);
            command->data[(index)+1] = (uint8)(u32>>16);
            command->data[(index)+2] = (uint8)(u32>>8 );
            command->data[(index)+3] = (uint8) u32;
            command->length += 4;
            SUCCESS_FuNCTION("Success: Reveal__AddDataU32");
        }
    }
    else{
        ERROR_FuNCTION("Error: Reveal__AddDataU32");
    }
}
/**
 *    @brief    Calls Reveal__NewFeedback with the feedback parameter to a command format
 *              and adds it to the message queue.
 *
 *    @details  This function should be called whenever a new outgoing Reveal command message is desired.
 *              Object creation of a new message is simulated by returning a pointer into a queue of structures.
 *              The specified api and opcode are set for the new message and the length is initialized to 0.
 *
 *    @param    api - the api id of the command
 *    @param    opcode - the opcode of the command
 *    @param    node - the node id to send the message to
 *    @return   REVEAL_COMMAND_TYPE* - a pointer to the reveal message structure
 */
/* REVEAL_COMMAND_TYPE * Reveal__NewCommand(uint8 api, uint8 opcode)
{
    REVEAL_COMMAND_TYPE *pt;
    pt->length= 0;
    if (pt->data == (REVEAL_COMMAND_TYPE *)NULL)
    {
      pt->data[pt->length] = api;
      pt->data[pt->length + 1] = opcode;
      pt->length += 2;
    }
    return (pt);
//   char mBuffer[2];
//   int mlength = 0;
//   mBuffer[mlength] = api;
//   mBuffer[mlength+1] = opcode;
//   //return(mBuffer);
// command->NWDATA[command->length] = api;
//   command->NWDATA[command->length + 1] = opcode;
  //command->length += 2;
}*/
void Reveal__NewCommand1(REVEAL_COMMAND_TYPE *command ,uint8_t api, uint8_t opcode)
{
  uint8 index;
  command->length = 0;
  index = command->length;
    if (command == (REVEAL_COMMAND_TYPE *)NULL)
    {
        command->data[ index   ] = api;
        command->data[(index)+1] = opcode;
        command->data[(index)+2] = Device_ID;
        command->length += 3;
    }
    else{
        //ERROR_PACKET = true;
        ERROR_FuNCTION("Error: buffer not null .....!");
    }
}
void Reveal__NewCommand2(REVEAL_COMMAND_TYPE *command ,uint8_t api, uint8_t opcode)
{
    uint8 index;
    command->length = 0;
    index = command->length;
    command->PACKET = false;
    if(command->PACKET == false)
    {
        command->data[ index   ] = api;
        command->data[(index)+1] = opcode;
        command->data[(index)+2] = Device_ID;
        command->length += 3;
        SUCCESS_FuNCTION("Success: API and Opcode set ");
    }
    else{
        command->PACKET = true;
        ERROR_FuNCTION("Error: API and Opcode Not set .....!");
    }
}

void PublishToSerial(REVEAL_COMMAND_TYPE *command){
    int LoopCounter = 0;
    if(command->PACKET == false){
        Serial.print("Packet : ");
        for(LoopCounter = 0; LoopCounter < command->length; LoopCounter++){
            Serial.print(command->data[LoopCounter],HEX);
        }
        Serial.println();
        delay(50);
    }
    else{
        ERROR_FuNCTION("Error: PublishToSerial Packet failed...");
    }
    
    command->length = 0;
}