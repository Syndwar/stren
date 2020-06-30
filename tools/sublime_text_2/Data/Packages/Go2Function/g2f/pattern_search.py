from pattern_manager import Patterns

import file_search_manager

class PatternSearchLogic():
	def __init__(self, word):
		self.files = []
		self.word = word

		self.patterns = Patterns()
		self.patterns.reset()
		self.patterns.init_common_patterns(self.word)


	def find_patterns_in_line(self, line, number, fn):
		for pattern in self.patterns.get_patterns():
			match = pattern.search(line)
			if match:
				self.files.append((fn, number))
				break
				
	def run(self):
		print "[G2f] Searching for 'function " + self.word + "'..."
		
		del self.files[:]
	
		file_search_manager.check_project_folders(self.find_patterns_in_line)
	
		result = file_search_manager.show_search_results(self.files)
			
		if not result:
			print "[G2f] " + self.word + " not found"