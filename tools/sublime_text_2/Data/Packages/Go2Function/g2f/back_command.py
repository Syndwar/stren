import sublime
import sublime_plugin

from back_path import BackPath
from project_file import ProjectFile

class GoToFunctionBackCommand(sublime_plugin.TextCommand):
	def run(self, text):
		if BackPath.is_valid():
			current_path = BackPath.get_end()
			destination_path = BackPath.get_start()
			if (current_path and destination_path):
				BackPath.set_start(current_path)
				BackPath.set_end(destination_path)
				ProjectFile.show(destination_path)