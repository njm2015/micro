from manim import *
import random

class ArrayTable(Scene):

	def construct(self):
	
		self.camera.background_color = WHITE

		#rand_arr = [[random.randint(-9, 9) for i in range(10)] for j in range(10)]
		empty_arr = [['.' for i in range(31)] for j in range(15)]

		t0 = Table(
			 	empty_arr,	
				include_outer_lines=True,
				h_buff=0.5,
				v_buff=0.5,
				entries_background_color=BLACK,
				)
		t0.scale(0.5)
		t0.set_column_colors(*(BLACK for i in range(31)))
		t0.get_horizontal_lines().set_color(BLACK)
		t0.get_vertical_lines().set_color(BLACK)
		self.add(t0)

		#t0.get_columns[0].color = RED

		prev_rect = None
		for i in range(0, 32, 8):
			if prev_rect is not None:
				self.play(Uncreate(prev_rect))

			prev_rect = SurroundingRectangle(t0.get_columns()[i:i+8], color=RED, stroke_width=10)
			self.play(Create(prev_rect))
			self.wait(1)
