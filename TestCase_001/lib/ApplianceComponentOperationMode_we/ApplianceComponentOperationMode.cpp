
#include<stdio.h>
#include <Arduino.h>
#include"ApplianceComponentOperationMode.h"


unsigned int RunningMinute;
_APPLIANCECOMPONENT_INPUT_PARAMETERS *ApplianceComponentInputParameter;
MachineCase mState;
void Initialize_ApplianceComponentOperationMode(){
    ApplianceComponentInputParameter->mRunningMinutes = 0;
    ApplianceComponentInputParameter->mRunningHours = 0;
}
void UpdateRunningHours(unsigned char instance){
    ApplianceComponentInputParameter->mRunningMinutes ++;
    Serial.print("RunningMinutes: ");
    Serial.println(ApplianceComponentInputParameter->mRunningMinutes);
    if((ApplianceComponentInputParameter->mRunningMinutes/60) == 1){
        ApplianceComponentInputParameter->mRunningHours ++;
        ApplianceComponentInputParameter->mRunningMinutes = 0;
        Serial.print("RunningHours: ");
        Serial.println(ApplianceComponentInputParameter->mRunningHours);
    }
}
void mDevice_State(){

    switch (mState)
    {
    case Data:
        Serial.println("Case 0");
        break;
    case Data1:
        Serial.println("Case 1");
        break;    
    
    default:
        Serial.println("Default");
        break;
    }
}