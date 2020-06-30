import sublime
import sublime_plugin
import subprocess
import threading

replace = ["assets", ""]

class RunFileCommand(sublime_plugin.TextCommand):
    def run(self, edit, filename, folder=None, args=None):

        folders = self.view.window().folders()

        filepath = folders[0].replace(replace[0], replace[1])
        
        if (None != folder):
            filepath += folder + "\\"

        th = RunFileThread(filepath, filename, args)
        th.start()


class RunFileThread(threading.Thread):
    def __init__(self, filepath, filename, args=None):
        self.filepath = filepath
        self.filename = filename
        self.args = args

        threading.Thread.__init__(self)

    def run(self):
        if self.filepath:
            command = self.filepath + self.filename
            if self.args:
                command = command + " " + self.args
            print command
            proc = subprocess.Popen(command, cwd = self.filepath)