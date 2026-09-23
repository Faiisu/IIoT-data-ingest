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
*    StaticDO_Remote.cpp
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use Static DO function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device.
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'startPort'as the first port for Do .
*    5. Set the 'portCount'to decide how many sequential ports to operate Do.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
#include <stdio.h>
#include <stdlib.h>
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
typedef unsigned char byte;

#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32          startPort   = 0;
int32          portCount   = 1;

inline void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a instantDoCtrl for DO function.
   InstantDoCtrl* instantDoCtrl = InstantDoCtrl::Create();
   do
   {
      // Step 2: Login the server by hostName.
      ret = instantDoCtrl->Login(L"IDAQ974Bid00");
      CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = instantDoCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = instantDoCtrl->LoadProfile(profilePath); //Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Write DO ports
      // Set port direction
      //Array<DioPort>* dioPort = instantDoCtrl->getPorts();
      //ret = dioPort->getItem(0).setDirectionMask(Output); // Setting port0 direction
      //CHK_RESULT(ret);
      uint8 bufferForWriting[64] = {0}; //the first element is used for start port
      //uint32 data = 0;//the data is used to the 'WriteBit';
      //int bit = 1;//the bit is used to the 'WriteBit';
      for (int32 i = startPort; i < portCount + startPort; ++i)
      {
         uint32 inputVal = 0;
         printf(" Input a 16 hex number for DO port %d to output(for example, 0x00): ", i);
         scanf("%x", &inputVal);
         bufferForWriting[i - startPort] = inputVal;
      }
      ret = instantDoCtrl->Write(startPort, portCount, bufferForWriting);

      /************************************************************************/
      /*printf(" Input value: ");
      //scanf("%d", &data);// Set 'WriteBit'
      //ret = instantDoCtrl->WriteBit(startPort, bit, data);
      //NOTE:
      //This function is used to write digital data to the specified DO channel immediately
      //argument1:which port you want to control? For example, startPort is 0.
      //argument2:which bit you want to control? You can write 0--7, any number you want.
      //argument3:What status you want, open or close 1 means open, 0 means close.*/
      /************************************************************************/
      CHK_RESULT(ret);
      printf("\n DO output completed !");

      // Read back the DO status.
      // Note:
      // For relay output, the read back must be deferred until the relay is stable.
      // The delay time is decided by the HW SPEC.
      // BYTE bufferForReading[64] = {0};
      // ret = instantDoCtrl->Read( startPort,portCount,bufferForReading );
      // if(BioFailed(ret))
      // {
      //    break;
      // }
      // Show DO ports' status
      // for ( LONG i = startPort;i < portCount + startPort; ++i)
      //{
      //    printf("Now, DO port %d status is:  0x%X\n\n", i, bufferForReading[i-startPort]);
      //}
   } while (false);

   // Step 5: Logout from server.
   instantDoCtrl->Logout();

   // Step 6: Close device and release any allocated resource.
   instantDoCtrl->Dispose();

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      wchar_t enumString[256];
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
   }
   waitAnyKey();
   return 0;
}
