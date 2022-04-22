EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L stm32f091-cache:STM32F091RCTx U6
U 1 1 625EC76C
P 5600 3800
F 0 "U6" H 5550 1911 50  0000 C CNN
F 1 "STM32F091RCTx" H 5550 1820 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 5000 2100 50  0001 R CNN
F 3 "" H 5600 3800 50  0001 C CNN
	1    5600 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5600 5300 6100
Wire Wire Line
	5300 6100 5400 6100
Wire Wire Line
	5400 6100 5400 5600
Wire Wire Line
	5500 5600 5500 6100
Connection ~ 5400 6100
Wire Wire Line
	5600 5600 5600 6100
Wire Wire Line
	5600 6100 5500 6100
Connection ~ 5500 6100
Wire Wire Line
	5700 5600 5700 6100
Wire Wire Line
	5700 6100 5600 6100
Connection ~ 5600 6100
$Comp
L stm32f091-cache:power_GND #PWR0101
U 1 1 625F1154
P 3950 700
F 0 "#PWR0101" H 3950 450 50  0001 C CNN
F 1 "power_GND" H 3955 527 50  0000 C CNN
F 2 "" H 3950 700 50  0001 C CNN
F 3 "" H 3950 700 50  0001 C CNN
	1    3950 700 
	1    0    0    -1  
$EndComp
$Comp
L stm32f091-cache:power_+5V #PWR0102
U 1 1 625F18E3
P 4350 750
F 0 "#PWR0102" H 4350 600 50  0001 C CNN
F 1 "power_+5V" H 4365 923 50  0000 C CNN
F 2 "" H 4350 750 50  0001 C CNN
F 3 "" H 4350 750 50  0001 C CNN
	1    4350 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 750  4350 800 
Wire Wire Line
	4350 1150 4650 1150
Wire Wire Line
	5250 2000 5300 2000
Wire Wire Line
	5400 2000 5300 2000
Connection ~ 5300 2000
Wire Wire Line
	5400 2000 5500 2000
Connection ~ 5400 2000
Wire Wire Line
	5500 2000 5600 2000
Connection ~ 5500 2000
Wire Wire Line
	5600 2000 5700 2000
Connection ~ 5600 2000
Wire Wire Line
	5700 2000 5800 2000
Connection ~ 5700 2000
Wire Wire Line
	3950 6100 5300 6100
Connection ~ 5300 6100
Wire Wire Line
	5400 6100 5500 6100
Wire Wire Line
	4050 1100 3950 1100
Connection ~ 3950 1100
Wire Wire Line
	4950 1450 3950 1450
Wire Wire Line
	3950 1100 3950 1250
Connection ~ 3950 1450
$Comp
L Connector:AudioJack4 J1
U 1 1 62608F2E
P 1500 1800
F 0 "J1" V 1411 1988 50  0000 L CNN
F 1 "AudioJack4" V 1502 1988 50  0000 L CNN
F 2 "ece362 footprints:audioJack" H 1500 1800 50  0001 C CNN
F 3 "~" H 1500 1800 50  0001 C CNN
	1    1500 1800
	0    1    1    0   
$EndComp
$Comp
L ece362~library:joystick_or_servo U8
U 1 1 6260C199
P 9250 3650
F 0 "U8" H 9677 3754 50  0000 L CNN
F 1 "joystick_or_servo" H 9677 3845 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 9250 3550 50  0001 C CNN
F 3 "" H 9250 3550 50  0001 C CNN
	1    9250 3650
	1    0    0    -1  
$EndComp
$Comp
L ece362~library:joystick_or_servo U13
U 1 1 6260F8E1
P 9300 3000
F 0 "U13" H 9727 3104 50  0000 L CNN
F 1 "joystick_or_servo" H 9727 3195 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 9300 2900 50  0001 C CNN
F 3 "" H 9300 2900 50  0001 C CNN
	1    9300 3000
	1    0    0    -1  
$EndComp
$Comp
L ece362~library:joystick_or_servo U12
U 1 1 6261062B
P 9300 2400
F 0 "U12" H 9727 2504 50  0000 L CNN
F 1 "joystick_or_servo" H 9727 2595 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 9300 2300 50  0001 C CNN
F 3 "" H 9300 2300 50  0001 C CNN
	1    9300 2400
	1    0    0    -1  
