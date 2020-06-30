import sublime

class Directory():
	default_settings = [".git", ".svn", "CVS", ".hg"]
	settings = sublime.load_settings("go2function.sublime-settings")
	dir_exclude_patterns = settings.get("folder_exclude_patterns", default_settings)
	dir_include_patterns = settings.get("folder_include_patterns", default_settings)

	def __init__(self, directory):
		self.dir = directory

	def should_check(self):
		result = self.check_pattern(self.dir_include_patterns)
		if result:
			result = not self.check_pattern(self.dir_exclude_patterns)
			return result
	
	def check_pattern(self, patterns):
		for pattern in patterns:
			if pattern in self.dir:
				return True
		return False