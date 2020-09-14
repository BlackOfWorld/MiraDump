#include <iostream>
#include "ConfigReader.h"
#include "Process.h"

int main() {
    DWORD procID = Process::GetProcId("csgo.exe");
    HANDLE processHandle = Process::GetProcessHandle(procID);
    std::vector configs = ConfigReader::Read(std::string("test.toml"));
    for (SignatureInfo& config : configs) {
        std::cout << config.name << std::endl;
        std::cout << config.module << std::endl;
        std::cout << config.signature << std::endl;
        std::cout << config.offset << std::endl;
        std::cout << config.extra << std::endl;
    }
}