import sublime
import sublime_plugin

from constants import Constants
from selected_region import SelectedRegion

class GoToFunctionEventListener(sublime_plugin.EventListener):
	def on_modified(self, view):
		settings = sublime.load_settings("go2function.sublime-settings")

		if settings.get("enable_auto_complete"):
			word = SelectedRegion(view).get_current_word()
			if ((word == Constants.POINT) or (word == Constants.COLON)):
				view.run_command("go_to_function")
