#pragma once

#include <cstdint>
#include <ipmid/api.hpp>

namespace ipmi
{

using NetFn = uint8_t;
using Cmd   = uint8_t;
using Cc    = uint8_t;

constexpr NetFn netfnKunlunOem = netFnOemSix;
namespace cmd
{
    constexpr Cmd cmdSetCpuInfo   = 0x0;
    constexpr Cmd cmdGetCpuInfo   = 0x1;
} // namespace cmd

RspType<> setCpuInfo(uint8_t index, std::vector<char> info);
RspType<std::vector<char>> getCpuInfo(uint8_t index);

} // namespace ipmi
