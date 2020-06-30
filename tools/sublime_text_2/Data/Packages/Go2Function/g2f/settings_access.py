import global_settings

class Param:
	def __init__(self, id):
		self.id = id

	def enable(self, value):
		global_settings.g_params[self.id] = value

	def is_enabled(self):
		return global_settings.g_params[self.id]

class Settings:
	@staticmethod
	def get_autocomplete_param():
		return Param("autocomplete")

	@staticmethod
	def get_word_param():
		return Param("word_completion")

	@staticmethod
	def get_explicit_param():
		return Param("explicit_completion")

	@classmethod
	def reset(cls):
		if (not cls.get_autocomplete_param().is_enabled()):
			cls.get_word_param().enable(True)
			cls.get_explicit_param().enable(True)