$EndComp
$Comp
L ece362~library:joystick_or_servo U9
U 1 1 62611ACA
P 9250 4300
F 0 "U9" H 9677 4404 50  0000 L CNN
F 1 "joystick_or_servo" H 9677 4495 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 9250 4200 50  0001 C CNN
F 3 "" H 9250 4200 50  0001 C CNN
	1    9250 4300
	1    0    0    -1  
$EndComp
$Comp
L ece362~library:joystick_or_servo U10
U 1 1 62611FCF
P 9250 4850
F 0 "U10" H 9677 4954 50  0000 L CNN
F 1 "joystick_or_servo" H 9677 5045 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 9250 4750 50  0001 C CNN
F 3 "" H 9250 4750 50  0001 C CNN
	1    9250 4850
	1    0    0    -1  
$EndComp
$Comp
L ece362~library:joystick_or_servo U11
U 1 1 626123D6
P 9250 5450
F 0 "U11" H 9677 5554 50  0000 L CNN
F 1 "joystick_or_servo" H 9677 5645 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 9250 5350 50  0001 C CNN
F 3 "" H 9250 5350 50  0001 C CNN
	1    9250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2300 9250 2300
Wire Wire Line
	9250 2300 9250 2250
Wire Wire Line
	6200 2400 9250 2400
Wire Wire Line
	9250 2400 9250 2850
Wire Wire Line
	6200 2500 9200 2500
Wire Wire Line
	9200 2500 9200 3500
Wire Wire Line
	6200 4000 9200 4000
Wire Wire Line
	9200 4000 9200 4150
Wire Wire Line
	6200 4300 9200 4300
Wire Wire Line
	9200 4300 9200 4700
Wire Wire Line
	6200 4400 8700 4400
Wire Wire Line
	8700 4400 8700 5300
Wire Wire Line
	8700 5300 9200 5300
Wire Wire Line
	9550 5100 10800 5100
Wire Wire Line
	10800 5100 10800 4500
Connection ~ 4350 800 
Wire Wire Line
	4350 800  4350 950 
Wire Wire Line
	9550 4500 10800 4500
Connection ~ 10800 4500
Wire Wire Line
	9550 3950 10800 3950
Wire Wire Line
	10800 800  10800 2050
Connection ~ 10800 3950
Wire Wire Line
	10800 3950 10800 4500
Wire Wire Line
	9550 3300 10800 3300
Connection ~ 10800 3300
Wire Wire Line
	10800 3300 10800 3950
Wire Wire Line
	9600 2650 10800 2650
Connection ~ 10800 2650
Wire Wire Line
	10800 2650 10800 3300
Wire Wire Line
	9600 2050 10800 2050
Connection ~ 10800 2050
Wire Wire Line
	10800 2050 10800 2650
Wire Wire Line
	9550 5500 11000 5500
Connection ~ 3950 700 
Wire Wire Line
	3950 700  3950 1100
Wire Wire Line
	9550 4900 11000 4900
Connection ~ 11000 4900
Wire Wire Line
	11000 4900 11000 4350
Wire Wire Line
	9550 4350 11000 4350
Connection ~ 11000 4350
Wire Wire Line
	11000 4350 11000 3700
Wire Wire Line
	9550 3700 11000 3700
Connection ~ 11000 3700
Wire Wire Line
	11000 3700 11000 3050
Wire Wire Line
	9600 3050 11000 3050
Connection ~ 11000 3050
Wire Wire Line
	11000 3050 11000 2450
Wire Wire Line
	9600 2450 11000 2450
Connection ~ 11000 2450
Wire Wire Line
	11000 2450 11000 600 
$Comp
L ece362~library:joystick_or_servo U1
U 1 1 6262D36D
P 1650 2850
F 0 "U1" H 2077 2954 50  0000 L CNN
F 1 "joystick_or_servo" H 2077 3045 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 1650 2750 50  0001 C CNN
F 3 "" H 1650 2750 50  0001 C CNN
	1    1650 2850
	-1   0    0    1   
$EndComp
$Comp
L ece362~library:joystick_or_servo U2
U 1 1 6262EF32
P 1650 3600
F 0 "U2" H 2077 3704 50  0000 L CNN
F 1 "joystick_or_servo" H 2077 3795 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 1650 3500 50  0001 C CNN
F 3 "" H 1650 3500 50  0001 C CNN
	1    1650 3600
	-1   0    0    1   
