import sublime_plugin

import time

from constants import Constants
from back_path import BackPath
from  pattern_search import PatternSearchLogic
from selected_region import SelectedRegion
from autocomplete_search import AutocompleteSearchLogic

class GoToFunctionCommand(sublime_plugin.TextCommand):
	def run(self, text):
		t1 = time.clock()
		
		self.do_search()

		t2 = time.clock()
		print t2 - t1

	def do_search(self):
		view = self.view
		
		self.store_start_file()

		word = SelectedRegion(view).get_current_word()

		if ((word == Constants.POINT) or (word == Constants.COLON)):
			AutocompleteSearchLogic(view).run()
		elif ("" != word):
			PatternSearchLogic(word).run()

	def store_start_file(self):
		view = self.view

		region = view.sel()[0]
		fn = view.file_name()
		line, col = view.rowcol(region.a)
		BackPath.set_start((fn, line))





