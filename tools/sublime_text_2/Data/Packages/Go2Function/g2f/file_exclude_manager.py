import sublime
import re

def create_pattern_regex(patterns):
	combined = None
	if patterns:
		rpatterns = []    #merge patterns into single regex
		for pattern in patterns:
			pattern = re.sub('\*\.', '.', pattern)
			pattern = re.escape(str(pattern))
			rpatterns.append(pattern)

		combined = "(" + ")|(".join(rpatterns) + ")"
			
	return combined

class File():
	settings = sublime.load_settings("go2function.sublime-settings")
			
	include_patterns = settings.get("file_include_patterns")
	include_files = create_pattern_regex(include_patterns)
			
	exclude_patterns = settings.get("file_exclude_patterns")
	excluded_files = create_pattern_regex(exclude_patterns)

	def __init__(self, filename):
		self.filename = filename

	def should_check(self):
		result = self.check_pattern(self.include_files)
		if result:
			result = not self.check_pattern(self.excluded_files)
		return result

	def check_pattern(self, patterns):
		if patterns:
			if re.search(patterns, self.filename):
				return True
		return False