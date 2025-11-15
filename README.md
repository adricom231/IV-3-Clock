# IV-3-Clock
![IMG_20250623_004342028 (1)](https://github.com/user-attachments/assets/cd358967-8a4d-4d6b-a54a-8071e23abfed)
This is my IV-3 clock that i designed and made by myself and here is a breakdown of the whole thing

Its based around 6 IV-3 VFD tubes that are staticly lit using shift registers and hiside switches. The clock is powered by a seedstudio XIAO ESP32S3.
For providing power to it i used a Adafruit USB-C Trigger Board which provides 5V over PD. The 30V and 1V for the tubes are acquired by using two DC-DC converters which are (litearly) hanged from the bottom.
If your wondering why are the tubes staticly lit and not just connected in parralel its because i wanted to extend the tubes life and i thought that it would be simpler (it was not).

The library for the IV-3 tube was made using this calculator by Nick De'Smith https://nick.desmith.net/Electronics/soculator.html

If anybody wants to make one of these clocks themselfs here are some things that are wrong with this desing that you'll need to figure out:

1.The data lane for shift registers coming from GPIO3 needs to be cut from it and jumped to GPIO44 because of pinstrapping at boot which i havent thought about when designing.

2.The holes for the tube legs are very very tight so if you can go ahead and widen them

3.The enable hiside switches at the bottom (the 2 transisior thing) is kinda not working IDK WHY HELP

If anybody needs the original f3d files or just the project files message me, right now i only leave gerber files and photos here.
