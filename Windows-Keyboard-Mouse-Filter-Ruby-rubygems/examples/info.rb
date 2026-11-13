require 'windows_keyboard_mouse_filter'
WindowsKeyboardMouseFilter::Interceptor.open { |client| p client.info }
