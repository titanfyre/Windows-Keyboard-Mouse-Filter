# SDK publication status

Current source layout and registry coverage. A GitHub download is distinct from publication on a central registry.

| Target | Status | Package / documentation |
| --- | --- | --- |
| CPP/vcpkg | published_custom_registry | windows-keyboard-mouse-filter |
| CPP/conan | published_custom_source_index | [windows-keyboard-mouse-filter](https://github.com/TitanCSA/sdk-packages/tree/089bc73095aa8eda89bacbe10d0b9e58394b0207/conan-index) [Source](packaging/native/) |
| CPP/nuget | published_payload_verified | [Windows-Keyboard-Mouse-Filter.Native](https://www.nuget.org/packages/Windows-Keyboard-Mouse-Filter.Native/0.1.0) |
| NET/nuget | published_payload_verified | [WindowsKeyboardMouseFilter.SDK](https://www.nuget.org/packages/WindowsKeyboardMouseFilter.SDK/1.0.0) |
| Python/pypi | built_fixture_and_production_verified | windows-keyboard-mouse-filter [Source](Windows-Keyboard-Mouse-Filter-Python-pypi/) |
| Python/conda-forge | custom_channel_install_verified_requires_conda_forge_review | [windows-keyboard-mouse-filter](https://raw.githubusercontent.com/TitanCSA/sdk-packages/089bc73095aa8eda89bacbe10d0b9e58394b0207/conda-channel) [Source](packaging/conda/) |
| Rust/cargo | published_install_verified | [windows-keyboard-mouse-filter](https://crates.io/crates/windows-keyboard-mouse-filter) [Source](Windows-Keyboard-Mouse-Filter-Rust-cargo/) |
| JavaScript/npm | registry_rate_limit_wait | windows-keyboard-mouse-filter [Source](Windows-Keyboard-Mouse-Filter-JavaScript-npm/) |
| Java/maven | published_install_verified | [windows-keyboard-mouse-filter](https://central.sonatype.com/artifact/io.github.titancsa/windows-keyboard-mouse-filter/1.0.0) [Source](Windows-Keyboard-Mouse-Filter-Java-maven/) |
| Java/jitpack | published_install_verified | [windows-keyboard-mouse-filter](https://jitpack.io/#titanfyre/Windows-Keyboard-Mouse-Filter/java-sdk-v1.0.0) [Source](Windows-Keyboard-Mouse-Filter-Java-maven/) |
| Go/modules | published_install_verified | [windows-keyboard-mouse-filter](https://pkg.go.dev/github.com/titanfyre/Windows-Keyboard-Mouse-Filter/Windows-Keyboard-Mouse-Filter-Go-modules@v1.0.0) [Source](Windows-Keyboard-Mouse-Filter-Go-modules/) |
| Go/pkg-go-dev | indexed_verified | [Documentation](https://pkg.go.dev/github.com/titanfyre/Windows-Keyboard-Mouse-Filter/Windows-Keyboard-Mouse-Filter-Go-modules@v1.0.0) |
| PowerShell/gallery | published_install_verified | [WindowsKeyboardMouseFilter](https://www.powershellgallery.com/packages/WindowsKeyboardMouseFilter/1.0.0) [Source](Windows-Keyboard-Mouse-Filter-PowerShell-gallery/) |
| Dart/pub-dev | published_install_verified | [windows_keyboard_mouse_filter](https://pub.dev/packages/windows_keyboard_mouse_filter) [Source](Windows-Keyboard-Mouse-Filter-Dart-pub-dev/) |
| Ruby/rubygems | published_install_verified | [windows-keyboard-mouse-filter](https://rubygems.org/gems/windows-keyboard-mouse-filter) [Source](Windows-Keyboard-Mouse-Filter-Ruby-rubygems/) |
| PHP/packagist | composer_source_and_tag_published | [titancsa/windows-keyboard-mouse-filter](https://packagist.org/packages/titancsa/windows-keyboard-mouse-filter) |

Native SDK source and CMake/Conan/vcpkg/NuGet recipes share [`packaging/native`](packaging/native/LAYOUT.md). Previous release archives and tags remain unchanged.

Application and driver prerequisites and original licensing remain those documented by each SDK. No driver installer is bundled with these source packages.
