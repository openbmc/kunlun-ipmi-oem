configure_file(output: 'config.h',
    configuration: cdata,
)

src_inc = include_directories('.')

so_version = '0.0.1'

shared_library(
  'kunlun-ipmi-oem',
  'kunlun_oem.cpp',
  dependencies: [
    phosphor_logging,
    libipmid,
  ],
  version: so_version,
  install: true,
  install_dir: get_option('libdir') / 'ipmid-providers'
  )
