from tkinter import *
from tkinter import ttk
from tkinter import font
from PIL import *
from PIL import ImageTk
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
from tkinter import filedialog


rects = []
grid = 5
images = []
indexs = []
flag = 0
ranges = []
photos = []
index = 0
images = []
imgs = []
chars = []
chcanvas = []
items_img = []
last_paint = 0
frchar = []

def_nameHeader = ""
def_name = ""
f_simWidth = ""
f_simHeight = ""
f_colSim = ""
f_bytesSim = ""
f_ranges = ""
f_printRanges = ""
f_printSimbols = ""


def dont_smooth(inp_im):
	w_im, h_im = inp_im.size
	for y in range(h_im):
		for x in range(w_im):
			col = (0,0,0,255) if inp_im.getpixel((x,y)) <= (170,170,170,255) else (255,255,255,255)
			inp_im.putpixel((x,y),col)


def addch(Frame,curch):
	global photos
	global chars
	global items_img
	index = len(images)
	frchar.append(LabelFrame(Frame))
	lchar = Label(frchar[index], text=f"'{curch}'")
	chcanvas.append(Canvas(frchar[index],width = 100, height = 100, bg="black", name=str(ord(curch))))
	# chcanvas.append(Canvas(Frame,width = 100, height = 100, bg="black"))
	chcanvas[index].bind("<Button-1>", clickl)
	chars.append(curch)
	images.append(image.copy())
	image_sub = sub_img.copy()
	draw = ImageDraw.Draw(image_sub)
	draw.text((0, 0), curch,(0,0,0),font=cur_font)
	images[index].paste(image_sub.resize((rec_h,rec_h)),(0,0))
	# draw = ImageDraw.Draw(images[index])
	# draw.text((0, 0), curch,(0,0,0),font=cur_font)
	# draw = ImageDraw.Draw(images[index])
	dont_smooth(images[index])
	photos.append(ImageTk.PhotoImage(images[index].resize((100,100))))
	items_img.append(chcanvas[index].create_image(3, 3, image=photos[index], anchor=NW))
	lchar.pack(side=LEFT) 
	chcanvas[index].pack(side=LEFT)
	frchar[index].pack(fill="both")


def fill_rect(Frame):
	for y in range(rec_h):
		for x in range(rec_w):
			rects.append(Frame.create_rectangle(
								x * grid + 10,
								y * grid + 10,
								x * grid + grid - 1 + 10,
								y * grid + grid - 1 + 10,
								fill = "white")
						)


def resize_rect():
	global rec_w
	global grid
	inp = spin.get()
	grid = int(inp)
	for y in range(rec_h):
		for x in range(rec_w):
			maincanva.coords(rects[y * rec_w + x],
								x * grid + 10,
								y * grid + 10,
								x * grid + grid - 1 + 10,
								y * grid + grid - 1 + 10
							)
	maincanva.configure(scrollregion=(0,0,(rec_w + 1) * grid + 10,(rec_h + 1) * grid))
	

def resize_chars():
	global image
	image = image.resize((rec_w,rec_h))
	for i in range(len(images)):
		img_sub = image.copy()
		img_sub.paste(images[i], (0,0))
		images[i] = img_sub.copy()


def add_col():
	global rec_w
	rec_w += 1
	print(rec_w)
	for y in range(rec_h):
		rects.insert(y * rec_w + rec_w - 1,maincanva.create_rectangle(0,0,1,1,fill="white"))
	image = Image.new("RGBA", (rec_w, rec_h),(255,255,255))
	resize_rect()
	resize_chars()


def add_row():
	global rec_h
	rec_h += 1
	print(rec_w)
	for y in range(rec_w):
		rects.append(maincanva.create_rectangle(0,0,1,1,fill="gray"))
	image = Image.new("RGBA", (rec_w, rec_h),(255,255,255))
	resize_rect()
	resize_chars()


def clickl(event):
	global index
	print(str(event.widget))
	char = chr(int(str(event.widget).split(".")[-1]))
	if not char:return
	index = chars.index(char)
	sub_img = images[index]
	load(images[index])

# chcanvas[1].itemconfig(items_img[1], image 