$EndComp
$Comp
L ece362~library:joystick_or_servo U3
U 1 1 626304E3
P 1650 4400
F 0 "U3" H 2077 4504 50  0000 L CNN
F 1 "joystick_or_servo" H 2077 4595 50  0000 L CNN
F 2 "ece362 footprints:joysticks" H 1650 4300 50  0001 C CNN
F 3 "" H 1650 4300 50  0001 C CNN
	1    1650 4400
	-1   0    0    1   
$EndComp
$Comp
L ece362~library:rx_tx U14
U 1 1 6263411A
P 9500 6400
F 0 "U14" H 10078 6821 50  0000 L CNN
F 1 "rx_tx" H 10078 6730 50  0000 L CNN
F 2 "ece362 footprints:txrx" H 9500 6400 50  0001 C CNN
F 3 "" H 9500 6400 50  0001 C CNN
	1    9500 6400
	1    0    0    -1  
$EndComp
$Comp
L ece362~library:lcdscreen U7
U 1 1 62635573
P 9200 800
F 0 "U7" H 9222 1137 50  0000 R CNN
F 1 "lcdscreen" H 9222 1228 50  0000 R CNN
F 2 "ece362 footprints:lcd screen" H 9200 800 50  0001 C CNN
F 3 "" H 9200 800 50  0001 C CNN
	1    9200 800 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3900 2450 3900
Wire Wire Line
	2450 3900 2450 3000
Wire Wire Line
	2450 3000 1700 3000
Wire Wire Line
	1700 3750 2300 3750
Wire Wire Line
	2300 3750 2300 4000
Wire Wire Line
	2300 4000 4900 4000
Wire Wire Line
	4900 4100 2300 4100
Wire Wire Line
	2300 4100 2300 4550
Wire Wire Line
	2300 4550 1700 4550
$Comp
L Device:R_POT_US RV1
U 1 1 6263C923
P 1450 5200
F 0 "RV1" H 1383 5246 50  0000 R CNN
F 1 "R_POT_US" H 1383 5155 50  0000 R CNN
F 2 "ece362 footprints:joysticks" H 1450 5200 50  0001 C CNN
F 3 "~" H 1450 5200 50  0001 C CNN
	1    1450 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV2
U 1 1 6263DAEC
P 1450 5750
F 0 "RV2" H 1383 5796 50  0000 R CNN
F 1 "R_POT_US" H 1383 5705 50  0000 R CNN
F 2 "ece362 footprints:joysticks" H 1450 5750 50  0001 C CNN
F 3 "~" H 1450 5750 50  0001 C CNN
	1    1450 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV3
U 1 1 6263F769
P 1450 6350
F 0 "RV3" H 1383 6396 50  0000 R CNN
F 1 "R_POT_US" H 1383 6305 50  0000 R CNN
F 2 "ece362 footprints:joysticks" H 1450 6350 50  0001 C CNN
F 3 "~" H 1450 6350 50  0001 C CNN
	1    1450 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2000 1300 2150
Wire Wire Line
	1400 2150 1400 2000
Wire Wire Line
	650  4350 1350 4350
Wire Wire Line
	650  4350 650  3550
Wire Wire Line
	650  3550 1350 3550
Connection ~ 650  4350
Wire Wire Line
	650  3550 650  2800
Wire Wire Line
	650  2800 1350 2800
Connection ~ 650  3550
Wire Wire Line
	650  2800 650  2500
Connection ~ 650  2800
Connection ~ 3950 600 
Wire Wire Line
	1600 5200 4300 5200
Wire Wire Line
	4300 5200 4300 4200
Wire Wire Line
	4300 4200 4900 4200
Wire Wire Line
	1600 5750 4700 5750
Wire Wire Line
	4700 5750 4700 4300
Wire Wire Line
	4700 4300 4900 4300
Wire Wire Line
	1600 6350 4800 6350
Wire Wire Line
	4800 6350 4800 4400
Wire Wire Line
	4800 4400 4900 4400
Wire Wire Line
	11000 4900 11000 5500
Connection ~ 11000 5500
Wire Wire Line
	11000 5500 11000 6350
