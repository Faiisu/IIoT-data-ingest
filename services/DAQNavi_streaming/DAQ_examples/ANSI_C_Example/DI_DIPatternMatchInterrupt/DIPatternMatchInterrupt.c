/*******************************************************************************
Copyright (c) 1983-2024 Advantech Co., Ltd.
********************************************************************************
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log:  $

--------------------------------------------------------------------------------
$NoKeywords:  $
*/

/******************************************************************************
*
* Windows Example:
*    PatternMatchInterrupt.c
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use DI snap function with a pattern match interrupt event
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'startPort' as the first port for Di scanning.
*    5. Set the 'portCount' to decide how many sequential ports to operate Di scanning.
*    6. Set pattern match channels and values for supported ports in system device manager configuration.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath  = L"../../profile/DemoDevice.xml";

int32          startPort   = 0;
int32          portCount   = 1;

// This is function declaration. This function is used to deal with 'pattern match' Event.
void BDAQCALL OnDiSnapEvent(void* sender, DiSnapEventArgs* args, void* userParam);

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode    ret         = Success;
   DiPmintPort* diPmintPort = NULL;
   IArray*      pmintPort   = NULL;
   wchar_t      enumString[256];

   // Step 1: Create a 'InstantDiCtrl' for DI function.
   InstantDiCtrl* instantDiCtrl = InstantDiCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   InstantDiCtrl_addPatternMatchHandler(instantDiCtrl, OnDiSnapEvent, NULL);

   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 3: Login the server by hostName
      //ret = InstantDiCtrl_Login(instantDiCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = InstantDiCtrl_setSelectedDevice(instantDiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = InstantDiCtrl_LoadProfile(instantDiCtrl, profilePath); // Loads a profile to initialize the device.

      // Step 5: Set necessary parameters
      pmintPort = InstantDiCtrl_getDiPmintPorts(instantDiCtrl);

      if (pmintPort == NULL)
      {
         printf(" The device doesn't support DI interrupt!\n");
         waitAnyKey();
         return 0;
      }

      // In this demo, we are using the first available one.
      diPmintPort = (DiPmintPort*)Array_getItem(pmintPort, 0);
      printf(" DI channel %d is used to detect interrupt!\n\n", DiPmintPort_getPort(diPmintPort));

      // Using 'pmEnableChans' mask to choose which channels to be enabled DI Pattern Match Interrupt.
      // ret = DiPmintPort_setMask(diPmintPort, pmEnableChans);
      // Using 'pmValue' to set which port value to be triggered DI Pattern Match Interrupt.
      // ret = DiPmintPort_setPattern(diPmintPort, pmValue);

      // Step 6: Start DIInterrupt.
      ret = InstantDiCtrl_SnapStart(instantDiCtrl);
      CHK_RESULT(ret);

      // Step 7: The device is working.
      printf(" Snap has start, any key to quit !\n");
      do
      {
         SLEEP(1);
      } while (!kbhit());

      // Step 8: Stop DIInterrupt.
      ret = InstantDiCtrl_SnapStop(instantDiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 9 : Logout from server.
   //InstantDiCtrl_Logout(instantDiCtrl);

   // Step 10: Close device, release any allocated resource.
   InstantDiCtrl_Dispose(instantDiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}

void BDAQCALL OnDiSnapEvent(void* sender, DiSnapEventArgs* args, void* userParam)
{
   int           i;
   unsigned char bufferForSnap[MAX_DIO_PORT_COUNT];
   memcpy(bufferForSnap, args->PortData, MAX_DIO_PORT_COUNT);
   // show snap data.
   printf(" DI Interrupt channel is %d\n", args->SrcNum);
   for (i = startPort; i < startPort + portCount; ++i)
   {
      printf(" DI port %d status: 0x%X\n\n", i, bufferForSnap[i - startPort]);
   }
}
