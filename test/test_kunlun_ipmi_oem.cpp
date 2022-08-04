#include "config.h"

#include "kunlun_oem.hpp"

#include <ipmid/api.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Invoke;
using ::testing::IsNull;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::VariantWith;

namespace ipmi
{

namespace impl
{

bool registerHandler(int prio, NetFn netFn, Cmd cmd, Privilege priv,
                     ::ipmi::HandlerBase::ptr handler)
{
    (void)prio;
    (void)netFn;
    (void)cmd;
    (void)priv;
    (void)handler;

    return true;
}

} // namespace impl

TEST(TestKunlunIpmiOem, SetAndGetCpuInfo)
{
    uint8_t index = 0;
    uint32_t loop;
    std::vector<char> infoSet;
    std::vector<char> infoGet;

    for (loop = 0; loop < 256; loop++)
    {
        infoSet.push_back(static_cast<char>(loop));
    }

    EXPECT_EQ(setCpuInfo(index, infoSet), responseSuccess());

    auto result = getCpuInfo(index);
    infoGet = std::get<0>(std::get<1>(result).value());

    EXPECT_TRUE(infoSet == infoGet);
}

} // namespace ipmi