Wire Wire Line
	9350 6350 9950 6350
Connection ~ 9950 6350
Wire Wire Line
	9950 6350 11000 6350
Wire Wire Line
	9350 5700 9950 5700
Wire Wire Line
	10800 5700 10800 5100
Connection ~ 9950 5700
Wire Wire Line
	9950 5700 10800 5700
Connection ~ 10800 5100
Wire Wire Line
	9100 6000 6800 6000
Wire Wire Line
	6800 6000 6800 4900
Wire Wire Line
	6800 4900 6200 4900
Wire Wire Line
	1500 2000 1500 2350
Wire Wire Line
	1500 2350 650  2350
Connection ~ 650  2350
Wire Wire Line
	650  2350 650  600 
$Comp
L Device:R_POT_US RV4
U 1 1 6268A4B6
P 2300 2350
F 0 "RV4" H 2232 2304 50  0000 R CNN
F 1 "R_POT_US" H 2232 2395 50  0000 R CNN
F 2 "ece362 footprints:joysticks" H 2300 2350 50  0001 C CNN
F 3 "~" H 2300 2350 50  0001 C CNN
	1    2300 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	650  4350 650  5050
Wire Wire Line
	1450 5050 650  5050
Connection ~ 650  5050
Wire Wire Line
	650  5050 650  5600
Wire Wire Line
	1450 5600 650  5600
Connection ~ 650  5600
Wire Wire Line
	650  5600 650  6200
Wire Wire Line
	1450 6200 650  6200
Wire Wire Line
	2150 2150 2150 2350
Wire Wire Line
	1300 2150 1400 2150
Connection ~ 1400 2150
Wire Wire Line
	1400 2150 2150 2150
Wire Wire Line
	2300 2500 650  2500
Connection ~ 650  2500
Wire Wire Line
	650  2500 650  2350
$Comp
L Device:CP1 C2
U 1 1 626E8A35
P 3400 1700
F 0 "C2" V 3148 1700 50  0000 C CNN
F 1 "10 uF" V 3239 1700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3400 1700 50  0001 C CNN
F 3 "~" H 3400 1700 50  0001 C CNN
	1    3400 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 1700 2300 1700
Wire Wire Line
	2300 1700 2300 2200
Wire Wire Line
	6250 2600 6200 2600
Wire Wire Line
	6250 2600 6250 1700
Wire Wire Line
	6250 1700 3550 1700
Wire Wire Line
	1450 5350 550  5350
Wire Wire Line
	550  6500 1450 6500
Wire Wire Line
	1450 5900 550  5900
Connection ~ 550  5900
Wire Wire Line
	550  5900 550  6500
Wire Wire Line
	550  1500 5250 1500
Wire Wire Line
	550  1500 550  3200
Connection ~ 550  5350
Wire Wire Line
	550  5350 550  5900
Wire Wire Line
	5250 1500 5250 1600
Wire Wire Line
	1350 3200 550  3200
Connection ~ 550  3200
Wire Wire Line
	550  3200 550  3950
Wire Wire Line
	1350 3950 550  3950
Connection ~ 550  3950
Wire Wire Line
	550  3950 550  4750
Wire Wire Line
	1350 4750 550  4750
Connection ~ 550  4750
Wire Wire Line
	550  4750 550  5350
$Comp
L Device:CP1 C4
U 1 1 6271BDBA
P 8250 1700
F 0 "C4" H 8365 1746 50  0000 L CNN
F 1 "10 uF" H 8365 1655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8250 1700 50  0001 C CNN
F 3 "~" H 8250 1700 50  0001 C CNN
	1    8250 1700
	1    0    0    -1  
$EndComp
$Comp
L stm32f091-cache:Device_C C3
U 1 1 6271D569
P 7650 1700
F 0 "C3" H 7765 1746 50  0000 L CNN
F 1 "0.1 uF" H 7765 1655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7688 1550 50  0001 C CNN
F 3 "" H 7650 1700 50  0001 C CNN
	1    7650 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1400 8250 1550
Connection ~ 8250 1550
Wire Wire Line
	8350 1400 8350 1850
Connection ~ 8250 1850
Wire Wire Line
	8250 1850 8350 1850
Wire Wire Line
	7150 1850 7650 1850
Connection ~ 7650 1850
Wire Wire Line
	7650 1850 8250 1850
