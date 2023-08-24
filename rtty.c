
#include <stdio.h>
#include "sdrplay_api.h"



void EventCallback(sdrplay_api_EventT eventId, sdrplay_api_TunerSelectT tuner, sdrplay_api_EventParamsT *params, void *cbContext){
    printf("Event Callback\n");
}

void DataStreamCallback(short *xi, short *xq, sdrplay_api_StreamCbParamsT *params, unsigned int numSamples, unsigned int reset, void *cbContext){
    printf("Data Stream Call back\nPrinting xi array\n");

    for (int i = 0; i < numSamples; i++) printf("%hi ", xi[i]);
    printf("\n");

}


int main(){
   
        
    //int i;
    //float ver = 0.0;
    sdrplay_api_ErrT err;       // generic error variable
    //sdrplay_api_DeviceParamsT *deviceParams = NULL;
    //sdrplay_api_CallbackFnsT cbFns;
    //sdrplay_api_RxChannelParamsT *chParams;

    //int reqTuner = 0;
    //int master_slave = 0;

    //unsigned int chosenIdx = 0;
 
    // Open API
    if ((err = sdrplay_api_Open()) != sdrplay_api_Success)
    {
        printf("sdrplay_api_Open failed %s\n", sdrplay_api_GetErrorString(err));
    }
    else
    {
        printf("Device opened...\n");

        //
        // Enable debug logging output
        if ((err = sdrplay_api_DebugEnable(NULL, 1)) != sdrplay_api_Success)
        {
            printf("sdrplay_api_DebugEnable failed %s\n", sdrplay_api_GetErrorString(err));
        }
        

        // Lock API while device selection is performed
        sdrplay_api_LockDeviceApi();


        // Get Devices
        unsigned int maxDevs = 6;  // max number of devices on the device list
        unsigned int ndevs = 6;
        sdrplay_api_DeviceT devs[6];
        sdrplay_api_GetDevices(devs, &ndevs, maxDevs);
        printf("We have %i device(s)\n", ndevs);

        // Select the devices
        sdrplay_api_DeviceT *sdr = &devs[ndevs - 1];
        sdrplay_api_SelectDevice(sdr);
        printf("We have selected the device...\n");
        
        // Edit the device's parameters
        //sdrplay_api_GetDeviceParams

        // Initialise the device
        sdrplay_api_CallbackFnsT cbFns;
        cbFns.StreamACbFn = DataStreamCallback;
        cbFns.StreamBCbFn = DataStreamCallback;
        cbFns.EventCbFn = EventCallback;

        sdrplay_api_Init(sdr->dev, &cbFns, NULL);
        printf("Intialising device...\n");

        while(1){
            sleep(1000);
        }

        // Unlock API whilst the device has been used
        sdrplay_api_UnlockDeviceApi();
    }


    // Close API
    if ((err =  sdrplay_api_Close()) == sdrplay_api_Success) {
        printf("Closing device...\n");
    } else {
        printf("sdrplay_api_Close failed %s - unable to close the device\n", sdrplay_api_GetErrorString(err));
    }

    
    return 1;
}