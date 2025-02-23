#include <stdio.h>
#include <string.h>


unsigned
serial_base_xor(const char *device, const char **norm_name)
{
    unsigned num;

    if (strcmp(device, "V107") == 0)
    {
        *norm_name = "V107";
        num = 107;
    }
    else if (strcmp(device, "V110") == 0)
    {
        *norm_name = "V110";
        num = 110;
    }
    else
    {
        *norm_name = "VUNK";
        num = 13;
    }

    return num;
}

unsigned
get_digit(const char c)
{
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return c - '0';
}

unsigned
get_byte(const char *mac_str, int pos)
{
    unsigned b = get_digit(mac_str[pos]) * 16 + get_digit(mac_str[pos + 1]);
    return b;
}

int
main(int argc, const char *argv[])
{
    const char *cmd;

    if (argc < 2)
    {
        return 3;
    }

    cmd = argv[1];
    if (strcmp(cmd, "encode") == 0 && argc > 3)
    {
        const char *device = argv[2];
        const char *mac_str = argv[3];
        unsigned b1, b2, b3, num;
        const char *norm_name;

        if (strlen(mac_str) < 17)
            return 2;

        b1 = get_byte(mac_str, 9);
        b2 = get_byte(mac_str, 12);
        b3 = get_byte(mac_str, 15);

        num = serial_base_xor(device, &norm_name);

        printf("%s0%03dV%03dA%03dB%03d\n", norm_name, b1 ^ num, b2 ^ (num - 1), b3 ^ (num + 2), b1 ^ (b2 + 3) ^ b3 );
        return 0;
    }
    else if (strcmp(cmd, "decode") == 0 && argc > 2)
    {
        const char *serial = argv[2];
        char device[5] = "";
        unsigned num;
        const char *norm_name;
        int b1n, b2n, b3n, crc;
        unsigned b1, b2, b3;

        if (strlen(serial) < 4)
            return 2;

        strncpy(device, serial, 4);

        num = serial_base_xor(device, &norm_name);

        sscanf(serial + 4, "0%dV%dA%dB%d", &b1n, &b2n, &b3n, &crc);

        b1 = b1n ^ num;
        b2 = b2n ^ (num - 1);
        b3 = b3n ^ (num + 2);

        printf("Model: %s\n", device);
        printf("MAC: %02X:%02X:%02X\n", b1, b2, b3);
        printf("CRC: %x vs %x", b1 ^ (b2 + 3) ^ b3, crc);
        return 0;
    }

    return 1;
}