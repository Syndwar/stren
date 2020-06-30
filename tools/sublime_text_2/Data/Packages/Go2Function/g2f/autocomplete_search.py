import re

from constants import Constants
from auto_complete_list import AutocompleteList
from settings_access import Settings
from pattern_manager import Patterns
from selected_region import SelectedRegion

import file_search_manager


class AutocompleteSearchLogic():
	def __init__(self, view):
		self.view = view
		self.patterns = Patterns()

	def run(self):
		view = self.view

		self.patterns.reset()
		Settings.reset()
		
		AutocompleteList.clear()
	
		prev_word = SelectedRegion(view).get_previous_word()
	
		if (Constants.SELF_WORD == prev_word):
			class_names = self.find_class_names()
		else:
			class_names = [prev_word]
	
		if (len(class_names) > 0):
			for class_name in class_names:
				self.patterns.init_autocomplete_patterns(class_name)
			file_search_manager.check_project_folders(self.find_methods_in_line)
			
			Settings.get_word_param().enable(False)
			Settings.get_explicit_param().enable(False)
			Settings.get_autocomplete_param().enable(True)
	
			view.run_command("auto_complete")
		else:
			print "[G2f] could not find function definition"


	def find_class_names(self):
		view = self.view
		word = None
		class_region = None
	
		selection_region = view.sel()[0]
		regions = view.find_by_selector('meta.class.simple.lua')
		regions = regions + view.find_by_selector('meta.class.derived.lua')
			
		for region in regions:
			if region.a < selection_region.a:
				class_region = region
	
		classes = []
		if class_region:
			word = view.substr(class_region)
			words = re.sub("[\'\"\(\)]", ' ', word).strip().split()
				
		classes.append(str(words[1]))
		if (len(words) > 2):
			classes.append(str(words[2]))
			
		return classes

	def find_methods_in_line(self, line, number, fn):
		if (Constants.FUNCTION in line) and (
			(Constants.POINT in line) or (Constants.COLON in line)):
			
			for pattern in self.patterns.get_patterns():
				match = pattern.search(line)
				if match:
					method = match.group(0)
					
					start_pos = line.find(Constants.COLON)
					if (start_pos < 0):
						start_pos = line.find(Constants.POINT)
					end_pos = line.find(')')
					if ((start_pos > 0) and (end_pos > start_pos)):
						subs = line[start_pos + 1 : end_pos + 1]
	
						method = re.sub("[.:\(\)]", ' ', method).strip().split()
						method = method[2]
						out = (method, subs)
	
					AutocompleteList.append(out)
