#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5f34face, "struct_module" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xdd132261, "printk" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0xf100ce32, "module_put" },
	{ 0x1877e68f, "register_chrdev" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0x9ef749e2, "unregister_chrdev" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

