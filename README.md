# TODO:
* Nuke dep on .fex
* Figure out a good way to boot reliably?!
* Minimize
* Update ACPI tables

DONT TRY HDMI IT WILL EXPLODE, it relies on an arm32 blob that I neutralized, so it will probably lock up big time.

-----

Based on @imbushuo's NintendoSwitchPkg, mashed together with AW BSP BSD2 drivers. ARM32 UEFI wouldn't be
much useful on the PinePhone. Tested building with edk2@f95cdd316c3d56e8f76b5044be54b9645e1dc60f + patches,
edk2-platforms@325097364dbdbc7b9311c723372e4e36a2f0012e.

-----

For now it prints some of my stupid debug prints on serial and hangs on MMU enablement.

</br>

Ideally, we want to bring back sunxi_de and sunxi PlatformPei AND nuke the FEX deps (probably by hardcoding stuff?)

</br>

Generally once somebody gets this to boot, W10 IoT should be bootable, and so should be W10 itself.

Maybe even W11 22000 builds, as armv8.1 is not yet an enforced requirement.

-----

bash [zsh won't work :( ]:

(cd edk2dir/edk2)
rm -rf Conf/ && mkdir Conf && rm -rf Build/ && source edksetup.sh && build -a AARCH64 -p PinePhonePkg/PinePhone.dsc -t GCC5 -j16 -s -n 0

cd Build/PinePhone-AARCH64/DEBUG_GCC5/FV

aarch64-linux-gnu-objcopy -I binary -O elf64-littleaarch64 --binary-architecture aarch64 PINEPHONE_EFI.fd Pine.elfobj && aarch64-linux-gnu-ld -m aarch64elf Pine.elfobj -T ../../../../PinePhonePkg/FvWrapper.ld -o Pine.elf

-----
You can then load it from u-boot shell (mmc1 is eMMC and part1 is /boot)

mmc dev 1;load mmc 1:1 ${kernel_addr_r} Pine.elf;bootelf 0x40080000
