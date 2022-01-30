# E-nose
Bill 's NSC project for develop ML model  for inference smell.


## Prepare Environments and Tools

1. Install Arduino IDE
     - install library : AduinoJson
     - install [CH43x](https://sparks.gogo.co.nz/ch340.html) [driver](http://www.mediafire.com/file/c9pyi2u7g93iqt6/CH341SER.ZIP/file) usb to serial    
     - board manager : Arduino Mega/Mega 2560
2. Install Anaconda
     - Create Environment python3.8
     - install packages 
       >  conda install pyserial
       
       > conda install pandas pyarrow
3. Install pyCharm Community
    install plug-in 
   1. Avro and Parquet Viewer
4. Install Orange data mining
5. Set pyCharm Interplator to Orange directory.
6. Goto Python Console on Pycharm 
     - install micromlgen
        >  !pip install micromlgen
     - copy vote.arduino.jinja to C:\PATH_TO_ORANGE\Orange\Lib\site-packages\micromlgen\templates\logisticregression\
7. Clone Git repo for this project
     - https://github.com/Pirachat/E-nose.git