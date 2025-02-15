## Clone no-OS-FatFS-SD-SPI-RPi-Pico

Create a subdirectory called lib and clone the repository

## Required modifications

Uncomment commented line in FatFS_SPI/CMakeLists.txt

Modify (copy from one place to another) files in FatFS_SPI:
  
  Required:
 * /source:
   *  00history.txt
  * 00readme.txt
  *  diskio.c
  *  diskio.h
  *  ff.c
  *  ff.h
  *  ffconf.h
  *  ffsystem.c
  *  ffunicode.c
 * /include:
  *  f_util.h
  *  ff_stdio.h
  *  my_debug.h
  *  rtc.h
  *  util.h
 * /sd_driver:
  *  crc.c
  *  crc.h
  *  demo_logging.c
  *  ff.c
  *  ff.h
  *  hw_config.c
  *  hw_config.h
  *  my_debug.c
  *  my_debug.h
  *  sd_card.c
  *  sd_card.h
  *  sd_spi.c
  *  sd_spi.h
  *  spi.c
  *  spi.h
* /src:
  *  f_util.c
  *  ff_stdio.c
  *  glue.c
  *  my_debug.c
  *  rtc.c
