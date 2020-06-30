import sublime
import sublime_plugin

import os
import time
import re

from constants import Constants
from auto_complete_list import AutocompleteList
from dir_exclude_manager import Directory
from file_exclude_manager import File
from settings_access import Settings
from pattern_manager import Patterns
from selected_region import SelectedRegion

import file_search_manager

class GoToFieldCommand(sublime_plugin.TextCommand):
	def __init__(self, *args, **kw):
		super(GoToFieldCommand, self).__init__(*args, **kw)
		
		self.files = []
		self.project_files = []
		self.patterns = Patterns()

	def run(self, text):
		t1 = time.clock()
		
		del self.files[:]

		self.patterns.reset()
		Settings.reset()
		
		AutocompleteList.clear()

		self.do_search()

		t2 = time.clock()
		print t2 - t1

	def do_search(self):
		prev_word = SelectedRegion(self.view).get_previous_word()

		if (Constants.SELF_WORD != prev_word):
			self.patterns.init_table_patterns(prev_word)
			self.check_project_folders(self.check_pattern_in_lines)
		
			Settings.get_word_param().enable(False)
			Settings.get_explicit_param().enable(False)
			Settings.get_autocomplete_param().enable(True)

			self.view.run_command("auto_complete")
		else:
			print "[G2f] Could not find function definition"

	def check_project_folders(self, callback):
		if (0 == len(self.project_files)):
			for folder in sublime.active_window().folders():
				for r, d, f in os.walk(folder):
					if Directory(r).should_check():
						for files in f:
							fn = os.path.join(r, files)
							if File(fn).should_check():
								self.project_files.append(fn)
								file_search_manager.check_file(fn, callback, True)
		else:
			print "[G2f] " + str(len(self.project_files)) + " files in cach to check."
			for fn in self.project_files:
				file_search_manager.check_file(fn, callback, True)

	def check_pattern_in_lines(self, lines):
		for pattern in self.patterns.get_patterns():
			for (content) in re.findall(pattern, lines):
				words = content.split('\n')
				for word in words:
					if Constants.EQUAL in word:
						word = word.split(Constants.EQUAL)[0].strip()
						out = (word, word)
						AutocompleteList.append(out)