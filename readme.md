# SoC - Central_AM

The Bluetooth example is a scanner that looks for a device with a specific service and characteristic. 

It advertises as ConnDev****, where the last 4 digits are the two last bytes of the device Mac Address.

DataService - UUID: CC
   Characteristics:
      |_ Data_TX -  UUID: 3A4855F62F9C4005815BDF746358668E
                    Properties: Read - 64 bytes
      |_ Data_RX -  UUID: C165393CF3374EFD8C8396226D85DE6E
                    Properties: Read/Write no Response - 5 bytes

Hardware: EFR31MG21 - BRD4180A
Compiler: GCC GNU ARM v10.2.1
Gecko SDK Suite: Amazon 202012.00, Bluetooth 4.2.0, Bluetooth Mesh 3.0.2, EmberZNet 7.1.2.0, Flex 3.4.2.0, HomeKit 1.2.2.0, MCU 6.3.1.0, Matter Demo, Micrium OS Kernel 5.13.10, OpenThread 2.1.2.0 (GitHub-2ce3d3bf0), Platform 4.1.0.0, USB 1.0.0.0, Wi-SUN 1.3.2.0, Z-Wave SDK 7.18.2.0
Version: 4.1.2


## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

