import sublime, sublime_plugin
import os
import re

class GoToDescriptionCommand(sublime_plugin.TextCommand):
	def run(self, edit):
		if len(self.view.file_name()) > 0:
			suffix = "_desc"
			file_type = ".lua"
			full_path = self.view.file_name()
			path_parts = full_path.split("\\")
			file_name = path_parts[len(path_parts) - 1]
			
			if (suffix in file_name):
			    file_name = file_name.split(suffix + '.')[0]
			    file_name = file_name + file_type
			else:
			    file_name = file_name.split('.')[0]
			    file_name = file_name + suffix + file_type

			file_name_regex = "\\b" + file_name

			for folder in sublime.active_window().folders():
				for r, d, f in os.walk(folder):
					for files in f:
						fn = os.path.join(r, files)
						if (re.search(file_name_regex, fn)):
							sublime.active_window().open_file(fn)
							break

	def is_enabled(self):
		return self.view.file_name() and len(self.view.file_name()) > 0
