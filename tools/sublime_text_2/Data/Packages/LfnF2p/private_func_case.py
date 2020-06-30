import sublime
import sublime_plugin
import re

class PrivateFuncCaseCommand(sublime_plugin.TextCommand):
    def run(self, edit):
        self.selection_region = self.view.sel()[0]
        word_region = self.view.word(self.selection_region)
        word = self.view.substr(word_region).strip()
        if (len(word) > 0):
            word = word[0].lower() + word[1:]
            self.view.replace(edit, word_region, "__" + word)