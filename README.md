# TODO:
* Nuke dep on .fex
* Figure out a good way to boot reliably?!
* Minimize
* Update ACPI tables
* Make all (useful) Sunxi drivers compile and work (needs lots of unlegacy-ing)

DONT TRY HDMI IT WILL EXPLODE, it relies on an arm32 blob that I neutralized, so it will probably lock up big time.

-----

Based on @imbushuo's NintendoSwitchPkg, mashed together with AW BSP BSD2 drivers. ARM32 UEFI wouldn't be
much useful on the PinePhone. Tested building with edk2@5b56c52b5c1cc817a1ddac7f03aa6a02aeab4c04 + GCC 10.2.1-6 + patches

-----

For now it prints some of my stupid debug prints on serial and hangs on MMU enablement.

</br>

Ideally, we want to bring back sunxi_de and sunxi PlatformPei AND nuke the FEX deps (probably by hardcoding stuff?)

</br>

Generally once somebody gets this to boot, W10 IoT should be bootable, and so should be W10 itself.

Maybe even W11 22000 builds, as armv8.1 is not yet an enforced requirement.

-----

# Building

[Install dependencies](https://github.com/tianocore/tianocore.github.io/wiki/Using-EDK-II-with-Native-GCC#install-required-software-from-apt)

```
# TODO: document exporting GCC prefix, not required if building on aarch64
# Similarly, the last commands don't need aarch64-linux-gnu- prefix if building on aarch64

git clone --recursive https://github.com/tianocore/edk2 # Cloning master may make it not compile some day, but fixes are welcome!
cd edk2

git clone https://github.com/konradybcio/PinePhonePkg # You need to keep the directory name case-sensitive or the build system will scream at you
git am PinePhonePkg/EDK2-patches/0001-BaseTools-tools_def-support-ASLC-files-on-AArch64.patch

bash # zsh and friends won't work :(

# Builds the image and packs it into an ELF
# Note that you can't dirtybuild EDK2, or your changes won't be picked up
rm -rf Conf/ && \
mkdir Conf && \
make -C BaseTools && \
rm -rf Build/ && \
source edksetup.sh && \
build -b DEBUG -a AARCH64 -p PinePhonePkg/PinePhone.dsc -t GCC5 -j$(nproc) -s -n 0 && \
cd Build/PinePhone-AARCH64/DEBUG_GCC5/FV && \
aarch64-linux-gnu-objcopy -I binary -O elf64-littleaarch64 --binary-architecture aarch64 PINEPHONE_EFI.fd Pine.elfobj && \
aarch64-linux-gnu-ld -m aarch64elf Pine.elfobj -T ../../../../PinePhonePkg/FvWrapper.ld -o Pine.elf
```

-----
You can then load it from u-boot shell: (mmc1 is eMMC and part1 is /boot)

`mmc dev 1;load mmc 1:1 ${kernel_addr_r} Pine.elf;bootelf 0x40080000`
