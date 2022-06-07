#include <filesystem>
#include <ipmid/api.hpp>
#include <phosphor-logging/log.hpp>

#include "config.h"
#include "kunlun_oem.hpp"

namespace ipmi
{

using namespace phosphor::logging;

// save cpu infomation from bios to file
// index[in]: cpu index
// info[in]: data saving to file
static int saveInfoToFile(uint8_t index, std::vector<char> &info)
{
    char infoPath[PATH_MAX];

    std::snprintf(infoPath, sizeof(infoPath), IPMI_BIOSDATA_DIR"/cpu%02x", index);

    if (!(std::filesystem::exists(IPMI_BIOSDATA_DIR)))
    {
        std::filesystem::create_directory(IPMI_BIOSDATA_DIR);
    }

    std::ofstream ofs(infoPath, std::ios::out | std::ios::binary);
    ofs.seekp(0);
    ofs.write(info.data(), info.size());
    ofs.close();

    return 0;
}

// load cpu infomation from file
// index[in]: cpu index
// info[out]: data loading from file
static int loadInfoFromFile(uint8_t index, std::vector<char> &info)
{
    char infoPath[PATH_MAX];

    std::snprintf(infoPath, sizeof(infoPath), IPMI_BIOSDATA_DIR"/cpu%02x", index);

    if (!(std::filesystem::exists(infoPath)))
    {
        std::filesystem::create_directory(infoPath);
    }

    std::ifstream ifs(infoPath, std::ios::in | std::ios::binary);

    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    info.resize(size);

    ifs.read(info.data(), size);
    ifs.close();

    return 0;
}

RspType<> setCpuInfo(uint8_t index, std::vector<char> info)
{
    saveInfoToFile(index, info);

    return responseSuccess();
}

RspType<std::vector<char>> getCpuInfo(uint8_t index)
{
    std::vector<char> output;

    loadInfoFromFile(index, output);

    return responseSuccess(output);
}

void register_kunlun_oem_functions(void)
{
    registerHandler(prioOemBase, netfnKunlunOem, cmd::cmdSetCpuInfo,
                    Privilege::Admin, setCpuInfo);
    registerHandler(prioOemBase, netfnKunlunOem, cmd::cmdGetCpuInfo,
                    Privilege::User, getCpuInfo);
}

void register_kunlun_oem_functions() __attribute__((constructor));

} // namespace ipmi
