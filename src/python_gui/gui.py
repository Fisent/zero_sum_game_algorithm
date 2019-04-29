import tkinter as tk

board = '''
W - white pawn
B - black pawn
o - empty field

B-----o-----B
|     |     |
| o---W---o |
| |   |   | |
| | B-B-W | |
| | |   | | |
W-B o   W-W-B
| | |   | | |
| | W-B-B | |
| |   |   | |
| o---W---o |
|     |     |
W-----B-----W
'''

def show_window():
    win = tk.Tk()

    win.title = "dupa"

    for i in range(24):
        tk.Button(win, text=str(i)).grid(row=i, column=i)
    tk.mainloop()
