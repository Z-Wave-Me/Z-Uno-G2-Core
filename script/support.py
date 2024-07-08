#!/usr/bin/python
# -*- coding: utf-8 -*-
import argparse
import platform
import os
import shutil
import json
import sys

def func_prog_dir_get() -> str:
	if getattr(sys, 'frozen', False):
		application_path = os.path.dirname(sys.executable)
	else:
		application_path = os.path.dirname(__file__)
	return (os.path.abspath(application_path))

MY_VERSION = "0.1"

def replace_text(filename:str, find:str, replace:str, count:int) -> bool:
	file = open(filename, "r")
	text = file.read()
	file.close()
	if text.count(find) != count:
		print("not find string count!")
		return (False)
	text = text.replace(find, replace)
	file = open(filename, "w")
	file.write(text)
	file.close()
	return (True)

def finallizeStepStatus(text, stat_text):
	print('\r%-40s %s' % (text, '.' * 30), end='')
	print('%30s\n' % (stat_text), end='')

def SdkFunc(path_sdk):
	path_core = os.path.abspath(os.path.join(func_prog_dir_get(), "..", "..","core"))
	path_core_metadata = os.path.join(path_core, "hardware", "arduino", "zunoG2", "cores", "core_metadata.json")
	path_emlib = os.path.join(path_core, "hardware", "arduino", "zunoG2", "cores", "emlib")
	path_cmsis = os.path.join(path_core, "hardware", "arduino", "zunoG2", "cores", "cmsis")
	path_sl = os.path.join(path_core, "hardware", "arduino", "zunoG2", "cores", "sl")
	path_device = os.path.join(path_core, "hardware", "arduino", "zunoG2", "device")
	path_emlib_sdk = os.path.join(path_sdk, "platform", "emlib")
	path_cmsis_sdk = os.path.join(path_sdk, "platform", "CMSIS", "Core", "Include")
	path_sl_sdk = os.path.join(path_sdk, "platform", "common", "inc")
	path_device_sdk = os.path.join(path_sdk, "platform", "Device", "SiliconLabs")
	file = open(path_core_metadata)
	core_metadata = json.load(file)
	file.close()
	if os.path.isdir(path_emlib) == True:
		shutil.rmtree(path_emlib)
	shutil.copytree(os.path.join(path_emlib_sdk, "inc"), path_emlib, dirs_exist_ok=True)
	shutil.copytree(os.path.join(path_emlib_sdk, "src"), path_emlib, dirs_exist_ok=True)
	os.remove(os.path.join(path_emlib, "em_core.c"))
	if os.path.isdir(path_cmsis) == True:
		shutil.rmtree(path_cmsis)
	shutil.copytree(path_cmsis_sdk, path_cmsis, dirs_exist_ok=True)
	if os.path.isdir(path_sl) == True:
		shutil.rmtree(path_sl)
	os.mkdir(path_sl)
	shutil.copyfile(os.path.join(path_sl_sdk, "sl_assert.h"), os.path.join(path_sl, "sl_assert.h"))
	shutil.copyfile(os.path.join(path_sl_sdk, "sl_common.h"), os.path.join(path_sl, "sl_common.h"))
	shutil.copyfile(os.path.join(path_sl_sdk, "sl_enum.h"), os.path.join(path_sl, "sl_enum.h"))
	if replace_text(os.path.join(path_emlib, "em_i2c.c"), "i2cMode &= _I2C_CTRL_CLHR_MASK >> _I2C_CTRL_CLHR_SHIFT;", "i2cMode = (I2C_ClockHLR_TypeDef)(i2cMode & (_I2C_CTRL_CLHR_MASK >> _I2C_CTRL_CLHR_SHIFT));", 0x1) == False:
		exit(-1)
	if replace_text(os.path.join(path_cmsis, "cmsis_gcc.h"), "__STATIC_FORCEINLINE __NO_RETURN void __cmsis_start(void)", "/*", 0x1) == False:
		exit(-1)
	if replace_text(os.path.join(path_cmsis, "cmsis_gcc.h"), "  _start();\n}", "*/", 0x1) == False:
		exit(-1)
	chip_depending = core_metadata["chip_depending"]
	chip_family = []
	for key in chip_depending:
		family = chip_depending[key]["family"]
		if not (family in chip_family):
			chip_family = chip_family + [family]
	for family in chip_family:
		path_family = os.path.join(path_device, family)
		path_family_sdk = os.path.join(path_device_sdk, family)
		if os.path.isdir(path_family) == True:
			shutil.rmtree(path_family)
		shutil.copytree(os.path.join(path_family_sdk, "Include"), path_family, dirs_exist_ok=True)
		shutil.copyfile(os.path.join(path_family_sdk, "Source", "system_" + family.lower() + ".c"), os.path.join(path_family, "system_" + family.lower() + ".c"))
	pass

if __name__ == "__main__":
	def dummyFunc(args):
		print("*** Platform: %s Version: %s ***"%(platform.system(), MY_VERSION))

	def mainSdkFunc(args):
		SdkFunc(args.path_sdk)
		pass

	def Main():
		parser = argparse.ArgumentParser(description='ZWave>ME. \n Welcome :)')

		parser.set_defaults(func=dummyFunc)
		subparsers = parser.add_subparsers()

		parserppSdk = subparsers.add_parser('sdk', help="")
		parserppSdk.add_argument('path_sdk', help="")
		parserppSdk.set_defaults(func=mainSdkFunc)

		args = parser.parse_args()
		args.func(args)

	Main()