Wire Wire Line
	7650 1550 7850 1550
Wire Wire Line
	7850 1550 7850 1150
Wire Wire Line
	7850 1150 5900 1150
Connection ~ 7850 1550
Wire Wire Line
	7850 1550 8250 1550
Wire Wire Line
	6200 2900 8750 2900
Wire Wire Line
	8750 2900 8750 1400
Wire Wire Line
	6200 2700 8850 2700
Wire Wire Line
	8850 2700 8850 1400
Wire Wire Line
	8250 1550 8950 1550
Wire Wire Line
	8950 1550 8950 1400
Wire Wire Line
	6200 5300 8650 5300
Wire Wire Line
	8650 5300 8650 1400
Wire Wire Line
	6200 5000 8550 5000
Wire Wire Line
	8550 5000 8550 1400
Wire Wire Line
	6200 4700 8450 4700
Wire Wire Line
	8450 4700 8450 1400
Wire Wire Line
	4350 800  10800 800 
Wire Wire Line
	7150 1850 7150 600 
Wire Wire Line
	3950 600  7150 600 
Connection ~ 7150 600 
Wire Wire Line
	7150 600  11000 600 
$Comp
L ece362~library:programmerblock U4
U 1 1 626433FD
P 3300 3050
F 0 "U4" H 3628 3404 50  0000 L CNN
F 1 "programmerblock" H 3628 3313 50  0000 L CNN
F 2 "ece362 footprints:programmerblockthing" H 3300 3050 50  0001 C CNN
F 3 "" H 3300 3050 50  0001 C CNN
	1    3300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2550 3250 1850
Wire Wire Line
	3250 1850 6650 1850
Wire Wire Line
	6650 1850 6650 3600
Wire Wire Line
	6650 3600 6200 3600
Wire Wire Line
	3350 2550 3350 2500
Wire Wire Line
	3350 2500 4600 2500
Wire Wire Line
	4600 2500 4600 6850
Wire Wire Line
	4600 6850 5500 6850
Wire Wire Line
	5500 6850 5500 6100
Wire Wire Line
	3450 2550 3450 1950
Wire Wire Line
	3450 1950 6750 1950
Wire Wire Line
	6750 1950 6750 3500
Wire Wire Line
	6750 3500 6200 3500
Wire Wire Line
	3550 2550 3550 2200
Wire Wire Line
	3150 2550 3150 950 
Wire Wire Line
	3150 950  4350 950 
Connection ~ 4350 950 
$Comp
L Diode:BAT60A D1
U 1 1 626855C9
P 5250 1350
F 0 "D1" H 5250 1567 50  0000 C CNN
F 1 "BAT60A" H 5250 1476 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 5250 1175 50  0001 C CNN
F 3 "https://www.infineon.com/dgdl/Infineon-BAT60ASERIES-DS-v01_01-en.pdf?fileId=db3a304313d846880113def70c9304a9" H 5250 1350 50  0001 C CNN
	1    5250 1350
	0    -1   -1   0   
$EndComp
Connection ~ 5250 1500
Wire Wire Line
	5250 1200 5250 1150
Wire Wire Line
	5250 1500 5900 1500
Wire Wire Line
	5900 1500 5900 1150
$Comp
L stm32f091-cache:LD1117S33TR_SOT223 U5
U 1 1 626B9BCA
P 4950 1150
F 0 "U5" H 4950 1392 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 4950 1301 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4950 1350 50  0001 C CNN
F 3 "" H 5050 900 50  0001 C CNN
	1    4950 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 950  4350 1100
$Comp
L Device:C_Small C12
U 1 1 626BABF1
P 4150 1100
F 0 "C12" V 3921 1100 50  0000 C CNN
F 1 "C_Small" V 4012 1100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4150 1100 50  0001 C CNN
F 3 "~" H 4150 1100 50  0001 C CNN
	1    4150 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 1100 4250 1100
Connection ~ 4350 1100
Wire Wire Line
	4350 1100 4350 1150
$Comp
L Device:C_Small C1
U 1 1 626C50D1
P 4150 1250
F 0 "C1" V 3921 1250 50  0000 C CNN
F 1 "22 uF" V 4012 1250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4150 1250 50  0001 C CNN
F 3 "~" H 4150 1250 50  0001 C CNN
	1    4150 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 1150 4250 1150
