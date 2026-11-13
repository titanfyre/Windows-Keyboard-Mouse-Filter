import 'package:windows_keyboard_mouse_filter/windows_keyboard_mouse_filter.dart';

Future<void> main() async {
  final client = await Interceptor.open();
  try {
    print(client.info());
  } finally {
    client.close();
  }
}
