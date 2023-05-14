// WebUI C - Minimal TLS Example

#include "webui.h"

// PEM SSL/TLS Certificate
const char* cert = "-----BEGIN CERTIFICATE-----\n"
"MIIDMzCCAhugAwIBAgIBADANBgkqhkiG9w0BAQsFADBdMQswCQYDVQQGEwJDQTEO\n"
"MAwGA1UECgwFV2ViVUkxDjAMBgNVBAsMBVdlYlVJMQ4wDAYDVQQDDAVXZWJVSTEO\n"
"MAwGA1UECAwFV2ViVUkxDjAMBgNVBAcMBVdlYlVJMB4XDTIzMDUxNDE5MjYxNloX\n"
"DTIzMDUxNzE5MjYxNlowXTELMAkGA1UEBhMCQ0ExDjAMBgNVBAoMBVdlYlVJMQ4w\n"
"DAYDVQQLDAVXZWJVSTEOMAwGA1UEAwwFV2ViVUkxDjAMBgNVBAgMBVdlYlVJMQ4w\n"
"DAYDVQQHDAVXZWJVSTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANS/\n"
"Aq6WRWJF/bstuMdzrg8P7aM0lv/Cz1EFCyFY9ilIC0yM98AiPk0jq0lHUDt+OH3R\n"
"aMUNn/mHzwce48OSJ0oSwXjItBXtZ3RNwXFbHNbkpUxCI/Tvehcb9TnV8qFTPZqT\n"
"mLuVTXGeNDI0pOBqIv35WmjR1z/d9ySeVfGUSjCNFfCPpZ8BA1nLR1H3cAb2IU4L\n"
"0wxYLALyZaihNrCI5YPscgsqRSVOhGiwx51R/jhTDXIJcXqIbtwpVBXvSpKlVFZ4\n"
"adfhU+LQZnLXE8fxF/jh/gs1t2IkKQo14y/GNRw02Qobr2iP18FM7gZ2aifSO1cv\n"
"L3rHDn6IOr3+A1PfQTcCAwEAATANBgkqhkiG9w0BAQsFAAOCAQEAtQAnIXhXMyGF\n"
"gRCYajbqX0bAmVhPFBvbStKermOIA9TgZtN58or3im7OQUubsRABVNd09sRK9mXv\n"
"6dT7CbNZ7HVO36AVxpt30fwqQ9k7PAW8J+WhtunPBTfKYyDhpg7u20tu4nhte40n\n"
"jUvMgnSSbKa1UYrKKgy3TBV2l/fcd0SUUHmo76uuV0+Pmyf2aymv1QzBNdKHEkLr\n"
"BH9+XcvfMIKaxTqZ+ceEjAwrnryuM846z4thgHVuLOCzRmKOGSuFx1Vu8s4WKhrh\n"
"RMOiJIg1sYO2Q2IvMJclS5M0xV1VxDmV+PbcBSUE4c10F9/eMkaqTLaT54VF18mg\n"
"lGk2OJ0v0g==\n"
"-----END CERTIFICATE-----\n";

// PEM SSL/TLS Private Key
const char* key = "-----BEGIN PRIVATE KEY-----\n"
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDUvwKulkViRf27\n"
"LbjHc64PD+2jNJb/ws9RBQshWPYpSAtMjPfAIj5NI6tJR1A7fjh90WjFDZ/5h88H\n"
"HuPDkidKEsF4yLQV7Wd0TcFxWxzW5KVMQiP073oXG/U51fKhUz2ak5i7lU1xnjQy\n"
"NKTgaiL9+Vpo0dc/3fcknlXxlEowjRXwj6WfAQNZy0dR93AG9iFOC9MMWCwC8mWo\n"
"oTawiOWD7HILKkUlToRosMedUf44Uw1yCXF6iG7cKVQV70qSpVRWeGnX4VPi0GZy\n"
"1xPH8Rf44f4LNbdiJCkKNeMvxjUcNNkKG69oj9fBTO4Gdmon0jtXLy96xw5+iDq9\n"
"/gNT30E3AgMBAAECggEAONYI3OSXh8AkH7AA2AQvIaYDOiFQH+cHJOGAjjmqle/B\n"
"2QMmIyXi2A/p8EtFg4dehzp9T3uq2+qs4/2cIsD2jyMAngicl+kTRO6K+gI5660s\n"
"/fkDiym5R9g3xOpEBlZrNFMvMBoclPiLgEgxLiUc0RYfUbaR12Ww448Lbd1Mjrh9\n"
"tA2p799R6WVqOzJP4fJsMMx1WhGo+ein8ZqmYk2DVdw2LcwZL3jA/Cio5MyN2BFj\n"
"o9p5H7zbBKoW0It4MxqZTBc3H7DVKryiTAv/Dwle0XxUkCAeLsKwxWiLgkj4IHR2\n"
"2xnetEtJaTyiGc6oPZt1dHYgWcts2VPDbwG5wSmS1QKBgQDgaLM9TVmn4/wFpenL\n"
"QaIKT3w3vdabSa5Jvyid8mhRCRSu/NVtK0wCM4/owOS2GX39Y6WMSaZVXEIMnG3I\n"
"eKzphA1n+LxN9pQVy7O89gquZUGC/3fXlmjkNm6gPkzNJ7L6+KGBqaeVQtfPUb+e\n"
"RsgcwFCSaf8c3Zebm1ycS+Rn6wKBgQDysgCCDz1Anowr3q3zyA0I50Jsz1uOYD3F\n"
"1OPWhsHcL3YNq1FuB0W5Ygdgk3WOLWvMumVBYi/ljnq+jMe3iNcy4J9g1ufziudE\n"
"zo2g3NDmJ1hs4rfw0SaPjIBbG5O7utxeq6KrG5mm1z0Iy+hAuQDGhKDL9S+wOv9V\n"
"ldhnlMPk5QKBgBpAxW9PhESa7FnwzggkVoOkRuDyiY/DL+uavHK18DRCvrO2CnXq\n"
"EctUIurU3izbkJy7MpvV5eqoj2WQS1ufmoL7GuJl/AmW5j4ihZV+p0M9v0tG/csv\n"
"4neIUqrWfv+lPFAWFDbqFRvmJP8xDhzDJRgP+50VX24OEnV22H/EdSUfAoGBALea\n"
"il/af5BfYdPehuMiuRm/OrVuuekgThtYT3WARTD6hukYbmY7AjiZPNOHOyvwmNkt\n"
"OmUYjvuvqpR1lLH4yDUpUenFK31H3GZljSfhZfh4U6Esc9Ovpuh6drB2UHF5kDXe\n"
"yxV/r+JUe0woVvCABWIp/CvQtd8xAvIQhsL1/K0xAoGBAN4KXa8SmtysrnlHLfig\n"
"LRiTwjw3BrOKDUnyGIjj+2l8DO5OuDRyM+byih+FhcZ7ypThbml+QVKl0rFfvht+\n"
"rSFLEJ9PqwJQpJqdvYi4qRPndhXVih/3ym+VFA3DDhhf/jkDgvMkXT6hftRLpAiX\n"
"vNN3TnHFp/6NXaFvcUBY43pb\n"
"-----END PRIVATE KEY-----\n";

int main() {

    // Set our custom certificate
    if(!webui_set_tls_certificate(cert, key)) {
        printf("Invalide certificate.");
        return -1;
    }

    size_t my_window = webui_new_window();
    webui_show(my_window, "<html>TLS Hello World</html>");
    webui_wait();
    return 0;
}

#if defined(_MSC_VER)
    int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
        return main();
    }
#endif
