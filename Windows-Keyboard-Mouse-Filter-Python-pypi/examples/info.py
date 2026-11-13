from windows_keyboard_mouse_filter import Client
with Client() as client:
    print(client.info())
