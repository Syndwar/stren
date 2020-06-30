import sublime
import sublime_plugin
import subprocess
import threading

class UpdateFolderCommand(sublime_plugin.TextCommand):
    def run(self, edit):
        folders = self.view.window().folders()
        folder_path = folders[0].replace("assets", "")
        
        th = UpdateFolderThread(folder_path)
        th.start()


class UpdateFolderThread(threading.Thread):
    def __init__(self, folder_path):
        self.folder_path = folder_path

        threading.Thread.__init__(self)

    def run(self):
        if self.folder_path:
            command = "TortoiseProc.exe /command:update /path:"
            command = command + self.folder_path
            subprocess.Popen(command)
