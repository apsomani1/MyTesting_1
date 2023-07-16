#ifndef APPLIANCECOMPONENTOPERATIONMODE_H__
#define APPLIANCECOMPONENTOPERATIONMODE_H__



struct _APPLIANCECOMPONENT_INPUT_PARAMETERS
{
   
    unsigned int mCycleCount;
	unsigned int mRunningHours;
    unsigned int mTotalHoursStartTime;
    unsigned int mRunningMinutes;
    
};   //ApplianceComponentInputParameter

enum MachineCase{
    Data = 0,
    Data1 = 1,
    Data2 = 2
}; //MACHINECASE

void Initialize_ApplianceComponentOperationMode();
void UpdateRunningHours(unsigned char instance);
void mDevice_State();

#endif //APPLIANCECOMPONENTOPERATIONMODE_H__