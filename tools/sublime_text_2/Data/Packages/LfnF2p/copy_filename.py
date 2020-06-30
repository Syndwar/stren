import sublime, sublime_plugin

class CopyFilenameCommand(sublime_plugin.TextCommand):
    def run(self, edit):
        if len(self.view.file_name()) > 0:
            full_path = self.view.file_name()
            path_parts = full_path.split("\\")
            file_name = path_parts[len(path_parts) - 1]
            sublime.set_clipboard(file_name)
            sublime.status_message("Copied file name")

    def is_enabled(self):
        return self.view.file_name() and len(self.view.file_name()) > 0
