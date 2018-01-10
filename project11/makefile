
all: tiltbuzz_1 tiltbuzz_2 tiltbuzz_3

clean: 
	rm -f tiltbuzz_1 tiltbuzz_2 tiltbuzz_3

tiltbuzz_1: tiltbuzz_1.c lcd1602.c pinreadwrite.c
	cc -o tiltbuzz_1 tiltbuzz_1.c lcd1602.c pinreadwrite.c -lwiringPi

tiltbuzz_2: tiltbuzz_2.c lcd1602.c pinreadwrite.c
	cc -o tiltbuzz_2 tiltbuzz_2.c  lcd1602.c pinreadwrite.c -lwiringPi

tiltbuzz_3: tiltbuzz_3.c lcd1602.c spilib.c pinreadwrite.c
	cc -o tiltbuzz_3 tiltbuzz_3.c  lcd1602.c spilib.c pinreadwrite.c -lwiringPi
