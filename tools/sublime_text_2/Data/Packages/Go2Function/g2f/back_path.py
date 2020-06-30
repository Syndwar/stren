import global_settings

class BackPath():
	@staticmethod
	def set_start(path):
		global_settings.g_back_path[0] = path
	
	@staticmethod
	def get_start():
		return global_settings.g_back_path[0]
	
	@staticmethod
	def set_end(path):
		global_settings.g_back_path[1] = path
	
	@staticmethod
	def get_end():
		return global_settings.g_back_path[1]
	
	@staticmethod
	def is_valid():
		return 2 == len(global_settings.g_back_path)