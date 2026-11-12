vcpkg_download_distfile(ARCHIVE
    URLS "https://github.com/titanfyre/Windows-Keyboard-Mouse-Filter/releases/download/sdk-v0.1.0/windows-keyboard-mouse-filter-sdk-0.1.0.tar.gz"
    FILENAME "windows-keyboard-mouse-filter-sdk-0.1.0.tar.gz"
    SHA512 433f6d94ce7e43c40b06ae73193131aec3eb7bc2109eeb3f71f6e91456fafcf58de63f6429fae1fb551bcbe9b935e462ecc013cf7510656cf031b768b6ab5fba
)
vcpkg_extract_source_archive(SOURCE_PATH ARCHIVE "${ARCHIVE}" NO_REMOVE_ONE_LEVEL)
vcpkg_cmake_configure(SOURCE_PATH "${SOURCE_PATH}")
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME WindowsKeyboardMouseFilterSDK CONFIG_PATH lib/cmake/WindowsKeyboardMouseFilterSDK)
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include" "${CURRENT_PACKAGES_DIR}/debug/share")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
