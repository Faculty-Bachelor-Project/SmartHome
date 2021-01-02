citeste LED_B_BL
citeste LED_G_BL
citeste LED_BL
citeste LED_PIR
citeste INP_PIR
citeste LED_TSL
citeste LED_B_TSL
citeste LED_G_TSL
citeste DHT_PIN
citeste COOLER_PIN
citeste MQ7_analog_IN
citeste MQ2_analog_IN
citeste humidity
citeste tempC
citeste tempF

Functie COSensor()

	daca Value >= 100 atunci
		porneste cooler
	altfel
		cooler oprit
	sfarsit daca

SfFunctie

Functie MonoxideSensorPrint()

	afiseaza pe LCD CO Value

SfFunctie

Functie GasSensorPrint()

	afiseaza pe LCD Gas Value

SfFunctie

Functie GasSensor()

	daca Value >= 170 atunci
		porneste cooler
	altfel
		cooler oprit
	sfarsit daca

SfFunctie

Functie DHTSensor()

	afisare pe LCD tempC

SfFunctie

Functie TSLSensor()

citeste visible

	daca detectez lumina atunci
		daca visible > 20000 atunci
			stige LED_RGB
		altfel
			aprinde LED_RGB
		sfarsit daca
	altfel
		afiseaza erroare
	sfarsit daca

SfFunctie

Functie PIRSensor()

	daca detectez miscare atunci
		aprinde LED_RGB
	altfel
		LED_RGB stins
	sfarsit daca

SfFunctie

Functie light_color()

	daca state = 1 atunci
		aprinde LED_RGB
	altfel
		LED_RGB stins
	sfarsit daca

SfFunctie

Functie Bluetooth()

citeste incoming_value

	daca incoming_value = 1 atunci
		aprinde LED_RGB
	altfel
		LED_RGB stins
	sfarsit daca

	daca incoming_value = a atunci
		afiseaza pe LCD DHTSensor
	altfel daca incoming_value = b atunci
		afiseaza pe LCD GasSensorPrint
	altfel daca incoming_value = c atunci
		afiseaza pe LCD MonoxideSensorPrint
	altfel daca incoming_value = 1 atuci
		afiseaza pe LCD DHTSensor
	sfarsit daca

SfFunctie