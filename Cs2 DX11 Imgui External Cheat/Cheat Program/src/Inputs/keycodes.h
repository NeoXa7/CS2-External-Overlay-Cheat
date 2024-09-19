inline const char* KeyCodeToString(int keyCode) {
    switch (keyCode) {
        // Function keys
    case 0x70: return "F1";
    case 0x71: return "F2";
    case 0x72: return "F3";
    case 0x73: return "F4";
    case 0x74: return "F5";
    case 0x75: return "F6";
    case 0x76: return "F7";
    case 0x77: return "F8";
    case 0x78: return "F9";
    case 0x79: return "F10";
    case 0x7A: return "F11";
    case 0x7B: return "F12";

        // Control keys
    case 0x01: return "LEFT_MOUSE_BUTTON";
    case 0x02: return "RIGHT_MOUSE_BUTTON";
    case 0x03: return "CONTROL_BREAK";
    case 0x04: return "MIDDLE_MOUSE_BUTTON";
    case 0x05: return "X1_MOUSE_BUTTON";
    case 0x06: return "X2_MOUSE_BUTTON";
    case 0x08: return "BACKSPACE";
    case 0x09: return "TAB";
    case 0x0C: return "CLEAR";
    case 0x0D: return "ENTER";
    case 0x10: return "SHIFT";
    case 0x11: return "CTRL";
    case 0x12: return "ALT";
    case 0x13: return "PAUSE";
    case 0x14: return "CAPS_LOCK";
    case 0x1B: return "ESC";
    case 0x1C: return "CONVERT";
    case 0x1D: return "NONCONVERT";
    case 0x1E: return "ACCEPT";
    case 0x1F: return "MODECHANGE";
    case 0x20: return "SPACE";
    case 0x21: return "PAGE_UP";
    case 0x22: return "PAGE_DOWN";
    case 0x23: return "END";
    case 0x24: return "HOME";
    case 0x25: return "LEFT_ARROW";
    case 0x26: return "UP_ARROW";
    case 0x27: return "RIGHT_ARROW";
    case 0x28: return "DOWN_ARROW";
    case 0x29: return "SELECT";
    case 0x2A: return "PRINT";
    case 0x2B: return "EXECUTE";
    case 0x2C: return "PRINT_SCREEN";
    case 0x2D: return "INSERT";
    case 0x2E: return "DELETE";
    case 0x2F: return "HELP";
    case 0x5B: return "LEFT_WIN";
    case 0x5C: return "RIGHT_WIN";
    case 0x5D: return "APPS";
    case 0x5E: return "POWER";
    case 0x5F: return "SLEEP";

        // Alphanumeric keys
    case 0x30: return "0";
    case 0x31: return "1";
    case 0x32: return "2";
    case 0x33: return "3";
    case 0x34: return "4";
    case 0x35: return "5";
    case 0x36: return "6";
    case 0x37: return "7";
    case 0x38: return "8";
    case 0x39: return "9";
    case 0x41: return "A";
    case 0x42: return "B";
    case 0x43: return "C";
    case 0x44: return "D";
    case 0x45: return "E";
    case 0x46: return "F";
    case 0x47: return "G";
    case 0x48: return "H";
    case 0x49: return "I";
    case 0x4A: return "J";
    case 0x4B: return "K";
    case 0x4C: return "L";
    case 0x4D: return "M";
    case 0x4E: return "N";
    case 0x4F: return "O";
    case 0x50: return "P";
    case 0x51: return "Q";
    case 0x52: return "R";
    case 0x53: return "S";
    case 0x54: return "T";
    case 0x55: return "U";
    case 0x56: return "V";
    case 0x57: return "W";
    case 0x58: return "X";
    case 0x59: return "Y";
    case 0x5A: return "Z";

        // Modifier keys
    case 0xA0: return "LEFT_SHIFT";
    case 0xA1: return "RIGHT_SHIFT";
    case 0xA2: return "LEFT_CTRL";
    case 0xA3: return "RIGHT_CTRL";
    case 0xA4: return "LEFT_ALT";
    case 0xA5: return "RIGHT_ALT";

        // Numeric keypad
    case 0x60: return "NUMPAD0";
    case 0x61: return "NUMPAD1";
    case 0x62: return "NUMPAD2";
    case 0x63: return "NUMPAD3";
    case 0x64: return "NUMPAD4";
    case 0x65: return "NUMPAD5";
    case 0x66: return "NUMPAD6";
    case 0x67: return "NUMPAD7";
    case 0x68: return "NUMPAD8";
    case 0x69: return "NUMPAD9";
    case 0x6A: return "NUMPAD_MULTIPLY";
    case 0x6B: return "NUMPAD_ADD";
    case 0x6C: return "NUMPAD_SEPARATOR";
    case 0x6D: return "NUMPAD_SUBTRACT";
    case 0x6E: return "NUMPAD_DECIMAL";
    case 0x6F: return "NUMPAD_DIVIDE";

        // Other keys
    case 0xBA: return "OEM_1"; // For ';:'
    case 0xBB: return "OEM_PLUS"; // For '=+'
    case 0xBC: return "OEM_COMMA"; // For ',<'
    case 0xBD: return "OEM_MINUS"; // For '-_'
    case 0xBE: return "OEM_PERIOD"; // For '.>'
    case 0xBF: return "OEM_2"; // For '/?'
    case 0xC0: return "OEM_3"; // For '`~'
    case 0xDB: return "OEM_4"; // For '[{'
    case 0xDC: return "OEM_5"; // For '\|'
    case 0xDD: return "OEM_6"; // For '] }'
    case 0xDE: return "OEM_7"; // For '''"

    default: return "Unknown";
    }
}