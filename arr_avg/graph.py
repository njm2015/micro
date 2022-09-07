import matplotlib.pyplot as plt

if __name__ == '__main__':

	#x = [128, 144, 160, 176, 192, 208, 224, 240, 256]
	#y_2d_row = [37, 52, 57, 74, 83, 111, 111, 121, 135]
	#y_2d_col = [39, 49, 56, 76, 81, 104, 106, 118, 135]
	#y_1d_row = [38, 47, 54, 76, 77, 98, 102, 118, 134]

	x = [500, 550, 600, 650, 700, 750, 800, 850, 900, 950]
	y_2d_row = [513, 613, 733, 842, 986, 1140, 1292, 1454, 1630, 1821]
	y_2d_col = [522, 647, 755, 918, 1031, 1335, 1663, 2099, 3190, 3501]
	y_1d_row = [499, 604, 735, 845, 1003, 1149, 1295, 1493, 1641, 1838] 

	plt.plot(x, y_2d_row, label='row2d')
	plt.plot(x, y_2d_col, label='col2d')
	plt.plot(x, y_1d_row, label='row1d')
	plt.xlabel('N')
	plt.ylabel('L1 DTLB Misses')
	plt.title('Cache Misses in Traversal of an NxN Array')
	plt.legend()
	plt.show()
