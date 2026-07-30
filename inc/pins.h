

// Stepper control pins
#define TRIS_Step	                _TRISB11
#define PORT_Step 	                _RB11
#define LAT_Step 	                _LATB11
#define ODC_Step	                _ODB11
#define PIN_Step 	                _RB11
#define RPOUT_Step		            RPOR5bits.RP11R
#define RPIN_Step		            11
#define CN_Step		                15
#define TRIS_Dir	                _TRISB10
#define PORT_Dir 	                _RB10
#define LAT_Dir 	                _LATB10
#define ODC_Dir	                _ODB10
#define PIN_Dir 	                _RB10
#define RPOUT_Dir	                RPOR5bits.RP10R
#define RPIN_Dir	                10
#define CN_Dir		                16
#define TRIS_MS1	                _TRISB13
#define PORT_MS1 	                _RB13
#define LAT_MS1 	                _LATB13
#define ODC_MS1	                _ODB13
#define PIN_MS1 	                _RB13
#define RPOUT_MS1		            RPOR6bits.RP13R
#define RPIN_MS1		            13
#define CN_MS1		                13
#define ADC_value_MS1              Buffer_entradas[11] 
#define HAL_SetAnalog_MS1()        {_PCFG11=0;\
                                        adc_addAnalogChannel(11);}

#define TRIS_MS2	                _TRISB12
#define PORT_MS2 	                _RB12
#define LAT_MS2 	                _LATB12
#define ODC_MS2	                _ODB12
#define PIN_MS2 	                _RB12
#define RPOUT_MS2		            RPOR6bits.RP12R
#define RPIN_MS2		            12
#define CN_MS2		                14
#define ADC_value_MS2              Buffer_entradas[12]
#define HAL_SetAnalog_MS2()        {_PCFG12=0;\
                                        adc_addAnalogChannel(12);}

#define TRIS_SLP	                _TRISB15
#define PORT_SLP 	                _RB15
#define LAT_SLP 	                _LATB15
#define ODC_SLP	                _ODB15
#define PIN_SLP 	                _RB15
#define RPOUT_SLP	                RPOR7bits.RP15R
#define RPIN_SLP	                15
#define CN_SLP		                11
#define ADC_value_SLP              Buffer_entradas[9] 
#define HAL_SetAnalog_SLP()        {_PCFG9=0;\
                                        adc_addAnalogChannel(9);}
#define TRIS_LimitSw	                _TRISB14
#define PORT_LimitSw 	                _RB14
#define LAT_LimitSw 	                _LATB14
#define ODC_LimitSw	                _ODB14
#define PIN_LimitSw 	                _RB14
#define RPOUT_LimitSw	                RPOR7bits.RP14R
#define RPIN_LimitSw	                14
#define CN_LimitSw		                12
#define ADC_value_LimitSw              Buffer_entradas[10] 
#define HAL_SetAnalog_LimitSw()        {_PCFG10=0;\
                                        adc_addAnalogChannel(10);}


// LEDs
#define TRIS_Led1	                _TRISB9
#define PIN_Led1 	                _RB9
#define LAT_Led1 	                _LATB9
#define ODC_Led1	                _ODB9
#define RPOUT_Led1		            RPOR4bits.RP9R
#define RPIN_Led1		            9
#define CN_Led1		                21
#define TRIS_Led2	                _TRISB8
#define PIN_Led2 	                _RB8
#define LAT_Led2 	                _LATB8
#define ODC_Led2	                _ODB8
#define RPOUT_Led2		            RPOR4bits.RP8R
#define RPIN_Led2		            8
#define CN_Led2		                22

// Board name

