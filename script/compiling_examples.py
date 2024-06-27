#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import tempfile
import subprocess
import hashlib
import sys

def func_prog_dir_get() -> str:
	if getattr(sys, 'frozen', False):
		application_path = os.path.dirname(sys.executable)
	else:
		application_path = os.path.dirname(__file__)
	return (os.path.abspath(application_path))


def finallizeStepStatus(text, stat_text):
	print('\r%-40s %s' % (text, '.' * 30), end='')
	print('%30s\n' % (stat_text), end='')

def CompliteAllChipLoopDirFunc(path_ino:str, chip_name:str, path_out:str, tool_path:str, gcc_version:str, question:bool) -> None:
	path_core =  os.path.abspath(os.path.join(func_prog_dir_get(), ".."))
	zme_make = os.path.abspath(os.path.join(tool_path, "zme_make", "zme_make"))
	path_gcc_include = os.path.abspath(os.path.join(tool_path, "gcc", "lib", "gcc", "arm-none-eabi", gcc_version, "include"))
	path_gcc_bin = os.path.abspath(os.path.join(tool_path, "gcc", "bin"))
	path_libclang = os.path.abspath(os.path.join(tool_path, "libClang"))
	path_cores = os.path.abspath(os.path.join(path_core, "hardware", "arduino", "zunoG2", "cores"))
	path_libraries = os.path.abspath(os.path.join(path_core, "hardware", "arduino", "zunoG2", "libraries"))
	with os.scandir(path_ino) as it:
		for entry in it:
			if entry.is_dir():
				CompliteAllChipLoopDirFunc(entry.path, chip_name, path_out, tool_path, gcc_version, question)
			if entry.is_file() and entry.name.endswith(".ino"):
				path_out_ino =  os.path.join(path_out, hashlib.md5(entry.path.encode()).hexdigest())
				try:
					if os.path.exists(path_out_ino) == False:
						os.makedirs(path_out_ino, exist_ok=True)
				except Exception as e:
					sys.stderr.write("Error: mkdir. Code %s"%e)
					sys.exit(-1)
				while True:
					try:
						arg = [zme_make, "build", entry.path, '-S', path_cores, '-S', path_libraries, "-S", path_gcc_include, "-B", path_out_ino, "-T", path_gcc_bin, "-lcl", path_libclang, "-O", "BO:-Wall", "-O", "BO:-Wextra", "-O", "BO:-Werror", "-C", chip_name]
						out = subprocess.run(arg, stdout=subprocess.PIPE, text=True)
					except Exception as e:
						sys.stderr.write("Error: No run. Code %s"%e)
						sys.exit(-1)
					if out.returncode == 0x0:
						finallizeStepStatus(os.path.basename(entry.path), "OK")
						break
					sys.stderr.write(out.stdout)
					if question == False:
						sys.exit(-1)
					while True:
						text = input("Would you like to repeat, skip or cancel? - repeat|skip|cancel\n")
						if text == "cancel":
							sys.exit(-1)
						if text == "repeat" or text == "skip":
							break
					if text == "repeat":
						continue
					if text == "skip":
						break
					finallizeStepStatus(os.path.basename(entry.path), "SKIP")
	pass

argv = sys.argv[0x1:]
if len(argv) < 0x2 or len(argv) > 0x3:
	sys.stderr.write("Wrong number of arguments\n")
	sys.exit(-1)
tool_path = argv[0x0]
gcc_version = argv[0x1]
question = False
if len(argv) == 0x3:
	question = True

path_out = tempfile.TemporaryDirectory().name
ino_lists = [os.path.abspath(os.path.join(func_prog_dir_get(), "..", "hardware", "arduino", "zunoG2", "ctt"))]
# ino_lists = ino_lists + [os.path.abspath(os.path.join(func_prog_dir_get(), "..", "hardware", "arduino", "zunoG2", "libraries", "Z-Uno-2G", "examples"))]
chip_list = ["ZGM130S037HGN1"]
for chip in chip_list:
	try:
		path_out_chip = os.path.join(path_out, chip)
		if os.path.exists(path_out_chip) == False:
			os.makedirs(path_out_chip, exist_ok=True)
	except Exception as e:
		sys.stderr.write("Error: mkdir. Code %s\n"%(e))
		sys.exit(-1)
	for ino in ino_lists:
		CompliteAllChipLoopDirFunc(ino, chip, path_out_chip, tool_path, gcc_version, question)
