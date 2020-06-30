import sublime
import functools

class ProjectFile:
	@classmethod
	def show(cls, response): #open the file and scroll to the definition
		filename, line = response
	
		print "[G2f] Opening file " + filename + " to line " + str(line)
		
		new_view = sublime.active_window().open_file(filename)
	
		cls.do_when(
			lambda: not new_view.is_loading(), 
			lambda: cls.cursor_to_pos(new_view, line)
		)
	
	@classmethod
	def do_when(cls, conditional, callback, *args, **kwargs):
		if conditional():
			return callback(*args, **kwargs)
		sublime.set_timeout(functools.partial(cls.do_when, conditional, callback, *args, **kwargs), 50)
	
	@staticmethod
	def cursor_to_pos(view, line): #move cursor to the definition too
		nav_line = line - 1
		nav_pt = view.text_point(nav_line, 0)
		fn_line = line
		pt = view.text_point(fn_line, 0)
	
		view.set_viewport_position(view.text_to_layout(nav_pt))
	
		view.sel().clear()
		view.sel().add(sublime.Region(pt))
	
		view.show(pt)