bash:

(cd edk2dir/edk2)
rm -rf Conf/ && mkdir Conf && rm -rf Build/ && source edksetup.sh && build -a AARCH64 -p PinePhonePkg/PinePhone.dsc -t GCC5 -j16 -s -n 0

cd Build/PinePhone-AARCH64/DEBUG_GCC5/FV

aarch64-linux-gnu-objcopy -I binary -O elf64-littleaarch64 --binary-architecture aarch64 TEGRA210_EFI.fd Pine.elfobj && aarch64-linux-gnu-ld -m aarch64elf Pine.elfobj -T ../../../../PinePhonePkg/FvWrapper.ld -o Pine.elf
