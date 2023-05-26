#!/usr/bin/python
# -*- coding: utf-8 -*-
import inspect
import argparse
import platform
import os
import tempfile
import subprocess
import hashlib

MY_VERSION = "0.1"

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

if __name__ == "__main__":
	def dummyFunc(args):
		print("*** Platform: %s Version: %s ***"%(platform.system(), MY_VERSION))

	def mainCompliteAllFunc(args):
		CompliteAllFunc(args.path_tools)
		pass

	def Main():
		parser = argparse.ArgumentParser(description='ZWave>ME. \n Welcome :)')

		parser.set_defaults(func=dummyFunc)
		subparsers = parser.add_subparsers()

		parserppCompliteAll = subparsers.add_parser('complite_all', help="")
		parserppCompliteAll.add_argument('path_tools', help="")
		parserppCompliteAll.set_defaults(func=mainCompliteAllFunc)

		args = parser.parse_args()
		args.func(args)

	Main()