import sublime
import sublime_plugin
import re
import os
import string

settings = sublime.load_settings("find_unused_strings.sublime-settings")
line_pattern = settings.get("input_line_pattern")
folder_include_patterns = settings.get("folder_include_patterns")
file_include_patterns = settings.get("file_include_patterns")
file_exclude_patterns = settings.get("file_exclude_patterns")

class FindUnusedStringsCommand(sublime_plugin.TextCommand):
    def run(self, edit):

        view = self.view

        search_texts = []

        regions = view.find_all(line_pattern)
        for region in regions:
            if (not region.empty()):
                text = view.substr(region).encode('ascii','ignore')
                text = text.split('"')[1]
                if (len(text) > 0):
                    search_texts.append(text)

        search_texts = self.check_project_folders(search_texts)
        new_view = sublime.active_window().new_file()
        last_point = 0
        for text in search_texts:
            last_point += new_view.insert(edit, last_point, text)
            last_point += new_view.insert(edit, last_point, "\n")

    def check_project_folders(self, search_texts):
        for folder in sublime.active_window().folders():
            for r, d, f in os.walk(folder):
                if self.should_check_dir(r):
                    for files in f:
                        fn = os.path.join(r, files)
                        if self.should_check_file(fn):
                            search_texts = self.find_texts(fn, search_texts)
        return search_texts

    def should_check_dir(self, dir_name):
        for pattern in folder_include_patterns:
            if pattern in dir_name:
                return True
        return False

    def should_check_file(self, file_name):
        for pattern in file_exclude_patterns:
            if pattern in file_name:
                return False

        for pattern in file_include_patterns:
            pattern = re.sub('\*\.', '.', pattern)
            if re.search(pattern, file_name):
                return True

        return False

    def find_texts(self, fn, search_texts):
        remained_texts = []
        search = open(fn, "r")
        lines = search.read()

        for text in search_texts:
            if (not (text in lines)):
                remained_texts.append(text)

        search.close()
        return remained_texts


    def is_enabled(self):
        current_file_name = self.view.file_name()
        for file_name in settings.get("include_files"):
            if file_name in current_file_name:
                return True
        return False


