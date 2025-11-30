# GCalendar Viewer
Start development with a FreeRTOS..


# Quickstart
## Arch
Maybe you want to install SDK with [esp8266-rtos-sdk AUR package](https://aur.archlinux.org/packages/esp8266-rtos-sdk)

Or more dirty:
## 1. Installing python2
Arch linux repositories does't have python2 version, to install use [AUR](https://wiki.archlinux.org/title/Arch_User_Repository), with [yay](https://aur.archlinux.org/packages/yay) package:
```bash
yay -S python2
```
Or direct from [python2 package](https://aur.archlinux.org/packages/python2)

## 2. Install ESP8266 RTOS SDK and Toolchain
[ESP8266 RTOS SDK Programming Guide](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/linux-setup.html)

## 3. Add enviroment variables:
Example export of **IDF_PATH**:
```bash
export IDF_PATH=~/.esp-toolchain/ESP8266_RTOS_SDK
```
And add /xtensa-lx106-elf/bin to PATH too
```bash
export PATH="$PATH:$HOME/.esp-toolchain/xtensa-lx106-elf/bin"
```

## 4. Install python2 dependences:

```bash
python python-click python-pyserial python-cryptography python-pyparsing python-future python-pyelftools ncurses
```

## 5. Generate&Configure **sdkconfig** file:
To make new or configure existing **sdkconfig** file run
```bash
make menuconfig
```
(Maybe you need to commented uncorrect python dependences check)

Important **sdkconfig** configuration settings:
- **SDK tool configuration ---> Python2 interpretater** to python2
- **Serial flasher config ---> Flash size** to esp8266 flash size

## 6. Build and flash
```bash
make flash
```