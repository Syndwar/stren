import sublime
import re

class SelectedRegion():
	def __init__(self, view):
		self.view = view
		self.selection_region = view.sel()[0]

	def get_current_word(self):
		word_region = self.view.word(self.selection_region)
		word = self.view.substr(word_region).strip()
		word = re.sub('[\(\)\{\}\s]', '', word)
		return str(word)
	
	def get_previous_word(self):
		prev_region = sublime.Region(self.selection_region.a - 2, self.selection_region.b - 2)
		word_region = self.view.word(prev_region)
		word = self.view.substr(word_region).strip()
		word = str(re.sub('[\s]', '', word))
		return word