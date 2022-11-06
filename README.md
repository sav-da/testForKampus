# testForKampus
Test task from Campus LLC

For build use: <br>
```cmake -B build && cmake --build build -- -j20 ```

For run with custom parameters use: <br>
```./build/ntrip_client ip port user passwd mountpoint output```

For example: <br>
```./build/ntrip_client 127.0.0.1 8090 test01 123456 RTCM32 stdout```
