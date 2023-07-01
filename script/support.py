#!/usr/bin/python
# -*- coding: utf-8 -*-
import inspect
import argparse
import platform
import os
import tempfile
import subprocess
import hashlib
import shutil
import json

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

def CompliteAllChipLoopDirFunc(path_ino, path_tools, path_out, chip_name):
	path_core =  os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))), "..", "..","core"))
	zme_make = os.path.abspath(os.path.join(path_tools, "toolchain", "zme_make", "zme_make"))
	path_gcc_include = os.path.abspath(os.path.join(path_tools, "gcc", "lib", "gcc", "arm-none-eabi", "10.3.1", "include"))
	path_gcc_bin = os.path.abspath(os.path.join(path_tools, "gcc", "bin"))
	path_libclang = os.path.abspath(os.path.join(path_tools, "toolchain", "libClang"))
	path_cores = os.path.abspath(os.path.join(path_core, "hardware", "arduino", "zunoG2", "cores"))
	path_libraries = os.path.abspath(os.path.join(path_core, "hardware", "arduino", "zunoG2", "libraries"))
	with os.scandir(path_ino) as it:
		for entry in it:
			if entry.is_dir():
				CompliteAllChipLoopDirFunc(entry.path, path_tools, path_out, chip_name)
			if entry.is_file() and entry.name.endswith(".ino"):
				path_out_ino =  os.path.join(path_out, hashlib.md5(entry.path.encode()).hexdigest())
				try:
					if os.path.exists(path_out_ino) == False:
						os.makedirs(path_out_ino, exist_ok=True)
				except Exception as e:
					print("Error: mkdir. Code %s"%e)
					exit(-1)
				while True:
					try:
						arg = [zme_make, "build", entry.path, '-S', path_cores, '-S', path_libraries, "-S", path_gcc_include, "-B", path_out_ino, "-T", path_gcc_bin, "-lcl", path_libclang, "-O", "BO:-Wall", "-O", "BO:-Wextra", "-O", "BO:-Werror", "-C", chip_name]
						out = subprocess.run(arg, stdout=subprocess.PIPE, text=True)
					except Exception as e:
						print("Error: No run. Code %s"%e)
						exit(-1)
					if out.returncode == 0x0:
						finallizeStepStatus(os.path.basename(entry.path), "OK")
						break
					print(out.stdout)
					while True:
						text = input("Would you like to repeat, skip or cancel? - repeat|skip|cancel\n")
						if text == "cancel":
							exit(-1)
						if text == "repeat" or text == "skip":
							break
					if text == "repeat":
						continue
					if text == "skip":
						break
					finallizeStepStatus(os.path.basename(entry.path), "SKIP")
	pass

def CompliteAllChipFunc(path_ino, path_out, path_tools, chip_name):
	try:
		if os.path.exists(path_out) == False:
			os.makedirs(path_out, exist_ok=True)
	except Exception as e:
		print("Error: mkdir. Code %s"%e)
		exit(-1)
	CompliteAllChipLoopDirFunc(path_ino, path_tools, path_out, chip_name)
	pass

def CompliteAllFunc(path_tools):
	path_out = os.path.join(tempfile.gettempdir(), "Zuno_test_7423A65F79394BC7B1DC1D417422781F")
	path_ino = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))), "..", "..","core", "hardware", "arduino", "zunoG2", "ctt"))
	chip_name = "ZGM130S037HGN1"
	CompliteAllChipFunc(path_ino, os.path.join(path_out, chip_name), path_tools, chip_name)
	path_ino = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))), "..", "..","core", "hardware", "arduino", "zunoG2", "libraries", "Z-Uno-2G", "examples"))
	CompliteAllChipFunc(path_ino, os.path.join(path_out, chip_name), path_tools, chip_name)
	pass

def SdkFunc(path_sdk):
	path_core = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))), "..", "..","core"))
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

	def mainCompliteAllFunc(args):
		CompliteAllFunc(args.path_tools)
		pass

	def mainSdkFunc(args):
		SdkFunc(args.path_sdk)
		pass

	def Main():
		parser = argparse.ArgumentParser(description='ZWave>ME. \n Welcome :)')

		parser.set_defaults(func=dummyFunc)
		subparsers = parser.add_subparsers()

		parserppCompliteAll = subparsers.add_parser('complite_all', help="")
		parserppCompliteAll.add_argument('path_tools', help="")
		parserppCompliteAll.set_defaults(func=mainCompliteAllFunc)

		parserppSdk = subparsers.add_parser('sdk', help="")
		parserppSdk.add_argument('path_sdk', help="")
		parserppSdk.set_defaults(func=mainSdkFunc)

		args = parser.parse_args()
		args.func(args)

	Main()