def draw_black(event):
	global last_paint
	tag = maincanva.find_overlapping(event.x, event.y, event.x, event.y)
	if not tag or tag[0] == last_paint:return
	tag = tag[0]
	last_paint = tag
	x = rects.index(tag) % rec_w
	y = rects.index(tag) // rec_w
	col = "#000" 
	maincanva.itemconfig(rects[y * rec_w + x],fill=col)


def draw_white(event):
	global last_paint
	print(event.type)
	print(event)
	tag = maincanva.find_overlapping(event.x, event.y, event.x, event.y)
	if not tag or tag[0] == last_paint:return
	tag = tag[0]
	last_paint = tag
	x = rects.index(tag) % rec_w
	y = rects.index(tag) // rec_w
	col = "#fff" 
	maincanva.itemconfig(rects[y * rec_w + x],fill=col)

def click(event):
	tag = maincanva.find_withtag(CURRENT)
	if not tag:return
	tag = tag[0]
	x = rects.index(tag) % rec_w
	y = rects.index(tag) // rec_w
	col = "#000" if maincanva.itemcget(rects[y * rec_w + x],"fill") == "#fff" else "#fff"
	maincanva.itemconfig(rects[y * rec_w + x],fill=col)
	

def app_char():
	for y in range(rec_h):
		for x in range(rec_w):
			col = (255, 255, 255, 255) if maincanva.itemcget(rects[y * rec_w + x],"fill") == "#fff" else (0,0,0,255)
			images[index].putpixel((x,y),col)
	# photos[index](ImageTk.PhotoImage(images[index].resize((100,100))))
	photos[index] = (ImageTk.PhotoImage(images[index].resize((100,100))))
	chcanvas[index].itemconfig(items_img[index], image = photos[index])



def load(img):
	for y in range(rec_h):
		for x in range(rec_w):
			pix = img.getpixel((x,y))
			col = "#fff" if pix == (255, 255, 255, 255) else "#000"
			maincanva.itemconfig(rects[y * rec_w + x],fill=col)

def app_range():
	global rec_w
	global rec_h
	global ch_size
	global image
	global sub_img
	global cur_font
	global sub_font
	global flag
	chfrom = int(spinfrom.get())
	chto = int(spinto.get()) + 1
	if flag == 0 and (chto - chfrom) > 0:
		print_button.configure(state="normal")
		spin.configure(state="normal")
		apply.configure(state="normal")
		font_name = filedialog.askopenfilename(defaultextension = '.ttf', filetypes = [('Fonts', '.ttf'), ('all files', '.*')])
		spin_size = int(spin_font.get())
		spin_font.configure(state="disable")
		# cur_font = ImageFont.truetype(font_name, spin_size)
		sub_font = ImageFont.truetype(font_name, spin_size)
		rec_w = sub_font.getmetrics()[0]
		rec_h = sub_font.getmetrics()[0] + sub_font.getmetrics()[1]
		cur_font = ImageFont.truetype(font_name, spin_size * 20)
		sfont_size = cur_font.getmetrics()[0] + cur_font.getmetrics()[1]
		ch_size = sub_font.getmetrics()[0] + sub_font.getmetrics()[1]
		sub_img = Image.new("RGBA", (sfont_size,sfont_size), (255,255,255,255))
		image = Image.new("RGBA", (rec_w, rec_h),(255,255,255,255))
		fill_rect(maincanva)
		flag = 1
	if (chto - chfrom) > 0:
		for i in range(chfrom, chto,1):
			addch(sslistfr,chr(i))
		ranges.append((chfrom, chto - 1))

