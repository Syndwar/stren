import sublime
import sublime_plugin

from  auto_complete_list import AutocompleteList
from settings_access import Settings

class GoToFunctionAutocomplete(sublime_plugin.EventListener):
	def on_query_completions(self, view, prefix, locations):
		
		Settings.reset()

		enabled = Settings.get_word_param().is_enabled() and (0 != len(prefix))
		word_completions = 0 if enabled else sublime.INHIBIT_WORD_COMPLETIONS

		enabled = Settings.get_explicit_param().is_enabled()
		explicit_completions = 0 if enabled else sublime.INHIBIT_EXPLICIT_COMPLETIONS

		Settings.get_autocomplete_param().enable(False)

		return (AutocompleteList.get() , word_completions | explicit_completions)