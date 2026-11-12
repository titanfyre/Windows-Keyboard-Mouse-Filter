cmake_minimum_required(VERSION 3.24)
project(WindowsKeyboardMouseFilterSDK VERSION 0.1.0.0 LANGUAGES C CXX)
if(NOT WIN32 OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "This SDK requires Windows x64. No driver is installed by this build.")
endif()
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_library(TitanWindowsKeyboardMouseFilter STATIC
  "sdk/InputFilter/InputFilter.cpp"
)
add_library(WindowsKeyboardMouseFilterSDK::sdk ALIAS TitanWindowsKeyboardMouseFilter)
set_target_properties(TitanWindowsKeyboardMouseFilter PROPERTIES EXPORT_NAME sdk)
target_compile_features(TitanWindowsKeyboardMouseFilter PUBLIC cxx_std_17)
target_compile_definitions(TitanWindowsKeyboardMouseFilter PUBLIC )
target_compile_definitions(TitanWindowsKeyboardMouseFilter PRIVATE UNICODE _UNICODE NOMINMAX WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0A00)
if(MSVC)
  target_compile_options(TitanWindowsKeyboardMouseFilter PRIVATE /utf-8 /EHsc /W4)
endif()
target_include_directories(TitanWindowsKeyboardMouseFilter PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sdk>"
  "$<INSTALL_INTERFACE:include/>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sdk/InputFilter>"
  "$<INSTALL_INTERFACE:include/InputFilter>"
)
target_link_libraries(TitanWindowsKeyboardMouseFilter PUBLIC advapi32 bcrypt cfgmgr32 comctl32 hid newdev ole32 setupapi user32)
install(TARGETS TitanWindowsKeyboardMouseFilter EXPORT WindowsKeyboardMouseFilterSDKTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY sdk/ DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl")
install(FILES LICENSE DESTINATION share/windows-keyboard-mouse-filter)
install(EXPORT WindowsKeyboardMouseFilterSDKTargets NAMESPACE WindowsKeyboardMouseFilterSDK:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WindowsKeyboardMouseFilterSDK)
configure_file("WindowsKeyboardMouseFilterSDKConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/WindowsKeyboardMouseFilterSDKConfig.cmake" @ONLY)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/WindowsKeyboardMouseFilterSDKConfigVersion.cmake" VERSION 0.1.0.0 COMPATIBILITY SameMajorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/WindowsKeyboardMouseFilterSDKConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/WindowsKeyboardMouseFilterSDKConfigVersion.cmake" DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WindowsKeyboardMouseFilterSDK)
