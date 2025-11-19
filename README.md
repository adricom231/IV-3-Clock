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

3.The enable hiside switches at the bottom (the 2 transisior thing) is kinda not working

If anybody needs the original f3d files or just the project files message me, right now i only leave gerber files and photos here.


Here are some more photos from this project:

https://github.com/user-attachments/assets/52ce1475-dcd7-491a-bb40-fd1fa4791a46

![IMG_20250628_190446561](https://github.com/user-attachments/assets/1549947b-319a-43ce-9e4c-d4360baf61f6)
![IMG_20250623_004346527 (1)](https://github.com/user-attachments/assets/6db98794-e997-4a63-b96a-ff6e2859f320)
![IMG_20250617_173658151](https://github.com/user-attachments/assets/4c9c9e69-d717-4207-be28-1063b9bef10b)
<img width="1370" height="696" alt="image-8" src="https://github.com/user-attachments/assets/9e7699e8-9578-4385-ae67-01b1e146339b" />
<img width="1332" height="692" alt="image-7" src="https://github.com/user-attachments/assets/5adc60de-c8c7-4aae-b184-f566e6573285" />
:

