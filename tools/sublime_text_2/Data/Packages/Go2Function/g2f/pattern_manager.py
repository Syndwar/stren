import string
import re

class Patterns():
	class_methods_str = "function\s+$SearchName[.:][_a-zA-Z0-9]+\("
	class_methods_template = string.Template(class_methods_str)

	methods_str = "function\s+[a-zA-Z0-9]+[:.]$SearchName\("
	methods_template = string.Template(methods_str)

	function_str = "function\s*$SearchName\s*\("
	function_template = string.Template(function_str)

	function_invert_str = "$SearchName\s*=\s*function\s*\("
	function_invert_template = string.Template(function_invert_str)

	class_str = "class\s+['\"]$SearchName['\"](\s+\([_a-zA-Z0-9]+\))*"
	class_tempate = string.Template(class_str)

	tables_str = "\\b$SearchName\s*=[^=]"
	tables_template = string.Template(tables_str)
		
	table_content_str = "\\b$SearchName\s*=\s*\{([^\{]*)\}"
	tables_content_template = string.Template(table_content_str)

	table_values_str = "\\b$SearchName\.([_a-zA-Z0-9]*\s*\=[^=])"
	tables_values_template = string.Template(table_values_str)
	
	def __init__(self):
		self.search_patterns = []

	def reset(self):
		del self.search_patterns[:]

	def init_autocomplete_patterns(self, word):
		self.search_patterns.append(self.create_pattern(word, self.class_methods_template))
	
	def init_table_patterns(self, word):
		self.search_patterns.append(self.create_pattern(word, self.tables_values_template))
		self.search_patterns.append(self.create_pattern(word, self.tables_content_template))
	
	def init_common_patterns(self, word):
		self.search_patterns.append(self.create_pattern(word, self.methods_template))
		self.search_patterns.append(self.create_pattern(word, self.class_tempate))
		self.search_patterns.append(self.create_pattern(word, self.tables_template))
		self.search_patterns.append(self.create_pattern(word, self.function_template))
		self.search_patterns.append(self.create_pattern(word, self.function_invert_template))
	
	@staticmethod
	def create_pattern(word, template):
		pattern = template.substitute(SearchName = word)
		return re.compile(pattern)
	
	def get_patterns(self):
		return self.search_patterns
	