def preparePrintRanges():
	global f_printRanges, f_bytesSim
	sim_len = (rec_h // 8 + 1) * rec_w + 1
	st_byte = 5 + 12 * len(ranges)
	col_sim = 0
	for i in range(len(ranges)):
		col_sim = ranges[i][1] - ranges[i][0] 
		f_printRanges += f"\t{format((ranges[i][0]) & 0xff, '#04x')}, {format((ranges[i][0] >> 8) & 0xff, '#04x')}, {format((ranges[i][0] >> 16) & 0xff, '#04x')}, {format(ranges[i][0] >> 24 & 0xff, '#04x')},\t\t\t//range - Start simbol\n"
		f_printRanges += f"\t{format((ranges[i][1]) & 0xff, '#04x')}, {format((ranges[i][1] >> 8) & 0xff, '#04x')}, {format((ranges[i][1] >> 16) & 0xff, '#04x')}, {format(ranges[i][1] >> 24 & 0xff, '#04x')},\t\t\t//\t\t\t\tend sibol,\n"
		f_printRanges += f"\t{format((st_byte) & 0xff, '#04x')}, {format((st_byte >> 8) & 0xff, '#04x')}, {format((st_byte >> 16) & 0xff, '#04x')}, {format(st_byte >> 24 & 0xff, '#04x')},\t\t\t//\t\t\t\tbyte of start\n"
		st_byte += col_sim * sim_len


def prepare_PrintSimbols():
	global f_printSimbols
	for i in range(len(images)):
		stret = print_ch(i)
		f_printSimbols += "\t"
		for ch in range(len(stret)):
			f_printSimbols += f"{format(stret[ch], '#04x')}"
			if (ch < len(stret) - 1): f_printSimbols += ", "
		if i < len(images) - 1: f_printSimbols += ","
		f_printSimbols += f"\t\t//Char {ord(chars[i])} '{chars[i]}'\n"

def prepareVar():
	global f_printRanges, f_printSimbols, def_nameHeader, def_nameHeader
	global def_name, f_simWidth, f_simHeight, f_colSim, f_bytesSim, f_ranges
	f_printRanges = ""
	f_printSimbols = ""
	def_nameHeader = (f"_font_{cur_font.getname()[0]}{rec_w}X{rec_h}_H_").upper()
	def_name = f"font{cur_font.getname()[0]}{rec_w}x{rec_h}"
	f_simWidth = format(rec_w, '#04x')
	f_simHeight = format(rec_h, '#04x')
	f_colSim = format(rec_w, '#04x')
	ret = 0
	# for i in range(len(ranges)):
		# ret += ranges[i][1] - ranges[i][0]
	# f_bytesSim = format(ret, '#04x')
	bytespersim = (rec_h // 8 + (1 if (rec_h % 8) else 0)) * rec_w + 1
	f_bytesSim = format(bytespersim, '#04x')
	f_ranges = format(len(ranges), '#04x')
	preparePrintRanges()
	prepare_PrintSimbols()

def savefont():
	filename = filedialog.asksaveasfilename(defaultextension = '.h', initialfile = f"{cur_font.getname()[0]}{rec_w}x{rec_h}")
	# filename = f"{cur_font.getname()[0]}{rec_w}x{rec_h}.h"
	f = open(filename, "w")
	prepareVar()
	f.write(f"""#ifndef {def_nameHeader}
#define {def_nameHeader}

//Font Generated by ZUNO Font Creator

extern const unsigned char {def_name}[] = {"{"}
	{f_simWidth}, {f_simHeight}, {f_colSim}, {f_bytesSim}, {f_ranges},		//width, height, col simbols, bytes simbol, ranges\n
	//Ranges
{f_printRanges}
	//Buf chars
{f_printSimbols}
{"}"};

#endif
""")
	f.close()

def print_ch(indx):
	ret = 0
	prints = []
	wd = 0
	for x in range(rec_w):
		for y in range(rec_h):
			cur_b = y // 8 
			cur_bit = y % 8
			bit = 0 if images[indx].getpixel((x,y)) == (255,255,255,255) else 1
			ret |= bit << cur_bit
			if cur_bit == 7 or y == (rec_h - 1):
				prints.append(ret)
				print(f"ret - {ret}")
				ret = 0
			# if x == rec_w - 1 and y == rec_h - 1:
			# 	print("")
	wd = 0
	print(len(prints))
	for i in range(len(prints)):
		if prints[i] != 0:
			wd = i // ((rec_h // 8) + 1) + 1
	print(f"{i // ((rec_h // 8) + 1) + 1} {sub_font.getsize(chars[indx])}")
	if wd == 0:
		wd = sub_font.getsize(chars[indx])[0]
	# if (sub_font.getsize(chars[indx])[0]) > wd:
	# 	wd = sub_font.getsize(chars[indx])[0]
	prints.insert(0,wd)
	# print(prints)
	return(prints)


def move(event):
	x = event.x
	y = event.y
	cur = CURRENT
	s = "Движение мышью {}x{}".format(x, y)
	root.title(s)

def on_configure(event):
	listcanvas.configure(scrollregion=listcanvas.bbox('all'))


def clear():
	global flag, grid, index
	for i in range(len(rects)):
		maincanva.delete(rects[i])
	for i in range(len(frchar)):
		frchar[i].destroy()
	frchar.clear()
	rects.clear()
	grid = 10
	images.clear()
	indexs.clear()
	flag = 0
	ranges.clear()
	photos.clear()
	index = 0
	imgs.clear()
	chars.clear()
	chcanvas.clear()
	last_paint = 0
	print_button.configure(state="disable")
	spin.configure(state="disable")
	apply.configure(state="disable")
	spin_font.configure(state="normal")

root = Tk()
root.bind('<Motion>', move) 

menufr = LabelFrame(root, text = "Menu")
menufr.pack(fill = "both", side=TOP)
add_range = LabelFrame(menufr, text = "Add Range")
add_range.pack(side=LEFT)
spin_font = Spinbox(add_range, width=3, from_=3, to = 70)
spin_font.setvar("10")
spin_font.pack(side=LEFT)
lbpt = Label(add_range, text='pt\t')
lbpt.pack(side=LEFT)
labelfrom = Label(add_range, text="From")
labelfrom.pack(side=LEFT)
spinfrom = Spinbox(add_range,width = 7, from_=0,to=137993)
spinfrom.pack(side=LEFT)
labelto = Label(add_range, text="to")
labelto.pack(side=LEFT)
spinto = Spinbox(add_range,width = 7,from_=1,to=137994)
spinto.pack(side=LEFT)
cr_range = Button(add_range, command=app_range, text = "ADD Range")
cr_range.pack()
clear_all = Button(add_range, command=clear, text = "Clear all")
clear_all.pack()
print_button = Button(menufr, command= savefont, text = "Print Char to console", state="disable")
print_button.pack(side = RIGHT)

bottomfr = LabelFrame(root)
bottomfr.pack(fill = "both", side = TOP)
mainfr = LabelFrame(bottomfr, text = "Main", padx = 10, pady = 10)
mainfr.pack(side = LEFT, expand=True, fill=BOTH)

# addCol = Button(text = "Добавить Колонку", command=add_col)
# addCol.pack()
# addRow = Button(text = "Добавить строчку", command=add_row)
# addRow.pack()

submainfr = Frame(mainfr)
submainfr.pack(side=TOP)
lbgrid = Label(submainfr, text = "Grid")
lbgrid.pack(side=LEFT)
spin = Spinbox(submainfr, from_=5, to=50, command = resize_rect, state="disable")
spin.pack(side=LEFT)
apply = Button(submainfr,command=app_char, text= "Save change", state="disable")
apply.pack(side=LEFT)
maincanva = Canvas(mainfr,width = 1200, height = 1000, bg="#AAA", scrollregion=(0,0,1500,1500))
maincanva.bind("<Button-1>", click)
maincanva.bind("<B1-Motion>", draw_black)
maincanva.bind("<B2-Motion>", draw_white)

hbar=Scrollbar(mainfr,orient=HORIZONTAL)
hbar.pack(side=BOTTOM,fill=X)
hbar.config(command=maincanva.xview)
vbar=Scrollbar(mainfr,orient=VERTICAL)
vbar.pack(side=RIGHT,fill=Y)
vbar.config(command=maincanva.yview)
maincanva.config(width=300,height=300)
maincanva.config(xscrollcommand=hbar.set, yscrollcommand=vbar.set)
maincanva.pack(side=TOP,expand=True,fill=BOTH)

listfr = LabelFrame(bottomfr, text="Chars")
listfr.pack()
listcanvas = Canvas(listfr,width=131, height = 700, bg="blue")
listcanvas.pack(side=LEFT)
lsitscrollbar = Scrollbar(listfr, command=listcanvas.yview)
lsitscrollbar.pack(side=RIGHT, fill='y')
win_canvas = listcanvas.configure(yscrollcommand = lsitscrollbar.set)

listcanvas.bind('<Configure>', on_configure)
slistfr = Frame(listcanvas)
slistfr.bind('<Configure>', on_configure)
sslistfr = Frame(slistfr)
sslistfr.pack()
listcanvas.create_window((0,0), window=slistfr, anchor='nw')

mainfr.pack(fill="both", side=LEFT)


root.mainloop()



