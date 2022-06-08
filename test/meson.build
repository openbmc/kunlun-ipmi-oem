gtest = dependency('gtest', main: true, disabler: true, required: build_tests)
gmock = dependency('gmock', disabler: true, required: build_tests)
openssl = dependency('openssl', disabler: true, required: build_tests)

configure_file(output: 'config.h',
  configuration: cdata,
)
test_inc = include_directories('.')

test_kunlun_ipmi_oem = executable(
  'test_kunlun-ipmi-oem',
  '../src/kunlun_oem.cpp',
  'test_kunlun_ipmi_oem.cpp',
  include_directories: [test_inc, src_inc],
  dependencies: [
    libipmid,
    gtest,
    gmock,
    phosphor_logging,
    openssl,
  ])

test('test_kunlun-ipmi-oem', test_kunlun_ipmi_oem)
