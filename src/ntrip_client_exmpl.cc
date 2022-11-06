#include "ntrip/ntrip_client.h"

#include <unistd.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstring>

#include <fstream>

#include "ntrip/ntrip_util.h"


using libntrip::NtripClient;

int main(int argc, char* argv[]) {
    std::string ip = "127.0.0.1";
    int port = 8090;
    std::string user = "test01";
    std::string passwd = "123456";
    std::string mountpoint = "RTCM32";
    if (argc < 7 || argc > 7) {
        std::cout << "Used default parameters" << std::endl
                  << "For customize use:" << std::endl
                  << "./ntrip_client ip port user passwd mountpoint output" << std::endl
                  << "example: ./ntrip_client 127.0.0.1 8090 test01 123456 RTCM32 stdout" << std::endl;
    } else {
        std::cout << "Setting customize parameters" << std::endl;
        ip = argv[1];
        port = atoi(argv[2]);
        user = argv[3];
        passwd = argv[4];
        mountpoint = argv[5];
    }
    NtripClient ntrip_client;
    ntrip_client.Init(ip, port, user, passwd, mountpoint);
    if (strcmp(argv[6], "file")) {
        std::cout << "setted output is " << argv[6] << std::endl;
        ntrip_client.OnReceived([](const char* buffer, int size) {
            std::cout << "Recv[" << size << "]: ";
            for (int i = 0; i < size; ++i) {
                std::cout << std::hex << std::setw(2) << static_cast<int>(static_cast<unsigned char>(buffer[i])) << ' ';
            }
            std::cout << std::endl;
        });
    } else {
        std::cout << "setted output is " << argv[6] << std::endl;
        ntrip_client.OnReceived([](const char* buffer, int size) {
            std::ofstream output{"./ntrip.log", std::ios::app};
            if (output.is_open()) {
                output << "Recv[" << size << "]: ";
                for (int i = 0; i < size; ++i) {
                    output << std::hex << static_cast<int>(static_cast<unsigned char>(buffer[i])) << ' ';
                }
                output << std::endl;
                output.close();
            }
        });
    }
    ntrip_client.set_location(22.57311, 113.94905);
    ntrip_client.set_report_interval(10);
    ntrip_client.Run();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (ntrip_client.service_is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ntrip_client.Stop();
    return 0;
}