Connection ~ 4350 1150
Connection ~ 3950 1250
Wire Wire Line
	3950 1250 3950 1450
Wire Wire Line
	3950 1250 4050 1250
$Comp
L Device:C_Small C6
U 1 1 626E2E01
P 5150 1600
F 0 "C6" V 4921 1600 50  0000 C CNN
F 1 "C_Small" V 5012 1600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5150 1600 50  0001 C CNN
F 3 "~" H 5150 1600 50  0001 C CNN
	1    5150 1600
	0    1    1    0   
$EndComp
Connection ~ 5250 1600
Wire Wire Line
	5250 1600 5250 1800
Wire Wire Line
	5050 1600 3950 1600
Wire Wire Line
	3950 1450 3950 1600
Connection ~ 3950 1600
Wire Wire Line
	3950 1600 3950 1800
$Comp
L Device:C_Small C7
U 1 1 626EDC42
P 5150 1800
F 0 "C7" V 4921 1800 50  0000 C CNN
F 1 "C_Small" V 5012 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5150 1800 50  0001 C CNN
F 3 "~" H 5150 1800 50  0001 C CNN
	1    5150 1800
	0    1    1    0   
$EndComp
Connection ~ 5250 1800
Wire Wire Line
	5250 1800 5250 2000
Wire Wire Line
	5050 1800 3950 1800
Connection ~ 3950 1800
Wire Wire Line
	3950 1800 3950 6100
$Comp
L Device:R_Small_US R2
U 1 1 62707E9E
P 4350 3500
F 0 "R2" V 4145 3500 50  0000 C CNN
F 1 "R_Small_US" V 4236 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4350 3500 50  0001 C CNN
F 3 "~" H 4350 3500 50  0001 C CNN
	1    4350 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 3500 4450 3500
Wire Wire Line
	3950 600  3950 700 
Wire Wire Line
	4250 1150 4250 1250
Wire Wire Line
	4250 3500 2750 3500
Wire Wire Line
	2750 3500 2750 600 
Connection ~ 2750 600 
Wire Wire Line
	2750 600  3950 600 
$Comp
L stm32f091-cache:Switch_SW_Push SW1
U 1 1 627297FD
P 1850 1100
F 0 "SW1" H 1850 1385 50  0000 C CNN
F 1 "Switch_SW_Push" H 1850 1294 50  0000 C CNN
F 2 "ece362 footprints:nrstButton" H 1850 1300 50  0001 C CNN
F 3 "" H 1850 1300 50  0001 C CNN
	1    1850 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2200 4900 2200
Wire Wire Line
	3550 2200 2950 2200
Wire Wire Line
	2950 2200 2950 1100
Wire Wire Line
	2950 1100 2300 1100
Connection ~ 3550 2200
Wire Wire Line
	1650 1100 1650 600 
Wire Wire Line
	650  600  1650 600 
Connection ~ 1650 600 
Wire Wire Line
	1650 600  2300 600 
$Comp
L Device:C_Small C5
U 1 1 62759D04
P 2300 1000
F 0 "C5" H 2392 1046 50  0000 L CNN
F 1 "C_Small" H 2392 955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2300 1000 50  0001 C CNN
F 3 "~" H 2300 1000 50  0001 C CNN
	1    2300 1000
	1    0    0    -1  
$EndComp
Connection ~ 2300 1100
Wire Wire Line
	2300 1100 2200 1100
Wire Wire Line
	2300 900  2300 600 
Connection ~ 2300 600 
Wire Wire Line
	2300 600  2750 600 
$Comp
L stm32f091-cache:Device_R_US R1
U 1 1 627679F8
P 2200 1250
F 0 "R1" H 2268 1296 50  0000 L CNN
F 1 "Device_R_US" H 2268 1205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2240 1240 50  0001 C CNN
F 3 "" H 2200 1250 50  0001 C CNN
	1    2200 1250
	1    0    0    -1  
$EndComp
Connection ~ 2200 1100
Wire Wire Line
	2200 1100 2050 1100
Wire Wire Line
	2200 1400 4550 1400
Wire Wire Line
	4550 1400 4550 2000
Wire Wire Line
	4550 2000 5250 2000
Connection ~ 5250 2000
$EndSCHEMATC
