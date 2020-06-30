import sublime
import sublime_plugin

import re
import os

from back_path import BackPath
from dir_exclude_manager import Directory
from file_exclude_manager import File
from project_file import ProjectFile

settings = sublime.load_settings("go2function.sublime-settings")
use_cached_files = settings.get("use_cached_files")

project_files = []

def show_search_results(files):
	result = True
	if (0 == len(files)):
		result = False
	elif (1 == len(files)):
		ProjectFile.show(files[0])
		BackPath.set_end(files[0])
	else:
		show_files_in_quick_panel(files)
	return result

def show_files_in_quick_panel(files):
	paths = []
	for path, line in files:
		paths.append(path + ":" + str(line))
	window = sublime.active_window()
	window.show_quick_panel(paths, lambda i: select_file(files, i))

def select_file(files, index):
	if index > -1 and len(files) > index:
		path = files[index]
		ProjectFile.show(path)
		BackPath.set_end(path)

def check_file(fn, callback, read_all = False):
	search = open(fn, "r")
	if read_all:
		lines = search.read()
		callback(lines)
	else:
		lines = search.readlines()
		for number, line in enumerate(lines):
			if line.strip():
				callback(line, number, fn)
	search.close()

def check_project_folders(callback):
	if (0 == len(project_files)):
		for folder in sublime.active_window().folders():
			for r, d, f in os.walk(folder):
				if Directory(r).should_check():
					for files in f:
						fn = os.path.join(r, files)
						if File(fn).should_check(): #a long list of patterns can slow this down...
							check_file(fn, callback)
							if use_cached_files:
								project_files.append(fn)
	else:
		print "[G2f] " + str(len(project_files)) + " files in cach to check."
		for fn in project_files:
			check_file(fn, callback)