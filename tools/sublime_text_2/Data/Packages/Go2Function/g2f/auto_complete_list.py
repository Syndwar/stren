import global_settings

class AutocompleteList():
	@staticmethod
	def get():
		return list(global_settings.g_auto_completion_list)
	
	@staticmethod
	def clear():
		del global_settings.g_auto_completion_list[:]
	
	@staticmethod
	def append(value):
		if not value in global_settings.g_auto_completion_list:
			global_settings.g_auto_completion_list.append(value)