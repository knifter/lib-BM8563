# lib-BM8563

Arduino/ESP32 driver for the **BM8563** I2C real-time clock IC (used on M5Stack devices).

Built on [lib-TwoWireDevice](https://github.com/knifter/lib-TwoWireDevice).

## Features

- Read and write date/time using standard C `struct tm` and `struct timeval`
- Supports multiple I2C buses and custom I2C address override
- Default I2C address: `0x51`

## Usage

```cpp
#include <BM8563.h>

BM8563 rtc(Wire);

void setup() {
    Wire.begin();
    rtc.begin();

    struct tm now;
    rtc.readDateTime(&now);
}
```

## PlatformIO

```ini
lib_deps =
    https://github.com/knifter/lib-BM8563
```

## Dependencies

- [lib-TwoWireDevice](https://github.com/knifter/lib-TwoWireDevice)
- [lib-tools](https://github.com/knifter/lib-tools)

## Author
This software is written by [Tijs van Roon](https://github.com/knifter). It is free to use under the [MIT License](LICENSE).
