# ESP32-Serial-To-Network-Bridge
An Arduino sketch for translating a network connection to an RS232 connection at 300 baud, for a slow typewriter (Brother EP-22)

by Nino Ivanov, April 2025

If you are having a dumb terminal, and in particular a hardcopy terminal, and you wish to control a device with it that does not permit directly a serial connection (e.g. some iOS device like an iPhone, or many Android devices, your "mainframe" of sorts), then using an ESP32 microcontroller board, you may upload the attached sketch, and you will gain the ESP32 as a "Wifi server" to which the "mainframe" can connect over Netcat at port 8088. Then, whatever the typewriter/hardcopy terminal/printing terminal is typing, arrives at the "mainframe", and whatever the "mainframe" sends is printed out.

In its simplest use, the RS232-to-Wifi bridge may be utilized to facilitate printing: the "mainframe" simply pipes out the entire document in text-only-form to the terminal, which then prints it.

By nature, the bridge is bidirectional and would translate "network to RS232" and "RS232 to network", but in case of an output-only-terminal, if you still wish to achieve "an effect LIKE on a printing terminal", you evidently will have to still do all the actual typing on the "mainframe", but the output can be channeled, e.g. from Termux or Linux on Android, or iSH on iOS, to the "terminal", with this pipe, which will show both the command typed as well as its reply, for an sh shell:

stdbuf -e0 -o0 tee >(stdbuf -e0 -o0 sh 2>&1 | stdbuf -e0 -o0 tee /dev/stderr) | stdbuf -e0 -o0 nc 192.168.4.1 8088

... or in a variant, if you do not wish to run sh but bwbasic, and if you do you wish to see the output on the "mainframe" (but ONLY on the typewriter):

stdbuf -e0 -o0 tee >(stdbuf -e0 -o0 bwbasic 2>&1) | stdbuf -e0 -o0 nc 192.168.4.1 8088

Delays are hardcoded in the sketch, to allow the typewriter to "catch up" / "keep up" with the "mainframe" output. Instead, if you prefer your own delays, you may add them over "pv" in the above pipe (adivisable to do so twice for greater accuracy), and set "delay(0);" instead of "delay(125);" / "delay(750);" in the Arduino sketch, e.g. running SBCL Lisp for 5 characters per second (about teletype speed; note the TWO pv, so as to avoid "too fast character dumps" that seem to happen at the beginning otherwise, and optionally adding a 5 spaces margin left and right (on 80 columns) via pr):

no margin:


stdbuf -e0 -o0 tee >(stdbuf -e0 -o0 sbcl --noinform 2>&1 | stdbuf -e0 -o0 tee /dev/stderr) | pv -L 5 2>/dev/null | pv -L 5 2>/dev/null | stdbuf -e0 -o0 nc 192.168.4.1 8088

with margin:

stdbuf -e0 -o0 tee >(stdbuf -e0 -o0 sbcl --noinform 2>&1 | stdbuf -e0 -o0 tee /dev/stderr) | pv -L 5 2>/dev/null | pr -t -o 5 -w 75 | pv -L 5 2>/dev/null | stdbuf -e0 -o0 nc 192.168.4.1 8088

When reset, the ESP32 outputs its network name, password as well as IP address and port - in case you forget... :)

Two variants are shown - one that also adds automatically a margin, and one without.

For a demonstration, see:

https://www.youtube.com/watch?v=M2M4mQGjXtM
